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
	void TerrainManager::createChunkMesh(const VoxelCoordinates& chunkCoordinates)
	{
		TerrainMeshChunk* chunk = generator->generate(chunkCoordinates);
		chunk->createMesh();
		terrain.emplace(chunkCoordinates, chunk);
	}
	TerrainMeshChunk* TerrainManager::findChunk(const VoxelCoordinates& chunkCoordinates)
	{
		auto chunk = terrain.find(chunkCoordinates);

		if (terrain.find(chunkCoordinates) != terrain.end())
			return chunk->second;

		return nullptr;
	}
	bool TerrainManager::traceRay(const Ray& ray, glm::vec3& outPos) const
	{
		//TODO
		return false;
	}
	void TerrainManager::clear()
	{
		for (const auto& chunk : terrain) {
			delete chunk.second;
		}
		terrain.clear();
	}
}