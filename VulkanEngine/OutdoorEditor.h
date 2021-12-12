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
			TERRAIN_EDITING_TEXTURE_SPHERE_FULL,
			TREE_PLACEMENT_SINGLE,
			BILLBOARD_PLACEMENT_SINGLE

		};
		enum class oeTerrainMaterial {
			OE_TEXTURE_GRASS,
			OE_TEXTURE_DIRT,
			OE_TEXTURE_WET_DIRT,
			OE_TEXTURE_MUD
		};

	private:
		//Managers
		VoxelManager* voxelManager;
		TerrainManager* terrainManager;
		NatureEntityDatabase* enitityDatabase;
		
		//Entity management
		std::unordered_map<std::string, NatureEntity*> entities;
		std::size_t entityCounter;

		//Brushes
		std::vector<EditingBrush*> brushes;
		EditingBrush* activeBrush;
		oeEditingModes activeMode;

		//Constants
		const std::size_t CHUNKS_CHANGED_VOXELS_THRESHOLD = 15;
		const int TERRAIN_BEDROCK_LEVEL = -10;

		const float RAY_DISTANCE_MAX = 40.0f;

		//Selected Texture
		std::size_t activeMaterial;

		void addTreeAt(const std::string& entityName, const glm::vec3& pos);
		void addBillboardAt(const std::string& entityName, const glm::vec3& pos);
		void removeEntitiesAt(const glm::vec3& pos);

		void changeTerrainMaterial(const glm::vec3& hitPos);
		void modifyTerrainVolumeWithActiveBrush(const glm::vec3& hitPos, bool subtractVolume = false);
		
	public:
		OutdoorEditor();
		~OutdoorEditor();

		/////////////////////////////////////////////////////////////////////////
		//Terrain manipulation
		void refresh() const;

		bool traceRay(const Ray& ray, glm::vec3& outPos) const;

		void handleInput(const glm::vec3& hitPos, const glm::vec3& direction, bool subtractVolume = false);

		/////////////////////////////////////////////////////////////////////////
		//Editor-Components
		TerrainManager* getTerrainManager() const;
		VoxelManager* getVoxelManager() const;

		oeEditingModes getEditingMode() const;
		void setEditingMode(const oeEditingModes& mode);
		void setActiveMaterial(const oeTerrainMaterial& terrainMaterial);
		EditingBrush* getActiveBrush() const;


	};
}
#endif // !VOXEL_CHUNK_DATA_H
