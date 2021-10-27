#include "OEInclude.h"

namespace oe {
	int MarchingCubes::determineCubeIndex(const GridCube& cube) const
	{
		int cubeIndex = 0;
		//Setting the bits of which vertice of the cube has been touched
		if (ISO_LEVEL < cube.voxelVal[0].density) cubeIndex |= 1;
		if (ISO_LEVEL < cube.voxelVal[1].density) cubeIndex |= 2;
		if (ISO_LEVEL < cube.voxelVal[2].density) cubeIndex |= 4;
		if (ISO_LEVEL < cube.voxelVal[3].density) cubeIndex |= 8;
		if (ISO_LEVEL < cube.voxelVal[4].density) cubeIndex |= 16;
		if (ISO_LEVEL < cube.voxelVal[5].density) cubeIndex |= 32;
		if (ISO_LEVEL < cube.voxelVal[6].density) cubeIndex |= 64;
		if (ISO_LEVEL < cube.voxelVal[7].density) cubeIndex |= 128;

		return cubeIndex;
	}

	glm::vec3 MarchingCubes::interpolateVertices(const VoxelCoordinates& v1, const VoxelCoordinates& v2, const float& d1, const float& d2) const
	{

			if (std::abs(ISO_LEVEL - d1) < 0.00001)
				return(v1.toVec3());
			if (std::abs(ISO_LEVEL - d2) < 0.00001)
				return(v2.toVec3());
			if (std::abs(d1 - d2) < 0.00001)
				return(v1.toVec3());

		float mu = (ISO_LEVEL - d1) / (d2 - d1);
		return (v1.toVec3() + mu * (v2.toVec3() - v1.toVec3()));
	}

	glm::vec3 MarchingCubes::interpolateNormals(const glm::vec3& n1, const glm::vec3& n2, const float& d1, const float& d2) const
	{
		if (std::abs(ISO_LEVEL - d1) < 0.00001)
			return(n1);
		if (std::abs(ISO_LEVEL - d2) < 0.00001)
			return(n2);
		if (std::abs(d1 - d2) < 0.00001)
			return(n1);

		float mu = (ISO_LEVEL - d1) / (d2 - d1);
		return glm::normalize(n1 * (1.0f - mu) + n2 * mu);
	}


	//Direction only (1,0,0), (0,1,0) or (0,0,1)
	float MarchingCubes::cubeGradientDir(const VoxelCoordinates& currentVertice,  const VoxelCoordinates& direction) const
	{
		float d1 = world->getVoxel(currentVertice - direction).density;
		float d2 = world->getVoxel(currentVertice + direction).density;
		return (d1-d2);
	}

