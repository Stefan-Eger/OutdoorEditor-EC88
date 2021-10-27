#include "OEInclude.h"
namespace oe {

	World* OutdoorEditorInfo::world = nullptr;

	void OutdoorEditorInfo::exit()
	{
		if(world != nullptr)
			delete world;
	}

}