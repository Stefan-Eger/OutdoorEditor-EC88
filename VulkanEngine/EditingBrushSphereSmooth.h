#ifndef EDITING_BRUSH_SPHERE_SMOOTH_H
#define EDITING_BRUSH_SPHERE_SMOOTH_H
namespace oe {
	class EditingBrushSphereSmooth : public EditingBrush
	{
	public:
		EditingBrushSphereSmooth() : EditingBrush() {}
		EditingBrushSphereSmooth(const float& radius, const float& strength) : EditingBrush(radius, strength) {}

		virtual std::vector<std::pair<VoxelCoordinates, float>> getAffected(const glm::vec3& pos) const override;
	};
}
#endif // !EDITING_BRUSH_SPHERE_SMOOTH_H

