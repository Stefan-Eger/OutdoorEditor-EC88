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
		NatureEntity* newEntityTrunk = new NatureEntity(VEentityName, pos, glm::vec3(0.0f, 0.0f, 0.0f), infoTrunk);
		NatureEntity* newEntityLeafs = new NatureEntityLeafs(VEentityName, pos, infoLeafs);

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);

		NatureEntity* tree = new NatureEntityModel(VEentityName, pos, {newEntityTrunk, newEntityLeafs});
		tree->createEntity(parentEntity);
		entities.emplace(VEentityName, std::make_pair(type, tree));
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

		entities.emplace(VEentityName, std::make_pair(type, newEntity));
	}

	void NatureEntityManager::addObject(const oeEntityModel& type, const std::string& objectName, const glm::vec3& pos, const glm::vec3& dir)
	{
		std::string VEentityName = objectName + '_' + std::to_string(entityCounter++);
		if (entities.contains(VEentityName)) return;

		NatureEntity_t* infoObj = enitityDatabase->getEntity(objectName);
		NatureEntity* newEntity = new NatureEntity(VEentityName, pos, dir, infoObj);

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);
		newEntity->createEntity(parentEntity);
		entities.emplace(VEentityName, std::make_pair(type, newEntity));
	}
	void NatureEntityManager::addBush(const oeEntityModel& type, const std::string& objectName, const glm::vec3& pos)
	{
		std::string VEentityName = objectName + '_' + std::to_string(entityCounter++);
		if (entities.contains(VEentityName)) return;

		NatureEntity_t* bushInfo = enitityDatabase->getEntity(objectName);
		NatureEntity* newEntityBush = new NatureEntityLeafs(VEentityName, pos, bushInfo);

		auto pScene = getSceneManagerPointer()->getSceneNode("Scene");
		VESceneNode* parentEntity = getSceneManagerPointer()->createSceneNode(VEentityName + "_Parent", pScene);
		newEntityBush->createEntity(parentEntity);

		entities.emplace(VEentityName, std::make_pair(type, newEntityBush));
	}
	void NatureEntityManager::addNatureEntity(const oeEntityModel& entity, const glm::vec3& pos, const glm::vec3& dir)
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
			addObject(entity, databaseName, pos, dir);
			break;
		case oeEntityModel::STONE_02:
			addObject(entity, databaseName, pos, dir);
			break;
		case oeEntityModel::STONE_03:
			addObject(entity, databaseName, pos, dir);
			break;
		case oeEntityModel::WOLVE:
			addObject(entity, databaseName, pos, dir);
			break;
		case oeEntityModel::STAG:
			addObject(entity, databaseName, pos, dir);
			break;
		case oeEntityModel::BUSH_01:
			addBush(entity, databaseName, pos);
			break;
		case oeEntityModel::BUSH_02:
			addBush(entity, databaseName, pos);
			break;
		case oeEntityModel::BUSH_03:
			addBush(entity, databaseName, pos);
			break;
		case oeEntityModel::BUSH_04:
			addBush(entity, databaseName, pos);
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
			glm::vec3 dir = entity.second.second->getDir();

			entityData["EntityType"] = entity.second.first;
			entityData["Position"] = { pos.x, pos.y, pos.z };
			entityData["Direction"] = { dir.x, dir.y, dir.z };

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


			glm::vec3 dir;
			dir.x = (*it)["Direction"].at(0).get<float>();
			dir.y = (*it)["Direction"].at(1).get<float>();
			dir.z = (*it)["Direction"].at(2).get<float>();

			addNatureEntity(type, pos, dir);
		}
	}

}