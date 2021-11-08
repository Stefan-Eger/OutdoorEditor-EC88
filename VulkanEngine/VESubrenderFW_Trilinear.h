#ifndef VE_SUBRENDERFW_TRILINEAR
#define VE_SUBRENDERFW_TRILINEAR

namespace ve {

	class VESubrenderFW_Trilinear : public VESubrenderFW {
	public:
		///Constructor
		VESubrenderFW_Trilinear() {};
		///Destructor
		virtual ~VESubrenderFW_Trilinear() {};

		///\returns the class of the subrenderer
		virtual veSubrenderClass getClass();
		///\returns the type of the subrenderer
		virtual veSubrenderType getType();

		virtual void initSubrenderer();
		virtual void setDynamicPipelineState(VkCommandBuffer commandBuffer, uint32_t numPass);
		virtual void addEntity(VEEntity* pEntity);
	};

}

#endif // !VE_SUBRENDERFW_TRILINEAR