	MarchingCubes::GridCube MarchingCubes::nextCube(const VoxelCoordinates& chunk, const VoxelCoordinates& offset) const
	{
		GridCube cube;

		for (int i = 0; i < 8; i++) {

			VoxelCoordinates cubeVerticesShifted = World::local2World(cube.vertices[i] + offset, chunk);
			
			//Lookup Voxel
			cube.voxelVal[i] = world->getVoxel(cubeVerticesShifted);

			//Calculate Surface Normal of with gradient if there is no neighbor then it is empty
			cube.voxelNormals[i].x = cubeGradientDir(cubeVerticesShifted, VoxelCoordinates(1, 0, 0));
			cube.voxelNormals[i].y = cubeGradientDir(cubeVerticesShifted, VoxelCoordinates(0, 1, 0));
			cube.voxelNormals[i].z = cubeGradientDir(cubeVerticesShifted, VoxelCoordinates(0, 0, 1));
			
			cube.voxelNormals[i] = (cube.voxelNormals[i] != glm::vec3(0,0,0)) ?  glm::normalize(cube.voxelNormals[i]) : cube.voxelNormals[i];
		}
		return cube;
	}
	//https://paulbourke.net/geometry/polygonise/ (17.10.21)
	void MarchingCubes::generate(const VoxelCoordinates& chunk) const
	{
		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");

		VESceneNode* chunkNode;
		std::string chunkName = "Chunk[" + std::to_string(chunk.X) + "," + std::to_string(chunk.Y) + "," + std::to_string(chunk.Z) + "]";
		chunkNode = getSceneManagerPointer()->createSceneNode(chunkName, pScene, glm::mat4(1.0));
		glm::vec3 nextChunkPos = (chunk * VoxelChunkData::CHUNK_SIZE).toVec3();
		chunkNode->multiplyTransform(glm::translate(glm::mat4(1.0f), nextChunkPos));


		//ChunkSize -1 because the grid value only allows per cube line Chunk Size -1
		//Examüple 3x3 Grid has 4 cube and 2 cubes per line (3D same principle applies) 
		//	y
		//	^
		//  |
		//  *------*------*
		//  |			 |			|
		//  |			 |			|
		//  *------*------*
		//  |		   |			|
		//  |			 |			|
		//  *------*------* -> x
		// but there has to be an overlap between the chunks so it will remain Chunk_Size this will allow us to
		//to bind the overlap to current chunk in the x+ y+ z+ direction.
		for (auto x = 0; x < VoxelChunkData::CHUNK_SIZE.X; ++x) {
			for (auto y = 0; y < VoxelChunkData::CHUNK_SIZE.Y; ++y) {
				for (auto z = 0; z < VoxelChunkData::CHUNK_SIZE.Z; ++z) {
					int cubeIndex = 0;
					GridCube cube = nextCube(chunk, VoxelCoordinates(x, y, z));

					cubeIndex = determineCubeIndex(cube);

					glm::vec3 vertList[12] = {};
					glm::vec3 normList[12] = {};
					/* Cube is entirely in/out of the surface -> nothing will be drawn next Cube */
					if (EDGE_TABLE[cubeIndex] == 0) continue;

					/* Find the vertices where the surface intersects the cube */
					if (EDGE_TABLE[cubeIndex] & 1) {
						vertList[0] = interpolateVertices(cube.vertices[0], cube.vertices[1], cube.voxelVal[0].density, cube.voxelVal[1].density);
						normList[0] = interpolateNormals(cube.voxelNormals[0], cube.voxelNormals[1], cube.voxelVal[0].density, cube.voxelVal[1].density);
					}
					if (EDGE_TABLE[cubeIndex] & 2) {
						vertList[1] = interpolateVertices(cube.vertices[1], cube.vertices[2], cube.voxelVal[1].density, cube.voxelVal[2].density);
						normList[1] = interpolateNormals(cube.voxelNormals[1], cube.voxelNormals[2], cube.voxelVal[1].density, cube.voxelVal[2].density);
					}
					if (EDGE_TABLE[cubeIndex] & 4) {
						vertList[2] = interpolateVertices(cube.vertices[2], cube.vertices[3], cube.voxelVal[2].density, cube.voxelVal[3].density);
						normList[2] = interpolateNormals(cube.voxelNormals[2], cube.voxelNormals[3], cube.voxelVal[2].density, cube.voxelVal[3].density);
					}
					if (EDGE_TABLE[cubeIndex] & 8) {
						vertList[3] = interpolateVertices(cube.vertices[3], cube.vertices[0], cube.voxelVal[3].density, cube.voxelVal[0].density);
						normList[3] = interpolateNormals(cube.voxelNormals[3], cube.voxelNormals[0], cube.voxelVal[3].density, cube.voxelVal[0].density);
					}
					if (EDGE_TABLE[cubeIndex] & 16) {
						vertList[4] = interpolateVertices(cube.vertices[4], cube.vertices[5], cube.voxelVal[4].density, cube.voxelVal[5].density);
						normList[4] = interpolateNormals(cube.voxelNormals[4], cube.voxelNormals[5], cube.voxelVal[4].density, cube.voxelVal[5].density);
					}
					if (EDGE_TABLE[cubeIndex] & 32) {
						vertList[5] = interpolateVertices(cube.vertices[5], cube.vertices[6], cube.voxelVal[5].density, cube.voxelVal[6].density);
						normList[5] = interpolateNormals(cube.voxelNormals[5], cube.voxelNormals[6], cube.voxelVal[5].density, cube.voxelVal[6].density);
					}
					if (EDGE_TABLE[cubeIndex] & 64) {
						vertList[6] = interpolateVertices(cube.vertices[6], cube.vertices[7], cube.voxelVal[6].density, cube.voxelVal[7].density);
						normList[6] = interpolateNormals(cube.voxelNormals[6], cube.voxelNormals[7], cube.voxelVal[6].density, cube.voxelVal[7].density);
					}
					if (EDGE_TABLE[cubeIndex] & 128) {
						vertList[7] = interpolateVertices(cube.vertices[7], cube.vertices[4], cube.voxelVal[7].density, cube.voxelVal[4].density);
						normList[7] = interpolateNormals(cube.voxelNormals[7], cube.voxelNormals[4], cube.voxelVal[7].density, cube.voxelVal[4].density);
					}
					if (EDGE_TABLE[cubeIndex] & 256) {
						vertList[8] = interpolateVertices(cube.vertices[0], cube.vertices[4], cube.voxelVal[0].density, cube.voxelVal[4].density);
						normList[8] = interpolateNormals(cube.voxelNormals[0], cube.voxelNormals[4], cube.voxelVal[0].density, cube.voxelVal[4].density);
					}
					if (EDGE_TABLE[cubeIndex] & 512) {
						vertList[9] = interpolateVertices(cube.vertices[1], cube.vertices[5], cube.voxelVal[1].density, cube.voxelVal[5].density);
						normList[9] = interpolateNormals(cube.voxelNormals[1], cube.voxelNormals[5], cube.voxelVal[1].density, cube.voxelVal[5].density);
					}
					if (EDGE_TABLE[cubeIndex] & 1024) {
						vertList[10] = interpolateVertices(cube.vertices[2], cube.vertices[6], cube.voxelVal[2].density, cube.voxelVal[6].density);
						normList[10] = interpolateNormals(cube.voxelNormals[2], cube.voxelNormals[6], cube.voxelVal[2].density, cube.voxelVal[6].density);
					}
					if (EDGE_TABLE[cubeIndex] & 2048) {
						vertList[11] = interpolateVertices(cube.vertices[3], cube.vertices[7], cube.voxelVal[3].density, cube.voxelVal[7].density);
						normList[11] = interpolateNormals(cube.voxelNormals[3], cube.voxelNormals[7], cube.voxelVal[3].density, cube.voxelVal[7].density);
					}

					generateTriangles(cubeIndex, vertList, normList, glm::vec3(x, y, z), chunkNode);
				}
			}
		}
		
	}

