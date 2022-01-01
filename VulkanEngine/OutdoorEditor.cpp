#include "OEInclude.h"
namespace oe {

	void OutdoorEditor::changeTerrainMaterial(const glm::vec3& hitPos)
	{
		activeBrush->setStrength(1.0f);

		auto affected = activeBrush->getAffected(hitPos);

		for (const auto& a : affected) {
			VoxelPoint oldVoxel = voxelManager->getVoxel(a.first);
			VoxelPoint voxel = VoxelPoint(oldVoxel.density, selectedMaterial);
			voxelManager->setVoxel(a.first, voxel);
		}
		refresh();
	}

	void OutdoorEditor::modifyTerrainVolumeWithActiveBrush(const glm::vec3& hitPos, bool subtractVolume)
	{
		float strength = subtractVolume ? 0.0f : 1.0f;
		activeBrush->setStrength(strength);

		auto affected = activeBrush->getAffected(hitPos);

		for (const auto& a : affected) {
			VoxelPoint oldVoxel = voxelManager->getVoxel(a.first);

			if (!subtractVolume && (oldVoxel.density < a.second)) {
				VoxelPoint voxel = VoxelPoint(a.second, selectedMaterial);
				voxelManager->setVoxel(a.first, voxel);
			}
			if (subtractVolume && (a.second < oldVoxel.density)) {
				VoxelPoint voxel = VoxelPoint(a.second, selectedMaterial);
				voxelManager->setVoxel(a.first, voxel);
			}
		}
		refresh();
	}

	OutdoorEditor::OutdoorEditor() {
		voxelManager = new VoxelManager();
		terrainManager = new TerrainManager(new MarchingCubes(voxelManager));
		entityManager = new NatureEntityManager();

		brushes.push_back(new EditingBrushSphereFull(2.0f, 1.0f));
		brushes.push_back(new EditingBrushDrill(0.3f));
		brushes.push_back(new EditingBrushSphereSmooth(3.0f, 1.0f));
		activeBrush = brushes.at(0);
		selectedMaterial = 0;
		activeMode = oeEditingModes::TERRAIN_EDITING_TEXTURE;
		activeBrushMode = oeBrushModes::BRUSH_DRILL;
		selectedModel = oeEntityModel::PINE_TREE;
		editModeChanged = false;
	}
	OutdoorEditor::~OutdoorEditor(){

		for (auto& b : brushes) {
			delete b;
		}
		brushes.clear();
		delete entityManager;
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
		case oeEditingModes::TERRAIN_EDITING_VOLUME:
			entityManager->removeEntitiesAt(hitPos, activeBrush->getRadius());
			modifyTerrainVolumeWithActiveBrush(hitPos, invertOperation);
			break;
		case oeEditingModes::TREE_PLACEMENT:
		case oeEditingModes::BILLBOARD_PLACEMENT:
			if (invertOperation) {
				entityManager->removeEntitiesAt(hitPos, activeBrush->getRadius());
				break;
			}
			entityManager->addNatureEntity(selectedModel, hitPos);
			break;
		case oeEditingModes::TERRAIN_EDITING_TEXTURE:
			changeTerrainMaterial(hitPos);
			break;
		default:
			std::cout << "Warning: Unknown Editing Mode" << std::endl;
			break;
		}
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
		editModeChanged = true;
		const char* brushName = "";
		switch (activeMode)
		{
			case oeEditingModes::TERRAIN_EDITING_VOLUME:
				setBrushMode(oeBrushModes::BRUSH_SPHERE_FULL);
				break;
			case oeEditingModes::TREE_PLACEMENT:
				setBrushMode(oeBrushModes::BRUSH_DRILL);
				break;
			case oeEditingModes::BILLBOARD_PLACEMENT:
				setBrushMode(oeBrushModes::BRUSH_DRILL);
				break;
			case oeEditingModes::TERRAIN_EDITING_TEXTURE:
				setBrushMode(oeBrushModes::BRUSH_SPHERE_FULL);
				break;
			default:
				std::cout << "Warning: Unknown Editing Mode" << std::endl;
				break;
		}
	}

	void OutdoorEditor::setActiveMaterial(const oeTerrainMaterial& terrainMaterial)
	{
		selectedMaterial = static_cast<std::size_t>(terrainMaterial);
	}

	EditingBrush* OutdoorEditor::getActiveBrush() const
	{
		return activeBrush;
	}

	void OutdoorEditor::setActiveModel(const oeEntityModel& model)
	{
		selectedModel = model;
	}

	void OutdoorEditor::setBrushMode(const oeBrushModes& brushMode)
	{

		const char* brushName = "";
		if (activeMode == oeEditingModes::TERRAIN_EDITING_VOLUME || editModeChanged) {
			this->activeBrushMode = brushMode;
			editModeChanged = false;
			switch (brushMode)
			{
			case oeBrushModes::BRUSH_DRILL:
				brushName = typeid(EditingBrushDrill).name();
				
				break;
			case oeBrushModes::BRUSH_SPHERE_FULL:
				brushName = typeid(EditingBrushSphereFull).name();
				break;
			case oeBrushModes::BRUSH_SPHERE_SMOOTH:
				brushName = typeid(EditingBrushSphereSmooth).name();
				break;
			default:
				std::cout << "Warning: Unknown Brush Mode" << std::endl;
				break;
			}
		}
		for (const auto& brush : brushes) {
			if (typeid(*brush).name() == brushName) {
				activeBrush = brush;
				break;
			}
		}
	}

	OutdoorEditor::oeBrushModes OutdoorEditor::getBrushMode() const
	{
		return activeBrushMode;
	}

	void OutdoorEditor::save(const std::string& path, const std::string& filename) const
	{
		//Open File
		std::ofstream ofs(path + "/" + filename + ".json", std::ios::out);
		//JSON Serializer
		nlohmann::json serialize;
		nlohmann::json voxelData;
		nlohmann::json entityData;

		auto timeNow = vh::vhTimeNow();

		std::cout << "Saving in Progress..." << std::endl;
		std::cout << "Time Duration[" << vh::vhTimeDuration(timeNow) << "]" << std::endl;
		//Write VoxelData
		serialize["VoxelData"] = voxelManager->save(voxelData);
		std::cout << "Voxel Data Saved" << std::endl;
		std::cout << "Time Duration[" << vh::vhTimeDuration(timeNow) << "]" << std::endl;

		//Write Models
		serialize["EntityData"] = entityManager->save(entityData);
		std::cout << "Nature Entities Saved" << std::endl;
		std::cout << "Time Duration[" << vh::vhTimeDuration(timeNow) << "]" << std::endl;
		
		//Write JSON Data to File
		ofs << std::setw(2) << serialize;

		//Close File
		ofs.close();
		std::cout << "Save Finished "<< std::endl;
		std::cout << "Time Duration[" << vh::vhTimeDuration(timeNow) << "]" << std::endl;
	}

	void OutdoorEditor::load(const std::string& path, const std::string& filename)
	{

		//Import Data
		std::ifstream file(path + "/" + filename + ".json", std::ios::in);
		nlohmann::json deserialize;
		file >> deserialize;
		file.close();

		//Update with Imported VoxelData
		/*
		voxelManager->clear();

		voxelManager->addChunk();
		voxelManager->setVoxel();
		voxelManager->setVoxel();
		*/
			
		//Update with Imported Entities

	}
};