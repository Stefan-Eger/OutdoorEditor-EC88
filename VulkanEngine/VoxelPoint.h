#ifndef VOXEL_POINT_H

namespace oe {
	struct VoxelPoint {
		float density;
		uint32_t terrainType;

		VoxelPoint();
		VoxelPoint(const float& density, const uint32_t& terrainType);

		static VoxelPoint Empty();
	};
}

#endif // !VOXEL_POINT_H