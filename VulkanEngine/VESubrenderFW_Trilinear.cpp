#include "VEInclude.h"

namespace ve {
	VESubrender::veSubrenderClass VESubrenderFW_Trilinear::getClass()
	{
		return VE_SUBRENDERER_CLASS_OBJECT; 
	}
	VESubrender::veSubrenderType VESubrenderFW_Trilinear::getType()
	{
		return VE_SUBRENDERER_TYPE_TRILINEAR_MAPPING;
	}

	void VESubrenderFW_Trilinear::initSubrenderer()
	{
		VESubrenderFW::initSubrenderer();
		
		vh::vhRenderCreateDescriptorSetLayout(getRendererForwardPointer()->getDevice(),
			{ m_resourceArrayLength },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER },
			{ VK_SHADER_STAGE_FRAGMENT_BIT },
			&m_descriptorSetLayoutResources);

		VkDescriptorSetLayout perObjectLayout = getRendererForwardPointer()->getDescriptorSetLayoutPerObject();




		vh::vhPipeCreateGraphicsPipelineLayout(getRendererForwardPointer()->getDevice(),
			{ perObjectLayout, perObjectLayout,  getRendererForwardPointer()->getDescriptorSetLayoutShadow(),
				perObjectLayout, m_descriptorSetLayoutResources },
			{ 
				{VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(BrushCircle)} 
			}, 
			& m_pipelineLayout);

		

		m_pipelines.resize(1);

		vh::vhPipeCreateGraphicsPipeline(getRendererForwardPointer()->getDevice(),
			{ "media/shader/Forward/Trilinear/vert.spv", "media/shader/Forward/Trilinear/frag.spv" },
			getRendererForwardPointer()->getSwapChainExtent(),
			m_pipelineLayout, getRendererForwardPointer()->getRenderPass(),
			{ VK_DYNAMIC_STATE_BLEND_CONSTANTS },
			&m_pipelines[0]);

		if (m_maps.empty()) m_maps.resize(1);
	}

	
	void VESubrenderFW_Trilinear::addEntity(VEEntity* pEntity)
	{
		std::vector<VkDescriptorImageInfo> maps = { pEntity->m_pMaterial->mapDiffuse->m_imageInfo };
		
		addMaps(pEntity, maps);

		VESubrender::addEntity(pEntity);
	}

	void VESubrenderFW_Trilinear::bindDescriptorSetsPerFrame(VkCommandBuffer commandBuffer, uint32_t imageIndex, VECamera* pCamera, VELight* pLight, std::vector<VkDescriptorSet> descriptorSetsShadow)
	{
		VESubrenderFW::bindDescriptorSetsPerFrame(commandBuffer, imageIndex, pCamera, pLight, descriptorSetsShadow);
		vkCmdPushConstants(commandBuffer, m_pipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(BrushCircle), &brushCircle);
	}
	void VESubrenderFW_Trilinear::setDynamicPipelineState(VkCommandBuffer commandBuffer, uint32_t numPass)
	{
		if (numPass == 0) {
			float blendConstants[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			vkCmdSetBlendConstants(commandBuffer, blendConstants);
			return;
		}

		float blendConstants[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		vkCmdSetBlendConstants(commandBuffer, blendConstants);
	}

	BrushCircle VESubrenderFW_Trilinear::brushCircle{
		glm::vec3(0.0f, 0.0f, 0.0f),
		2.0f,
		VK_FALSE
	};
}