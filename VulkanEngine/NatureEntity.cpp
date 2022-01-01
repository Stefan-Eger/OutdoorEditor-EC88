#include "OEInclude.h"

namespace oe {
	NatureEntity::NatureEntity(const std::string& entityName, const std::string& entityType, const glm::vec3& pos, NatureEntity_t* modelInfo) : entityName{ entityName }, entityType{entityType}, pos{ pos }, modelInfo{ modelInfo }{}
	NatureEntity::~NatureEntity(){
		getSceneManagerPointer()->deleteSceneNodeAndChildren(entityName);
	}
	void NatureEntity::createEntity(VESceneNode* parent)
	{
		VESceneNode* entity;
		VECHECKPOINTER(entity = getSceneManagerPointer()->loadModel(entityName, modelInfo->baseDirectory, modelInfo->modelFileName, modelInfo->aiFlags, parent));
	}
	NatureEntity_t* NatureEntity::getModelInfo() const {
		return modelInfo;
	}
	glm::vec3 NatureEntity::getPos() const {
		return pos;
	}	
	std::string NatureEntity::getEntityName() const
	{
		return entityName;
	}

	std::string NatureEntity::getEntityType() const {
		return entityType;
	}
}