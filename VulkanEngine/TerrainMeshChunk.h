#ifndef TERRAIN_MESH_CHUNK_H
#define TERRAIN_MESH_CHUNK_H

namespace oe {
	/// <summary>
	/// This Cube contains the Mesh information of a Cube that is marching between the voxel Data 
	/// It is build upon small marching cubes to ensure multiple materials instead of just one, 
	/// which would be applied to the chunk
	/// </summary>
	
	struct MeshCell {
		std::vector<vh::vhVertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<glm::vec3> surfaceNormals;
		std::size_t material;
	};

	class TerrainMeshChunk
	{
		VoxelCoordinates chunkCoordinates;
		
		//stores all cube coordinates to access the map
		std::unordered_map<VoxelCoordinates, MeshCell*> cubes;

		//https://3dtextures.me/ (12.12.21)
		//All textures from this site except grass
		//Little collection of textures
		const std::map < std::size_t, std::tuple < std::string, std::string, std::string >> terrainMaterials = {
			{0, { "Grass", "media/models/editor/TerrainTextures/Grass", "grass.png"} },
			{1, { "Dirt", "media/models/editor/TerrainTextures/Dirt", "dirt_color.jpg"} },
			{2, { "Wet_Dirt", "media/models/editor/TerrainTextures/Wet", "wet_color.jpg"} },
			{3, { "Mud", "media/models/editor/TerrainTextures/Mud", "mud_color.jpg"} }
		};
		
		//for cleanup
		std::string chunkName;
		std::vector<std::string> meshNames;

		const float RAY_EPSILON = 0.00001f;

		bool rayTriangleIntersection(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal, glm::vec3& outPos) const;


	public:
		TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates);
		~TerrainMeshChunk();
		
		void insertOrAssignCube(const VoxelCoordinates& cellPos, MeshCell* cell);
		VEMaterial* getTerrainMaterial(const std::size_t& material) const;

		/// <summary>
		/// Removes the stored mesh does not cleanup the mesh in renderer tough
		/// </summary>
		void clear();

		void meshCleanup();

		/// <summary>
		/// Chunk that is stored is finally created with the VVE in this method.
		/// chunk Coordinates are used for giving the Scene node a name
		/// </summary>
		void renderChunk();

		/// <summary>
		/// Traces the ray if it has hit the mesh
		/// </summary>
		/// <param name="ray"></param>
		/// <param name="outPos">Returns the hit Position of Ray if function return true</param>
		/// <returns>True if it has hit something</returns>
		bool traceRay(const Ray& ray, glm::vec3& outPos) const;

		VoxelCoordinates getChunkCoordinates() const;
	};
}
#endif // !MESH_CHUNK_H

