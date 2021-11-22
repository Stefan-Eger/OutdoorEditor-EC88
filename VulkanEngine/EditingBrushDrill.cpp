#include "OEInclude.h"

namespace oe {
	void EditingBrushDrill::increaseRadius(){return;}
	void EditingBrushDrill::decreaseRadius(){return;}
	std::vector<std::pair<VoxelCoordinates, float>> EditingBrushDrill::getAffected(const glm::vec3& pos) const
	{
		std::vector<std::pair<VoxelCoordinates, float>> ret;
		VoxelCoordinates roundedPos(std::lround(pos.x), std::lround(pos.y), std::lround(pos.z));
		ret.push_back(std::make_pair(roundedPos, strength));
		return ret;
	}

}