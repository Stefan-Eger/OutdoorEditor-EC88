#include "OEInclude.h"

namespace oe {
	NatureEntityManager::NatureEntityManager()
	{
		enitityDatabase = new NatureEntityDatabase();
		entityCounter = 0;
	}
	NatureEntityManager::~NatureEntityManager()
	{
		delete enitityDatabase;
	}
	void NatureEntityManager::addTreeAt(const std::string& treeName, const glm::vec3& pos)
	{
		std::string VEentityName = treeName + '_' + std::to_string(entityCounter++);
		if (entities.contains(VEentityName)) return;

		NatureEntity_t* infoTrunk = enitityDatabase->getEntity(treeName + "_Trunk");
		NatureEntity_t* infoLeafs = enitityDatabase->getEntity(treeName + "_Leafs");
		NatureEntity* newEntity = new NatureEntityTree(VEentityName, treeName, pos, infoTrunk, infoLeafs);

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);
		newEntity->createEntity(parentEntity);
		//parentEntity->multiplyTransform(glm::translate(pos));
		parentEntity->setPosition(pos);

		entities.emplace(VEentityName, newEntity);
	}
	void NatureEntityManager::addBillboardAt(const std::string& billboardName, const glm::vec3& pos)
	{
		std::string VEentityName = billboardName + '_' + std::to_string(entityCounter++);
		if (entities.contains(VEentityName)) return;

		NatureEntity_t* billboardInfo = enitityDatabase->getEntity(billboardName);
		NatureEntity* newEntity = new NatureEntityBillboard(VEentityName, billboardName, pos, billboardInfo);

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);
		newEntity->createEntity(parentEntity);
		//TODO RESIZE BILLBOARDS
		//parentEntity->multiplyTransform(glm::scale(glm::vec3(0.5f,0.5f,0.5f)));
		parentEntity->setPosition(pos);

		entities.emplace(VEentityName, newEntity);
	}
	void NatureEntityManager::addNatureEntity(const oeEntityModel& entity, const glm::vec3& pos)
	{
		int index = static_cast<int>(entity);
		std::string type = modelType.at(index);
		switch (entity)
		{
		case oeEntityModel::PINE_TREE:
			addTreeAt(type, pos);
			break;
		case oeEntityModel::BILLBOARD_GRASS_01:
			addBillboardAt(type, pos);
			break;
		default:
			break;
		}
	}
	void NatureEntityManager::removeEntitiesAt(const glm::vec3& pos, const float& radius)
	{
		for (auto it = entities.begin(); it != entities.end();) {
			float currentDistance = glm::length(it->second->getPos() - pos);
			if (currentDistance < radius) {
				delete it->second;
				it = entities.erase(it);
			}
			else {
				++it;
			}
		}
	}

	nlohmann::json& NatureEntityManager::save(nlohmann::json& serializer) const
	{
		nlohmann::json entityData;
		for (const auto& entity : entities) {
			glm::vec3 pos = entity.second->getPos();

			entityData["EntityType"] = entity.second->getEntityType() ;
			entityData["Position"] = { pos.x, pos.y, pos.z };

			serializer.push_back(entityData);
		}
		return serializer;
	}

}