#ifndef VOXEL_CHUNK_DATA_H
#define VOXEL_CHUNK_DATA_H


namespace oe {
	class VoxelChunkData
	{
		static constexpr VoxelCoordinates::value_type CHUNK_SIZE_X = 4;
		static constexpr VoxelCoordinates::value_type CHUNK_SIZE_Y = 4;
		static constexpr VoxelCoordinates::value_type CHUNK_SIZE_Z = 4;

		VoxelPoint voxels[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
		
		//0 is no block is above 0.0 density -> Airchunk
		std::size_t voxelCounter;

	public:
		static const VoxelCoordinates CHUNK_SIZE;

		VoxelChunkData();
		/// <summary>
		/// Fills the VoxelPoint ary with the reference 
		/// </summary>
		/// <param name="ref">The Standard reference that the Chunk will be filled with</param>
		VoxelChunkData(const VoxelPoint& ref);
		~VoxelChunkData();

		void setVoxel(const VoxelCoordinates& localCoordinates, const VoxelPoint& voxelValue );
		VoxelPoint getVoxel(const VoxelCoordinates& localCoordinates) const;

		/// <summary>
		/// Check if Chunk has something to render or not
		/// </summary>
		/// <returns></returns>
		bool isAirChunk() const;
	};
}
#endif // !VOXEL_CHUNK_DATA_H
