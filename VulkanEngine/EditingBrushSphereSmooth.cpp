#include "OEInclude.h"

namespace oe {
	std::vector<std::pair<VoxelCoordinates, float>> EditingBrushSphereSmooth::getAffected(const glm::vec3& pos) const
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
					//We know length is  0 < length <= radius
					//cos(2 * pi / f) * amplitude
					//We want cos from 0 to pi / 2
					//this is f by varying radius and calculated length in order to get pi / 2
					// 2*pi* 1/f  * radius * length == pi / 2
					// => 4*radius*length and a shortcut by using PI instead of 2*Pi results in 2 * radius * length
					// so in the end we want f = 2*r^2 because this is the maximum the length can achieve
					float frequency = (2.0f * radius * radius);
					float nextStrength = std::cos((static_cast<float>(M_PI) / frequency) * radius*length)*strength;

					ret.push_back(std::make_pair(nextPos, nextStrength));
				}
			}
		}

		return ret;
	}
}