#include "OEInclude.h"

namespace oe {
	TerrainMeshChunk::TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates) : chunkCoordinates{chunkCoordinates}, verticeCount{ 0 } {
		chunkName = "Chunk[" + std::to_string(chunkCoordinates.X) + "," + std::to_string(chunkCoordinates.Y) + "," + std::to_string(chunkCoordinates.Z) + "]";
	}
	TerrainMeshChunk::~TerrainMeshChunk(){
		getSceneManagerPointer()->deleteSceneNodeAndChildren(chunkName);
		getSceneManagerPointer()->deleteMesh(chunkName + "_Mesh");
	}

	void TerrainMeshChunk::addVertice(const vh::vhVertex& vertice)
	{
		vertices.push_back(vertice);
		indices.push_back(verticeCount++);
	}
	void TerrainMeshChunk::clear()
	{
		vertices.clear();
		indices.clear();
		verticeCount = 0;
		getSceneManagerPointer()->deleteSceneNodeAndChildren(chunkName);
		getSceneManagerPointer()->deleteMesh(chunkName + "_Mesh" );
	}
	void TerrainMeshChunk::createSceneNode()
	{
		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* pChunkNodeParent;
		VECHECKPOINTER(pChunkNodeParent = getSceneManagerPointer()->createSceneNode(chunkName, pScene, glm::mat4(1.0)));
		glm::vec3 nextChunkPos = (chunkCoordinates * VoxelChunkData::CHUNK_SIZE).toVec3();
		pChunkNodeParent->multiplyTransform(glm::translate(glm::mat4(1.0f), nextChunkPos));

		//Actual Engine Mesh generation
		VEMesh* chunk_mesh;
		VECHECKPOINTER(chunk_mesh = getSceneManagerPointer()->createMesh(chunkName + "_Mesh", vertices, indices));

		//VESubrendererFW_D -> Texture is not rendered yet only to test vertex normals
 		VEMaterial* chunk_material;
		VECHECKPOINTER(chunk_material = getSceneManagerPointer()->createMaterial(chunkName + "_Material"));
		chunk_material->mapDiffuse = getSceneManagerPointer()->createTexture(chunkName + "_Texture_1", "media/models/editor/TerrainTextures", "grass.png");
		chunk_material->color = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);

		VEEntity* entity;
		VECHECKPOINTER(entity = getSceneManagerPointer()->createEntity(chunkName+"_Entity", VEEntity::veEntityType::VE_ENTITY_TYPE_NORMAL, chunk_mesh, chunk_material, pChunkNodeParent));
		entity->m_castsShadow = false;
	}
	VoxelCoordinates TerrainMeshChunk::getChunkCoordinates() const
	{
		return chunkCoordinates;
	}
	const std::vector<vh::vhVertex> TerrainMeshChunk::getVertices() const
	{
		return vertices;
	}
	const std::vector<uint32_t> TerrainMeshChunk::getIndices() const {
		return indices;
	}


}