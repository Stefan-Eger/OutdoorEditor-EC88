#ifndef TERRAIN_MESH_CHUNK_H
#define TERRAIN_MESH_CHUNK_H

namespace oe {
	class TerrainMeshChunk
	{
		VoxelCoordinates chunkCoordinates;

		uint32_t verticeCount;

		std::vector<vh::vhVertex> vertices;
		std::vector<uint32_t> indices;

	public:
		TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates);
		~TerrainMeshChunk();

		void addVertice(const vh::vhVertex& vertice);	

		void clear();

		void createMesh();

	};
}
#endif // !MESH_CHUNK_H

