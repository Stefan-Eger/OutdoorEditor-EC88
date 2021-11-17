#include "OEInclude.h"

namespace oe {
	std::vector<std::pair<VoxelCoordinates, float>> EditingBrushSphereFull::getAffected(const glm::vec3& pos) const
	{
		std::vector<std::pair<VoxelCoordinates, float>> ret;
		VoxelCoordinates midPoint(std::lround(pos.x), std::lround(pos.y), std::lround(pos.z));

		for (auto x = -radius; x <= radius; ++x) {
			for (auto y = -radius; y <= radius; ++y) {
				for (auto z = -radius; z <= radius; ++z) {
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
