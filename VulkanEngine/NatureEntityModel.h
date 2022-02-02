#ifndef NATURE_ENTITY_MODEL
#define NATURE_ENTITY_MODEL
namespace oe {

	class NatureEntityModel : public NatureEntity
	{
		std::vector<NatureEntity*> entities;
		public:
			NatureEntityModel(const std::string & entityName, const glm::vec3& pos, const std::vector<NatureEntity*>& entities);
			virtual ~NatureEntityModel() override;
			virtual void createEntity(VESceneNode * parent) override;
			void addEntity(NatureEntity* entity);
			void removeEntity(std::string& entityName);
			void clear();
		
	};
}
#endif

