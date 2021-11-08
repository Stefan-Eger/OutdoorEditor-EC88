#include "OEInclude.h"

namespace oe {
	TerrainMeshChunk::TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates) : chunkCoordinates{chunkCoordinates} {
		chunkName = "Chunk[" + std::to_string(chunkCoordinates.X) + "," + std::to_string(chunkCoordinates.Y) + "," + std::to_string(chunkCoordinates.Z) + "]";
	}
	TerrainMeshChunk::~TerrainMeshChunk(){

		getSceneManagerPointer()->deleteSceneNodeAndChildren(chunkName);
		for (auto& cube : cubes) {
			std::string cubeName = chunkName + "Cube[" + std::to_string(cube.cubePos.X) + "," + std::to_string(cube.cubePos.Y) + "," + std::to_string(cube.cubePos.Z) + "]";
			getSceneManagerPointer()->deleteMesh(cubeName + "_Mesh");
			getSceneManagerPointer()->deleteMaterial(chunkName + "_Material");
		}
	}

	void TerrainMeshChunk::addCube(const MeshCube& cube)
	{
		cubes.push_back(cube);
	}
	
	void TerrainMeshChunk::clear(){
		for (auto& cube : cubes) {
			std::string cubeName = chunkName + "_Cube[" + std::to_string(cube.cubePos.X) + "," + std::to_string(cube.cubePos.Y) + "," + std::to_string(cube.cubePos.Z) + "]";
			getSceneManagerPointer()->deleteMesh(cubeName + "_Mesh");
		}
		getSceneManagerPointer()->deleteSceneNodeAndChildren(chunkName);
		cubes.clear();

	}
	void TerrainMeshChunk::renderChunk(){
		//Create Chunk SceneNode
		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* pChunkNodeParent;
		VECHECKPOINTER(pChunkNodeParent = getSceneManagerPointer()->createSceneNode(chunkName, pScene, glm::mat4(1.0)));
		glm::vec3 nextChunkPos = (chunkCoordinates * VoxelChunkData::CHUNK_SIZE).toVec3();
		pChunkNodeParent->multiplyTransform(glm::translate(glm::mat4(1.0f), nextChunkPos));

		//Create Mesh for each cube stored in cubes
		for (auto& cube : cubes) {
			std::string cubeName = chunkName + "_Cube[" + std::to_string(cube.cubePos.X) + "," + std::to_string(cube.cubePos.Y) + "," + std::to_string(cube.cubePos.Z) + "]";

			//Actual Engine Mesh generation (Creates only a mesh if there are vertices)
			VEMesh* cube_mesh = nullptr;
			if (cube.vertices.size() > 0) {
				VECHECKPOINTER(cube_mesh = getSceneManagerPointer()->createMesh(cubeName + "_Mesh", cube.vertices, cube.indices));
			}
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
			entity->multiplyTransform(glm::translate(glm::mat4(1.0f), cube.cubePos.toVec3()));
		}

	}
	VoxelCoordinates TerrainMeshChunk::getChunkCoordinates() const{
		return chunkCoordinates;
	}
	const std::vector<MeshCube>& TerrainMeshChunk::getCubes() const {
		return cubes;
	}

}