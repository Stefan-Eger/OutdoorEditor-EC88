#include "OEInclude.h"


//TODO JSON SAVE LOAD

namespace oe {
	VoxelPoint::VoxelPoint() : density{0.0f}, terrainType(0) {}
	VoxelPoint::VoxelPoint(const float& density, const uint32_t& terrainType) : terrainType{ terrainType }{
		//Ensures denity is between 0.0f and 1.0f
		this->density = density < 0.0f ? 0.0f : 1.0f < density ? 1.0f : density;
	}

	VoxelPoint VoxelPoint::Empty()
	{
		return VoxelPoint(0.0f, 0);	
	}
	
}