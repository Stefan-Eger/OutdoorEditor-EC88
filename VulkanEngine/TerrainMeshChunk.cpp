#include "OEInclude.h"

namespace oe {
	TerrainMeshChunk::TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates) : chunkCoordinates{chunkCoordinates} {
		chunkName = "Chunk[" + std::to_string(chunkCoordinates.X) + "," + std::to_string(chunkCoordinates.Y) + "," + std::to_string(chunkCoordinates.Z) + "]";
	}
	TerrainMeshChunk::~TerrainMeshChunk(){

		for (auto& cube : cubes) {
			std::string cubeName = chunkName + "_Cube[" + std::to_string(cube.first.X) + "," + std::to_string(cube.first.Y) + "," + std::to_string(cube.first.Z) + "]";
			getSceneManagerPointer()->deleteMesh(cubeName + "_Mesh");
			delete cube.second;
		}
		getSceneManagerPointer()->deleteSceneNodeAndChildren(chunkName);
	}

	void TerrainMeshChunk::insertOrAssignCube(const VoxelCoordinates& cellPos, MeshCell* cell){
		if (cubes.count(cellPos) > 0) {
			MeshCell* pMesh = cubes.at(cellPos);
			delete pMesh;

			if (cell->vertices.size() <= 0) {
				cubes.erase(cellPos);
				return;
			}
		}

		if (cell->vertices.size() <= 0) return;
		
		auto isAssigned = cubes.insert_or_assign(cellPos, cell);
	}
	

	void TerrainMeshChunk::meshCleanup() {
		for (auto& name : meshNames) {
			getSceneManagerPointer()->deleteMesh(name + "_Mesh");
		}
		getSceneManagerPointer()->deleteSceneNodeAndChildren(chunkName);
		meshNames.clear();
	}

	void TerrainMeshChunk::clear(){
		cubes.clear();
	}

	void TerrainMeshChunk::renderChunk(){
		meshCleanup();

		//Create Chunk SceneNode
		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* pChunkNodeParent;
		VECHECKPOINTER(pChunkNodeParent = getSceneManagerPointer()->createSceneNode(chunkName, pScene, glm::mat4(1.0)));
		glm::vec3 nextChunkPos = (chunkCoordinates * VoxelChunkData::CHUNK_SIZE).toVec3();
		pChunkNodeParent->multiplyTransform(glm::translate(glm::mat4(1.0f), nextChunkPos));


		//Create Mesh for each cube stored in cubes
		for (auto& cube : cubes) {
			std::string cubeName = chunkName + "_Cube[" + std::to_string(cube.first.X) + "," + std::to_string(cube.first.Y) + "," + std::to_string(cube.first.Z) + "]";
			meshNames.push_back(cubeName);

			//Actual Engine Mesh generation (Creates only a mesh if there are vertices)
			VEMesh* cube_mesh = nullptr;
			VECHECKPOINTER(cube_mesh = getSceneManagerPointer()->createMesh(cubeName + "_Mesh", cube.second->vertices, cube.second->indices));
			//VEMaterial* cube_material = cube->material;

			//TODO Make small Material Database
			//VESubrendererFW_D -> Texture is not rendered yet only to test vertex normals
			VEMaterial* cube_material;
			VECHECKPOINTER(cube_material = getSceneManagerPointer()->createMaterial("_Material"));
			VECHECKPOINTER(cube_material->mapDiffuse = getSceneManagerPointer()->createTexture("_Texture_1", "media/models/editor/TerrainTextures", "grass.png"));
			cube_material->color = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);

			//CreateCube Entity
			VEEntity* entity;
			VECHECKPOINTER(entity = getSceneManagerPointer()->createEntity(cubeName + "_Entity", VEEntity::veEntityType::VE_ENTITY_TYPE_VOXEL_TERRAIN, cube_mesh, cube_material, pChunkNodeParent));
			entity->multiplyTransform(glm::translate(glm::mat4(1.0f), cube.first.toVec3()));
			
		}

	}
	VoxelCoordinates TerrainMeshChunk::getChunkCoordinates() const{
		return chunkCoordinates;
	}

	std::vector<std::pair<VoxelCoordinates, MeshCell*>> TerrainMeshChunk::getChunkMesh() const
	{
		std::vector<std::pair<VoxelCoordinates, MeshCell*>> ret;

		for (auto& cube : cubes) {
			ret.push_back(cube);
		}
		
		return ret;
	}
	

}