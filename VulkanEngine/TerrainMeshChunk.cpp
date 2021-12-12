#include "OEInclude.h"

namespace oe {
	TerrainMeshChunk::TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates) : chunkCoordinates{chunkCoordinates} {
		chunkName = "Chunk[" + std::to_string(chunkCoordinates.X) + "," + std::to_string(chunkCoordinates.Y) + "," + std::to_string(chunkCoordinates.Z) + "]";
	}
	TerrainMeshChunk::~TerrainMeshChunk(){

		for (auto& cube : cubes) {
			std::string cubeName = chunkName + "_Cube[" + std::to_string(cube.first.X) + "," + std::to_string(cube.first.Y) + "," + std::to_string(cube.first.Z) + "]";
			getSceneManagerPointer()->deleteMesh(cubeName + "_Mesh");
			delete cube.second;
		}
		getSceneManagerPointer()->deleteSceneNodeAndChildren(chunkName);
	}

	void TerrainMeshChunk::insertOrAssignCube(const VoxelCoordinates& cellPos, MeshCell* cell){
		if (cubes.count(cellPos) > 0) {
			MeshCell* pMesh = cubes.at(cellPos);
			delete pMesh;

			if (cell->vertices.size() <= 0) {
				cubes.erase(cellPos);
				return;
			}
		}

		if (cell->vertices.size() <= 0) return;
		
		auto isAssigned = cubes.insert_or_assign(cellPos, cell);
	}

	VEMaterial* TerrainMeshChunk::getTerrainMaterial(const std::size_t& material) const
	{
		VEMaterial* ret;
		auto terrainMat = terrainMaterials.at(material);

		std::string matName = std::get<0>(terrainMat);
		std::string baseDir = std::get<1>(terrainMat);
		std::string fileName = std::get<2>(terrainMat);

		VECHECKPOINTER(ret = getSceneManagerPointer()->createMaterial(matName + "_Material"));
		VECHECKPOINTER(ret->mapDiffuse = getSceneManagerPointer()->createTexture(matName + "_Texture_1", baseDir, fileName));

		return ret;
	}
	

	void TerrainMeshChunk::meshCleanup() {
		for (auto& name : meshNames) {
			getSceneManagerPointer()->deleteMesh(name + "_Mesh");
		}
		getSceneManagerPointer()->deleteSceneNodeAndChildren(chunkName);
		meshNames.clear();
	}

	void TerrainMeshChunk::clear(){
		cubes.clear();
	}

	void TerrainMeshChunk::renderChunk(){
		meshCleanup();

		//Create Chunk SceneNode
		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* pChunkNodeParent;
		VECHECKPOINTER(pChunkNodeParent = getSceneManagerPointer()->createSceneNode(chunkName, pScene, glm::mat4(1.0)));
		glm::vec3 nextChunkPos = (chunkCoordinates * VoxelChunkData::CHUNK_SIZE).toVec3();
		pChunkNodeParent->multiplyTransform(glm::translate(glm::mat4(1.0f), nextChunkPos));


		//Create Mesh for each cube stored in cubes
		for (auto& cube : cubes) {
			std::string cubeName = chunkName + "_Cube[" + std::to_string(cube.first.X) + "," + std::to_string(cube.first.Y) + "," + std::to_string(cube.first.Z) + "]";
			meshNames.push_back(cubeName);

			//Actual Engine Mesh generation (Creates only a mesh if there are vertices)
			VEMesh* cube_mesh = nullptr;
			VECHECKPOINTER(cube_mesh = getSceneManagerPointer()->createMesh(cubeName + "_Mesh", cube.second->vertices, cube.second->indices));
			
			VEMaterial* cube_material = getTerrainMaterial(cube.second->material);

			//CreateCube Entity
			VEEntity* entity;
			VECHECKPOINTER(entity = getSceneManagerPointer()->createEntity(cubeName + "_Entity", VEEntity::veEntityType::VE_ENTITY_TYPE_VOXEL_TERRAIN, cube_mesh, cube_material, pChunkNodeParent));
			entity->multiplyTransform(glm::translate(glm::mat4(1.0f), cube.first.toVec3()));
			
		}

	}
	VoxelCoordinates TerrainMeshChunk::getChunkCoordinates() const{
		return chunkCoordinates;
	}

	bool TerrainMeshChunk::traceRay(const Ray& ray, glm::vec3& outPos) const
	{
		
		//Trace All Triangles and if a Triangle is hit return true
		for (const auto& cube : cubes) {
			const auto vertices = cube.second->vertices;
			const auto indices = cube.second->indices;

			for (std::size_t i = 0, j = 0; i < indices.size(); i += 3, ++j) {
				auto chunkOffset = (VoxelChunkData::CHUNK_SIZE * chunkCoordinates).toVec3();
				auto cubePosOffset = cube.first.toVec3();

				auto v0 = vertices.at(indices.at(i)).pos + chunkOffset + cubePosOffset;
				auto v1 = vertices.at(indices.at(i + 1)).pos + chunkOffset + cubePosOffset;
				auto v2 = vertices.at(indices.at(i + 2)).pos + chunkOffset + cubePosOffset;

				auto surfaceNormal = cube.second->surfaceNormals.at(j);

				bool hit = rayTriangleIntersection(ray, v0, v1, v2, surfaceNormal, outPos);
				if (hit) {
					return hit;
				}
			}
		}
		return false;
	}
	//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution (04.11.21)
	//Implements and Explains the Geometric intersection algorithm with a plane equation and left right tests to ensure the hit point is in the triangle
	bool TerrainMeshChunk::rayTriangleIntersection(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal, glm::vec3& outPos) const
	{
		float surfaceNormalDOTRayDirection = glm::dot(surfaceNormal, ray.getDirection());
		//Check if Direction of Ray and Surface normal are perpendicular (Direction of ray is parallel to triangle)
		if (std::abs(surfaceNormalDOTRayDirection) < RAY_EPSILON)
			return false;

		//Direction and Surface normal should oppose each other so if it bigger than 0 then they point in the same direction
		if (0.0f < surfaceNormalDOTRayDirection)
			return false;

		//Calculate alpha to determine if triangle was hit by the ray
		//it uses the Ray Equation P = alpha * direction + origin and the plane Equation: A*x + B*y + C*z + D = 0 (x = Px, y = Py, z=Pz)  
		float D = -glm::dot(surfaceNormal, v0);
		float alpha = -(glm::dot(surfaceNormal, ray.getOrigin()) + D) / surfaceNormalDOTRayDirection;

		//Ray hits a triangle behind the origin -> no hit
		if (alpha < 0.0f)
			return false;

		//Successful hit (it has hit the plane not the triangle yet)
		glm::vec3 hitPos = ray.getPositionOnRay(alpha);

		//Test if hit was inside Triangle (right is below 0.0f so return false if left)
		glm::vec3 e01 = v1 - v0;
		glm::vec3 v0toHit = hitPos - v0;
		glm::vec3 c0 = glm::cross(e01, v0toHit);
		if (glm::dot(surfaceNormal, c0) > 0.0f)
			return false;

		glm::vec3 e12 = v2 - v1;
		glm::vec3 v1toHit = hitPos - v1;
		glm::vec3 c1 = glm::cross(e12, v1toHit);
		if (glm::dot(surfaceNormal, c1) > 0.0f)
			return false;

		glm::vec3 e20 = v0 - v2;
		glm::vec3 v2toHit = hitPos - v2;
		glm::vec3 c2 = glm::cross(e20, v2toHit);
		if (glm::dot(surfaceNormal, c2) > 0.0f)
			return false;

		//Hit is inside Triangle return hitPos and true for hit
		outPos = hitPos;
		return true;
	}
}