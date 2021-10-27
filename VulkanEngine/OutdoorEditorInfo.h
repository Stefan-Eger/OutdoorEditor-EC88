#ifndef OUTDOOR_EDITOR_INFO_H
#define OUTDOOR_EDITOR_INFO_H

namespace oe {
	struct OutdoorEditorInfo
	{
		//World
		static World* world;

		//Camera
		static constexpr glm::vec3 CAMERA_POS_ORIGIN{ 0.0f, 5.0f, -3.0f };
		static constexpr float CAMERA_X_AXIS_THETA = 45.0f * (float)M_PI / 180.0f;

		static void exit();
	};	
}
#endif
