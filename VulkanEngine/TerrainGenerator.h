#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H
#include "OEInclude.h"
namespace oe {
	
	class TerrainGenerator
	{
	protected:
		VoxelManager* voxelManager;
	public:
		TerrainGenerator(VoxelManager* const voxelManager) : voxelManager{ voxelManager } {}
		virtual ~TerrainGenerator() = default;
		virtual void generateChunk(TerrainMeshChunk * chunk) const = 0;
		virtual void generateCell(TerrainMeshChunk * chunk, const VoxelCoordinates & cellCoordinates) const = 0;
	};
}
#endif // !TERRAIN_GENERATOR_H
