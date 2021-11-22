#ifndef NATURE_ENTITY_DATABASE_H
#define NATURE_ENTITY_DATABASE_H

using namespace ve;
namespace oe {
	class NatureEntityDatabase
	{
		std::unordered_map <std::string, NatureEntity_t*>  entities = {};
		
		const std::vector<std::pair<std::string, NatureEntity_t*>> database = {
			{"Pine_Tree", new NatureEntity_t{ "media/models/editor/PineTree", "Tree_Pine.obj"}}
		};
		



	public:
		NatureEntityDatabase();
		~NatureEntityDatabase();

		void addEntity(std::string name, NatureEntity_t* entity);
		NatureEntity_t* getEntity(std::string name) const;
		std::vector<std::string> getAllEntityNames() const;
		
	};
}
#endif

