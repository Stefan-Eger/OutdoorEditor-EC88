#ifndef VE_SUBRENDER_FW_DN_ALPHA
#define VE_SUBRENDER_FW_DN_ALPHA

namespace ve {
	class VESubrenderFW_DN_Alpha : public VESubrenderFW {
		VkResult createCustomGraphicsPipeline(VkDevice device,
			std::vector<std::string> shaderFileNames,
			VkExtent2D swapChainExtent,
			VkPipelineLayout pipelineLayout,
			VkRenderPass renderPass,
			std::vector<VkDynamicState> dynamicStates,
			VkPipeline* graphicsPipeline);
	public:
		///Constructor for class VESubrenderFW_DN
		VESubrenderFW_DN_Alpha() { };
		///Destructor for class VESubrenderFW_DN
		virtual ~VESubrenderFW_DN_Alpha() {};

		///\returns the class of the subrenderer
		virtual veSubrenderClass getClass() { return VE_SUBRENDERER_CLASS_OBJECT; };
		///\returns the type of the subrenderer
		virtual veSubrenderType getType() { return VE_SUBRENDERER_TYPE_DN_ALPHA; };

		virtual void initSubrenderer();
		virtual void addEntity(VEEntity* pEntity);


	};
}
#endif // !VE_SUBRENDER_FW_TREE_DN
