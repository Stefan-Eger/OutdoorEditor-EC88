#include "OEInclude.h"

namespace oe {
	NatureEntityDatabase::NatureEntityDatabase(){
		for (const auto& entry : database) {
			entities.emplace(entry.first, entry.second);
		}
	}
	NatureEntityDatabase::~NatureEntityDatabase()
	{
		for (const auto& e : entities) {
			delete e.second;
		}
		entities.clear();
	}
	void NatureEntityDatabase::addEntity(std::string name, NatureEntity_t* entity)
	{
		entities.emplace(name, entity);
	}
	NatureEntity_t* NatureEntityDatabase::getEntity(std::string name) const
	{

		if (entities.contains(name)) {
			return entities.at(name);
		}

		return nullptr;
	}
	std::vector<std::string> NatureEntityDatabase::getAllEntityNames() const
	{
		std::vector<std::string> ret;
		for (const auto& e : entities) {
			ret.push_back(e.first);
		}
		return ret;
	}
}