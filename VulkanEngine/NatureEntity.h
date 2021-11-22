#ifndef NATURE_ENTITY_H
#define NATURE_ENTITY_H
using namespace ve;
namespace oe {
	class NatureEntity
	{
		glm::vec3 pos;
		NatureEntity_t* modelInfo;

		VESceneNode* entity;
		
	public:
		NatureEntity(const glm::vec3& pos, NatureEntity_t* modelInfo);
		~NatureEntity();

		virtual void createEntity(const std::string& entityName, VESceneNode* parent);

		NatureEntity_t* getModelInfo() const;
		glm::vec3 getPos() const;
	};
}
#endif // !NATURE_ENTITY_H

