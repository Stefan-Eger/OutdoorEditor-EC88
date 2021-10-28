#ifndef WORLD_H
#define WORLD_H
namespace oe {

	class OutdoorEditor
	{
		//ChunkCoordinates, Chunk
		VoxelManager* voxelManager;
		TerrainManager* terrainManager;

	public:
		OutdoorEditor();
		~OutdoorEditor();

		/// <summary>
		/// Ray returns true if mesh was was hit.
		/// </summary>
		/// <param name="ray"></param>
		/// <param name="outPos">Returns the hit Position of Ray if function return true</param>
		/// <returns>True if it has hit something</returns>
		bool traceRay(const Ray& ray, glm::vec3& outPos) const;

		TerrainManager* getTerrainManager() const;
		VoxelManager* getVoxelManager() const;
		


		void generateAll() const;

	};
}
#endif // !VOXEL_CHUNK_DATA_H
