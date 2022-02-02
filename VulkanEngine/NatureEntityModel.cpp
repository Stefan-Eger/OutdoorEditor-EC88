#include "OEInclude.h"

namespace oe {

	NatureEntityModel::NatureEntityModel(const std::string& entityName, const glm::vec3& pos, const std::vector<NatureEntity*>& entities) : NatureEntity(entityName, pos, glm::vec3(0.0f, 0.0f, 0.0f), nullptr), entities {entities} {}
	NatureEntityModel::~NatureEntityModel()
	{
		for (auto& e : entities) {
			delete e;
		}
		entities.clear();
	}
	void NatureEntityModel::createEntity(VESceneNode* parent){

		for (const auto& e : entities) {
			e->createEntity(parent);
		}
	}

	void NatureEntityModel::addEntity(NatureEntity* entity)
	{
		entities.push_back(entity);
	}
	void NatureEntityModel::removeEntity(std::string& entityName)
	{
		for (auto it = entities.begin(); it != entities.end(); ) {
			
			if ((*it)->getEntityName() == entityName) {
				it = entities.erase(it);
			}
			else {
				++it;
			}
		}
	}
	void NatureEntityModel::clear()
	{
		for (auto& e : entities) {
			delete e;
		}
		entities.clear();
	}
}