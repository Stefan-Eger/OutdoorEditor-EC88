#include "OEInclude.h"

namespace ve {
	VkResult VESubrenderFW_Trilinear::createCustomGraphicsPipeline(VkDevice device, std::vector<std::string> shaderFileNames, VkExtent2D swapChainExtent, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkDynamicState> dynamicStates, VkPipeline* graphicsPipeline)
	{
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

		auto vertShaderCode = vh::vhFileRead(shaderFileNames[0]);

		VkShaderModule vertShaderModule = vh::vhPipeCreateShaderModule(device, vertShaderCode);

		VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";
		shaderStages.push_back(vertShaderStageInfo);

		

		VkShaderModule fragShaderModule = VK_NULL_HANDLE;
		if (shaderFileNames.size() > 1 && shaderFileNames[1].size() > 0) {
			auto fragShaderCode = vh::vhFileRead(shaderFileNames[1]);

			fragShaderModule = vh::vhPipeCreateShaderModule(device, fragShaderCode);

			VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
			fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			fragShaderStageInfo.module = fragShaderModule;
			fragShaderStageInfo.pName = "main";

			shaderStages.push_back(fragShaderStageInfo);
		}

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		auto bindingDescription = vh::vhVertex::getBindingDescription();
		auto attributeDescriptions = vh::vhVertex::getAttributeDescriptions();

		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport = {};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)swapChainExtent.width;
		viewport.height = (float)swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor = {};
		scissor.offset = { 0, 0 };
		scissor.extent = swapChainExtent;

		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineDepthStencilStateCreateInfo depthStencil = {};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = VK_TRUE;
		depthStencil.depthWriteEnable = VK_TRUE;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.stencilTestEnable = VK_FALSE;

		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_CONSTANT_COLOR;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;

		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		VkPipelineDynamicStateCreateInfo dynamicState = {};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = (uint32_t)dynamicStates.size();
		if (dynamicStates.size() > 0) {
			dynamicState.pDynamicStates = dynamicStates.data();
		}

		VkGraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = (uint32_t)shaderStages.size();
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		if (dynamicStates.size() > 0) {
			pipelineInfo.pDynamicState = &dynamicState;
		}
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		VHCHECKRESULT(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, graphicsPipeline));

		if (fragShaderModule != VK_NULL_HANDLE)
			vkDestroyShaderModule(device, fragShaderModule, nullptr);

		vkDestroyShaderModule(device, vertShaderModule, nullptr);
		return VK_SUCCESS;
	}
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

		createCustomGraphicsPipeline(getRendererForwardPointer()->getDevice(),
			{ "media/shader/Forward/Trilinear/vert.spv", "media/shader/Forward/Trilinear/frag.spv" },
			getRendererForwardPointer()->getSwapChainExtent(),
			m_pipelineLayout, getRendererForwardPointer()->getRenderPass(),
			{ VK_DYNAMIC_STATE_BLEND_CONSTANTS },
			&m_pipelines[0]);

		if (m_maps.empty()) m_maps.resize(1);
	}

	void VESubrenderFW_Trilinear::setDynamicPipelineState(VkCommandBuffer commandBuffer, uint32_t numPass){
		if (numPass == 0) {
			float blendConstants[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			vkCmdSetBlendConstants(commandBuffer, blendConstants);
			return;
		}

		float blendConstants[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		vkCmdSetBlendConstants(commandBuffer, blendConstants);
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
		std::cout << "Push Constants" << std::endl;
		vkCmdPushConstants(commandBuffer, m_pipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(BrushCircle), &brushCircle);
	}

	BrushCircle VESubrenderFW_Trilinear::brushCircle{
		glm::vec3(0.0f, 0.0f, 0.0f),
		2.0f,
		VK_FALSE
	};
}