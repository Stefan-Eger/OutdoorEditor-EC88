#include "OEInclude.h"
namespace oe {
	Ray EventListenerUser::createRayThroughPixel(const float& cursorX, const float& cursorY) const
	{

		VkExtent2D window = getEnginePointer()->getWindow()->getExtent();
		VECameraProjective* pCamera = dynamic_cast<VECameraProjective*> (getSceneManagerPointer()->getCamera());

		//Helper Variables
		float aspectRatio = pCamera->m_aspectRatio;
		float invWidth = 1.0f / window.width;
		float invHeight = 1.0f / window.height;

		float fovVertical = std::tan(glm::radians(pCamera->m_fov * 0.5f));

		//Screen Space 
		float xx = (((cursorX + 0.5f) * invWidth) * 2 - 1) * aspectRatio * fovVertical;
		float yy = (1 - 2 * ((cursorY + 0.5f) * invHeight)) * fovVertical;


		//Camera CS to calculate the direction of the ray (if the camera Rotates then the Ray has to adjust accordingly) 
		glm::vec3 u = pCamera->getWorldTransform() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 v = pCamera->getWorldTransform() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		glm::vec3 camDir = pCamera->getWorldTransform() * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

		//creating Ray
		glm::vec3 cameraPos = pCamera->getWorldTransform()[3];
		glm::vec3 direction = u * xx + v * yy + camDir;

		Ray r(cameraPos, direction);
		return r;
	}
	
	bool EventListenerUser::onMouseScroll(veEvent event)
	{
		auto brush = OutdoorEditorInfo::editor->getActiveBrush();
		if (brush == nullptr) { return false; }

		float xoffset = event.fdata1;
		float yoffset = event.fdata2;

		if (yoffset < 0) {
			brush->increaseRadius();
			
		}
		if (0 < yoffset) {
			brush->decreaseRadius();
		}

		VESubrenderFW_Trilinear::brushCircle.radius = brush->getRadius();
		getRendererForwardPointer()->updateCmdBuffers();
		
		return true;
	}
	bool EventListenerUser::onMouseMove(veEvent event)
	{
		auto brush = OutdoorEditorInfo::editor->getActiveBrush();
		if (brush == nullptr) { return false; }
		

		float x = event.fdata1;
		float y = event.fdata2;


		Ray r = createRayThroughPixel(x, y);

		glm::vec3 hitPos(0.0f, 0.0f, 0.0f);
		bool isHit = OutdoorEditorInfo::editor->traceRay(r, hitPos);
		if (isHit) {
			VESubrenderFW_Trilinear::brushCircle.mouseHitPos = hitPos;

			
			getRendererForwardPointer()->updateCmdBuffers();
		}
		return true;
	}



	//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays (26.10.21)
	bool EventListenerUser::onMouseButton(veEvent event)
	{
		if (event.idata3 == GLFW_PRESS) {
			m_usePrevCursorPosition = false;
			if (event.idata1 == GLFW_MOUSE_BUTTON_LEFT) {
				std::cout << "Left Click Pressed: " << std::endl;
				std::cout << "MousePos: [" << "X: " << event.fdata1 << "Y: " << event.fdata2 << "]" << std::endl;


				float cursorX = event.fdata1;
				float cursorY = event.fdata2;

				Ray r = createRayThroughPixel(cursorX, cursorY);


				glm::vec3 hitPos(0.0f, 0.0f, 0.0f);
				bool isHit = OutdoorEditorInfo::editor->traceRay(r, hitPos);
				if (isHit) {
					OutdoorEditorInfo::editor->handleInput(hitPos, r.getDirection());
					VESubrenderFW_Trilinear::brushCircle.mouseHitPos = hitPos;
					getRendererForwardPointer()->updateCmdBuffers();
				}

				return true;
			}
		}

		if (event.idata3 == GLFW_PRESS) {
			m_usePrevCursorPosition = false;
			if (event.idata1 == GLFW_MOUSE_BUTTON_RIGHT) {
				std::cout << "Right Click Pressed" << std::endl;
				std::cout << "MousePos: [" << "X: " << event.fdata1 << "Y: " << event.fdata2 << "]" << std::endl;
				m_rightButtonClicked = true;


				float cursorX = event.fdata1;
				float cursorY = event.fdata2;

				Ray r = createRayThroughPixel(cursorX, cursorY);

				glm::vec3 hitPos(0.0f, 0.0f, 0.0f);
				bool isHit = OutdoorEditorInfo::editor->traceRay(r, hitPos);
				if (isHit) {
					OutdoorEditorInfo::editor->handleInput(hitPos, r.getDirection(), true);
				}

				return true;
			}
		}

		if (event.idata3 == GLFW_RELEASE) {
			m_usePrevCursorPosition = false;
			if (event.idata1 == GLFW_MOUSE_BUTTON_LEFT) {
				std::cout << "Left Click Released: " << std::endl;
				return true;
			}
		}
		if (event.idata3 == GLFW_RELEASE) {
			m_usePrevCursorPosition = false;
			if (event.idata1 == GLFW_MOUSE_BUTTON_RIGHT) {
				std::cout << "Right Click Released" << std::endl;
				m_rightButtonClicked = false;
				return true;
			}
		}
		return false;
	}

