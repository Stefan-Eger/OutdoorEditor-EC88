#include "OEInclude.h"

namespace oe {
	NatureEntity::NatureEntity(const glm::vec3& pos, NatureEntity_t* modelInfo) : pos{pos}, modelInfo{ modelInfo }{}
	NatureEntity::~NatureEntity(){
		getSceneManagerPointer()->deleteSceneNodeAndChildren(entityName);
	}
	void NatureEntity::createEntity(const std::string& entityName, VESceneNode* parent)
	{
		VESceneNode* entity;
		VECHECKPOINTER(entity = getSceneManagerPointer()->loadModel(entityName, modelInfo->baseDirectory, modelInfo->modelFileName, modelInfo->aiFlags, parent));
		this->entityName = entityName;
	}
	NatureEntity_t* NatureEntity::getModelInfo() const {
		return modelInfo;
	}
	glm::vec3 NatureEntity::getPos() const {
		return pos;
	}
}