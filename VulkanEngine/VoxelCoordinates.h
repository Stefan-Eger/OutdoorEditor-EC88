#ifndef VOXEL_COORDINATES_H
#define VOXEL_COORDINATES_H
namespace oe {
	struct VoxelCoordinates
	{
		using value_type = int;

		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		value_type X, Y, Z;

		VoxelCoordinates(const_reference x, const_reference y, const_reference z);

		bool operator==(const VoxelCoordinates& rhs) const;

	  VoxelCoordinates operator+(const VoxelCoordinates& rhs) const;
		VoxelCoordinates operator-(const VoxelCoordinates& rhs) const;
		VoxelCoordinates operator*(const VoxelCoordinates& rhs) const;

		VoxelCoordinates operator*(const_reference scalar) const;
		friend VoxelCoordinates operator*(const_reference scalar, const VoxelCoordinates& rhs);

		
		glm::vec3 toVec3() const;
	};
}

namespace std {
	//https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key (26.10.21)
	template<> struct hash<oe::VoxelCoordinates> {
		size_t operator()(const oe::VoxelCoordinates& vc) const {
			size_t res = 17;

			res = res * 31 + hash<int>()(vc.X);
			res = res * 31 + hash<int>()(vc.Y);
			res = res * 31 + hash<int>()(vc.Z);
			return res;
		}
	};
}

#endif // !VOXEL_COORDINATES_Hs

