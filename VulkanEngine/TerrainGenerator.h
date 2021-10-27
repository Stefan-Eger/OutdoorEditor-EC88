#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H
#include "OEInclude.h"
namespace oe {
	
	class World;
	class MarchingCubes;

	class TerrainGenerator
	{
	protected:
		World* world;
	public:
		virtual void generate(const VoxelCoordinates& chunk) const = 0;
		TerrainGenerator(World* const world) : world {world} {}
		virtual ~TerrainGenerator() = default;
	};
}
#endif // !TERRAIN_GENERATOR_H
