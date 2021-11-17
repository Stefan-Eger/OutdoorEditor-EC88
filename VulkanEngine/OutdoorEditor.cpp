#include "OEInclude.h"
namespace oe {
	OutdoorEditor::OutdoorEditor() {
		voxelManager = new VoxelManager();
		terrainManager = new TerrainManager(new MarchingCubes(voxelManager));
	}
	OutdoorEditor::~OutdoorEditor(){
		delete voxelManager;
		delete terrainManager;
	}

	void OutdoorEditor::refresh() const
	{
		auto chunks2Generate = voxelManager->getAllChunks2Refresh();
		std::size_t i = 0, chunkLoad = chunks2Generate.size();
		for (const auto& chunkPos : chunks2Generate) {
			VoxelChunkData* voxelChunk = voxelManager->findChunk(chunkPos);
			auto changedVoxels = voxelChunk->getChangedVoxels();

			//If too many Voxels have been changed than render the entire chunk
			if (changedVoxels.size() > 10) {
				terrainManager->updateChunkMesh(chunkPos);
				voxelChunk->clearChangedVoxels();
				std::cout << "Chunk Update " << i++ << "\t[" << chunkPos.X << ", " << chunkPos.Y << ", " << chunkPos.Z << "] \t of " << chunkLoad << " has been generated" << std::endl;
				continue;
			}
			//iterate through each changed voxel and generate its mesh
			for (const auto& voxelPos : changedVoxels) {
				auto worldVoxelPos = VoxelManager::local2World(voxelPos, chunkPos);
				terrainManager->updateCellsAroundVoxel(worldVoxelPos);
			}
			voxelChunk->clearChangedVoxels();

			std::cout << "Chunk Cell Update "<< i++ << "\t[" << chunkPos.X << ", " << chunkPos.Y << ", " << chunkPos.Z << "] \t of " << chunkLoad << " has been generated" << std::endl;
		}
		terrainManager->renderChangedChunks();
	}




	bool OutdoorEditor::traceRay(const Ray& ray, glm::vec3& outPos) const
	{
		//TODO Not implemented nicely find ways for speed up
		//travel from chunk to chunk and test ray/TriangleIntersection
		TerrainMeshChunk* oldMeshChunk = nullptr;
		float distance = 0.0f;
		while (distance < 20.0f) {
			
			auto rayPos = ray.getPositionOnRay(distance);
			auto rayChunkCoordinates = VoxelManager::world2ChunkCoordinates(VoxelCoordinates((int)rayPos.x, (int)rayPos.y, (int)rayPos.z));


			TerrainMeshChunk* chunk = terrainManager->findChunk(rayChunkCoordinates);

			if ((chunk != nullptr) && (chunk != oldMeshChunk)) {
				//std::cout << "Ray Chunk Coordinates: " << rayChunkCoordinates.X << ", " << rayChunkCoordinates.Y << ", " << rayChunkCoordinates.Z << std::endl;
				oldMeshChunk = chunk;
				const auto cubes = chunk->getChunkMesh();
				//Trace All Triangles and if a Triangle is hit return true
				for (const auto& cube : cubes) {
					const auto vertices = cube.second->vertices;
					const auto indices = cube.second->indices;
					
					for (std::size_t i = 0, j = 0; i < indices.size(); i += 3, ++j) {
						auto chunkOffset = (VoxelChunkData::CHUNK_SIZE * chunk->getChunkCoordinates()).toVec3();
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
			}
			distance += 1.0f;
		}	
		return false;
	}

	void OutdoorEditor::modifyTerrain(const glm::vec3& hitPos, const glm::vec3& direction, bool subtractVolume)
	{
		VoxelPoint voxel = subtractVolume ? VoxelPoint(0.0f,0) : VoxelPoint(1.0f, 0);
		glm::vec3 newPos = subtractVolume ? glm::round(hitPos) : glm::round(hitPos - direction * 0.3f);

		VoxelCoordinates modifyVoxel(newPos.x, newPos.y, newPos.z);

		std::cout << "MODIFY VOXEL: " << modifyVoxel.X << ", " << modifyVoxel.Y << ", " << modifyVoxel.Z << std::endl;

		voxelManager->setVoxel(modifyVoxel, voxel);
		refresh();
	}

	//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution (04.11.21)
	//Implements and Explains the Geometric intersection algorithm with a plane equation and left right tests to ensure the hit point is in the triangle
	bool OutdoorEditor::rayTriangleIntersection(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal, glm::vec3& outPos) const
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

	

	TerrainManager* OutdoorEditor::getTerrainManager() const
	{
		return terrainManager;
	}

	VoxelManager* OutdoorEditor::getVoxelManager() const
	{
		return voxelManager;
	}


};