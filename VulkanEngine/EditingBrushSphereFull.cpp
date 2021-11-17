#include "OEInclude.h"

namespace oe {
	std::vector<std::pair<VoxelCoordinates, float>> EditingBrushSphereFull::getAffected(const glm::vec3& pos) const
	{
		std::vector<std::pair<VoxelCoordinates, float>> ret;
		VoxelCoordinates midPoint(std::lround(pos.x), std::lround(pos.y), std::lround(pos.z));
		long iRadius = lround(radius);
		long invRadius = lround(-radius);
		for (auto x = invRadius; x <= iRadius; ++x) {
			for (auto y = invRadius; y <= iRadius; ++y) {
				for (auto z = invRadius; z <= iRadius; ++z) {
					/*
					if ((x == 0) && (y == 0) && (z == 0)) {
						ret.push_back(std::make_pair(VoxelCoordinates(midPoint.X, midPoint.Y, midPoint.Z), strength));
						continue;
					}
					*/
					float length = glm::length(glm::vec3(x, y, z));
					if (length > radius) {
						continue;
					}
					
					VoxelCoordinates nextPos = midPoint + VoxelCoordinates(x, y, z);

					ret.push_back(std::make_pair(nextPos, strength));
				}
			}
		}

		return ret;
	}
}
