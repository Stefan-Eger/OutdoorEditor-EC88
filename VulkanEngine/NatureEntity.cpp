#include "OEInclude.h"

namespace oe {
	NatureEntity::NatureEntity(const glm::vec3& pos, NatureEntity_t* modelInfo) : pos{pos}, modelInfo{ modelInfo }
	{
	}
	NatureEntity::~NatureEntity(){
		getSceneManagerPointer()->deleteSceneNodeAndChildren(entity->getName());
	}
	void NatureEntity::createEntity(const std::string& entityName, VESceneNode* parent)
	{
		VECHECKPOINTER(entity = getSceneManagerPointer()->loadModel(entityName, modelInfo->baseDirectory, modelInfo->modelFileName, modelInfo->aiFlags, parent));
	}
	NatureEntity_t* NatureEntity::getModelInfo() const {
		return modelInfo;
	}
	glm::vec3 NatureEntity::getPos() const {
		return pos;
	}
}