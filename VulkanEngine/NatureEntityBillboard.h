#ifndef NATURE_ENTITY_BILLBOARDS
#define NATURE_ENTITY_BILLBOARDS
namespace oe {
	class NatureEntityBillboard : public NatureEntity
	{
	public:
		NatureEntityBillboard(const std::string& entityName, const glm::vec3& pos, NatureEntity_t* modelInfo);
		virtual void createEntity( VESceneNode* parent) override;
	};
}

#endif // !NATURE_ENTITY_BILLBOARDS
