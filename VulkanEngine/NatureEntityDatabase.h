#ifndef NATURE_ENTITY_DATABASE_H
#define NATURE_ENTITY_DATABASE_H

using namespace ve;
namespace oe {
	class NatureEntityDatabase
	{
		std::unordered_map <std::string, NatureEntity_t*>  entities = {};
		
		std::vector<std::pair<std::string, NatureEntity_t*>> database = {
			
			{"Pine_Tree", new NatureEntity_t{ "media/models/editor/PineTree", "Tree_Pine.obj"}},

			//PINETREES
			{"Pine_Tree_01_Trunk", new NatureEntity_t{ "media/models/editor/PineTree", "Tree_Pine_01_Trunk.obj"}},
			{"Pine_Tree_01_Leafs", new NatureEntity_t{ "media/models/editor/PineTree", "Tree_Pine_01_Leafs.obj"}},
			{"Pine_Tree_02_Trunk", new NatureEntity_t{ "media/models/editor/PineTree", "Pine_Tree_02_Trunk.obj"}},
			{"Pine_Tree_02_Leafs", new NatureEntity_t{ "media/models/editor/PineTree", "Pine_Tree_02_Leafs.obj"}},

			//OAK TREE
			{"Oak_Tree_01_Trunk", new NatureEntity_t{ "media/models/editor/OakTree", "Oak_Tree_01_Trunk.obj"}},
			{"Oak_Tree_01_Leafs", new NatureEntity_t{ "media/models/editor/OakTree", "Oak_Tree_01_Leafs.obj"}},


			//STONES
			{"Stone_01", new NatureEntity_t{ "media/models/editor/Stones", "Stone_01.obj"}},
			{"Stone_02", new NatureEntity_t{ "media/models/editor/Stones", "Stone_02.obj"}},
			{"Stone_03", new NatureEntity_t{ "media/models/editor/Stones", "Stone_03.obj"}},


			//BILLBOARDS
			{"Bill_Board_Grass", new NatureEntity_t{ "media/models/editor/billboards", "grass_1.png"}}
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

