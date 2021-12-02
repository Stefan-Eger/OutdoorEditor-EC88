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

		VEMaterial* material;
	};

	class TerrainMeshChunk
	{
		VoxelCoordinates chunkCoordinates;
		
		//stores all cube coordinates to access the map
		std::unordered_map<VoxelCoordinates, MeshCell*> cubes;

		//for cleanup
		std::string chunkName;
		std::vector<std::string> meshNames;

		const float RAY_EPSILON = 0.00001f;

		bool rayTriangleIntersection(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& surfaceNormal, glm::vec3& outPos) const;


		//TODO Make small Material Database
	public:
		TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates);
		~TerrainMeshChunk();
		
		void insertOrAssignCube(const VoxelCoordinates& cellPos, MeshCell* cell);


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