	void MarchingCubes::generateTriangles(const int& cubeIndex,  glm::vec3* vertList, glm::vec3* normList, const glm::vec3& localVoxelPos, VESceneNode* parent) const
	{
		std::vector<vh::vhVertex> vertices;
		std::vector<uint32_t> indices;
		for(int i = 0; TRI_TABLE[cubeIndex][i] != -1; i += 3) {
			vh::vhVertex vertice0, vertice1, vertice2;

			vertice0.pos = *(vertList + TRI_TABLE[cubeIndex][i]);
			vertice0.normal = *(normList + TRI_TABLE[cubeIndex][i]);

			vertice1.pos = *(vertList + TRI_TABLE[cubeIndex][i+1]);
			vertice1.normal = *(normList + TRI_TABLE[cubeIndex][i+1]);

			vertice2.pos = *(vertList + TRI_TABLE[cubeIndex][i+2]);
			vertice2.normal = *(normList + TRI_TABLE[cubeIndex][i+2]);

			vertices.push_back(vertice0);
			vertices.push_back(vertice1);
			vertices.push_back(vertice2);

			indices.push_back(i);
			indices.push_back(i+1);
			indices.push_back(i+2);
		}

		//Actual Engine Mesh generation
		std::string cubeName = parent->getName() + "_Cube_[" + std::to_string(localVoxelPos.x) + "," + std::to_string(localVoxelPos.y) + "," + std::to_string(localVoxelPos.z) + "]";
		VEMesh* cube_mesh;
		VECHECKPOINTER(cube_mesh = getSceneManagerPointer()->createMesh(cubeName + "_Mesh", vertices, indices));
		


		//No textures -> VESubrendererFW_C1 
		VEMaterial* cube_material;
		VECHECKPOINTER(cube_material = getSceneManagerPointer()->createMaterial(cubeName + "_Material"));
		cube_material->mapDiffuse = getSceneManagerPointer()->createTexture(cubeName + "_Texture_1", "media/models/editor/TerrainTextures", "grass.png");
		cube_material->color = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);

		VEEntity* entity;
		VECHECKPOINTER(entity = getSceneManagerPointer()->createEntity(cubeName, VEEntity::veEntityType::VE_ENTITY_TYPE_NORMAL, cube_mesh, cube_material, parent));
		entity->multiplyTransform(glm::translate(glm::mat4(1.0f), localVoxelPos));
		entity->m_castsShadow = false;


	}
	MarchingCubes::MarchingCubes(World* const world) : TerrainGenerator(world) {}
	MarchingCubes::~MarchingCubes() {}
}