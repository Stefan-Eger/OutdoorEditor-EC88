#ifndef TERRAIN_MANAGER_H
#define TERRAIN_MANAGER_H

namespace oe {
	
	/// <summary>
	/// This Manager stores the actual Mesh that is displayed.
	/// It is the basis for interaction with the terrain.
	/// </summary>
	class TerrainManager
	{
		std::unordered_map<VoxelCoordinates, TerrainMeshChunk*> terrain;
		TerrainGenerator* generator;
	public:
		TerrainManager(TerrainGenerator* generator);
		~TerrainManager();
		
		void setGenerator(TerrainGenerator* generator);
		void createChunkMesh(const VoxelCoordinates& chunkCoordinates);
		TerrainMeshChunk* findChunk(const VoxelCoordinates& chunkCoordinates);
		bool traceRay(const Ray& ray, glm::vec3& outPos) const;
		void clear();
		
	};
}
#endif // !TERRAIN_MANAGER_H
