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
		void addChunkMesh(const VoxelCoordinates& chunkCoordinates);
		void updateChunkMesh(const VoxelCoordinates& chunkCoordinates);
		TerrainMeshChunk* findChunk(const VoxelCoordinates& chunkCoordinates);
	};
}
#endif // !TERRAIN_MANAGER_H
