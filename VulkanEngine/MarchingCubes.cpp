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

	void MarchingCubes::edgeTableLookup(const int& cubeIndex, const GridCube& cube, glm::vec3* vertList, std::size_t* materialList, glm::vec3* normList) const
	{
		/* Find the vertices where the surface intersects the cube */
		if (EDGE_TABLE[cubeIndex] & 1) {
			vertList[0] = interpolatePositions(cube.vertices[0], cube.vertices[1], cube.voxelVal[0].density, cube.voxelVal[1].density);
			normList[0] = interpolateVectors(cube.voxelNormals[0], cube.voxelNormals[1], cube.voxelVal[0].density, cube.voxelVal[1].density);
			materialList[0] = cube.voxelVal[0].terrainType > cube.voxelVal[1].terrainType ? cube.voxelVal[0].terrainType : cube.voxelVal[1].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 2) {
			vertList[1] = interpolatePositions(cube.vertices[1], cube.vertices[2], cube.voxelVal[1].density, cube.voxelVal[2].density);
			normList[1] = interpolateVectors(cube.voxelNormals[1], cube.voxelNormals[2], cube.voxelVal[1].density, cube.voxelVal[2].density);
			materialList[1] = cube.voxelVal[1].terrainType > cube.voxelVal[2].terrainType ? cube.voxelVal[1].terrainType : cube.voxelVal[2].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 4) {
			vertList[2] = interpolatePositions(cube.vertices[2], cube.vertices[3], cube.voxelVal[2].density, cube.voxelVal[3].density);
			normList[2] = interpolateVectors(cube.voxelNormals[2], cube.voxelNormals[3], cube.voxelVal[2].density, cube.voxelVal[3].density);
			materialList[2] = cube.voxelVal[2].terrainType > cube.voxelVal[3].terrainType ? cube.voxelVal[2].terrainType : cube.voxelVal[3].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 8) {
			vertList[3] = interpolatePositions(cube.vertices[3], cube.vertices[0], cube.voxelVal[3].density, cube.voxelVal[0].density);
			normList[3] = interpolateVectors(cube.voxelNormals[3], cube.voxelNormals[0], cube.voxelVal[3].density, cube.voxelVal[0].density);
			materialList[3] = cube.voxelVal[3].terrainType > cube.voxelVal[0].terrainType ? cube.voxelVal[3].terrainType : cube.voxelVal[0].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 16) {
			vertList[4] = interpolatePositions(cube.vertices[4], cube.vertices[5], cube.voxelVal[4].density, cube.voxelVal[5].density);
			normList[4] = interpolateVectors(cube.voxelNormals[4], cube.voxelNormals[5], cube.voxelVal[4].density, cube.voxelVal[5].density);
			materialList[4] = cube.voxelVal[4].terrainType > cube.voxelVal[5].terrainType ? cube.voxelVal[4].terrainType : cube.voxelVal[5].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 32) {
			vertList[5] = interpolatePositions(cube.vertices[5], cube.vertices[6], cube.voxelVal[5].density, cube.voxelVal[6].density);
			normList[5] = interpolateVectors(cube.voxelNormals[5], cube.voxelNormals[6], cube.voxelVal[5].density, cube.voxelVal[6].density);
			materialList[5] = cube.voxelVal[5].terrainType > cube.voxelVal[6].terrainType ? cube.voxelVal[5].terrainType : cube.voxelVal[6].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 64) {
			vertList[6] = interpolatePositions(cube.vertices[6], cube.vertices[7], cube.voxelVal[6].density, cube.voxelVal[7].density);
			normList[6] = interpolateVectors(cube.voxelNormals[6], cube.voxelNormals[7], cube.voxelVal[6].density, cube.voxelVal[7].density);
			materialList[6] = cube.voxelVal[6].terrainType > cube.voxelVal[7].terrainType ? cube.voxelVal[6].terrainType : cube.voxelVal[7].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 128) {
			vertList[7] = interpolatePositions(cube.vertices[7], cube.vertices[4], cube.voxelVal[7].density, cube.voxelVal[4].density);
			normList[7] = interpolateVectors(cube.voxelNormals[7], cube.voxelNormals[4], cube.voxelVal[7].density, cube.voxelVal[4].density);
			materialList[7] = cube.voxelVal[7].terrainType > cube.voxelVal[4].terrainType ? cube.voxelVal[7].terrainType : cube.voxelVal[4].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 256) {
			vertList[8] = interpolatePositions(cube.vertices[0], cube.vertices[4], cube.voxelVal[0].density, cube.voxelVal[4].density);
			normList[8] = interpolateVectors(cube.voxelNormals[0], cube.voxelNormals[4], cube.voxelVal[0].density, cube.voxelVal[4].density);
			materialList[8] = cube.voxelVal[0].terrainType > cube.voxelVal[4].terrainType ? cube.voxelVal[0].terrainType : cube.voxelVal[4].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 512) {
			vertList[9] = interpolatePositions(cube.vertices[1], cube.vertices[5], cube.voxelVal[1].density, cube.voxelVal[5].density);
			normList[9] = interpolateVectors(cube.voxelNormals[1], cube.voxelNormals[5], cube.voxelVal[1].density, cube.voxelVal[5].density);
			materialList[9] = cube.voxelVal[1].terrainType > cube.voxelVal[5].terrainType ? cube.voxelVal[1].terrainType : cube.voxelVal[5].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 1024) {
			vertList[10] = interpolatePositions(cube.vertices[2], cube.vertices[6], cube.voxelVal[2].density, cube.voxelVal[6].density);
			normList[10] = interpolateVectors(cube.voxelNormals[2], cube.voxelNormals[6], cube.voxelVal[2].density, cube.voxelVal[6].density);
			materialList[10] = cube.voxelVal[2].terrainType > cube.voxelVal[6].terrainType ? cube.voxelVal[2].terrainType : cube.voxelVal[6].terrainType;
		}
		if (EDGE_TABLE[cubeIndex] & 2048) {
			vertList[11] = interpolatePositions(cube.vertices[3], cube.vertices[7], cube.voxelVal[3].density, cube.voxelVal[7].density);
			normList[11] = interpolateVectors(cube.voxelNormals[3], cube.voxelNormals[7], cube.voxelVal[3].density, cube.voxelVal[7].density);
			materialList[11] = cube.voxelVal[3].terrainType > cube.voxelVal[7].terrainType ? cube.voxelVal[3].terrainType : cube.voxelVal[7].terrainType;
		}
	}

	glm::vec3 MarchingCubes::interpolatePositions(const VoxelCoordinates& v1, const VoxelCoordinates& v2, const float& d1, const float& d2) const
	{
			if (std::abs(ISO_LEVEL - d1) < EPSILON)
				return(v1.toVec3());
			if (std::abs(ISO_LEVEL - d2) < EPSILON)
				return(v2.toVec3());
			if (std::abs(d1 - d2) < EPSILON)
				return(v1.toVec3());

		float mu = (ISO_LEVEL - d1) / (d2 - d1);
		return (v1.toVec3() + mu * (v2.toVec3() - v1.toVec3()));
	}

	glm::vec3 MarchingCubes::interpolateVectors(const glm::vec3& n1, const glm::vec3& n2, const float& d1, const float& d2) const
	{
		if (std::abs(ISO_LEVEL - d1) < EPSILON)
			return(n1);
		if (std::abs(ISO_LEVEL - d2) < EPSILON)
			return(n2);
		if (std::abs(d1 - d2) < EPSILON)
			return(n1);

		float mu = (ISO_LEVEL - d1) / (d2 - d1);
		return glm::normalize(n1 * (1.0f - mu) + n2 * mu);
	}


	//Direction only (1,0,0), (0,1,0) or (0,0,1)
	float MarchingCubes::cubeGradientDir(const VoxelCoordinates& currentVertice,  const VoxelCoordinates& direction) const
	{
		float d1 = voxelManager->getVoxel(currentVertice - direction).density;
		float d2 = voxelManager->getVoxel(currentVertice + direction).density;
		return (d1-d2);
	}

	MarchingCubes::GridCube MarchingCubes::nextCube(const VoxelCoordinates& chunk, const VoxelCoordinates& offset) const
	{
		GridCube cube;

		for (int i = 0; i < 8; i++) {

			VoxelCoordinates cubeVerticesShifted = VoxelManager::local2World(cube.vertices[i] + offset, chunk);
			
			//Lookup Voxel
			cube.voxelVal[i] = voxelManager->getVoxel(cubeVerticesShifted);

			//Calculate Surface Normal of with gradient if there is no neighbor then it is empty
			cube.voxelNormals[i].x = cubeGradientDir(cubeVerticesShifted, VoxelCoordinates(1, 0, 0));
			cube.voxelNormals[i].y = cubeGradientDir(cubeVerticesShifted, VoxelCoordinates(0, 1, 0));
			cube.voxelNormals[i].z = cubeGradientDir(cubeVerticesShifted, VoxelCoordinates(0, 0, 1));
			
			cube.voxelNormals[i] = (cube.voxelNormals[i] != glm::vec3(0,0,0)) ?  glm::normalize(cube.voxelNormals[i]) : cube.voxelNormals[i];
		}
		return cube;
	}
	//https://paulbourke.net/geometry/polygonise/ (17.10.21)
	void MarchingCubes::generateChunk(TerrainMeshChunk* mc) const
	{
		if (mc == nullptr) return;

		//ChunkSize -1 because the grid value only allows per cube line Chunk Size -1
		//Exam�ple 3x3 Grid has 4 cube and 2 cubes per line (3D same principle applies) 
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
					GridCube cube = nextCube(mc->getChunkCoordinates(), VoxelCoordinates(x, y, z));

					cubeIndex = determineCubeIndex(cube);

					glm::vec3 vertList[12] = {};
					std::size_t terrainMaterial[12] = {};
					glm::vec3 normList[12] = {};
					/* Cube is entirely in/out of the surface -> nothing will be drawn next Cube */
					if (EDGE_TABLE[cubeIndex] == 0) continue;

					edgeTableLookup(cubeIndex, cube, vertList, terrainMaterial, normList);

					generateTriangles(cubeIndex, vertList, terrainMaterial, normList, VoxelCoordinates(x, y, z), mc);
				}
			}
		}
	}

	void MarchingCubes::generateCell(TerrainMeshChunk* mc, const VoxelCoordinates& cellCoordinates) const
	{

		if (mc == nullptr) return;
		
		//2 because a single voxel is surrounded by 8 voxel 
		int cubeIndex = 0;	

		GridCube cube = nextCube(mc->getChunkCoordinates(), cellCoordinates);

		cubeIndex = determineCubeIndex(cube);

		glm::vec3 vertList[12] = {};
		std::size_t terrainMaterial[12] = {};
		glm::vec3 normList[12] = {};

		edgeTableLookup(cubeIndex, cube, vertList, terrainMaterial, normList);

		generateTriangles(cubeIndex, vertList, terrainMaterial, normList, cellCoordinates, mc);
	}

	void MarchingCubes::generateTriangles(const int& cubeIndex,  glm::vec3* vertList, std::size_t* materialList, glm::vec3* normList, const VoxelCoordinates& cellCoordinates, TerrainMeshChunk* mc) const
	{

		std::vector<vh::vhVertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<glm::vec3> surfaceNormals;

		std::size_t dominantMat = 0;
		std::unordered_map<std::size_t, std::size_t> materialsCounter;

		for(int i = 0; TRI_TABLE[cubeIndex][i] != -1; i += 3) {
			vh::vhVertex vertice0, vertice1, vertice2;
			std::size_t mat0, mat1, mat2;

			vertice0.pos = *(vertList + TRI_TABLE[cubeIndex][i]);
			vertice0.normal = *(normList + TRI_TABLE[cubeIndex][i]);
			mat0 = *(materialList + TRI_TABLE[cubeIndex][i]);

			vertice1.pos = *(vertList + TRI_TABLE[cubeIndex][i+1]);
			vertice1.normal = *(normList + TRI_TABLE[cubeIndex][i+1]);
			mat1 = *(materialList + TRI_TABLE[cubeIndex][i+1]);

			vertice2.pos = *(vertList + TRI_TABLE[cubeIndex][i+2]);
			vertice2.normal = *(normList + TRI_TABLE[cubeIndex][i+2]);
			mat2 = *(materialList + TRI_TABLE[cubeIndex][i+2]);

			glm::vec3 surfaceNormal = glm::normalize(glm::cross((vertice2.pos - vertice0.pos), (vertice1.pos - vertice0.pos)));

			
			vertices.push_back(vertice0);
			vertices.push_back(vertice1);
			vertices.push_back(vertice2);
			
			indices.push_back(i);
			indices.push_back(i+1);
			indices.push_back(i+2);

			surfaceNormals.push_back(surfaceNormal);

			if (!materialsCounter.contains(mat0))
				materialsCounter.emplace(mat0, 0);

			if (!materialsCounter.contains(mat1))
				materialsCounter.emplace(mat1, 0);

			if (!materialsCounter.contains(mat2))
				materialsCounter.emplace(mat2, 0);

			++materialsCounter.at(mat0);
			++materialsCounter.at(mat1);
			++materialsCounter.at(mat2);

		}
		if (0 < materialsCounter.size()) {
			dominantMat = std::max_element(materialsCounter.begin(), materialsCounter.end(),
				[](const std::pair<std::size_t, std::size_t>& p1, const std::pair<std::size_t, std::size_t>& p2) {
				return p1.second < p2.second;
			})->first;
		}
		mc->insertOrAssignCube(cellCoordinates, new MeshCell{ vertices, indices, surfaceNormals, dominantMat });
	}
	MarchingCubes::MarchingCubes(VoxelManager* const voxelManager) : TerrainGenerator(voxelManager) {}
	MarchingCubes::~MarchingCubes() {}
}