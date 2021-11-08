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
	void TerrainManager::addChunkMesh(const VoxelCoordinates& chunkCoordinates)
	{
		TerrainMeshChunk* chunk = new TerrainMeshChunk(chunkCoordinates);
		generator->generateMesh(chunk);
		chunk->renderChunk();

		terrain.emplace(chunkCoordinates, chunk);
	}
	void TerrainManager::updateChunkMesh(const VoxelCoordinates& chunkCoordinates)
	{
		//if chunk already exists then update
		TerrainMeshChunk* pOldChunk = findChunk(chunkCoordinates);
		if (pOldChunk != nullptr) {
			pOldChunk->clear();
			generator->generateMesh(pOldChunk);
			pOldChunk->renderChunk();
			return;
		}

		//if not then create a new chunk
		addChunkMesh(chunkCoordinates);
	}
	TerrainMeshChunk* TerrainManager::findChunk(const VoxelCoordinates& chunkCoordinates)
	{
		auto chunk = terrain.find(chunkCoordinates);

		if (terrain.find(chunkCoordinates) != terrain.end())
			return chunk->second;

		return nullptr;
	}
}