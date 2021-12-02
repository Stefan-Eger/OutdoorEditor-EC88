#ifndef NATURE_ENTITY_TREE
#define NATURE_ENTITY_TREE

namespace oe {
	class NatureEntityTree : public NatureEntity
	{
		NatureEntity_t* leafsInfo;

		std::vector<std::string> leafEntityNames;
		int leafModelCounter = 0;

		//TODO Random Number of leafs applied	
		void loadLeafs(const aiScene* pScene, std::vector<VEMesh*>& meshes,
			std::vector<VEMaterial*>& materials, aiNode* node, const std::string& entityName, VESceneNode* parent);
	public:
		NatureEntityTree(const glm::vec3& pos, NatureEntity_t* modelInfo, NatureEntity_t* leafsInfo);
		virtual ~NatureEntityTree() override;
		virtual void createEntity(const std::string& entityName, VESceneNode* parent) override;

	};
}

#endif
