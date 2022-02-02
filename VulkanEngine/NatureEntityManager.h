#ifndef NATURE_ENTITY_MANAGER
#define NATURE_ENTITY_MANAGER

namespace oe {

	enum class oeEntityModel {
		PINE_TREE_01,
		PINE_TREE_02,
		OAK_TREE_01,
		BILLBOARD_GRASS_01,
		STONE_01,
		STONE_02,
		STONE_03,
		WOLVE,
		STAG,
		BUSH_01,
		BUSH_02,
		BUSH_03,
		BUSH_04
	};

	class NatureEntityManager
	{
		NatureEntityDatabase* enitityDatabase;

		//Entity management
		//<Entity name, <entityType,entity>>
		std::unordered_map<std::string, std::pair<oeEntityModel, NatureEntity*>> entities;
		std::unordered_map <oeEntityModel, NatureEntity*> toSave;

		std::size_t entityCounter;

		const std::vector<std::string> modelTypes = {
			"Pine_Tree_01",
			"Pine_Tree_02",
			"Oak_Tree_01",
			"Bill_Board_Grass",
			"Stone_01",
			"Stone_02",
			"Stone_03",
			"Wolve",
			"Stag",
			"Bush_01",
			"Bush_02",
			"Bush_03",
			"Bush_04"
		};

		void addTreeAt(const oeEntityModel& type, const std::string& treeName, const glm::vec3& pos);
		void addBillboardAt(const oeEntityModel& type, const std::string& billboardName, const glm::vec3& pos);
		void addObject(const oeEntityModel& type, const std::string& objectName, const glm::vec3& pos, const glm::vec3& dir);
		void addBush(const oeEntityModel& type, const std::string& objectName, const glm::vec3& pos);

	public:
		NatureEntityManager();
		~NatureEntityManager();
		
		void addNatureEntity(const oeEntityModel& entity, const glm::vec3& pos, const glm::vec3& dir);
		void removeEntitiesAt(const glm::vec3& pos, const float& radius);

		void clear();

		nlohmann::json& save(nlohmann::json& serializer) const;
		void load(nlohmann::json& serializer);

	};
}
#endif // !NATURE_ENTITY_MANAGER
