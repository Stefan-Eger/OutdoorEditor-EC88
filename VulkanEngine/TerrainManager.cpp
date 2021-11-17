#include "OEInclude.h"


namespace oe {
	TerrainManager::TerrainManager(TerrainGenerator* generator) : generator{generator}{}
	TerrainManager::~TerrainManager()
	{
		for (const auto& chunk : terrain) {
			delete chunk.second;
		}
		terrain.clear();
		delete generator;
	}
	void TerrainManager::setGenerator(TerrainGenerator* generator)
	{
		if (generator != nullptr) {
			this->generator = generator;
		}
	}
	void TerrainManager::addChunkMesh(const VoxelCoordinates& chunkPos)
	{
		TerrainMeshChunk* chunk = new TerrainMeshChunk(chunkPos);
		generator->generateChunk(chunk);
		terrain.emplace(chunkPos, chunk);

		changedChunks.emplace(chunkPos);
	}
	void TerrainManager::updateChunkMesh(const VoxelCoordinates& chunkPos)
	{
		//if chunk already exists then update
		TerrainMeshChunk* pChunk = findChunk(chunkPos);
		if (pChunk != nullptr) {
			pChunk->clear();
			generator->generateChunk(pChunk);
			changedChunks.emplace(chunkPos);

			auto leftNeighbor = chunkPos - VoxelCoordinates(1, 0, 0);
			auto lowerNeighbor = chunkPos - VoxelCoordinates(0, 1, 0);
			auto backNeighbor = chunkPos - VoxelCoordinates(0, 0, 1);

			if (terrain.contains(leftNeighbor)) {
				auto left = terrain.at(leftNeighbor);
				left->clear();
				generator->generateChunk(left);
				changedChunks.emplace(leftNeighbor);
			}
			if (terrain.contains(lowerNeighbor)) {
				auto lower = terrain.at(lowerNeighbor);
				lower->clear();
				generator->generateChunk(lower);
				changedChunks.emplace(lowerNeighbor);
			}
			if (terrain.contains(backNeighbor)) {
				auto back = terrain.at(backNeighbor);
				back->clear();
				generator->generateChunk(back);
				changedChunks.emplace(backNeighbor);
			}
			return;
		}

		//if not then create a new chunk
		addChunkMesh(chunkPos);
	}
	void TerrainManager::updateCellsAroundVoxel(const VoxelCoordinates& voxelWorldPos)
	{

		//TODO Reduce to 3 with shared vertices. otherwise the update radius has to be 2 (which results in 5x5x5 cube with the voxelWorldPos representing the cube in the middle)
		for (auto x = 0; x < 5; ++x) {
			for (auto y = 0; y < 5; ++y) {
				for (auto z = 0; z < 5; ++z) {
					VoxelCoordinates cellCoordinates = voxelWorldPos + VoxelCoordinates(2,2,2)  - VoxelCoordinates(x, y, z); //BackLowerLeft Corner for voxelCoordinates
					VoxelCoordinates localCellCoordinates = VoxelManager::world2Local(cellCoordinates);
					auto chunkPos = VoxelManager::world2ChunkCoordinates(cellCoordinates);
					TerrainMeshChunk* pChunk = findChunk(chunkPos);
					if (pChunk != nullptr) {
						generator->generateCell(pChunk, localCellCoordinates);
						changedChunks.emplace(chunkPos);
						continue;
					}
					addChunkMesh(chunkPos);
				}
			}
		}
	}
	void TerrainManager::renderChangedChunks(){
		for (const auto& chunk : changedChunks) {
			TerrainMeshChunk* pChunk = terrain.at(chunk);
			pChunk->renderChunk();
		}
		changedChunks.clear();
	}
	TerrainMeshChunk* TerrainManager::findChunk(const VoxelCoordinates& chunkPos)
	{
		auto chunk = terrain.find(chunkPos);

		if (terrain.find(chunkPos) != terrain.end())
			return chunk->second;

		return nullptr;
	}
}