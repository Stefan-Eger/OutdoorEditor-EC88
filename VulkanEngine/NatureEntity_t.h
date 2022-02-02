#ifndef NATURE_ENTITY_TYPE_H
#define NATURE_ENTITY_TYPE_H
using namespace ve;
namespace oe {
	struct NatureEntity_t
	{
		std::string baseDirectory;
		//Should be an obj File
		std::string modelFileName;
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		uint32_t aiFlags = aiProcess_FlipUVs | aiProcess_FlipWindingOrder;


	};
}
#endif
