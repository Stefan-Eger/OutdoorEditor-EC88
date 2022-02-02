#ifndef NATURE_ENTITY_TREE
#define NATURE_ENTITY_TREE

namespace oe {
	class NatureEntityLeafs : public NatureEntity
	{
		std::vector<std::string> leafEntityNames;
		std::size_t leafModelCounter = 0;


		std::bernoulli_distribution distribution;		// for random bool values
		std::default_random_engine generator{ 123 };	// generator for random numbers

		void loadLeafs(const aiScene* pScene, std::vector<VEMesh*>& meshes, std::vector<VEMaterial*>& materials, aiNode* node, 
			const std::string& entityName, VESceneNode* parent);
	public:	
		NatureEntityLeafs(const std::string& entityName, const glm::vec3& pos, NatureEntity_t* leafsInfo, const double& branchCutOffRatio = 0.25);
		virtual ~NatureEntityLeafs() override;
		virtual void createEntity(VESceneNode* parent) override;


	};
}

#endif
