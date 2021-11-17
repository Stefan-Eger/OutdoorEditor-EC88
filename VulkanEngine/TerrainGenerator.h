#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H
#include "OEInclude.h"
namespace oe {
	
	class TerrainGenerator
	{
	protected:
		VoxelManager* voxelManager;
	public:
		virtual void generateChunk(TerrainMeshChunk* chunk) const = 0;
		virtual void generateCell(TerrainMeshChunk* chunk, const VoxelCoordinates& cellCoordinates) const = 0;
		TerrainGenerator(VoxelManager* const voxelManager) : voxelManager{ voxelManager } {}
		virtual ~TerrainGenerator() = default;
	};
}
#endif // !TERRAIN_GENERATOR_H
