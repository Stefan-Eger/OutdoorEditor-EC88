#include "OEInclude.h"
namespace oe {
	OutdoorEditor::OutdoorEditor() {
		voxelManager = new VoxelManager();
		terrainManager = new TerrainManager(new MarchingCubes(voxelManager));
	}
	OutdoorEditor::~OutdoorEditor(){
		delete voxelManager;
		delete terrainManager;
	}

	void OutdoorEditor::generateAll() const
	{
		terrainManager->clear();
		auto chunks2Generate = voxelManager->getAllChunks2Generate();
		std::size_t i = 0, chunkLoad = chunks2Generate.size();
		for (const auto& chunk : chunks2Generate) {
			terrainManager->createChunkMesh(chunk);
			std::cout << "Chunk "<< i++ << "\t[" << chunk.X << ", " << chunk.Y << ", " << chunk.Z << "] \t of " << chunkLoad << " has been generated" << std::endl;
		}
	}

	bool OutdoorEditor::traceRay(const Ray& ray, glm::vec3& outPos) const
	{
		glm::vec3 origin = ray.getOrigin();

		VoxelManager::world2ChunkCoordinates(VoxelCoordinates((int)origin.x, (int)origin.y, (int)origin.z));

		return false;
	}

	TerrainManager* OutdoorEditor::getTerrainManager() const
	{
		return terrainManager;
	}

	VoxelManager* OutdoorEditor::getVoxelManager() const
	{
		return voxelManager;
	}

};