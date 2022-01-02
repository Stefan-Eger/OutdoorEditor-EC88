#include "OEInclude.h"
#include "VoxelChunkData.h"

namespace oe {
	VoxelChunkData::VoxelChunkData() : voxels{}, voxelCounter{ 0 } {}

	VoxelChunkData::VoxelChunkData(const VoxelPoint& ref) : voxelCounter{ 0 } 
	{
		for (auto x = 0; x < CHUNK_SIZE_X; x++)
		{
			for (auto y = 0; y < CHUNK_SIZE_Y; y++)
			{
				for (auto z = 0; z < CHUNK_SIZE_Z; z++)
				{
					voxels[x][y][z] = ref;
					voxelCounter += 0.0f != ref.density ? 1 : 0;
					changedVoxels.push_back(VoxelCoordinates(x,y,z));
				}
			}
		}
	}
		
	VoxelChunkData::~VoxelChunkData(){}

	const VoxelCoordinates VoxelChunkData::CHUNK_SIZE = VoxelCoordinates(VoxelChunkData::CHUNK_SIZE_X, VoxelChunkData::CHUNK_SIZE_Y, VoxelChunkData::CHUNK_SIZE_Z);

	void VoxelChunkData::setVoxel(const VoxelCoordinates& localCoordinates, const VoxelPoint& voxelValue){
		VoxelPoint oldVal = voxels[localCoordinates.X][localCoordinates.Y][localCoordinates.Z];
		voxels[localCoordinates.X][localCoordinates.Y][localCoordinates.Z] = voxelValue;

		//Check if there is a difference from the old value
		if ((oldVal.density - voxelValue.density) != 0.0f || (oldVal.terrainType - voxelValue.terrainType) != 0) {
			voxelCounter += 0.0f != voxelValue.density  ? 1 : -1;
			changedVoxels.push_back(localCoordinates);
		}
	}

	VoxelPoint VoxelChunkData::getVoxel(const VoxelCoordinates& localCoordinates) const{
		return voxels[localCoordinates.X] [localCoordinates.Y] [localCoordinates.Z];
	}


	bool VoxelChunkData::isAirChunk() const{
		return !voxelCounter;
	}

	const std::vector<VoxelCoordinates>& VoxelChunkData::getChangedVoxels() const
	{
		return changedVoxels;
	}

	void VoxelChunkData::clearChangedVoxels()
	{
		changedVoxels.clear();
	}

	nlohmann::json& VoxelChunkData::save(nlohmann::json& serializer) const
	{
		nlohmann::json voxel;
		for (auto x = 0; x < CHUNK_SIZE_X; x++)
		{
			for (auto y = 0; y < CHUNK_SIZE_Y; y++)
			{
				for (auto z = 0; z < CHUNK_SIZE_Z; z++)
				{
					voxel["LocalCoordinates"] = { x, y, z };
					voxel["Density"] = voxels[x][y][z].density;
					voxel["TerrainType"] = voxels[x][y][z].terrainType;
					
					serializer.push_back(voxel);
					voxel.clear();
				}
			}
		}
		return serializer;
	}

	void VoxelChunkData::load(nlohmann::json& data)
	{
		for (nlohmann::json::iterator it = data.begin(); it != data.end(); ++it) {

			VoxelCoordinates::value_type x, y, z;
			x = (*it)["LocalCoordinates"].at(0).get<VoxelCoordinates::value_type>();
			y = (*it)["LocalCoordinates"].at(1).get<VoxelCoordinates::value_type>();
			z = (*it)["LocalCoordinates"].at(2).get<VoxelCoordinates::value_type>();

			float density;
			density = (*it)["Density"].get<float>();

			std::size_t terrainType;
			terrainType = (*it)["TerrainType"].get<std::size_t>();
			
			voxels[x][y][z] = VoxelPoint(density, terrainType);

			//for updating later
			voxelCounter += 0.0f != density ? 1 : 0;
			changedVoxels.push_back(VoxelCoordinates(x, y, z));

		}

	}

}
