#include "OEInclude.h"
namespace oe {

	//copied from copyaiNode but with slight adjustments to enable branch building with probabilities
	void NatureEntityTree::loadLeafs(const aiScene* pScene, std::vector<VEMesh*>& meshes, std::vector<VEMaterial*>& materials, aiNode* node, const std::string& entityName, VESceneNode* parent)
	{

		for (uint32_t i = 0; i < node->mNumMeshes; i++) {	//go through the meshes of the Assimp node
			
			if (distribution(generator)) { continue; }

			VEMesh* pMesh = nullptr;
			VEMaterial* pMaterial = nullptr;

			uint32_t paiMeshIdx = node->mMeshes[i];			//get mesh index in global mesh list
			pMesh = meshes[paiMeshIdx];						//use index to get pointer to VEMesh
			aiMesh* paiMesh = pScene->mMeshes[paiMeshIdx];	//also get handle to the Assimp mesh

			uint32_t paiMatIdx = paiMesh->mMaterialIndex;	//get the material index for this mesh
			pMaterial = materials[paiMatIdx];				//use the index to get the right VEMaterial

			glm::mat4* pMatrix = (glm::mat4*)&node->mTransformation;

			std::string leafName = entityName + "_Leaf" + std::to_string(leafModelCounter++);

			VEEntity* pEnt = nullptr;
			VECHECKPOINTER(pEnt = getSceneManagerPointer()->createEntity(leafName, VEEntity::VE_ENTITY_TYPE_NORMAL_WITH_ALPHA, pMesh, pMaterial, parent, *pMatrix));
			leafEntityNames.push_back(leafName);
		}

		for (uint32_t i = 0; i < node->mNumChildren; i++) {		//recursivly go down the node tree
			loadLeafs(pScene, meshes, materials, node->mChildren[i], entityName, parent);
		}
	}
	NatureEntityTree::NatureEntityTree(const glm::vec3& pos, NatureEntity_t* modelInfo, NatureEntity_t* leafsInfo, const double& branchCutOffRatio) : NatureEntity(pos, modelInfo), leafsInfo{ leafsInfo }, distribution{0.5}{}
	NatureEntityTree::~NatureEntityTree()
	{
		NatureEntity::~NatureEntity();
		for (const auto& name : leafEntityNames) {
			getSceneManagerPointer()->deleteSceneNodeAndChildren(name);
		}
	}
	void NatureEntityTree::createEntity(const std::string& entityName, VESceneNode* parent)
	{
		NatureEntity::createEntity(entityName, parent);
		
		
		std::vector<ve::VEMesh*> leafMeshes;
		std::vector<ve::VEMaterial*> leafMaterials;

		aiScene* scene = getSceneManagerPointer()->loadAssets(leafsInfo->baseDirectory, leafsInfo->modelFileName, leafsInfo->aiFlags, leafMeshes, leafMaterials);
		aiNode* pRoot = scene->mRootNode;
		
		loadLeafs(scene, leafMeshes, leafMaterials, pRoot, entityName, parent);
		

		delete scene; // We are now responsible for destroying the imported scene
	}
	
}