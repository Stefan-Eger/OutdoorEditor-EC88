#ifndef VOXEL_POINT_H

namespace oe {
	struct VoxelPoint {
		float density;
		std::size_t terrainType;

		VoxelPoint();
		VoxelPoint(const float& density, const std::size_t& terrainType);

		static VoxelPoint Empty();
	};
}

#endif // !VOXEL_POINT_H