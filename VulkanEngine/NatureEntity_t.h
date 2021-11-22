#ifndef NATURE_ENTITY_TYPE_H
#define NATURE_ENTITY_TYPE_H
using namespace ve;
namespace oe {
	struct NatureEntity_t
	{
		std::string baseDirectory;
		//Should be an obj File
		std::string modelFileName;
		uint32_t aiFlags = aiProcess_FlipUVs | aiProcess_FlipWindingOrder;
	};
}
#endif
