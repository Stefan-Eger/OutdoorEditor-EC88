#include "OEInclude.h"
namespace oe {
	VoxelCoordinates::VoxelCoordinates() : X{ 0 }, Y{ 0 }, Z{ 0 }{}
	VoxelCoordinates::VoxelCoordinates(const_reference x, const_reference y, const_reference z) : X{ x }, Y{ y }, Z{ z } {}

	VoxelCoordinates::VoxelCoordinates(const VoxelCoordinates& vc)
	{
		X = vc.X;
		Y = vc.Y;
		Z = vc.Z;
	}

	VoxelCoordinates& VoxelCoordinates::operator=(const VoxelCoordinates& vc)
	{
		X = vc.X;
		Y = vc.Y;
		Z = vc.Z;

		return *this;
	}

	bool VoxelCoordinates::operator==(const VoxelCoordinates& rhs) const
	{
		return  ((X == rhs.X) && (Y == rhs.Y) && (Z == rhs.Z));
	}
		
	VoxelCoordinates VoxelCoordinates::operator+(const VoxelCoordinates& rhs) const{
		return VoxelCoordinates(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
	}
	VoxelCoordinates VoxelCoordinates::operator-(const VoxelCoordinates& rhs) const {
		return VoxelCoordinates(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
	}

	VoxelCoordinates VoxelCoordinates::operator*(const VoxelCoordinates& rhs) const
	{
		return VoxelCoordinates(X * rhs.X, Y * rhs.Y, Z * rhs.Z);
	}

	VoxelCoordinates VoxelCoordinates::operator*(const_reference scalar) const{
		return VoxelCoordinates(X * scalar, Y * scalar, Z * scalar);
	}
		
	

	glm::vec3 VoxelCoordinates::toVec3() const { return glm::vec3(X, Y, Z); }

	VoxelCoordinates operator*( VoxelCoordinates::const_reference scalar, const VoxelCoordinates& rhs){
		return (rhs * scalar);
	}

}
