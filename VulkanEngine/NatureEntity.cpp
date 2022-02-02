#include "OEInclude.h"

namespace oe {
	NatureEntity::NatureEntity(const std::string& entityName, const glm::vec3& pos, const glm::vec3& dir, NatureEntity_t* modelInfo) : entityName{ entityName }, pos{ pos }, dir{dir}, modelInfo{ modelInfo }{}
	NatureEntity::~NatureEntity(){
		getSceneManagerPointer()->deleteSceneNodeAndChildren(entityName);
	}
	void NatureEntity::createEntity(VESceneNode* parent)
	{
		VESceneNode* entity;
		VECHECKPOINTER(entity = getSceneManagerPointer()->loadModel(entityName, modelInfo->baseDirectory, modelInfo->modelFileName, modelInfo->aiFlags, parent));

		parent->multiplyTransform(glm::scale(modelInfo->scale));
		parent->multiplyTransform(dir2RotationXZ(dir));
		parent->setPosition(pos);
	}

	glm::mat4 NatureEntity::dir2RotationXZ(const glm::vec3& dir)
	{
		float angle = std::atan2(dir.x, dir.z);
		return glm::rotate(angle, glm::vec3(0, 1.0, 0));
	}

	NatureEntity_t* NatureEntity::getModelInfo() const {
		return modelInfo;
	}
	glm::vec3 NatureEntity::getPos() const {
		return pos;
	}
	glm::vec3 NatureEntity::getDir() const
	{
		return dir;
	}

	std::string NatureEntity::getEntityName() const
	{
		return entityName;
	}

}