#ifndef EDITING_BRUSH_H
#define EDITING_BRUSH_H

namespace oe {
	class EditingBrush
	{
	protected:
		float radius; // Area affected
		float strength; // how strong the brush is
			
		const float RADIUS_MAX = 5.0f;
		const float RADIUS_MIN = 1.0f;
		const float RADIUS_STEP = 0.5f;


		const float STRENGTH_MIN = 0.0f;
		const float STRENGTH_MAX = 1.0f;

		const float STRENGTH_STEP = 0.1f;


	public:
		EditingBrush();
		EditingBrush(const float& radius, const float& strength);
		
		void increaseRadius();
		void decreaseRadius();

		void setStrength(const float& strength);

		float getStrength() const;
		float getRadius() const;

		/// <summary>
		/// This method calculates how much a position is affected by the brush
		/// </summary>
		/// <param name="pos">position that represents the middle point</param>
		/// <returns>1.0f -> Maximum, 0.0f -> Minimum</returns>
		virtual std::vector<std::pair<VoxelCoordinates,float>> getAffected(const glm::vec3& pos) const = 0;
	};
}
#endif // !EDITING_BRUSH_H
