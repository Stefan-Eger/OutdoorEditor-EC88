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
		for (const auto& entity : entities) {
			delete entity.second.second;
		}
		entities.clear();
	}
	void NatureEntityManager::addTreeAt(const oeEntityModel& type, const std::string& treeName, const glm::vec3& pos)
	{
		std::string VEentityName = treeName + '_' + std::to_string(entityCounter++);
		if (entities.contains(VEentityName)) return;

		NatureEntity_t* infoTrunk = enitityDatabase->getEntity(treeName + "_Trunk");
		NatureEntity_t* infoLeafs = enitityDatabase->getEntity(treeName + "_Leafs");
		NatureEntity* newEntity = new NatureEntityTree(VEentityName, pos, infoTrunk, infoLeafs);

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);
		newEntity->createEntity(parentEntity);
		//parentEntity->multiplyTransform(glm::translate(pos));
		parentEntity->setPosition(pos);

		entities.emplace(VEentityName, std::make_pair(type,newEntity));
	}
	void NatureEntityManager::addBillboardAt(const oeEntityModel& type, const std::string& billboardName, const glm::vec3& pos)
	{
		std::string VEentityName = billboardName + '_' + std::to_string(entityCounter++);
		if (entities.contains(VEentityName)) return;

		NatureEntity_t* billboardInfo = enitityDatabase->getEntity(billboardName);
		NatureEntity* newEntity = new NatureEntityBillboard(VEentityName, pos, billboardInfo);

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);
		newEntity->createEntity(parentEntity);
		//TODO RESIZE BILLBOARDS
		//parentEntity->multiplyTransform(glm::scale(glm::vec3(0.5f,0.5f,0.5f)));
		parentEntity->setPosition(pos);

		entities.emplace(VEentityName, std::make_pair(type, newEntity));
	}
	void NatureEntityManager::addObject(const oeEntityModel& type, const std::string& objectName, const glm::vec3& pos)
	{
		std::string VEentityName = objectName + '_' + std::to_string(entityCounter++);
		if (entities.contains(VEentityName)) return;

		NatureEntity_t* infoObj = enitityDatabase->getEntity(objectName);
		NatureEntity* newEntity = new NatureEntity(VEentityName, pos, infoObj);

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);
		newEntity->createEntity(parentEntity);
		//parentEntity->multiplyTransform(glm::translate(pos));
		parentEntity->setPosition(pos);
	}
	void NatureEntityManager::addNatureEntity(const oeEntityModel& entity, const glm::vec3& pos)
	{
		int index = static_cast<int>(entity);
		std::string databaseName = modelTypes.at(index);
		switch (entity)
		{
		case oeEntityModel::PINE_TREE_01:
			addTreeAt(entity, databaseName, pos);
			break;
		case oeEntityModel::PINE_TREE_02:
			addTreeAt(entity, databaseName, pos);
			break;
		case oeEntityModel::OAK_TREE_01:
			addTreeAt(entity, databaseName, pos);
			break;
		case oeEntityModel::BILLBOARD_GRASS_01:
			addBillboardAt(entity, databaseName, pos);
			break;
		case oeEntityModel::STONE_01:
			addObject(entity, databaseName, pos);
			break;
		case oeEntityModel::STONE_02:
			addObject(entity, databaseName, pos);
			break;
		case oeEntityModel::STONE_03:
			addObject(entity, databaseName, pos);
			break;
		default:
			break;
		}
	}
	void NatureEntityManager::removeEntitiesAt(const glm::vec3& pos, const float& radius)
	{
		for (auto it = entities.begin(); it != entities.end();) {
			float currentDistance = glm::length(it->second.second->getPos() - pos);
			if (currentDistance < radius) {
				delete it->second.second;
				it = entities.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void NatureEntityManager::clear()
	{
		for (const auto& entity : entities) {
			delete entity.second.second;
		}
		entities.clear();
	}

	nlohmann::json& NatureEntityManager::save(nlohmann::json& serializer) const
	{
		nlohmann::json entityData;
		for (const auto& entity : entities) {
			glm::vec3 pos = entity.second.second->getPos();

			entityData["EntityType"] = entity.second.first;
			entityData["Position"] = { pos.x, pos.y, pos.z };

			serializer.push_back(entityData);
		}
		return serializer;
	}

	void NatureEntityManager::load(nlohmann::json& serializer)
	{
		clear();
		for (nlohmann::json::iterator it = serializer.begin(); it != serializer.end(); ++it) {

			oeEntityModel type;
			int t = (*it)["EntityType"].get<int>();
			type = static_cast<oeEntityModel>(t);


			glm::vec3 pos;
			pos.x = (*it)["Position"].at(0).get<float>();
			pos.y = (*it)["Position"].at(1).get<float>();
			pos.z = (*it)["Position"].at(2).get<float>();

			addNatureEntity(type, pos);
		}
	}

}