#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H
#include "OEInclude.h"
namespace oe {
	
	class TerrainGenerator
	{
	protected:
		VoxelManager* voxelManager;
	public:
		virtual TerrainMeshChunk* generate(const VoxelCoordinates& chunk) const = 0;
		TerrainGenerator(VoxelManager* const voxelManager) : voxelManager{ voxelManager } {}
		virtual ~TerrainGenerator() = default;
	};
}
#endif // !TERRAIN_GENERATOR_H
