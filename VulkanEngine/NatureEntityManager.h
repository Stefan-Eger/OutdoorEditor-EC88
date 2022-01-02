#ifndef NATURE_ENTITY_MANAGER
#define NATURE_ENTITY_MANAGER

namespace oe {

	enum class oeEntityModel {
		PINE_TREE,
		BILLBOARD_GRASS_01

	};

	class NatureEntityManager
	{
		NatureEntityDatabase* enitityDatabase;

		//Entity management
		//<Entity name, <entityType,entity>>
		std::unordered_map<std::string, std::pair<oeEntityModel, NatureEntity*>> entities;
		std::size_t entityCounter;

		const std::vector<std::string> modelType = {
			"Pine_Tree",
			"Bill_Board_Grass"
		};

		void addTreeAt(const oeEntityModel& type, const std::string& treeName, const glm::vec3& pos);
		void addBillboardAt(const oeEntityModel& type, const std::string& billboardName, const glm::vec3& pos);

	public:
		NatureEntityManager();
		~NatureEntityManager();
		
		void addNatureEntity(const oeEntityModel& entity, const glm::vec3& pos );
		void removeEntitiesAt(const glm::vec3& pos, const float& radius);

		void clear();

		nlohmann::json& save(nlohmann::json& serializer) const;
		void load(nlohmann::json& serializer);

	};
}
#endif // !NATURE_ENTITY_MANAGER
