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


	public:
		TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates);
		~TerrainMeshChunk();
		
		void insertOrAssignCube(const VoxelCoordinates& cellPos, MeshCell* cell);


		/// <summary>
		/// Removes Mesh and node from the engine
		/// </summary>
		void clear();


		void meshCleanup();

		/// <summary>
		/// Chunk that is stored is finally created with the VVE in this method.
		/// chunk Coordinates are used for giving the Scene node a name
		/// </summary>
		void renderChunk();

		VoxelCoordinates getChunkCoordinates() const;

		std::vector<std::pair<VoxelCoordinates, MeshCell*>> getChunkMesh() const;

	};
}
#endif // !MESH_CHUNK_H

