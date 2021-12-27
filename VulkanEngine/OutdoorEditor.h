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
			TERRAIN_EDITING_VOLUME,
			TERRAIN_EDITING_TEXTURE,
			TREE_PLACEMENT,
			BILLBOARD_PLACEMENT,
			OBJECT_PLACEMENT

		};

		enum class oeBrushModes
		{
			BRUSH_SPHERE_FULL,
			BRUSH_SPHERE_SMOOTH,
			BRUSH_DRILL,
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
		bool editModeChanged;

		oeBrushModes activeBrushMode;

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

		void handleInput(const glm::vec3& hitPos, const glm::vec3& direction, bool invertOperation = false);

		/////////////////////////////////////////////////////////////////////////
		//Editor-Components
		TerrainManager* getTerrainManager() const;
		VoxelManager* getVoxelManager() const;

		oeEditingModes getEditingMode() const;
		void setEditingMode(const oeEditingModes& mode);
		void setActiveMaterial(const oeTerrainMaterial& terrainMaterial);
		EditingBrush* getActiveBrush() const;

		/// <summary>
		/// Only works if edit Mode == TERRAIN_EDITING_VOLUME
		/// </summary>
		/// <param name="brushMode"></param>
		void setBrushMode(const oeBrushModes& brushMode );
		oeBrushModes getBrushMode() const;

	};
}
#endif // !VOXEL_CHUNK_DATA_H
