#include "OEInclude.h"

namespace oe {
	VoxelChunkData::VoxelChunkData() : voxels{}, voxelCounter{ 0 }, hasChanged{true} {}

	VoxelChunkData::VoxelChunkData(const VoxelPoint& ref) : voxelCounter{ 0 }, hasChanged{true}
	{
		for (auto x = 0; x < CHUNK_SIZE_X; x++)
		{
			for (auto y = 0; y < CHUNK_SIZE_Y; y++)
			{
				for (auto z = 0; z < CHUNK_SIZE_Z; z++)
				{
					voxels[x][y][z] = ref;
					voxelCounter += 0.0f != ref.density ? 1 : 0;
				}
			}
		}
	}
		
	VoxelChunkData::~VoxelChunkData(){}

	const VoxelCoordinates VoxelChunkData::CHUNK_SIZE = VoxelCoordinates(VoxelChunkData::CHUNK_SIZE_X, VoxelChunkData::CHUNK_SIZE_Y, VoxelChunkData::CHUNK_SIZE_Z);

	void VoxelChunkData::setVoxel(const VoxelCoordinates& localCoordinates, const VoxelPoint& voxelValue){
		VoxelPoint oldVal = voxels[localCoordinates.X][localCoordinates.Y][localCoordinates.Z];
		voxels[localCoordinates.X][localCoordinates.Y][localCoordinates.Z] = voxelValue;
		hasChanged = true;

		//Check if there is a difference from the old value
		if ((oldVal.density - voxelValue.density) != 0.0f) {
			voxelCounter += 0.0f != voxelValue.density  ? 1 : -1;
		}
   
	}

	VoxelPoint VoxelChunkData::getVoxel(const VoxelCoordinates& localCoordinates) const{
		return voxels[localCoordinates.X] [localCoordinates.Y] [localCoordinates.Z];
	}


	bool VoxelChunkData::isAirChunk() const{
		return !voxelCounter;
	}
	
}
