#include "OEInclude.h"


namespace oe {
	void OutdoorEditorEngine::registerEventListeners() {
		//VEEngine::registerEventListeners();

		registerEventListener(new EventListenerUser("StandardEventListener"));
		registerEventListener(new EventListenerGUI("GUI"), { veEvent::VE_EVENT_DRAW_OVERLAY });
	}
	void OutdoorEditorEngine::loadLevel(uint32_t numLevel) {
		VEEngine::loadLevel(numLevel);			//create standard cameras and lights

		VESceneNode* pScene;
		VECHECKPOINTER(pScene = getSceneManagerPointer()->createSceneNode("Scene", getRoot()));

		//scene models
		VESceneNode* sp1;
		VECHECKPOINTER(sp1 = getSceneManagerPointer()->createSkybox("The Sky", "media/models/test/sky/cloudy",
			{ "bluecloud_ft.jpg", "bluecloud_bk.jpg", "bluecloud_up.jpg",
				"bluecloud_dn.jpg", "bluecloud_rt.jpg", "bluecloud_lf.jpg" }, pScene));



		//Camera
		//StandardCameraParent -> Translation
		VESceneNode* cameraParent = getSceneManagerPointer()->getSceneNode("StandardCameraParent");
		cameraParent->setPosition(OutdoorEditorInfo::CAMERA_POS_ORIGIN);

		//Standard Camera -> Rotation
		VESceneNode* camera = getSceneManagerPointer()->getSceneNode("StandardCamera");
		camera->multiplyTransform(glm::rotate(OutdoorEditorInfo::CAMERA_X_AXIS_THETA, glm::vec3(1.0f, 0.0f, 0.0f)));



		OutdoorEditorInfo::editor = new OutdoorEditor();
		auto voxelManager = OutdoorEditorInfo::editor->getVoxelManager();
		std::cout << "Load Editor" << std::endl;
		

		voxelManager->addChunk(VoxelCoordinates(0,0,0));
		voxelManager->setVoxel(VoxelCoordinates(1, 1, 1), VoxelPoint(1.0f, 1));

		voxelManager->setVoxel(VoxelCoordinates(2, 1, 1), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(1, 2, 1), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(1, 1, 2), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(2, 2, 1), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(2, 1, 2), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(2, 2, 2), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(1, 2, 2), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(3, 1, 1), VoxelPoint(1.0f, 1));
		
		voxelManager->addChunk(VoxelCoordinates(1, 0, 0));
		voxelManager->setVoxel(VoxelCoordinates(4, 1, 1), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(5, 1, 1), VoxelPoint(1.0f, 1));
		voxelManager->setVoxel(VoxelCoordinates(6, 1, 1), VoxelPoint(1.0f, 1));
		
		OutdoorEditorInfo::editor->refresh();
		


		/*
		OutdoorEditorInfo::world->setChunkAt(VoxelCoordinates(0, 0, 0));

		for (auto x = 0; x < WORLD_CHUNKS_WIDTH; ++x) {
			for (auto y = 0; y < WORLD_CHUNKS_HEIGHT; ++y) {
				for (auto z = 0; z < WORLD_CHUNKS_DEPTH; ++z) {
					if (y - 1 < 0) {
						OutdoorEditorInfo::world->setChunkAt(VoxelCoordinates(x, y - 1, z), VoxelPoint(1.0f, 1));
					}
					else {
						OutdoorEditorInfo::world->setChunkAt(VoxelCoordinates(x, y - 1, z));
					}
				}
			}
		}
		OutdoorEditorInfo::world->generateAll();
		*/

		/*
		VoxelCoordinates offset(-1, -1, 0);

		for (auto x = 0; x < WORLD_CHUNKS_WIDTH; ++x) {
			for (auto y = 0; y < WORLD_CHUNKS_HEIGHT; ++y) {
				for (auto z = 0; z < WORLD_CHUNKS_DEPTH; ++z) {
					if ((y + offset.Y) < 0)
						OutdoorEditorInfo::editor->getVoxelManager()->addChunk(VoxelCoordinates(x, y, z) + offset, VoxelPoint(1.0f, 0));
					else
						OutdoorEditorInfo::editor->getVoxelManager()->addChunk(VoxelCoordinates(x, y, z) + offset);
				}
			}
		}
		OutdoorEditorInfo::editor->generateAll();
		*/
	}
	void OutdoorEditorEngine::end()
	{
		VEEngine::end();
		OutdoorEditorInfo::exit();
	}
}