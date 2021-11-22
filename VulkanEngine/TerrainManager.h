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

		std::unordered_set<VoxelCoordinates> changedChunks;

		void addChunkMesh(const VoxelCoordinates& chunkPos);
		void updateNeighborsOfChunk(const VoxelCoordinates& chunkPos);
		void updateSingleChunk(const VoxelCoordinates& chunkPos);


	public:
		TerrainManager(TerrainGenerator* generator);
		~TerrainManager();
		
		void updateChunkMesh(const VoxelCoordinates& chunkPos);
		void updateCellsAroundVoxel(const VoxelCoordinates& voxelWorldPos);
		void renderChangedChunks();	
		TerrainMeshChunk* findChunk(const VoxelCoordinates& chunkPos);

		void setGenerator(TerrainGenerator* generator);
	};
}
#endif // !TERRAIN_MANAGER_H
