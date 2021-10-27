#ifndef WORLD_H
#define WORLD_H
namespace oe {

	class TerrainGenerator;
	class World
	{
		//ChunkCoordinates, Chunk
		std::unordered_map<VoxelCoordinates, VoxelChunkData*> chunks;
		
		TerrainGenerator* terrainGenerator = nullptr;
			

		/// <summary>
		/// Chunks that have to be rendered are in this List. The Marching Cubes algorithm or others can use this to know which Chunks need to be
		/// generated
		/// </summary>
		/// <returns>List of Chunks that have to be generated</returns>
		std::vector<VoxelCoordinates> getAllChunks2Generate() const;

	public:
		World();
		~World();


		static VoxelCoordinates world2ChunkCoordinates(const VoxelCoordinates& worldCoordinates);
		static VoxelCoordinates world2Local(const VoxelCoordinates& worldCoordinates);
		static VoxelCoordinates local2World(const VoxelCoordinates& localCoordinates, const VoxelCoordinates& chunkCoordinates);

		void setChunkAt(const VoxelCoordinates& chunkCoordinates);
		/// <summary>
		/// Fills the Chunk with the filler reference Grass for example
		/// </summary>
		/// <param name="chunkCoordinates"></param>
		/// <param name="filler"></param>
		void setChunkAt(const VoxelCoordinates& chunkCoordinates, const VoxelPoint& filler);

		/// <summary>
		/// Sets a Voxel if Chunk exists and generates new chunk immediately
		/// </summary>
		/// <param name="worldCoordinates">Voxel World Coordinate</param>
		/// <param name="voxelValue">Voxel Value (Id)</param>
		void setVoxel(const VoxelCoordinates& worldCoordinates, const VoxelPoint& voxelValue);

		/// <summary>
		/// Returns the value of the world Coordinate if there is no chunk at this position it return empty -> 0
		/// </summary>
		/// <param name="worldCoordinates">Voxel World Coordinate</param>
		/// <returns>Voxel Value (Id)</returns>
		VoxelPoint getVoxel(const VoxelCoordinates& worldCoordinates) const;

		VoxelChunkData* getChunk(const VoxelCoordinates& chunkCoordinates) const;

		
		/// <summary>
		/// Ray returns true if mesh was was hit.
		/// </summary>
		/// <param name="ray"></param>
		/// <param name="outPos">Returns the hit Position of Ray if function return true</param>
		/// <returns>True if it has hit something</returns>
		bool traceRay(const Ray& ray, glm::vec3& outPos) const;


		void generateAll() const;

	};
}
#endif // !VOXEL_CHUNK_DATA_H
