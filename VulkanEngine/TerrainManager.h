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


	public:
		TerrainManager(TerrainGenerator* generator);
		~TerrainManager();
		
		void setGenerator(TerrainGenerator* generator);
		void addChunkMesh(const VoxelCoordinates& chunkPos);
		void updateChunkMesh(const VoxelCoordinates& chunkPos);
		void updateCellsAroundVoxel(const VoxelCoordinates& voxelWorldPos);

		void renderChangedChunks();	

		TerrainMeshChunk* findChunk(const VoxelCoordinates& chunkPos);
	};
}
#endif // !TERRAIN_MANAGER_H
