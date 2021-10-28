#include "OEInclude.h"
namespace oe {

	OutdoorEditor* OutdoorEditorInfo::editor = nullptr;

	void OutdoorEditorInfo::exit()
	{
		if(editor != nullptr)
			delete editor;
	}

}