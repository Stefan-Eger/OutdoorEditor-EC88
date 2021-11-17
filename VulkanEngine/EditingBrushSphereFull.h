#ifndef EDITING_BRUSH_SPHERE_FULL_H
#define EDITING_BRUSH_SPHERE_FULL_H

namespace oe {
	class EditingBrushSphereFull : public EditingBrush
	{
	public:
		EditingBrushSphereFull() : EditingBrush() {}
		EditingBrushSphereFull(const float& radius, const float& strength) : EditingBrush(radius, strength){}

		std::vector<std::pair<VoxelCoordinates, float>> getAffected(const glm::vec3& pos) const override;
	};
}

#endif