	bool EventListenerUser::onKeyboard(veEvent event)
	{
		if (event.idata1 == GLFW_KEY_ESCAPE) {				//ESC pressed - end the engine
			getEnginePointer()->end();
			return true;
		}

		if (event.idata3 == GLFW_RELEASE) return false;

		if (event.idata1 == GLFW_KEY_P && event.idata3 == GLFW_PRESS) {
			m_makeScreenshot = true;
			return false;
		}
		if (event.idata1 == GLFW_KEY_O && event.idata3 == GLFW_PRESS) {
			m_makeScreenshotDepth = true;
			return false;
		}

		///create some default constants for the actions 
		glm::vec4 translate = glm::vec4(0.0, 0.0, 0.0, 1.0);	//total translation
		glm::vec4 rot4 = glm::vec4(1.0);						//total rotation around the axes, is 4d !
		float angle = 0.0;
		float rotSpeed = 2.0;

		VECamera* pCamera = getSceneManagerPointer()->getCamera();
		VESceneNode* pParent = pCamera->getParent();

		switch (event.idata1) {
		case GLFW_KEY_A:
			translate = pCamera->getTransform() * glm::vec4(-1.0, 0.0, 0.0, 1.0);	//left
			break;
		case GLFW_KEY_D:
			translate = pCamera->getTransform() * glm::vec4(1.0, 0.0, 0.0, 1.0); //right
			break;
		case GLFW_KEY_W:
			translate = pCamera->getTransform() * glm::vec4(0.0, 0.0, 1.0, 1.0); //forward
			translate.y = 0.0f;
			break;
		case GLFW_KEY_S:
			translate = pCamera->getTransform() * glm::vec4(0.0, 0.0, -1.0, 1.0); //back
			translate.y = 0.0f;
			break;
		case GLFW_KEY_Q: //yaw rotation is already in parent space
			angle = rotSpeed * (float)event.dt * -1.0f;
			rot4 = glm::vec4(0.0, 1.0, 0.0, 1.0);
			break;
		case GLFW_KEY_E: //yaw rotation is already in parent space
			angle = rotSpeed * (float)event.dt * 1.0f;
			rot4 = glm::vec4(0.0, 1.0, 0.0, 1.0);
			break;
		case GLFW_KEY_C:							
			translate = pCamera->getTransform() * glm::vec4(0.0, -1.0, 0.0, 1.0); //down
			break;
		case GLFW_KEY_SPACE:						
			translate = pCamera->getTransform() * glm::vec4(0.0, 1.0, 0.0, 1.0); //up
			break;
		case GLFW_KEY_1:
			OutdoorEditorInfo::editor->setEditingMode(OutdoorEditor::oeEditingModes::TERRAIN_EDITING_VOLUME_SPHERE_FULL);
			std::cout << "Changed editing Mode to TERRAIN_EDITING_VOLUME_SPHERE_FULL" << std::endl;
			getRendererForwardPointer()->updateCmdBuffers();
			break;

		case GLFW_KEY_2:
			OutdoorEditorInfo::editor->setEditingMode(OutdoorEditor::oeEditingModes::TERRAIN_EDITING_VOLUME_DRILL);
			std::cout << "Changed editing Mode to TERRAIN_EDITING_VOLUME_DRILL" << std::endl;
			getRendererForwardPointer()->updateCmdBuffers();
			break;

		case GLFW_KEY_3:
			OutdoorEditorInfo::editor->setEditingMode(OutdoorEditor::oeEditingModes::ENTITY_PLACEMENT_SINGLE_PLACEMENT);
			std::cout << "Changed editing Mode to ENTITY_PLACEMENT_SINGLE_PLACEMENT" << std::endl;
			getRendererForwardPointer()->updateCmdBuffers();
			break;
		
		case GLFW_KEY_4:
			OutdoorEditorInfo::editor->setEditingMode(OutdoorEditor::oeEditingModes::TERRAIN_EDITING_VOLUME_SPHERE_SMOOTH);
			std::cout << "Changed editing Mode to TERRAIN_EDITING_VOLUME_SPHERE_SMOOTH "<< std::endl;
			getRendererForwardPointer()->updateCmdBuffers();
			break;

		default:
			return false;
		};
		auto brush = OutdoorEditorInfo::editor->getActiveBrush();
		VESubrenderFW_Trilinear::brushCircle.isActive = brush == nullptr ? VK_FALSE : VK_TRUE;
		if (brush != nullptr) {
			VESubrenderFW_Trilinear::brushCircle.radius = brush->getRadius();
		}
		

		if (pParent == nullptr) {
			pParent = pCamera;
		}

		///add the new translation vector to the previous one
		float speed = 6.0f;
		glm::vec3 trans = speed * glm::vec3(translate.x, translate.y, translate.z);
		pParent->multiplyTransform(glm::translate(glm::mat4(1.0f), (float)event.dt * trans));

		///combination of yaw and pitch, both wrt to parent space
		glm::vec3  rot3 = glm::vec3(rot4.x, rot4.y, rot4.z);
		glm::mat4  rotate = glm::rotate(glm::mat4(1.0), angle, rot3);
		pCamera->multiplyTransform(rotate);

		return true;
	}

	EventListenerUser::EventListenerUser(std::string name) :VEEventListenerGLFW(name) {}

	EventListenerUser::~EventListenerUser() {}
}