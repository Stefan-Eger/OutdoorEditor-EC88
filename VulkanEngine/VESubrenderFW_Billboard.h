#ifndef VESUBRENDER_FW_BILLBOARD
#define VESUBRENDER_FW_BILLBOARD

namespace ve {
	class VESubrenderFW_Billboard : public VESubrenderFW {
		VkResult createCustomGraphicsPipeline(VkDevice device,
			std::vector<std::string> shaderFileNames,
			VkExtent2D swapChainExtent,
			VkPipelineLayout pipelineLayout,
			VkRenderPass renderPass,
			std::vector<VkDynamicState> dynamicStates,
			VkPipeline* graphicsPipeline);
		public:
			///Constructor
			VESubrenderFW_Billboard() {};
			///Destructor
			virtual ~VESubrenderFW_Billboard() {};

			///\returns the class of the subrenderer
			virtual veSubrenderClass getClass() { return VE_SUBRENDERER_CLASS_OBJECT; };
			///\returns the type of the subrenderer
			virtual veSubrenderType getType() { return VE_SUBRENDERER_TYPE_BILLBOARD; };

			virtual void initSubrenderer();
			virtual void addEntity(VEEntity* pEntity);
	};
}

#endif // !VESUBRENDER_FW_BILLBOARD

