#ifndef VOXEL_MANAGER_H
#define VOXEL_MANAGER_H
namespace oe {
	class VoxelManager
	{
		std::unordered_map<VoxelCoordinates, VoxelChunkData*> chunks;

	public:
		VoxelManager();
		~VoxelManager();

		static VoxelCoordinates world2ChunkCoordinates(const VoxelCoordinates& worldCoordinates);
		static VoxelCoordinates world2Local(const VoxelCoordinates& worldCoordinates);
		static VoxelCoordinates local2World(const VoxelCoordinates& localCoordinates, const VoxelCoordinates& chunkCoordinates);

		VoxelChunkData* addChunk(const VoxelCoordinates& chunkCoordinates);
		/// <summary>
		/// Fills the Chunk with the filler reference Grass for example
		/// </summary>
		/// <param name="chunkCoordinates"></param>
		/// <param name="filler"></param>
		VoxelChunkData* addChunk(const VoxelCoordinates& chunkCoordinates, const VoxelPoint& filler);

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

		VoxelChunkData* findChunk(const VoxelCoordinates& chunkCoordinates) const;


		void clear();

		std::vector<VoxelCoordinates> getAllChunks2Refresh() const;

		nlohmann::json& save(nlohmann::json& serializer) const;
		void load(nlohmann::json& serializer);

	};
}
#endif // !VOXEL_MANAGER_H

