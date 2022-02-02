#ifndef NATURE_ENTITY_H
#define NATURE_ENTITY_H
using namespace ve;
namespace oe {
	class NatureEntity
	{
		glm::vec3 pos;
		glm::vec3 dir;
		NatureEntity_t* modelInfo;
		std::string entityName;

		glm::mat4 dir2RotationXZ(const glm::vec3& dir);
	public:
		NatureEntity(const std::string& entityName, const glm::vec3& pos, const glm::vec3& dir, NatureEntity_t* modelInfo);
		virtual	~NatureEntity();

		virtual void createEntity(VESceneNode* parent);

		NatureEntity_t* getModelInfo() const;
		glm::vec3 getPos() const;	
		glm::vec3 getDir() const;
		std::string getEntityName() const;
	};
}
#endif // !NATURE_ENTITY_H

