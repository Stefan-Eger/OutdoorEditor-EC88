#include "OEInclude.h"

namespace oe {
	NatureEntityBillboard::NatureEntityBillboard(const std::string& entityName, const std::string& entityType, const glm::vec3& pos, NatureEntity_t* modelInfo) : NatureEntity(entityName, entityType, pos, modelInfo){}
	
	void NatureEntityBillboard::createEntity(VESceneNode* parent)
	{
		std::vector<vh::vhVertex> vertices;
		std::vector<uint32_t> indices;
		NatureEntity_t* billboardInfo = getModelInfo();
		
		vh::vhVertex billboard_vertice;
		billboard_vertice.pos = glm::vec3(0.0f,0.0f,0.0f);
		uint32_t index = 0;

		vertices.push_back(billboard_vertice);
		indices.push_back(index);

		std::string entityName = getEntityName();

		VEMesh* billmesh;
		VECHECKPOINTER(billmesh = getSceneManagerPointer()->createMesh(entityName + "_Mesh", vertices, indices));

		//Material with texture for billboard
		VEMaterial* billMaterial;
		VECHECKPOINTER(billMaterial = getSceneManagerPointer()->createMaterial(entityName + "_Material"));
		billMaterial->mapDiffuse = getSceneManagerPointer()->createTexture(entityName + "_Texture", billboardInfo->baseDirectory, billboardInfo->modelFileName);

		//getRenderer()->removeEntityFromSubrenderers(x);
		//getRenderer()->addEntityToSubrenderer(x); //Extend Entity Type enum for further subrenderes
		VEEntity* entity;
		VECHECKPOINTER(entity = getSceneManagerPointer()->createEntity(entityName, VEEntity::veEntityType::VE_ENTITY_TYPE_BILLBOARD, billmesh, billMaterial, parent));

	}
}