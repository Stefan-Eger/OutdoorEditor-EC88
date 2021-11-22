#include "OEInclude.h"
namespace oe {
	void OutdoorEditor::addEntityAt(const std::string& entityName, const glm::vec3& pos)
	{
		std::string VEentityName = entityName + '_' + std::to_string(entityCounter++);
		if (entities.contains(VEentityName)) return;

		NatureEntity_t* info = enitityDatabase->getEntity(entityName);
		NatureEntity* newEntity = new NatureEntity(pos, info);

		

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);
		newEntity->createEntity(VEentityName, parentEntity);
		//parentEntity->multiplyTransform(glm::translate(pos));
		parentEntity->setPosition(pos);

		entities.emplace(VEentityName, newEntity);
	}
	void OutdoorEditor::removeEntitiesAt(const glm::vec3& pos)
	{
		for (auto it = entities.begin(); it != entities.end();) {
			float currentDistance = glm::length(it->second->getPos() - pos);
			float distance = activeBrush->getRadius();
			if (currentDistance < distance) {
				delete it->second;
				it = entities.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void OutdoorEditor::modifyTerrainVolumeWithActiveBrush(const glm::vec3& hitPos, bool subtractVolume)
	{
		float strength = subtractVolume ? 0.0f : 1.0f;
		activeBrush->setStrength(strength);

		auto affected = activeBrush->getAffected(hitPos);

		for (const auto& a : affected) {
			VoxelPoint oldVoxel = voxelManager->getVoxel(a.first);

			if (!subtractVolume && (oldVoxel.density < a.second)) {
				VoxelPoint voxel = VoxelPoint(a.second, 0);
				voxelManager->setVoxel(a.first, voxel);
			}
			if (subtractVolume && (a.second < oldVoxel.density)) {
				VoxelPoint voxel = VoxelPoint(a.second, 0);
				voxelManager->setVoxel(a.first, voxel);
			}
		}
		refresh();
	}

	OutdoorEditor::OutdoorEditor() {
		voxelManager = new VoxelManager();
		terrainManager = new TerrainManager(new MarchingCubes(voxelManager));
		enitityDatabase = new NatureEntityDatabase();

		brushes.push_back(new EditingBrushSphereFull(2.0f, 1.0f));
		brushes.push_back(new EditingBrushDrill(0.3f));
		brushes.push_back(new EditingBrushSphereSmooth(3.0f, 1.0f));
		entityCounter = 0;
		activeBrush = brushes.at(0);
		activeMode = oeEditingModes::TERRAIN_EDITING_TEXTURE_SPHERE_FULL;
	}
	OutdoorEditor::~OutdoorEditor(){

		for (const auto& b : brushes) {
			delete b;
		}
		brushes.clear();
		delete enitityDatabase;
		delete terrainManager;
		delete voxelManager;
	}

	void OutdoorEditor::refresh() const
	{
		auto chunks2Generate = voxelManager->getAllChunks2Refresh();
		std::size_t i = 0, chunkLoad = chunks2Generate.size();
		for (const auto& chunkPos : chunks2Generate) {
			VoxelChunkData* voxelChunk = voxelManager->findChunk(chunkPos);
			auto changedVoxels = voxelChunk->getChangedVoxels();

			//If too many Voxels have been changed than render the entire chunk
			if (changedVoxels.size() > CHUNKS_CHANGED_VOXELS_THRESHOLD) {
				terrainManager->updateChunkMesh(chunkPos);
				voxelChunk->clearChangedVoxels();
				std::cout << "Chunk Update " << i++ << "\t[" << chunkPos.X << ", " << chunkPos.Y << ", " << chunkPos.Z << "] \t of " << chunkLoad << " has been generated" << std::endl;
				continue;
			}
			//iterate through each changed voxel and generate its mesh
			for (const auto& voxelPos : changedVoxels) {
				auto worldVoxelPos = VoxelManager::local2World(voxelPos, chunkPos);
				terrainManager->updateCellsAroundVoxel(worldVoxelPos);
			}
			voxelChunk->clearChangedVoxels();

			std::cout << "Chunk Cell Update "<< i++ << "\t[" << chunkPos.X << ", " << chunkPos.Y << ", " << chunkPos.Z << "] \t of " << chunkLoad << " has been generated" << std::endl;
		}
		terrainManager->renderChangedChunks();
	}




	

	bool OutdoorEditor::traceRay(const Ray& ray, glm::vec3& outPos) const
	{

		//TODO Not very well implemented. find ways for speed up
		//travel from chunk to chunk and test ray/TriangleIntersection
		TerrainMeshChunk* oldMeshChunk = nullptr;
		float distance = 0.0f;
		while (distance < RAY_DISTANCE_MAX) {

			auto rayPos = ray.getPositionOnRay(distance);
			auto rayChunkCoordinates = VoxelManager::world2ChunkCoordinates(VoxelCoordinates((int)rayPos.x, (int)rayPos.y, (int)rayPos.z));


			TerrainMeshChunk* chunk = terrainManager->findChunk(rayChunkCoordinates);

			if ((chunk != nullptr) && (chunk != oldMeshChunk)) {
				oldMeshChunk = chunk;

				bool hit = chunk->traceRay(ray, outPos);
				if (hit) {
					return hit;
				}
			}
			distance += 1.0f;
		}
		return false;
	}

	void OutdoorEditor::handleInput(const glm::vec3& hitPos, const glm::vec3& direction, bool invertOperation)
	{
		switch (activeMode)
		{
		case oeEditingModes::TERRAIN_EDITING_VOLUME_SPHERE_FULL:
			removeEntitiesAt(hitPos);
			modifyTerrainVolumeWithActiveBrush(hitPos, invertOperation);
			break;
		case oeEditingModes::TERRAIN_EDITING_VOLUME_DRILL:
			removeEntitiesAt(hitPos);
			modifyTerrainVolumeWithActiveBrush(hitPos, invertOperation);
			break;
		case oeEditingModes::ENTITY_PLACEMENT_SINGLE_PLACEMENT: //TODO different models -> create Enums
			if (invertOperation) {
				removeEntitiesAt(hitPos);
				break;
			}
			addEntityAt("Pine_Tree", hitPos);
			break;
		case oeEditingModes::TERRAIN_EDITING_VOLUME_SPHERE_SMOOTH:
			removeEntitiesAt(hitPos);
			modifyTerrainVolumeWithActiveBrush(hitPos, invertOperation);
			break;
		case oeEditingModes::TERRAIN_EDITING_TEXTURE_SPHERE_FULL:
			break;
		default:
			std::cout << "Warning: Unknown Editing Mode" << std::endl;
			break;
		}

		
		/*
		VoxelPoint voxel = subtractVolume ? VoxelPoint(0.0f,0) : VoxelPoint(1.0f, 0);
		glm::vec3 newPos = subtractVolume ? glm::round(hitPos) : glm::round(hitPos - direction * 0.3f);

		VoxelCoordinates modifyVoxel(newPos.x, newPos.y, newPos.z);

		std::cout << "MODIFY VOXEL: " << modifyVoxel.X << ", " << modifyVoxel.Y << ", " << modifyVoxel.Z << std::endl;

		voxelManager->setVoxel(modifyVoxel, voxel);
		refresh();
		*/
	}
	TerrainManager* OutdoorEditor::getTerrainManager() const
	{
		return terrainManager;
	}

	VoxelManager* OutdoorEditor::getVoxelManager() const
	{
		return voxelManager;
	}

	OutdoorEditor::oeEditingModes OutdoorEditor::getEditingMode() const
	{
		return activeMode;
	}

	void OutdoorEditor::setEditingMode(const oeEditingModes& mode){
		activeMode = mode;

		const char* brushName = "";
		switch (activeMode)
		{
			case oeEditingModes::TERRAIN_EDITING_VOLUME_SPHERE_FULL:
				brushName = typeid(EditingBrushSphereFull).name();
				break;
			case oeEditingModes::TERRAIN_EDITING_VOLUME_DRILL:
				brushName = typeid(EditingBrushDrill).name();
				break;
			case oeEditingModes::ENTITY_PLACEMENT_SINGLE_PLACEMENT:
				brushName = typeid(EditingBrushDrill).name(); 
				break;
			case oeEditingModes::TERRAIN_EDITING_VOLUME_SPHERE_SMOOTH:
				brushName = typeid(EditingBrushSphereSmooth).name();
				break;
			case oeEditingModes::TERRAIN_EDITING_TEXTURE_SPHERE_FULL: //TODO IMPLEMENT
				activeBrush = nullptr;
				break;
			default:
				std::cout << "Warning: Unknown Editing Mode" << std::endl;
				break;
		}

		for (const auto& brush : brushes) {
			if (typeid(*brush).name() == brushName) {
				activeBrush = brush;
				break;
			}
		}

	}

	EditingBrush* OutdoorEditor::getActiveBrush() const
	{
		return activeBrush;
	}


};