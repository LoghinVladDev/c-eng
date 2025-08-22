//
// Created by loghin on 8/21/25.
//

#include "VulkanPipeline.hpp"
#include "VulkanPipelineLayout.hpp"

#include <cds/collection/VectorView>

#include <device/VulkanLogicalDevice.hpp>
#include <wsi/VulkanSwapChain.hpp>
#include <shader/VulkanShaderModule.hpp>
#include <core/VulkanHandles.hpp>

namespace c_eng::api::vk::detail {
namespace {
using cds::Unexpected;
using cds::VectorView;

auto stagesFor(auto const& stages) noexcept {
  Vector<VkPipelineShaderStageCreateInfo> stageCreateInfos{};
  stageCreateInfos.reserve(stages.size());
  for (auto const& [module, stageFlag, entryPoint] : stages) {
    stageCreateInfos.pushBack(VkPipelineShaderStageCreateInfo{
        .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0u,
        .stage = stageFlag,
        .module = module,
        .pName = entryPoint.data(),
        .pSpecializationInfo = nullptr,
    });
  }

  return stageCreateInfos;
}

auto dynamicStateInfoFor(auto const& dynamicStates) noexcept {
  return VkPipelineDynamicStateCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .dynamicStateCount = static_cast<std::uint32_t>(dynamicStates.size()),
      .pDynamicStates = dynamicStates.data(),
  };
}

auto vertexInputInfoFor() noexcept {
  return VkPipelineVertexInputStateCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .vertexBindingDescriptionCount = 0u,
      .pVertexBindingDescriptions = nullptr,
      .vertexAttributeDescriptionCount = 0u,
      .pVertexAttributeDescriptions = 0u,
  };
}

auto inputAssemblyInfoFor() noexcept {
  return VkPipelineInputAssemblyStateCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .topology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
      .primitiveRestartEnable = VK_FALSE,
  };
}

auto viewportStateInfoFor(VkViewport const& viewport, VkRect2D const& scissor, auto const& dynamicStates) noexcept {
  assert(
      dynamicStates.containsAllOf({VkDynamicState::VK_DYNAMIC_STATE_VIEWPORT, VkDynamicState::VK_DYNAMIC_STATE_SCISSOR})
      && "unhandled case of viewport and/or scissor not dynamic"
  );

  return VkPipelineViewportStateCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .viewportCount = 1u,
      .pViewports = &viewport,
      .scissorCount = 1u,
      .pScissors = &scissor
  };
}

auto rasterizationInfoFor() noexcept {
  return VkPipelineRasterizationStateCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .depthClampEnable = VK_FALSE,
      .rasterizerDiscardEnable = VK_FALSE,
      .polygonMode = VkPolygonMode::VK_POLYGON_MODE_FILL,
      .cullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT,
      .frontFace = VkFrontFace::VK_FRONT_FACE_CLOCKWISE,
      .depthBiasEnable = VK_TRUE,
      .depthBiasConstantFactor = 0.0f,
      .depthBiasClamp = 0.0f,
      .depthBiasSlopeFactor = 1.0f,
      .lineWidth = 1.0f,
  };
}

auto multisampleInfoFor() noexcept {
  return VkPipelineMultisampleStateCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .rasterizationSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT,
      .sampleShadingEnable = VK_FALSE,
      .minSampleShading = 0.0f,
      .pSampleMask = nullptr,
      .alphaToCoverageEnable = VK_FALSE,
      .alphaToOneEnable = VK_FALSE,
  };
}

auto colorBlendAttachmentFor() noexcept {
  return VkPipelineColorBlendAttachmentState{
      .blendEnable = VK_FALSE,
      .srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO,
      .dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO,
      .colorBlendOp = VkBlendOp::VK_BLEND_OP_MIN,
      .srcAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO,
      .dstAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO,
      .alphaBlendOp = VkBlendOp::VK_BLEND_OP_MIN,
      .colorWriteMask = VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT
                      | VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT
                      | VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT
                      | VkColorComponentFlagBits::VK_COLOR_COMPONENT_A_BIT,
  };
}

auto colorBlendInfoFor(VkPipelineColorBlendAttachmentState const& attachmentState) noexcept {
  return VkPipelineColorBlendStateCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0u,
      .logicOpEnable = VK_FALSE,
      .logicOp = VkLogicOp::VK_LOGIC_OP_COPY,
      .attachmentCount = 1u,
      .pAttachments = &attachmentState,
      .blendConstants = {0.0f, 0.0f, 0.0f, 0.0f}
  };
}

auto renderingInfoFor(VkFormat const& format) noexcept {
  return VkPipelineRenderingCreateInfo {
      .sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
      .pNext = nullptr,
      .viewMask = 0u,
      .colorAttachmentCount = 1u,
      .pColorAttachmentFormats = &format,
      .depthAttachmentFormat = VkFormat::VK_FORMAT_UNDEFINED,
      .stencilAttachmentFormat = VkFormat::VK_FORMAT_UNDEFINED
  };
}

