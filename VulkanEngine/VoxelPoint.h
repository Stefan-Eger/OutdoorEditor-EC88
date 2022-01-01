#ifndef VOXEL_POINT_H

namespace oe {
	struct VoxelPoint {
		float density;
		std::size_t terrainType;

		VoxelPoint();
		VoxelPoint(const float& density, const std::size_t& terrainType);

		static VoxelPoint Empty();


		nlohmann::json& save(nlohmann::json& serializer) const;
	};
}

#endif // !VOXEL_POINT_H