#ifndef TERRAIN_MESH_CHUNK_H
#define TERRAIN_MESH_CHUNK_H

namespace oe {
	class TerrainMeshChunk
	{
		VoxelCoordinates chunkCoordinates;
		std::string chunkName;

		uint32_t verticeCount;

		std::vector<vh::vhVertex> vertices;
		std::vector<uint32_t> indices;

	public:
		TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates);
		~TerrainMeshChunk();
		
		void addVertice(const vh::vhVertex& vertice);	

		void clear();

		/// <summary>
		/// Chunk that is stored is finally created with the VVE in this method.
		/// chunk Coordinates are used for giving the Scene node a name
		/// </summary>
		void createSceneNode();

		VoxelCoordinates getChunkCoordinates() const;

		const std::vector<vh::vhVertex> getVertices() const;
		const std::vector<uint32_t> getIndices() const;
	};
}
#endif // !MESH_CHUNK_H

