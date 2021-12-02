#ifndef NATURE_ENTITY_BILLBOARDS
#define NATURE_ENTITY_BILLBOARDS
namespace oe {
	class NatureEntityBillboard : public NatureEntity
	{
		std::string entityName = "";
	public:
		NatureEntityBillboard(const glm::vec3& pos, NatureEntity_t* modelInfo);
		virtual ~NatureEntityBillboard() override;
		virtual void createEntity(const std::string& entityName, VESceneNode* parent) override;
	};
}

#endif // !NATURE_ENTITY_BILLBOARDS
