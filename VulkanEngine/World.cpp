#include "OEInclude.h"
namespace oe {
	World::World() {
		terrainGenerator = new MarchingCubes(this);
	}
	
	World::~World(){
		for (const auto& chunk : chunks) {
			delete chunk.second;
		}
		chunks.clear();
		delete terrainGenerator;
	}

	VoxelCoordinates World::world2Local(const VoxelCoordinates& worldCoordinates)
	{
		auto x = worldCoordinates.X < 0 ? (VoxelChunkData::CHUNK_SIZE.X - 1) + ((worldCoordinates.X+1) % VoxelChunkData::CHUNK_SIZE.X) : worldCoordinates.X % VoxelChunkData::CHUNK_SIZE.X;
		auto y = worldCoordinates.Y < 0 ? (VoxelChunkData::CHUNK_SIZE.Y - 1) + ((worldCoordinates.Y+1) % VoxelChunkData::CHUNK_SIZE.Y) : worldCoordinates.Y % VoxelChunkData::CHUNK_SIZE.Y;
		auto z = worldCoordinates.Z < 0 ? (VoxelChunkData::CHUNK_SIZE.Z - 1) + ((worldCoordinates.Z+1) % VoxelChunkData::CHUNK_SIZE.Z) : worldCoordinates.Z % VoxelChunkData::CHUNK_SIZE.Z;

		return VoxelCoordinates(x, y, z);
	}
	VoxelCoordinates World::local2World(const VoxelCoordinates& localCoordinates, const VoxelCoordinates& chunkCoordinate)
	{
		return localCoordinates + VoxelChunkData::CHUNK_SIZE * chunkCoordinate;
	}

	VoxelCoordinates World::world2ChunkCoordinates(const VoxelCoordinates& worldCoordinate)
	{
		auto x = worldCoordinate.X < 0 ? -1 + (worldCoordinate.X+1) / VoxelChunkData::CHUNK_SIZE.X : worldCoordinate.X / VoxelChunkData::CHUNK_SIZE.X;
		auto y = worldCoordinate.Y < 0 ? -1 + (worldCoordinate.Y+1) / VoxelChunkData::CHUNK_SIZE.Y : worldCoordinate.Y / VoxelChunkData::CHUNK_SIZE.Y;
		auto z = worldCoordinate.Z < 0 ? -1 + (worldCoordinate.Z+1) / VoxelChunkData::CHUNK_SIZE.Z : worldCoordinate.Z / VoxelChunkData::CHUNK_SIZE.Z;

		return VoxelCoordinates(x, y, z);
	}

	void World::generateAll() const
	{
		auto chunks2Generate = getAllChunks2Generate();
		int i = 0, chunkLoad = chunks2Generate.size();
		for (const auto& chunk : chunks2Generate) {
			terrainGenerator->generate(chunk);

			std::cout << "Chunk "<< i++ << "\t[" << chunk.X << ", " << chunk.Y << ", " << chunk.Z << "] \t of " << chunkLoad << " has been generated" << std::endl;
		}
	}

	void World::setChunkAt(const VoxelCoordinates& chunkCoordinates){
		chunks.emplace(chunkCoordinates, new VoxelChunkData());
	}

	void World::setChunkAt(const VoxelCoordinates& chunkCoordinates, const VoxelPoint& filler)
	{
		chunks.emplace(chunkCoordinates, new VoxelChunkData(filler));
	}

	void World::setVoxel(const VoxelCoordinates& worldCoordinates, const VoxelPoint& voxelValue){
		VoxelCoordinates localCoordinates = world2Local(worldCoordinates);
		VoxelCoordinates chunkCoordinates = world2ChunkCoordinates(worldCoordinates);

		for (const auto& chunk : chunks) {
			if (chunk.first == chunkCoordinates) {
				chunk.second->setVoxel(localCoordinates, voxelValue);
			}
		}
	}

	VoxelPoint World::getVoxel(const VoxelCoordinates& worldCoordinates) const{
		VoxelCoordinates localCoordinates = world2Local(worldCoordinates);
		VoxelCoordinates chunkCoordinates = world2ChunkCoordinates(worldCoordinates);

		for (const auto& chunk : chunks) {
			if (chunk.first == chunkCoordinates) {
				return chunk.second->getVoxel(localCoordinates);
			}
		}
		return VoxelPoint::Empty();
	}


	VoxelChunkData* World::getChunk(const VoxelCoordinates& chunkCoordinates) const
	{
		auto chunk = chunks.find(chunkCoordinates);
		if (chunk != chunks.end()) {
			return chunk->second;
		}
		return nullptr;
	}

	std::vector<VoxelCoordinates> World::getAllChunks2Generate() const
	{
		std::vector<VoxelCoordinates> ret;
		for (auto const& chunk : chunks) {
			if(!chunk.second->isAirChunk())
				ret.push_back(chunk.first);
		}
		return ret;
	}

	bool World::traceRay(const Ray& ray, glm::vec3& outPos) const
	{
		glm::vec3 origin = ray.getOrigin();

		world2ChunkCoordinates(VoxelCoordinates((int)origin.x, (int)origin.y, (int)origin.z));

		return false;
	}

};