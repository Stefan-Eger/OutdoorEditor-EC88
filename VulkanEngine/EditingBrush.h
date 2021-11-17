#ifndef EDITING_BRUSH_H
#define EDITING_BRUSH_H

namespace oe {
	struct EditingBrush
	{
		float radius; // Area affected
		float brushStrength; // how strong the brush is

		enum BrushTypes {
			OE_SINGLE_VOLUME_EDITING_BRUSH,
			OE_SPHERE_VOLUME_EDITING_BRUSH,
			OE_TERRAIN_VOLUME_EDITING_SMOOTH_BRUSH,
			OE_SPHERE_VOLUME_EDITING_BRUSH
		};

	};
}
#endif // !EDITING_BRUSH_H
