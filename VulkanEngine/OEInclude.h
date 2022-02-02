#ifndef OUTDOOR_EDITOR_INCLUDE_H
#define OUTDOOR_EDITOR_INCLUDE_H

#include "VEInclude.h"
#include <unordered_set>
#include "json.hpp" //https://github.com/nlohmann/json (31.12.21)
#include "Ray.h"
#include "EventListenerUser.h"
#include "VoxelCoordinates.h"
#include "VoxelPoint.h"
#include "VoxelChunkData.h"

#include "VoxelManager.h"
#include "TerrainMeshChunk.h"
#include "TerrainGenerator.h"
#include "MarchingCubes.h"
#include "TerrainManager.h"

#include "EditingBrush.h"
#include "EditingBrushSphereFull.h"
#include "EditingBrushSphereSmooth.h"
#include "EditingBrushDrill.h"

#include "NatureEntity_t.h"
#include "NatureEntity.h"
#include "NatureEntityLeafs.h"
#include "NatureEntityBillboard.h"
#include "NatureEntityModel.h"
#include "NatureEntityDatabase.h"
#include "NatureEntityManager.h"

#include "OutdoorEditor.h"


#include "OutdoorEditorInfo.h"
#include "EventListenerGUI.h"

#include "OutdoorEditorEngine.h"



#endif // !OUTDOOR_EDITOR_INCLUDE_H