inline auto buildPipeline(
    LogicalDevice const& device,
    VkAllocationCallbacks const* allocationCallbacks,
    VectorView<VkPipelineShaderStageCreateInfo const> stages,
    VkPipelineDynamicStateCreateInfo const& dynamicStateInfo,
    VkPipelineViewportStateCreateInfo const& viewportStateInfo,
    VkPipelineColorBlendStateCreateInfo const& colorBlendInfo,
    VkPipelineLayout layout,
    void const* nextChain
) noexcept -> Expected<Pipeline, VkResult> {
  auto const& fns = device.functions();
  assert(fns.vkCreateGraphicsPipelines && fns.vkDestroyPipeline && "undefined behavior");

  auto const vertexInputInfo = vertexInputInfoFor();
  auto const inputAssemblyInfo = inputAssemblyInfoFor();
  auto const rasterizationInfo = rasterizationInfoFor();
  auto const multisampleInfo = multisampleInfoFor();

  auto const createInfo = VkGraphicsPipelineCreateInfo{
      .sType = VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
      .pNext = nextChain,
      .flags = 0u,
      .stageCount = static_cast<std::uint32_t>(stages.size()),
      .pStages = stages.data(),
      .pVertexInputState = &vertexInputInfo,
      .pInputAssemblyState = &inputAssemblyInfo,
      .pTessellationState = nullptr,
      .pViewportState = &viewportStateInfo,
      .pRasterizationState = &rasterizationInfo,
      .pMultisampleState = &multisampleInfo,
      .pDepthStencilState = nullptr,
      .pColorBlendState = &colorBlendInfo,
      .pDynamicState = &dynamicStateInfo,
      .layout = layout,
      .renderPass = VK_NULL_HANDLE,
      .subpass = 0u,
      .basePipelineHandle = VK_NULL_HANDLE,
      .basePipelineIndex = -1
  };

  VkPipeline handle;
  if (auto const result = fns.vkCreateGraphicsPipelines(
      device.handle(), VK_NULL_HANDLE,
      1u, &createInfo, allocationCallbacks, &handle
  ); result != VkResult::VK_SUCCESS) {
    return Unexpected{result};
  }

  return {device, allocationCallbacks, handle};
}

inline auto buildPipelineRenderingOn(
    LogicalDevice const& device,
    VkAllocationCallbacks const* allocationCallbacks,
    VectorView<VkPipelineShaderStageCreateInfo const> stages,
    VkPipelineDynamicStateCreateInfo const& dynamicStateInfo,
    VkPipelineViewportStateCreateInfo const& viewportStateInfo,
    VkPipelineColorBlendStateCreateInfo const& colorBlendInfo,
    VkPipelineLayout layoutHandle,
    SwapChain const& swapChain
) noexcept -> Expected<Pipeline, VkResult> {
  auto const format = swapChain.imageFormat();
  auto const renderingInfo = renderingInfoFor(format);
  return buildPipeline(
      device,
      allocationCallbacks,
      stages,
      dynamicStateInfo,
      viewportStateInfo,
      colorBlendInfo,
      layoutHandle,
      &renderingInfo
  );
}

inline auto buildPipelineStages(
    LogicalDevice const& device,
    VkAllocationCallbacks const* allocationCallbacks,
    auto const& shaderStages,
    auto const& dynamicStates,
    auto const* renderTarget,
    auto const* pipelineLayout
) noexcept -> Expected<Pipeline, VkResult> {
  auto const stages = stagesFor(shaderStages);
  auto const dynamicStateInfo = dynamicStateInfoFor(dynamicStates);

  auto const viewport = VkViewport{};
  auto const scissor = VkRect2D{};
  auto const viewportStateInfo = viewportStateInfoFor(viewport, scissor, dynamicStates);

  auto const colorBlendAttachment = colorBlendAttachmentFor();
  auto const colorBlendInfo = colorBlendInfoFor(colorBlendAttachment);

  VkPipelineLayout layoutHandle = pipelineLayout ? pipelineLayout->handle() : VK_NULL_HANDLE;

  if (!renderTarget) {
    return buildPipeline(
        device,
        allocationCallbacks,
        stages,
        dynamicStateInfo,
        viewportStateInfo,
        colorBlendInfo,
        layoutHandle,
        nullptr
    );
  }

  return buildPipelineRenderingOn(
      device,
      allocationCallbacks,
      stages,
      dynamicStateInfo,
      viewportStateInfo,
      colorBlendInfo,
      layoutHandle,
      *renderTarget
  );
}
} // namespace

Pipeline::~Pipeline() noexcept {
  assert(device().functions().vkDestroyPipeline && "undefined behavior");
  device().functions().vkDestroyPipeline(device().handle(), handle(), allocationCallbacks());
}

auto PipelineBuilder::withShader(
    ShaderModule const& module,
    VkShaderStageFlagBits stage,
    StringView entrypoint
) noexcept -> PipelineBuilder& {
  _shaderStages.emplaceBack(module.handle(), stage, entrypoint);
  return *this;
}

auto PipelineBuilder::build() const noexcept -> Expected<Pipeline, VkResult> {
  return buildPipelineStages(
      device(),
      allocationCallbacks().getOr(device().allocationCallbacks()),
      _shaderStages,
      _dynamicStates,
      _renderTarget,
      _pipelineLayout
  );
}
} // namespace c_eng::api::vk::detail
