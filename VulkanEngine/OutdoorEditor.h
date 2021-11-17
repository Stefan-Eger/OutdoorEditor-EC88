#ifndef WORLD_H
#define WORLD_H
namespace oe {

	class OutdoorEditor
	{
	public:
		/// <summary>
		/// Volume -> editing density of model
		/// Texture -> editing Textures of Voxels
		/// Sphere_... -> Brush
		/// </summary>
		enum class oeEditingModes {
			TERRAIN_EDITING_VOLUME_SPHERE_FULL,
			TERRAIN_EDITING_VOLUME_SPHERE_SMOOTH,
			TERRAIN_EDITING_VOLUME_DRILL,
			TERRAIN_EDITING_TEXTURE_SPHERE_FULL
		};

	private:
		//ChunkCoordinates, Chunk
		VoxelManager* voxelManager;
		TerrainManager* terrainManager;

		std::vector<EditingBrush*> brushes;
		EditingBrush* activeBrush;
		oeEditingModes activeMode;

		const float RAY_DISTANCE_MAX = 20.0f;
		const float RAY_EPSILON = 0.00001f;

		const std::size_t CHUNKS_CHANGED_VOXELS_THRESHOLD = 10;
		const int TERRAIN_BEDROCK_LEVEL = -10;

		bool rayTriangleIntersection(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal, glm::vec3& outPos) const;	

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

		void modifyTerrain(const glm::vec3& hitPos, const glm::vec3& direction, bool subtractVolume = false);
		//void changeBrush();
		


		TerrainManager* getTerrainManager() const;
		VoxelManager* getVoxelManager() const;


		oeEditingModes getEditingMode() const;
		void setEditingMode(const oeEditingModes& mode);

		EditingBrush* getActiveBrush() const;

		void refresh() const;

	};
}
#endif // !VOXEL_CHUNK_DATA_H
