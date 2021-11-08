#ifndef TERRAIN_MESH_CHUNK_H
#define TERRAIN_MESH_CHUNK_H

namespace oe {
	/// <summary>
	/// This Cube contains the Mesh information of a Cube that is marching between the voxel Data 
	/// It is build upon small marching cubes to ensure multiple materials instead of just one, 
	/// which would be applied to the chunk
	/// </summary>
	struct MeshCube {
		VoxelCoordinates cubePos;

		std::vector<vh::vhVertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<glm::vec3> surfaceNormals;

		VEMaterial* material;
	};

	class TerrainMeshChunk
	{
		VoxelCoordinates chunkCoordinates;
		std::string chunkName;

		std::vector<MeshCube> cubes;

	public:
		TerrainMeshChunk(const VoxelCoordinates& chunkCoordinates);
		~TerrainMeshChunk();
		
		void addCube(const MeshCube& cube);


		/// <summary>
		/// Removes Mesh and node from the engine
		/// </summary>
		void clear();

		/// <summary>
		/// Chunk that is stored is finally created with the VVE in this method.
		/// chunk Coordinates are used for giving the Scene node a name
		/// </summary>
		void renderChunk();

		VoxelCoordinates getChunkCoordinates() const;

		const std::vector<MeshCube>& getCubes() const;
	};
}
#endif // !MESH_CHUNK_H

