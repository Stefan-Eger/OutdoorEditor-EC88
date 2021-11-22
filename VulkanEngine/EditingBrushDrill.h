#ifndef EDITING_BRUSH_DRILL_H
#define EDITING_BRUSH_DRILL_H
namespace oe {
	class EditingBrushDrill : public EditingBrush
	{
	public:
		EditingBrushDrill() : EditingBrush() {}
		EditingBrushDrill(const float& strength) : EditingBrush(1.0f, strength) {}

		//To ensure that the radius will not change
		virtual void increaseRadius() override;
		virtual void decreaseRadius() override;

		virtual std::vector<std::pair<VoxelCoordinates, float>> getAffected(const glm::vec3& pos) const override;
	};
}

#endif

