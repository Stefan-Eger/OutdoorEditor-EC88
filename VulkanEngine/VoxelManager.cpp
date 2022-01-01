#include "OEInclude.h"

namespace oe {
	VoxelManager::VoxelManager()
	{
	}
	VoxelManager::~VoxelManager()
	{
		for (const auto& chunk : chunks) {
			delete chunk.second;
		}
		chunks.clear();
	}

	VoxelCoordinates VoxelManager::world2Local(const VoxelCoordinates& worldCoordinates)
	{
		auto x = worldCoordinates.X < 0 ? (VoxelChunkData::CHUNK_SIZE.X - 1) + ((worldCoordinates.X + 1) % VoxelChunkData::CHUNK_SIZE.X) : worldCoordinates.X % VoxelChunkData::CHUNK_SIZE.X;
		auto y = worldCoordinates.Y < 0 ? (VoxelChunkData::CHUNK_SIZE.Y - 1) + ((worldCoordinates.Y + 1) % VoxelChunkData::CHUNK_SIZE.Y) : worldCoordinates.Y % VoxelChunkData::CHUNK_SIZE.Y;
		auto z = worldCoordinates.Z < 0 ? (VoxelChunkData::CHUNK_SIZE.Z - 1) + ((worldCoordinates.Z + 1) % VoxelChunkData::CHUNK_SIZE.Z) : worldCoordinates.Z % VoxelChunkData::CHUNK_SIZE.Z;

		return VoxelCoordinates(x, y, z);
	}
	VoxelCoordinates VoxelManager::local2World(const VoxelCoordinates& localCoordinates, const VoxelCoordinates& chunkCoordinate)
	{
		return localCoordinates + VoxelChunkData::CHUNK_SIZE * chunkCoordinate;
	}
	VoxelCoordinates VoxelManager::world2ChunkCoordinates(const VoxelCoordinates& worldCoordinate)
	{
		auto x = worldCoordinate.X < 0 ? -1 + (worldCoordinate.X + 1) / VoxelChunkData::CHUNK_SIZE.X : worldCoordinate.X / VoxelChunkData::CHUNK_SIZE.X;
		auto y = worldCoordinate.Y < 0 ? -1 + (worldCoordinate.Y + 1) / VoxelChunkData::CHUNK_SIZE.Y : worldCoordinate.Y / VoxelChunkData::CHUNK_SIZE.Y;
		auto z = worldCoordinate.Z < 0 ? -1 + (worldCoordinate.Z + 1) / VoxelChunkData::CHUNK_SIZE.Z : worldCoordinate.Z / VoxelChunkData::CHUNK_SIZE.Z;

		return VoxelCoordinates(x, y, z);
	}

	void VoxelManager::addChunk(const VoxelCoordinates& chunkCoordinates) {
		chunks.emplace(chunkCoordinates, new VoxelChunkData());
	}

	void VoxelManager::addChunk(const VoxelCoordinates& chunkCoordinates, const VoxelPoint& filler)
	{
		chunks.emplace(chunkCoordinates, new VoxelChunkData(filler));
	}

	void VoxelManager::setVoxel(const VoxelCoordinates& worldCoordinates, const VoxelPoint& voxelValue) {
		VoxelCoordinates localCoordinates = world2Local(worldCoordinates);
		VoxelCoordinates chunkCoordinates = world2ChunkCoordinates(worldCoordinates);

		auto chunk = chunks.find(chunkCoordinates);
		if (chunk != chunks.end()) {
			chunk->second->setVoxel(localCoordinates, voxelValue);
		}
	}

	VoxelPoint VoxelManager::getVoxel(const VoxelCoordinates& worldCoordinates) const {
		VoxelCoordinates localCoordinates = world2Local(worldCoordinates);
		VoxelCoordinates chunkCoordinates = world2ChunkCoordinates(worldCoordinates);

		auto chunk = chunks.find(chunkCoordinates);
		if (chunk != chunks.end()) {
			return chunk->second->getVoxel(localCoordinates);
		}
		
		return VoxelPoint::Empty();
	}


	VoxelChunkData* VoxelManager::findChunk(const VoxelCoordinates& chunkCoordinates) const
	{
		auto chunk = chunks.find(chunkCoordinates);
		if (chunk != chunks.end()) {
			return chunk->second;
		}
		return nullptr;
	}

	void VoxelManager::clear()
	{
		for (const auto& chunk : chunks) {
			delete chunk.second;
		}
		chunks.clear();
	}

	std::vector<VoxelCoordinates> VoxelManager::getAllChunks2Refresh() const
	{
		std::vector<VoxelCoordinates> ret;

		for (auto const& chunk : chunks) {
			if (!chunk.second->isAirChunk() && (chunk.second->getChangedVoxels().size() > 0))
				ret.push_back(chunk.first);
		}
		return ret;
	}
	nlohmann::json& VoxelManager::save(nlohmann::json& serializer) const
	{
		nlohmann::json voxelChunk, chunkData;
		for (const auto& chunk : chunks) {

			voxelChunk["ChunkCoordinates"] = { chunk.first.X, chunk.first.Y, chunk.first.Z };
			voxelChunk["VoxelChunk"] = chunk.second->save(chunkData);
			
			serializer.push_back(voxelChunk);
			voxelChunk.clear();
		}

		return serializer;
	}
	
}