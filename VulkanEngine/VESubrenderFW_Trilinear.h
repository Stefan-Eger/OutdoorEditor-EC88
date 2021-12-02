#ifndef VE_SUBRENDERFW_TRILINEAR
#define VE_SUBRENDERFW_TRILINEAR

namespace ve {

	struct BrushCircle {
		glm::vec3 mouseHitPos; //Mid Point of Circle
		float radius;

		VkBool32 isActive;
	};


	class VESubrenderFW_Trilinear : public VESubrenderFW {
		

	public:
		static BrushCircle brushCircle;

		///Constructor
		VESubrenderFW_Trilinear() {};
		///Destructor
		virtual ~VESubrenderFW_Trilinear() {};

		///\returns the class of the subrenderer
		virtual veSubrenderClass getClass() override;
		///\returns the type of the subrenderer
		virtual veSubrenderType getType() override;

		virtual void bindDescriptorSetsPerFrame(VkCommandBuffer commandBuffer, uint32_t imageIndex, VECamera* pCamera, VELight* pLight,
			std::vector<VkDescriptorSet> descriptorSetsShadow) override;

		virtual void initSubrenderer() override;
		virtual void addEntity(VEEntity* pEntity) override;
	};

}

#endif // !VE_SUBRENDERFW_TRILINEAR


