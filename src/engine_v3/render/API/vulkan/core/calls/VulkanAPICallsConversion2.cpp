//
// Created by loghin on 07.03.2022.
//

#include <calls/VulkanAPICallsConversion.hpp>
#include <calls/VulkanAPICallsPrivate.hpp>
#include <calls/VulkanAPICallsTypes.hpp>
#include <calls/VulkanAPICallsConversionContextDiagnosis.hpp>
#include <CDS/String>

using namespace cds;

#define C_ENG_MAP_START     SOURCE
#include <ObjectMapping.hpp>

namespace engine :: vulkan {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateGraphicsPipelineContext             * pContext,
            cds :: uint32                               count,
            Type ( GraphicsPipelineCreateInfo ) const * pCreateInfos
    ) noexcept -> VkGraphicsPipelineCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pCreateInfos == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: graphicsPipelineCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: graphicsPipelineCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: graphicsPipelineCount,
                    count
            ))

            count = engine :: vulkan :: config :: graphicsPipelineCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfos[i], & pCreateInfos[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if ( __C_ENG_VULKAN_API_EXTENSION_AMD_MIXED_ATTACHMENT_SAMPLES_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE ) && ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE )

                    case StructureTypeAttachmentSampleCountInfoAMD: {
                        auto pAttachmentSampleCountInfo = reinterpret_cast < hidden :: __AttachmentSampleCountInfo const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->attachmentSampleCountInfos[i],
                                        pAttachmentSampleCountInfo
                                )
                        );

                        pContext->attachmentSampleCountInfos[i].pColorAttachmentSamples = & pContext->attachmentSamples[i][0];

                        if ( pContext->attachmentSampleCountInfos[i].colorAttachmentCount > engine :: vulkan :: config :: sampleCountAttachmentSamplesCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: graphicsPipelineCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: graphicsPipelineCount,
                                    pContext->attachmentSampleCountInfos[i].colorAttachmentCount
                            ))

                            pContext->attachmentSampleCountInfos[i].colorAttachmentCount = engine :: vulkan :: config :: sampleCountAttachmentSamplesCount;
                        }

                        for ( uint32 j = 0U; j < pContext->attachmentSampleCountInfos[i].colorAttachmentCount; ++ j ) {
                            pContext->attachmentSamples[i][j] = static_cast < VkSampleCountFlagBits > ( pAttachmentSampleCountInfo->pColorAttachmentSamples[j] );
                        }

                        break;
                    }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE

                    case StructureTypeGraphicsPipelineShaderGroupsCreateInfoNVidia: {
                        auto pShaderGroupsCreateInfo = reinterpret_cast < Type ( GraphicsPipelineShaderGroupsCreateInfoNVidia ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->pipelineShaderGroupsCreateInfos[i],
                                        pShaderGroupsCreateInfo
                                )
                        );

                        pContext->pipelineShaderGroupsCreateInfos[i].pGroups = & pContext->graphicsShaderGroupCreateInfos[i][0];

                        if ( pContext->pipelineShaderGroupsCreateInfos[i].groupCount > engine :: vulkan :: config :: graphicsPipelineShaderGroupCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: graphicsPipelineShaderGroupCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: graphicsPipelineShaderGroupCount,
                                    pContext->pipelineShaderGroupsCreateInfos[i].groupCount
                            ))

                            pContext->pipelineShaderGroupsCreateInfos[i].groupCount = engine :: vulkan :: config :: graphicsPipelineShaderGroupCount;
                        }

                        for ( uint32 j = 0U; j < pContext->pipelineShaderGroupsCreateInfos[i].groupCount; ++ j ) {
                            (void) toVulkanFormat ( & pContext->graphicsShaderGroupCreateInfos[i][j], & pShaderGroupsCreateInfo->pGroups[j] );

                            pContext->graphicsShaderGroupCreateInfos[i][j].pStages = & pContext->shaderGroupStageCreateInfos[i][j][0];

                            if ( pContext->graphicsShaderGroupCreateInfos[i][j].stageCount > engine :: vulkan :: config :: graphicsPipelineShaderStageCount ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                        "config :: graphicsPipelineShaderStageCount = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: graphicsPipelineShaderStageCount,
                                        pContext->graphicsShaderGroupCreateInfos[i][j].stageCount
                                ))

                                pContext->graphicsShaderGroupCreateInfos[i][j].stageCount = engine :: vulkan :: config :: graphicsPipelineShaderStageCount;
                            }

                            for ( cds :: uint32 k = 0U; k < pContext->graphicsShaderGroupCreateInfos[i][j].stageCount; ++ k ) {
                                auto pInnerCurrent      = reinterpret_cast < Type ( GenericInStructure ) const * > ( pShaderGroupsCreateInfo->pGroups[j].pStages[k].pNext );
                                auto pInnerCurrentVk    = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->shaderGroupStageCreateInfos[i][j][k], & pShaderGroupsCreateInfo->pGroups[j].pStages[k] ) );

                                while ( pInnerCurrent != nullptr ) {

                                    switch ( pInnerCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE

                                        case StructureTypePipelineShaderStageRequiredSubgroupSizeCreateInfo:
                                            pInnerCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                                    toVulkanFormat (
                                                            & pContext->shaderGroupRequiredSubgroupSizeCreateInfos[i][j][k],
                                                            reinterpret_cast < Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const * > ( pInnerCurrent )
                                                    )
                                            );
                                            break;

#endif

                                        default:
                                            break;
                                    }

                                    pInnerCurrentVk = pInnerCurrentVk->pNext == nullptr ? pInnerCurrentVk : pInnerCurrentVk->pNext;
                                    pInnerCurrent   = pInnerCurrent->pNext;
                                }

                                if ( pShaderGroupsCreateInfo->pGroups[j].pStages[k].pSpecializationInfo != nullptr ) {
                                    pContext->shaderGroupStageCreateInfos[i][j][k].pSpecializationInfo = toVulkanFormat ( & pContext->shaderGroupShaderStageSpecializationInfos[i][j][k], pShaderGroupsCreateInfo->pGroups[j].pStages[k].pSpecializationInfo);
                                    pContext->shaderGroupShaderStageSpecializationInfos[i][j][k].pMapEntries = & pContext->shaderGroupShaderStageSpecializationMapEntries[i][j][k][0];

                                    if ( pContext->shaderGroupShaderStageSpecializationInfos[i][j][k].mapEntryCount > engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount ) {
                                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                                "config :: graphicsPipelineSpecializationMapEntryCount = %d. Minimum Required = %d",
                                                engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount,
                                                pContext->shaderGroupShaderStageSpecializationInfos[i][j][k].mapEntryCount
                                        ))

                                        pContext->shaderGroupShaderStageSpecializationInfos[i][j][k].mapEntryCount = engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount;
                                    }

                                    for ( uint32 t = 0U; t < pContext->shaderGroupShaderStageSpecializationInfos[i][j][k].mapEntryCount; ++ t ) {
                                        (void) toVulkanFormat ( & pContext->shaderGroupShaderStageSpecializationMapEntries[i][j][k][t], & pShaderGroupsCreateInfo->pGroups[j].pStages[k].pSpecializationInfo->pMapEntries[t] );
                                    }
                                }

                                pInnerCurrentVk->pNext = nullptr;
                            }

                            if ( pShaderGroupsCreateInfo->pGroups[j].pVertexInputState != nullptr ) {
                                pContext->graphicsShaderGroupCreateInfos[i][j].pVertexInputState = toVulkanFormat ( & pContext->shaderGroupVertexInputStateCreateInfos[i][j], pShaderGroupsCreateInfo->pGroups[j].pVertexInputState );

                                auto pInnerCurrent      = reinterpret_cast < Type ( GenericInStructure ) const * > ( pShaderGroupsCreateInfo->pGroups[j].pVertexInputState->pNext );
                                auto pInnerCurrentVk    = reinterpret_cast < VkBaseOutStructure * > ( & pContext->shaderGroupVertexInputStateCreateInfos[i][j] );

                                while ( pInnerCurrent != nullptr ) {

                                    switch ( pInnerCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

                                        case StructureTypePipelineVertexInputDivisorStateCreateInfo: {
                                            auto pVertexInputDivisorStateCreateInfo = reinterpret_cast < Type ( PipelineVertexInputDivisorStateCreateInfo ) const * > ( pInnerCurrent );
                                            pInnerCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                                    toVulkanFormat (
                                                            & pContext->shaderGroupVertexInputDivisorStateCreateInfos[i][j],
                                                            pVertexInputDivisorStateCreateInfo
                                                    )
                                            );

                                            pContext->shaderGroupVertexInputDivisorStateCreateInfos[i][j].pVertexBindingDivisors = & pContext->shaderGroupVertexInputDivisorDescriptions[i][j][0];

                                            if ( pContext->shaderGroupVertexInputDivisorStateCreateInfos[i][j].vertexBindingDivisorCount > engine :: vulkan :: config :: graphicsPipelineVertexInputBindingDivisorCount ) {
                                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                                        "config :: graphicsPipelineVertexInputBindingDivisorCount = %d. Minimum Required = %d",
                                                        engine :: vulkan :: config :: graphicsPipelineVertexInputBindingDivisorCount,
                                                        pContext->shaderGroupVertexInputDivisorStateCreateInfos[i][j].vertexBindingDivisorCount
                                                ))

                                                pContext->shaderGroupVertexInputDivisorStateCreateInfos[i][j].vertexBindingDivisorCount = engine :: vulkan :: config :: graphicsPipelineVertexInputBindingDivisorCount;
                                            }

                                            for ( uint32 k = 0U; k < pContext->shaderGroupVertexInputDivisorStateCreateInfos[i][j].vertexBindingDivisorCount; ++ k ) {
                                                (void) toVulkanFormat ( & pContext->shaderGroupVertexInputDivisorDescriptions[i][j][k], & pVertexInputDivisorStateCreateInfo->pVertexBindingDivisors[k] );
                                            }

                                            break;
                                        }

#endif

                                        default:
                                            break;
                                    }

                                    pInnerCurrentVk = pInnerCurrentVk->pNext == nullptr ? pInnerCurrentVk : pInnerCurrentVk->pNext;
                                    pInnerCurrent   = pInnerCurrent->pNext;
                                }

                                pInnerCurrentVk->pNext = nullptr;

                                pContext->shaderGroupVertexInputStateCreateInfos[i][j].pVertexBindingDescriptions = & pContext->shaderGroupVertexInputBindingDescriptions[i][j][0];

                                if ( pContext->shaderGroupVertexInputStateCreateInfos[i][j].vertexBindingDescriptionCount > engine :: vulkan :: config :: graphicsPipelineVertexInputBindingCount ) {
                                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                            "config :: graphicsPipelineVertexInputBindingCount = %d. Minimum Required = %d",
                                            engine :: vulkan :: config :: graphicsPipelineVertexInputBindingCount,
                                            pContext->shaderGroupVertexInputStateCreateInfos[i][j].vertexBindingDescriptionCount
                                    ))

                                    pContext->shaderGroupVertexInputStateCreateInfos[i][j].vertexBindingDescriptionCount = engine :: vulkan :: config :: graphicsPipelineVertexInputBindingCount;
                                }

                                for ( uint32 k = 0U; k < pContext->shaderGroupVertexInputStateCreateInfos[i][j].vertexBindingDescriptionCount; ++ k ) {
                                    (void) toVulkanFormat ( & pContext->shaderGroupVertexInputBindingDescriptions[i][j][k], & pShaderGroupsCreateInfo->pGroups[j].pVertexInputState->pVertexBindingDescriptions[k] );
                                }

                                pContext->shaderGroupVertexInputStateCreateInfos[i][j].pVertexAttributeDescriptions = & pContext->shaderGroupVertexInputAttributeDescriptions[i][j][0];

                                if ( pContext->shaderGroupVertexInputStateCreateInfos[i][j].vertexAttributeDescriptionCount > engine :: vulkan :: config :: graphicsPipelineVertexInputAttributeCount ) {
                                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                            "config :: graphicsPipelineVertexInputAttributeCount = %d. Minimum Required = %d",
                                            engine :: vulkan :: config :: graphicsPipelineVertexInputAttributeCount,
                                            pContext->shaderGroupVertexInputStateCreateInfos[i][j].vertexAttributeDescriptionCount
                                    ))

                                    pContext->shaderGroupVertexInputStateCreateInfos[i][j].vertexAttributeDescriptionCount = engine :: vulkan :: config :: graphicsPipelineVertexInputAttributeCount;
                                }

                                for ( uint32 k = 0U; k < pContext->shaderGroupVertexInputStateCreateInfos[i][j].vertexAttributeDescriptionCount; ++ k ) {
                                    (void) toVulkanFormat ( & pContext->shaderGroupVertexInputAttributeDescriptions[i][j][k], & pShaderGroupsCreateInfo->pGroups[j].pVertexInputState->pVertexAttributeDescriptions[k] );
                                }
                            }

                            if ( pShaderGroupsCreateInfo->pGroups[j].pTessellationState != nullptr ) {
                                pContext->graphicsShaderGroupCreateInfos[i][j].pTessellationState = toVulkanFormat ( & pContext->shaderGroupTessellationStateCreateInfos[i][j], pShaderGroupsCreateInfo->pGroups[j].pTessellationState );

                                auto pInnerCurrent      = reinterpret_cast < Type ( GenericInStructure ) const * > ( pShaderGroupsCreateInfo->pGroups[j].pTessellationState->pNext );
                                auto pInnerCurrentVk    = reinterpret_cast < VkBaseOutStructure * > ( & pContext->shaderGroupTessellationStateCreateInfos[i][j] );

                                while ( pInnerCurrent != nullptr ) {

                                    switch ( pInnerCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                                        case StructureTypePipelineTessellationDomainOriginStateCreateInfo:
                                            pInnerCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                                    toVulkanFormat (
                                                            & pContext->shaderGroupTessellationDomainOriginStateCreateInfos[i][j],
                                                            reinterpret_cast < Type ( PipelineTessellationDomainOriginStateCreateInfo ) const * > ( pInnerCurrent )
                                                    )
                                            );
                                            break;

#endif

                                        default:
                                            break;
                                    }

                                    pInnerCurrentVk = pInnerCurrentVk->pNext == nullptr ? pInnerCurrentVk : pInnerCurrentVk->pNext;
                                    pInnerCurrent   = pInnerCurrent->pNext;
                                }

                                pInnerCurrentVk->pNext = nullptr;
                            }
                        }

                        break;
                    }

#endif

#if ( __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE ||__C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE ) && __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXPERIMENTAL_MULTIVIEW_PER_VIEW_ATTRIBUTES_AVAILABLE

                    case StructureTypeMultiviewPerViewAttributesInfoNVidiaExperimental:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->multiviewPerViewAttributesInfos[i],
                                        reinterpret_cast < Type ( MultiviewPerViewAttributesInfoNVidia ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_PIPELINE_COMPILER_CONTROL_AVAILABLE

                    case StructureTypePipelineCompilerControlCreateInfoAMD:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->pipelineCompilerControlCreateInfos[i],
                                        reinterpret_cast < Type ( PipelineCompilerControlCreateInfoAMD ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

                    case StructureTypePipelineCreationFeedbackCreateInfo: {
                        auto pFeedbackCreateInfo = reinterpret_cast < Type ( PipelineCreationFeedbackCreateInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->pipelineCreationFeedbackCreateInfos[i],
                                        pFeedbackCreateInfo
                                )
                        );

                        if ( pFeedbackCreateInfo->pPipelineCreationFeedback != nullptr ) {
                            pContext->pipelineCreationFeedbackCreateInfos[i].pPipelineCreationFeedback = toVulkanFormat (
                                    & pContext->pipelineCreationFeedbacks[i],
                                    pFeedbackCreateInfo->pPipelineCreationFeedback
                            );
                        }

                        pContext->pipelineCreationFeedbackCreateInfos[i].pPipelineStageCreationFeedbacks = & pContext->pipelineCreationStageFeedbacks[i][0];

                        if ( pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount > engine :: vulkan :: config :: graphicsPipelineStageCreationFeedbackCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: graphicsPipelineStageCreationFeedbackCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: graphicsPipelineStageCreationFeedbackCount,
                                    pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount
                            ))

                            pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount = engine :: vulkan :: config :: graphicsPipelineStageCreationFeedbackCount;
                        }

                        for ( uint32 j = 0U; j < pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount; ++ j ) {
                            (void) toVulkanFormat ( & pContext->pipelineCreationStageFeedbacks[i][j], & pFeedbackCreateInfo->pPipelineStageCreationFeedbacks[j] );
                        }

                        break;
                    }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE

                    case StructureTypePipelineDiscardRectangleStateCreateInfo: {
                        auto pDiscardRectangleStateCreateInfo = reinterpret_cast < Type ( PipelineDiscardRectangleStateCreateInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->discardRectangleStateCreateInfos[i],
                                        pDiscardRectangleStateCreateInfo
                                )
                        );

                        pContext->discardRectangleStateCreateInfos[i].pDiscardRectangles = & pContext->discardRectanglesRectangles[i][0];

                        if ( pContext->discardRectangleStateCreateInfos[i].discardRectangleCount > engine :: vulkan :: config :: graphicsPipelineDiscardRectanglesCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: graphicsPipelineDiscardRectanglesCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: graphicsPipelineDiscardRectanglesCount,
                                    pContext->discardRectangleStateCreateInfos[i].discardRectangleCount
                            ))

                            pContext->discardRectangleStateCreateInfos[i].discardRectangleCount = engine :: vulkan :: config :: graphicsPipelineDiscardRectanglesCount;
                        }

                        for ( uint32 j = 0U; j < pContext->discardRectangleStateCreateInfos[i].discardRectangleCount; ++ j ) {
                            pContext->discardRectanglesRectangles[i][j] = {
                                    .offset = {
                                            .x = pDiscardRectangleStateCreateInfo->pDiscardRectangles[j].offset.x,
                                            .y = pDiscardRectangleStateCreateInfo->pDiscardRectangles[j].offset.y
                                    },
                                    .extent = {
                                            .width  = pDiscardRectangleStateCreateInfo->pDiscardRectangles[j].extent.width,
                                            .height = pDiscardRectangleStateCreateInfo->pDiscardRectangles[j].extent.height
                                    }
                            };
                        }

                        break;
                    }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE

                    case StructureTypePipelineFragmentShadingRateEnumStateCreateInfoNVidia:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->fragmentShadingRateEnumStateCreateInfos[i],
                                        reinterpret_cast < Type ( PipelineFragmentShadingRateEnumStateCreateInfoNVidia ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE

                    case StructureTypePipelineFragmentShadingRateStateCreateInfo:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->fragmentShadingRateStateCreateInfos[i],
                                        reinterpret_cast < Type ( PipelineFragmentShadingRateStateCreateInfo ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE

                    case StructureTypePipelineRenderingCreateInfo: {
                        auto pRenderingCreateInfo = reinterpret_cast < Type ( PipelineRenderingCreateInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->dynamicRenderingCreateInfos[i],
                                        pRenderingCreateInfo
                                )
                        );

                        pContext->dynamicRenderingCreateInfos[i].pColorAttachmentFormats = & pContext->dynamicRenderingColorAttachmentFormats[i][0];

                        if ( pContext->dynamicRenderingCreateInfos[i].colorAttachmentCount > engine :: vulkan :: config :: graphicsPipelineDynamicRenderingColorAttachmentCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: graphicsPipelineDynamicRenderingColorAttachmentCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: graphicsPipelineDynamicRenderingColorAttachmentCount,
                                    pContext->dynamicRenderingCreateInfos[i].colorAttachmentCount
                            ))

                            pContext->dynamicRenderingCreateInfos[i].colorAttachmentCount = engine :: vulkan :: config :: graphicsPipelineDynamicRenderingColorAttachmentCount;
                        }

                        for ( uint32 j = 0U; j < pContext->dynamicRenderingCreateInfos[i].colorAttachmentCount; ++ j ) {
                            pContext->dynamicRenderingColorAttachmentFormats[i][j] = static_cast < VkFormat > ( pRenderingCreateInfo->pColorAttachmentFormats[j] );
                        }

                        break;
                    }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE

                    case StructureTypePipelineRepresentativeFragmentTestStateCreateInfoNVidia:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->representativeFragmentTestStateCreateInfos[i],
                                        reinterpret_cast < Type ( PipelineRepresentativeFragmentTestStateCreateInfoNVidia ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;

            pContext->createInfos[i].pStages = & pContext->shaderStageCreateInfos[i][0];

            if ( pContext->createInfos[i].stageCount > engine :: vulkan :: config :: graphicsPipelineShaderStageCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                        "config :: graphicsPipelineShaderStageCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: graphicsPipelineShaderStageCount,
                        pContext->createInfos[i].stageCount
                ))

                pContext->createInfos[i].stageCount = engine :: vulkan :: config :: graphicsPipelineShaderStageCount;
            }

            for ( uint32 j = 0U; j < pContext->createInfos[i].stageCount; ++ j ) {
                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pStages[j].pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->shaderStageCreateInfos[i][j], & pCreateInfos->pStages[j] ) );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                        case StructureTypePipelineShaderStageRequiredSubgroupSizeCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->requiredSubgroupSizeCreateInfos[i][j],
                                            reinterpret_cast < Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                if ( pCreateInfos[i].pStages[j].pSpecializationInfo != nullptr ) {
                    pContext->shaderStageCreateInfos[i][j].pSpecializationInfo = toVulkanFormat (
                            & pContext->shaderStageSpecializationInfos[i][j],
                            pCreateInfos[i].pStages[j].pSpecializationInfo
                    );

                    pContext->shaderStageSpecializationInfos[i][j].pMapEntries = & pContext->shaderStageSpecializationMapEntries[i][j][0];

                    if ( pContext->shaderStageSpecializationInfos[i][j].mapEntryCount > engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: graphicsPipelineSpecializationMapEntryCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount,
                                pContext->shaderStageSpecializationInfos[i][j].mapEntryCount
                        ))

                        pContext->shaderStageSpecializationInfos[i][j].mapEntryCount = engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount;
                    }

                    for ( uint32 k = 0U; k < pContext->shaderStageSpecializationInfos[i][j].mapEntryCount; ++ k ) {
                        (void) toVulkanFormat ( & pContext->shaderStageSpecializationMapEntries[i][j][k], & pCreateInfos[i].pStages[j].pSpecializationInfo->pMapEntries[k] );
                    }
                }

                pCurrentVk->pNext = nullptr;
            }

            if ( pCreateInfos[i].pVertexInputState != nullptr ) {
                pContext->createInfos[i].pVertexInputState = toVulkanFormat (
                        & pContext->vertexInputStateCreateInfos[i],
                        pCreateInfos[i].pVertexInputState
                );

                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pVertexInputState->pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( & pContext->vertexInputStateCreateInfos[i] );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE

                        case StructureTypePipelineVertexInputDivisorStateCreateInfo: {
                            auto pInputDivisorStateCreateInfo = reinterpret_cast < Type ( PipelineVertexInputDivisorStateCreateInfo ) const * > ( pCurrent );
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->vertexInputDivisorStateCreateInfos[i],
                                            pInputDivisorStateCreateInfo
                                    )
                            );

                            pContext->vertexInputDivisorStateCreateInfos[i].pVertexBindingDivisors = & pContext->vertexInputDivisorDescriptions[i][0];

                            if ( pContext->vertexInputDivisorStateCreateInfos[i].vertexBindingDivisorCount > engine :: vulkan :: config :: graphicsPipelineVertexInputBindingDivisorCount ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                        "config :: graphicsPipelineVertexInputBindingDivisorCount = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: graphicsPipelineVertexInputBindingDivisorCount,
                                        pContext->vertexInputDivisorStateCreateInfos[i].vertexBindingDivisorCount
                                ))

                                pContext->vertexInputDivisorStateCreateInfos[i].vertexBindingDivisorCount = engine :: vulkan :: config :: graphicsPipelineVertexInputBindingDivisorCount;
                            }

                            for ( uint32 j = 0U; j < pContext->vertexInputDivisorStateCreateInfos[i].vertexBindingDivisorCount; ++ j ) {
                                (void) toVulkanFormat ( & pContext->vertexInputDivisorDescriptions[i][j], & pInputDivisorStateCreateInfo->pVertexBindingDivisors[j] );
                            }

                            break;
                        }

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;

                pContext->vertexInputStateCreateInfos[i].pVertexBindingDescriptions = & pContext->vertexInputBindingDescriptions[i][0];

                if ( pContext->vertexInputStateCreateInfos[i].vertexBindingDescriptionCount > engine :: vulkan :: config :: graphicsPipelineVertexInputBindingCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                            "config :: graphicsPipelineVertexInputBindingCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: graphicsPipelineVertexInputBindingCount,
                            pContext->vertexInputStateCreateInfos[i].vertexBindingDescriptionCount
                    ))

                    pContext->vertexInputStateCreateInfos[i].vertexBindingDescriptionCount = engine :: vulkan :: config :: graphicsPipelineVertexInputBindingCount;
                }

                for ( uint32 j = 0U; j < pContext->vertexInputStateCreateInfos[i].vertexBindingDescriptionCount; ++ j ) {
                    (void) toVulkanFormat ( & pContext->vertexInputBindingDescriptions[i][j], & pCreateInfos[i].pVertexInputState->pVertexBindingDescriptions[j] );
                }

                pContext->vertexInputStateCreateInfos[i].pVertexAttributeDescriptions = & pContext->vertexInputAttributeDescriptions[i][0];

                if ( pContext->vertexInputStateCreateInfos[i].vertexAttributeDescriptionCount > engine :: vulkan :: config :: graphicsPipelineVertexInputAttributeCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                            "config :: graphicsPipelineVertexInputAttributeCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: graphicsPipelineVertexInputAttributeCount,
                            pContext->vertexInputStateCreateInfos[i].vertexAttributeDescriptionCount
                    ))

                    pContext->vertexInputStateCreateInfos[i].vertexAttributeDescriptionCount = engine :: vulkan :: config :: graphicsPipelineVertexInputAttributeCount;
                }

                for ( uint32 j = 0U; j < pContext->vertexInputStateCreateInfos[i].vertexAttributeDescriptionCount; ++ j ) {
                    (void) toVulkanFormat ( & pContext->vertexInputAttributeDescriptions[i][j], & pCreateInfos[i].pVertexInputState->pVertexAttributeDescriptions[j] );
                }
            }

            if ( pCreateInfos[i].pInputAssemblyState != nullptr ) {
                pContext->createInfos[i].pInputAssemblyState = toVulkanFormat (
                        & pContext->inputAssemblyStateCreateInfos[i],
                        pCreateInfos[i].pInputAssemblyState
                );
            }

            if ( pCreateInfos[i].pTessellationState != nullptr ) {
                pContext->createInfos[i].pTessellationState = toVulkanFormat (
                        & pContext->tessellationStateCreateInfos[i],
                        pCreateInfos[i].pTessellationState
                );

                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pTessellationState->pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( & pContext->tessellationStateCreateInfos[i] );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                        case StructureTypePipelineTessellationDomainOriginStateCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->tessellationDomainOriginStateCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineTessellationDomainOriginStateCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }

            if ( pCreateInfos[i].pViewportState != nullptr ) {
                pContext->createInfos[i].pViewportState = toVulkanFormat (
                        & pContext->viewportStateCreateInfos[i],
                        pCreateInfos[i].pViewportState
                );

                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pViewportState->pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( & pContext->viewportStateCreateInfos[i] );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

                        case StructureTypePipelineViewportCoarseSampleOrderStateCreateInfoNVidia: {
                            auto pCoarseSampleOrderStateCreateInfo  = reinterpret_cast < Type ( PipelineViewportCoarseSampleOrderStateCreateInfoNVidia ) const * > ( pCurrent );
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->viewportCoarseSampleOrderStateCreateInfos[i],
                                            pCoarseSampleOrderStateCreateInfo
                                    )
                            );

                            pContext->viewportCoarseSampleOrderStateCreateInfos[i].pCustomSampleOrders = & pContext->viewportCoarseSampleCustomOrders[i][0];

                            if ( pContext->viewportCoarseSampleOrderStateCreateInfos[i].customSampleOrderCount > engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleOrderCount ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                        "config :: graphicsPipelineViewportCustomSampleOrderCount = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleOrderCount,
                                        pContext->viewportCoarseSampleOrderStateCreateInfos[i].customSampleOrderCount
                                ))

                                pContext->viewportCoarseSampleOrderStateCreateInfos[i].customSampleOrderCount = engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleOrderCount;
                            }

                            for ( uint32 j = 0U; j < pContext->viewportCoarseSampleOrderStateCreateInfos[i].customSampleOrderCount; ++ j ) {
                                toVulkanFormat (
                                        & pContext->viewportCoarseSampleCustomOrders[i][j],
                                        & pCoarseSampleOrderStateCreateInfo->pCustomSampleOrders[j]
                                )->pSampleLocations = & pContext->viewportCoarseSampleCustomLocations[i][j][0];

                                if ( pContext->viewportCoarseSampleCustomOrders[i][j].sampleLocationCount > engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleLocationCount ) {
                                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                            "config :: graphicsPipelineViewportCustomSampleLocationCount = %d. Minimum Required = %d",
                                            engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleLocationCount,
                                            pContext->viewportCoarseSampleCustomOrders[i][j].sampleLocationCount
                                    ))

                                    pContext->viewportCoarseSampleCustomOrders[i][j].sampleLocationCount = engine :: vulkan :: config :: graphicsPipelineViewportCustomSampleLocationCount;
                                }

                                for ( uint32 k = 0U; k < pContext->viewportCoarseSampleCustomOrders[i][j].sampleLocationCount; ++ k ) {
                                    (void) toVulkanFormat ( & pContext->viewportCoarseSampleCustomLocations[i][j][k], & pCoarseSampleOrderStateCreateInfo->pCustomSampleOrders[j].pSampleLocations[k] );
                                }
                            }

                            break;
                        }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE

                        case StructureTypePipelineViewportDepthClipControlCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->viewportDepthClipControlCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineViewportDepthClipControlCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE

                        case StructureTypePipelineViewportExclusiveScissorStateCreateInfoNVidia: {
                            auto pExclusiveScissorStateCreateInfo = reinterpret_cast < Type ( PipelineViewportExclusiveScissorStateCreateInfoNVidia ) const * > ( pCurrent );
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->viewportExclusiveScissorStateCreateInfos[i],
                                            pExclusiveScissorStateCreateInfo
                                    )
                            );

                            pContext->viewportExclusiveScissorStateCreateInfos[i].pExclusiveScissors = & pContext->viewportExclusiveScissors[i][0];

                            if ( pContext->viewportExclusiveScissorStateCreateInfos[i].exclusiveScissorCount > engine :: vulkan :: config :: graphicsPipelineScissorCount ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                        "config :: graphicsPipelineScissorCount = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: graphicsPipelineScissorCount,
                                        pContext->viewportExclusiveScissorStateCreateInfos[i].exclusiveScissorCount
                                ))

                                pContext->viewportExclusiveScissorStateCreateInfos[i].exclusiveScissorCount = engine :: vulkan :: config :: graphicsPipelineScissorCount;
                            }

                            for ( uint32 j = 0U; j < pContext->viewportExclusiveScissorStateCreateInfos[i].exclusiveScissorCount; ++ j ) {
                                pContext->viewportExclusiveScissors[i][j] = {
                                        .offset = {
                                                .x = pExclusiveScissorStateCreateInfo->pExclusiveScissors[j].offset.x,
                                                .y = pExclusiveScissorStateCreateInfo->pExclusiveScissors[j].offset.y
                                        },
                                        .extent = {
                                                .width  = pExclusiveScissorStateCreateInfo->pExclusiveScissors[j].extent.width,
                                                .height = pExclusiveScissorStateCreateInfo->pExclusiveScissors[j].extent.height
                                        }
                                };
                            }

                            break;
                        }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE

                        case StructureTypePipelineViewportShadingRateImageStateCreateInfoNVidia: {
                            auto pShadingRateImageStateCreateInfo = reinterpret_cast < Type ( PipelineViewportShadingRateImageStateCreateInfoNVidia ) const * > ( pCurrent );
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->viewportShadingRateImageStateCreateInfos[i],
                                            pShadingRateImageStateCreateInfo
                                    )
                            );

                            pContext->viewportShadingRateImageStateCreateInfos[i].pShadingRatePalettes = & pContext->viewportShadingRatePalettes[i][0];

                            if ( pContext->viewportShadingRateImageStateCreateInfos[i].viewportCount > engine :: vulkan :: config :: graphicsPipelineViewportCount ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                        "config :: graphicsPipelineViewportCount = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: graphicsPipelineViewportCount,
                                        pContext->viewportShadingRateImageStateCreateInfos[i].viewportCount
                                ))

                                pContext->viewportShadingRateImageStateCreateInfos[i].viewportCount = engine :: vulkan :: config :: graphicsPipelineViewportCount;
                            }

                            for ( uint32 j = 0U; j < pContext->viewportShadingRateImageStateCreateInfos[i].viewportCount; ++ j ) {
                                toVulkanFormat (
                                        & pContext->viewportShadingRatePalettes[i][j],
                                        & pShadingRateImageStateCreateInfo->pShadingRatePalettes[j]
                                )->pShadingRatePaletteEntries = & pContext->viewportShadingRatePaletteEntries[i][j][0];

                                if ( pContext->viewportShadingRatePalettes[i][j].shadingRatePaletteEntryCount > engine :: vulkan :: config :: graphicsPipelineViewportShadingRatePaletteEntryCount ) {
                                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                            "config :: graphicsPipelineViewportShadingRatePaletteEntryCount = %d. Minimum Required = %d",
                                            engine :: vulkan :: config :: graphicsPipelineViewportShadingRatePaletteEntryCount,
                                            pContext->viewportShadingRatePalettes[i][j].shadingRatePaletteEntryCount
                                    ))

                                    pContext->viewportShadingRatePalettes[i][j].shadingRatePaletteEntryCount = engine :: vulkan :: config :: graphicsPipelineViewportShadingRatePaletteEntryCount;
                                }

                                for ( uint32 k = 0U; k < pContext->viewportShadingRatePalettes[i][j].shadingRatePaletteEntryCount; ++ k ) {
                                    pContext->viewportShadingRatePaletteEntries[i][j][k] = static_cast < VkShadingRatePaletteEntryNV > ( pShadingRateImageStateCreateInfo->pShadingRatePalettes[j].pShadingRatePaletteEntries[k] );
                                }
                            }

                            break;
                        }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE

                        case StructureTypePipelineViewportSwizzleStateCreateInfoNVidia: {
                            auto pSwizzleStateCreateInfo = reinterpret_cast < Type ( PipelineViewportSwizzleStateCreateInfoNVidia ) const * > ( pCurrent );
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->viewportSwizzleStateCreateInfos[i],
                                            pSwizzleStateCreateInfo
                                    )
                            );

                            pContext->viewportSwizzleStateCreateInfos[i].pViewportSwizzles = & pContext->viewportSwizzles[i][0];

                            if ( pContext->viewportSwizzleStateCreateInfos[i].viewportCount > engine :: vulkan :: config :: graphicsPipelineViewportCount ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                        "config :: graphicsPipelineViewportCount = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: graphicsPipelineViewportCount,
                                        pContext->viewportSwizzleStateCreateInfos[i].viewportCount
                                ))

                                pContext->viewportSwizzleStateCreateInfos[i].viewportCount = engine :: vulkan :: config :: graphicsPipelineViewportCount;
                            }

                            for ( uint32 j = 0U; j < pContext->viewportSwizzleStateCreateInfos[i].viewportCount; ++ j ) {
                                (void) toVulkanFormat ( & pContext->viewportSwizzles[i][j], & pSwizzleStateCreateInfo->pViewportSwizzles[j] );
                            }

                            break;
                        }

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE

                        case StructureTypePipelineViewportWScalingStateCreateInfoNVidia: {
                            auto pWScalingCreateInfo = reinterpret_cast < Type ( PipelineViewportWScalingStateCreateInfoNVidia ) const * > ( pCurrent );
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->viewportWScalingStateCreateInfos[i],
                                            pWScalingCreateInfo
                                    )
                            );

                            pContext->viewportWScalingStateCreateInfos[i].pViewportWScalings = & pContext->viewportWScalings[i][0];

                            if ( pContext->viewportWScalingStateCreateInfos[i].viewportCount > engine :: vulkan :: config :: graphicsPipelineViewportCount ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                        "config :: graphicsPipelineViewportCount = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: graphicsPipelineViewportCount,
                                        pContext->viewportWScalingStateCreateInfos[i].viewportCount
                                ))

                                pContext->viewportWScalingStateCreateInfos[i].viewportCount = engine :: vulkan :: config :: graphicsPipelineViewportCount;
                            }

                            for ( uint32 j = 0U; j < pContext->viewportWScalingStateCreateInfos[i].viewportCount; ++ j ) {
                                (void) toVulkanFormat ( & pContext->viewportWScalings[i][j], & pWScalingCreateInfo->pViewportWScalings[j] );
                            }

                            break;
                        }

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;

                pContext->viewportStateCreateInfos[i].pViewports = & pContext->viewportStateViewports[i][0];

                if ( pContext->viewportStateCreateInfos[i].viewportCount > engine :: vulkan :: config :: graphicsPipelineViewportCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                            "config :: graphicsPipelineViewportCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: graphicsPipelineViewportCount,
                            pContext->viewportStateCreateInfos[i].viewportCount
                    ))

                    pContext->viewportStateCreateInfos[i].viewportCount = engine :: vulkan :: config :: graphicsPipelineViewportCount;
                }

                for ( uint32 j = 0U; j < pContext->viewportStateCreateInfos[i].viewportCount; ++ j ) {
                    (void) toVulkanFormat ( & pContext->viewportStateViewports[i][j], & pCreateInfos[i].pViewportState->pViewports[j] );
                }

                pContext->viewportStateCreateInfos[i].pScissors = & pContext->viewportStateScissors[i][0];

                if ( pContext->viewportStateCreateInfos[i].scissorCount > engine :: vulkan :: config :: graphicsPipelineScissorCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                            "config :: graphicsPipelineScissorCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: graphicsPipelineScissorCount,
                            pContext->viewportStateCreateInfos[i].scissorCount
                    ))

                    pContext->viewportStateCreateInfos[i].scissorCount = engine :: vulkan :: config :: graphicsPipelineScissorCount;
                }

                for ( uint32 j = 0U; j < pContext->viewportStateCreateInfos[i].scissorCount; ++ j ) {
                    pContext->viewportStateScissors[i][j] = {
                            .offset = {
                                    .x = pCreateInfos[i].pViewportState->pScissors[j].offset.x,
                                    .y = pCreateInfos[i].pViewportState->pScissors[j].offset.y
                            },
                            .extent = {
                                    .width  = pCreateInfos[i].pViewportState->pScissors[j].extent.width,
                                    .height = pCreateInfos[i].pViewportState->pScissors[j].extent.height
                            }
                    };
                }
            }

            if ( pCreateInfos[i].pRasterizationState != nullptr ) {
                pContext->createInfos[i].pRasterizationState = toVulkanFormat (
                        & pContext->rasterizationStateCreateInfos[i],
                        pCreateInfos[i].pRasterizationState
                );

                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pRasterizationState->pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( & pContext->rasterizationStateCreateInfos[i] );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE

                        case StructureTypePipelineRasterizationConservativeStateCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->rasterizationConservativeStateCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineRasterizationConservativeStateCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE

                        case StructureTypePipelineRasterizationDepthClipStateCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->rasterizationDepthClipStateCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineRasterizationDepthClipStateCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE

                        case StructureTypePipelineRasterizationLineStateCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->rasterizationLineStateCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineRasterizationLineStateCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE

                        case StructureTypePipelineRasterizationProvokingVertexStateCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->rasterizationProvokingVertexStateCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineRasterizationProvokingVertexStateCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE

                        case StructureTypePipelineRasterizationStateRasterizationOrderAMD:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->rasterizationStateRasterizationOrders[i],
                                            reinterpret_cast < Type ( PipelineRasterizationStateRasterizationOrderAMD ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE

                        case StructureTypePipelineRasterizationStateStreamCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->rasterizationStateStreamCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineRasterizationStateStreamCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }

            if ( pCreateInfos[i].pMultisampleState != nullptr ) {
                pContext->createInfos[i].pMultisampleState = toVulkanFormat (
                        & pContext->multisampleStateCreateInfos[i],
                        pCreateInfos[i].pMultisampleState
                );

                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pMultisampleState->pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( & pContext->multisampleStateCreateInfos[i] );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE

                        case StructureTypePipelineCoverageModulationStateCreateInfoNVidia:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->multisampleCoverageModulationCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineCoverageModulationStateCreateInfoNVidia ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE

                        case StructureTypePipelineCoverageReductionStateCreateInfoNVidia:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->multisampleCoverageReductionCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineCoverageReductionStateCreateInfoNVidia ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE

                        case StructureTypePipelineCoverageToColorStateCreateInfoNVidia:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->multisampleCoverageToColorCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineCoverageToColorStateCreateInfoNVidia ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE

                        case StructureTypePipelineSampleLocationsStateCreateInfo: {
                            auto pSampleLocationsStateCreateInfo = reinterpret_cast < Type ( PipelineSampleLocationsStateCreateInfo ) const * > ( pCurrent );
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->multisampleSampleLocationsCreateInfos[i],
                                            pSampleLocationsStateCreateInfo
                                    )
                            );

                            pContext->multisampleSampleLocationsCreateInfos[i].sampleLocationsInfo.pSampleLocations = & pContext->multisampleSampleLocations[i][0];

                            if ( pContext->multisampleSampleLocationsCreateInfos[i].sampleLocationsInfo.sampleLocationsCount > engine :: vulkan :: config :: graphicsPipelineMultisampleSampleLocations ) {
                                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                        "config :: graphicsPipelineMultisampleSampleLocations = %d. Minimum Required = %d",
                                        engine :: vulkan :: config :: graphicsPipelineMultisampleSampleLocations,
                                        pContext->multisampleSampleLocationsCreateInfos[i].sampleLocationsInfo.sampleLocationsCount
                                ))

                                pContext->multisampleSampleLocationsCreateInfos[i].sampleLocationsInfo.sampleLocationsCount = engine :: vulkan :: config :: graphicsPipelineMultisampleSampleLocations;
                            }

                            for ( uint32 j = 0U; j < pContext->multisampleSampleLocationsCreateInfos[i].sampleLocationsInfo.sampleLocationsCount; ++ j ) {
                                pContext->multisampleSampleLocations[i][j] = {
                                        .x  = pSampleLocationsStateCreateInfo->sampleLocationsInfo.pSampleLocations[j].x,
                                        .y  = pSampleLocationsStateCreateInfo->sampleLocationsInfo.pSampleLocations[j].y
                                };
                            }

                            break;
                        }

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }

            if ( pCreateInfos[i].pDepthStencilState != nullptr ) {
                pContext->createInfos[i].pDepthStencilState = toVulkanFormat (
                        & pContext->depthStencilStateCreateInfos[i],
                        pCreateInfos[i].pDepthStencilState
                );
            }

            if ( pCreateInfos[i].pColorBlendState != nullptr ) {
                pContext->createInfos[i].pColorBlendState = toVulkanFormat (
                        & pContext->colorBlendStateCreateInfos[i],
                        pCreateInfos[i].pColorBlendState
                );

                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pColorBlendState->pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( & pContext->colorBlendStateCreateInfos[i] );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE

                        case StructureTypePipelineColorBlendAdvancedStateCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->colorBlendAdvancedStateCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineColorBlendAdvancedStateCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE

                        case StructureTypePipelineColorWriteCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->colorBlendColorWriteCreateInfos[i],
                                            reinterpret_cast < Type ( PipelineColorWriteCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;

                pContext->colorBlendStateCreateInfos[i].pAttachments = & pContext->colorBlendStateAttachments[i][0];

                if ( pContext->colorBlendStateCreateInfos[i].attachmentCount > engine :: vulkan :: config :: graphicsPipelineColorBlendAttachmentCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                            "config :: graphicsPipelineColorBlendAttachmentCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: graphicsPipelineColorBlendAttachmentCount,
                            pContext->colorBlendStateCreateInfos[i].attachmentCount
                    ))

                    pContext->colorBlendStateCreateInfos[i].attachmentCount = engine :: vulkan :: config :: graphicsPipelineColorBlendAttachmentCount;
                }

                for ( uint32 j = 0U; j < pContext->colorBlendStateCreateInfos[i].attachmentCount; ++ j ) {
                    (void) toVulkanFormat ( & pContext->colorBlendStateAttachments[i][j], & pCreateInfos[i].pColorBlendState->pAttachments[j] );
                }
            }

            if ( pCreateInfos[i].pDynamicState != nullptr ) {
                pContext->createInfos[i].pDynamicState = toVulkanFormat (
                        & pContext->dynamicStateCreateInfos[i],
                        pCreateInfos[i].pDynamicState
                );

                pContext->dynamicStateCreateInfos[i].pDynamicStates = & pContext->dynamicStateStates[i][0];

                if ( pContext->dynamicStateCreateInfos[i].dynamicStateCount > engine :: vulkan :: config :: graphicsPipelineDynamicStateCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                            "config :: graphicsPipelineDynamicStateCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: graphicsPipelineDynamicStateCount,
                            pContext->dynamicStateCreateInfos[i].dynamicStateCount
                    ))

                    pContext->dynamicStateCreateInfos[i].dynamicStateCount = engine :: vulkan :: config :: graphicsPipelineDynamicStateCount;
                }

                for ( uint32 j = 0U; j < pContext->dynamicStateCreateInfos[i].dynamicStateCount; ++ j ) {
                    pContext->dynamicStateStates[i][j] = static_cast < VkDynamicState > ( pCreateInfos[i].pDynamicState->pDynamicStates[j] );
                }
            }
        }

        return & pContext->createInfos[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkGraphicsPipelineCreateInfo              * pDestination,
            Type ( GraphicsPipelineCreateInfo ) const * pSource
    ) noexcept -> VkGraphicsPipelineCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .stageCount             = pSource->stageCount,
                .pStages                = nullptr,
                .pVertexInputState      = nullptr,
                .pInputAssemblyState    = nullptr,
                .pTessellationState     = nullptr,
                .pViewportState         = nullptr,
                .pRasterizationState    = nullptr,
                .pMultisampleState      = nullptr,
                .pDepthStencilState     = nullptr,
                .pColorBlendState       = nullptr,
                .pDynamicState          = nullptr,
                .layout                 = pSource->layout,
                .renderPass             = pSource->renderPass,
                .subpass                = pSource->subpass,
                .basePipelineHandle     = pSource->basePipelineHandle,
                .basePipelineIndex      = pSource->basePipelineIndex
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkGraphicsPipelineShaderGroupsCreateInfoNV              * pDestination,
            Type ( GraphicsPipelineShaderGroupsCreateInfoNVidia ) const * pSource
    ) noexcept -> VkGraphicsPipelineShaderGroupsCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .groupCount             = pSource->groupCount,
                .pGroups                = nullptr,
                .pipelineCount          = pSource->pipelineCount,
                .pPipelines             = pSource->pPipelines
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEVICE_GENERATED_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkGraphicsShaderGroupCreateInfoNV              * pDestination,
            Type ( GraphicsShaderGroupCreateInfoNVidia ) const * pSource
    ) noexcept -> VkGraphicsShaderGroupCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .stageCount             = pSource->stageCount,
                .pStages                = nullptr,
                .pVertexInputState      = nullptr,
                .pTessellationState     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineVertexInputStateCreateInfo              * pDestination,
            Type ( PipelineVertexInputStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineVertexInputStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .vertexBindingDescriptionCount      = pSource->vertexBindingDescriptionCount,
                .pVertexBindingDescriptions         = nullptr,
                .vertexAttributeDescriptionCount    = pSource->vertexAttributeDescriptionCount,
                .pVertexAttributeDescriptions       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkVertexInputBindingDescription              * pDestination,
            Type ( VertexInputBindingDescription ) const * pSource
    ) noexcept -> VkVertexInputBindingDescription * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .binding    = pSource->binding,
                .stride     = pSource->stride,
                .inputRate  = static_cast < VkVertexInputRate > ( pSource->inputRate )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkVertexInputAttributeDescription              * pDestination,
            Type ( VertexInputAttributeDescription ) const * pSource
    ) noexcept -> VkVertexInputAttributeDescription * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .location   = pSource->location,
                .binding    = pSource->binding,
                .format     = static_cast < VkFormat > ( pSource->format ),
                .offset     = pSource->offset
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    auto toVulkanFormat (
            VkPipelineVertexInputDivisorStateCreateInfoEXT              * pDestination,
            Type ( PipelineVertexInputDivisorStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineVertexInputDivisorStateCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT,
                .pNext                      = nullptr,
                .vertexBindingDivisorCount  = pSource->vertexBindingDivisorCount,
                .pVertexBindingDivisors     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VERTEX_ATTRIBUTE_DIVISOR_AVAILABLE
    auto toVulkanFormat (
            VkVertexInputBindingDivisorDescriptionEXT              * pDestination,
            Type ( VertexInputBindingDivisorDescription ) const * pSource
    ) noexcept -> VkVertexInputBindingDivisorDescriptionEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .binding    = pSource->binding,
                .divisor    = pSource->divisor
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineTessellationStateCreateInfo              * pDestination,
            Type ( PipelineTessellationStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineTessellationStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .patchControlPoints = pSource->patchControlPoints
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkPipelineTessellationDomainOriginStateCreateInfo              * pDestination,
            Type ( PipelineTessellationDomainOriginStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineTessellationDomainOriginStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO,
                .pNext              = nullptr,
                .domainOrigin       = static_cast < VkTessellationDomainOrigin > ( pSource->domainOrigin )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DISCARD_RECTANGLES_AVAILABLE
    auto toVulkanFormat (
            VkPipelineDiscardRectangleStateCreateInfoEXT              * pDestination,
            Type ( PipelineDiscardRectangleStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineDiscardRectangleStateCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .discardRectangleMode   = static_cast < VkDiscardRectangleModeEXT > ( pSource->discardRectangleMode ),
                .discardRectangleCount  = pSource->discardRectangleCount,
                .pDiscardRectangles     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_SHADING_RATE_ENUMS_AVAILABLE
    auto toVulkanFormat (
            VkPipelineFragmentShadingRateEnumStateCreateInfoNV              * pDestination,
            Type ( PipelineFragmentShadingRateEnumStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineFragmentShadingRateEnumStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .shadingRateType        = static_cast < VkFragmentShadingRateTypeNV > ( pSource->shadingRateType ),
                .shadingRate            = static_cast < VkFragmentShadingRateNV > ( pSource->shadingRate ),
                .combinerOps            = {
                        static_cast < VkFragmentShadingRateCombinerOpKHR > ( pSource->combinerOperations[0] ),
                        static_cast < VkFragmentShadingRateCombinerOpKHR > ( pSource->combinerOperations[1] )
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_FRAGMENT_SHADING_RATE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineFragmentShadingRateStateCreateInfoKHR              * pDestination,
            Type ( PipelineFragmentShadingRateStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineFragmentShadingRateStateCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR,
                .pNext                  = nullptr,
                .fragmentSize           = {
                        .width                  = pSource->fragmentSize.width,
                        .height                 = pSource->fragmentSize.height
                },
                .combinerOps            = {
                        static_cast < VkFragmentShadingRateCombinerOpKHR > ( pSource->combinerOperations[0] ),
                        static_cast < VkFragmentShadingRateCombinerOpKHR > ( pSource->combinerOperations[1] )
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRenderingCreateInfo_t              * pDestination,
            Type ( PipelineRenderingCreateInfo ) const * pSource
    ) noexcept -> VkPipelineRenderingCreateInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
#elif __C_ENG_VULKAN_API_EXTENSION_KHRONOS_DYNAMIC_RENDERING_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR,
#endif
                .pNext                      = nullptr,
                .viewMask                   = pSource->viewMask,
                .colorAttachmentCount       = pSource->colorAttachmentCount,
                .pColorAttachmentFormats    = nullptr,
                .depthAttachmentFormat      = static_cast < VkFormat > ( pSource->depthAttachmentFormat ),
                .stencilAttachmentFormat    = static_cast < VkFormat > ( pSource->stencilAttachmentFormat )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_REPRESENTATIVE_FRAGMENT_TEST_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRepresentativeFragmentTestStateCreateInfoNV              * pDestination,
            Type ( PipelineRepresentativeFragmentTestStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineRepresentativeFragmentTestStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV,
                .pNext                              = nullptr,
                .representativeFragmentTestEnable   = pSource->representativeFragmentTestEnable
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineInputAssemblyStateCreateInfo              * pDestination,
            Type ( PipelineInputAssemblyStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineInputAssemblyStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .topology               = static_cast < VkPrimitiveTopology > ( pSource->topology ),
                .primitiveRestartEnable = pSource->primitiveRestartEnable
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineViewportStateCreateInfo              * pDestination,
            Type ( PipelineViewportStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineViewportStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .viewportCount          = pSource->viewportCount,
                .pViewports             = nullptr,
                .scissorCount           = pSource->scissorCount,
                .pScissors              = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineViewportCoarseSampleOrderStateCreateInfoNV              * pDestination,
            Type ( PipelineViewportCoarseSampleOrderStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineViewportCoarseSampleOrderStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .sampleOrderType        = static_cast < VkCoarseSampleOrderTypeNV > ( pSource->sampleOrderType ),
                .customSampleOrderCount = pSource->customSampleOrderCount,
                .pCustomSampleOrders    = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    auto toVulkanFormat (
            VkCoarseSampleOrderCustomNV              * pDestination,
            Type ( CoarseSampleOrderCustomNVidia ) const * pSource
    ) noexcept -> VkCoarseSampleOrderCustomNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .shadingRate            = static_cast < VkShadingRatePaletteEntryNV > ( pSource->shadingRate ),
                .sampleCount            = pSource->sampleCount,
                .sampleLocationCount    = pSource->sampleLocationCount,
                .pSampleLocations       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    auto toVulkanFormat (
            VkCoarseSampleLocationNV              * pDestination,
            Type ( CoarseSampleLocationNVidia ) const * pSource
    ) noexcept -> VkCoarseSampleLocationNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .pixelX     = pSource->pixelX,
                .pixelY     = pSource->pixelY,
                .sample     = pSource->sample
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_CONTROL_AVAILABLE
    auto toVulkanFormat (
            VkPipelineViewportDepthClipControlCreateInfoEXT              * pDestination,
            Type ( PipelineViewportDepthClipControlCreateInfo ) const * pSource
    ) noexcept -> VkPipelineViewportDepthClipControlCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_DEPTH_CLIP_CONTROL_CREATE_INFO_EXT,
                .pNext              = nullptr,
                .negativeOneToOne   = pSource->negativeOneToOne
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SCISSOR_EXCLUSIVE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineViewportExclusiveScissorStateCreateInfoNV              * pDestination,
            Type ( PipelineViewportExclusiveScissorStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineViewportExclusiveScissorStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .exclusiveScissorCount  = pSource->exclusiveScissorCount,
                .pExclusiveScissors     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineViewportShadingRateImageStateCreateInfoNV              * pDestination,
            Type ( PipelineViewportShadingRateImageStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineViewportShadingRateImageStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .shadingRateImageEnable = pSource->shadingRateImageEnable,
                .viewportCount          = pSource->viewportCount,
                .pShadingRatePalettes   = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_SHADING_RATE_IMAGE_AVAILABLE
    auto toVulkanFormat (
            VkShadingRatePaletteNV              * pDestination,
            Type ( ShadingRatePaletteNVidia ) const * pSource
    ) noexcept -> VkShadingRatePaletteNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .shadingRatePaletteEntryCount   = pSource->shadingRatePaletteEntryCount,
                .pShadingRatePaletteEntries     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineViewportSwizzleStateCreateInfoNV              * pDestination,
            Type ( PipelineViewportSwizzleStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineViewportSwizzleStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .viewportCount      = pSource->viewportCount,
                .pViewportSwizzles  = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_VIEWPORT_SWIZZLE_AVAILABLE
    auto toVulkanFormat (
            VkViewportSwizzleNV              * pDestination,
            Type ( ViewportSwizzleNVidia ) const * pSource
    ) noexcept -> VkViewportSwizzleNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .x  = static_cast < VkViewportCoordinateSwizzleNV > ( pSource->x ),
                .y  = static_cast < VkViewportCoordinateSwizzleNV > ( pSource->y ),
                .z  = static_cast < VkViewportCoordinateSwizzleNV > ( pSource->z ),
                .w  = static_cast < VkViewportCoordinateSwizzleNV > ( pSource->w )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
    auto toVulkanFormat (
            VkPipelineViewportWScalingStateCreateInfoNV              * pDestination,
            Type ( PipelineViewportWScalingStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineViewportWScalingStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .viewportWScalingEnable = pSource->viewportWScalingEnable,
                .viewportCount          = pSource->viewportCount,
                .pViewportWScalings     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_CLIP_SPACE_W_SCALING_AVAILABLE
    auto toVulkanFormat (
            VkViewportWScalingNV              * pDestination,
            Type ( ViewportWScalingNVidia ) const * pSource
    ) noexcept -> VkViewportWScalingNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .xcoeff = pSource->xCoefficient,
                .ycoeff = pSource->yCoefficient
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRasterizationStateCreateInfo              * pDestination,
            Type ( PipelineRasterizationStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineRasterizationStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .depthClampEnable           = pSource->depthClampEnable,
                .rasterizerDiscardEnable    = pSource->rasterizerDiscardEnable,
                .polygonMode                = static_cast < VkPolygonMode > ( pSource->polygonMode ),
                .cullMode                   = pSource->cullMode,
                .frontFace                  = static_cast < VkFrontFace > ( pSource->frontFace ),
                .depthBiasEnable            = pSource->depthBiasEnable,
                .depthBiasConstantFactor    = pSource->depthBiasConstantFactor,
                .depthBiasClamp             = pSource->depthBiasClamp,
                .depthBiasSlopeFactor       = pSource->depthBiasSlopeFactor,
                .lineWidth                  = pSource->lineWidth
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CONSERVATIVE_RASTERIZATION_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRasterizationConservativeStateCreateInfoEXT              * pDestination,
            Type ( PipelineRasterizationConservativeStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineRasterizationConservativeStateCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .conservativeRasterizationMode      = static_cast < VkConservativeRasterizationModeEXT > ( pSource->conservativeRasterizationMode ),
                .extraPrimitiveOverestimationSize   = pSource->extraPrimitiveOverestimationSize
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_DEPTH_CLIP_ENABLE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRasterizationDepthClipStateCreateInfoEXT              * pDestination,
            Type ( PipelineRasterizationDepthClipStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineRasterizationDepthClipStateCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .depthClipEnable                    = pSource->depthClipEnable
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_LINE_RASTERIZATION_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRasterizationLineStateCreateInfoEXT              * pDestination,
            Type ( PipelineRasterizationLineStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineRasterizationLineStateCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT,
                .pNext                              = nullptr,
                .lineRasterizationMode              = static_cast < VkLineRasterizationModeEXT > ( pSource->lineRasterizationMode ),
                .stippledLineEnable                 = pSource->stippledLineEnable,
                .lineStippleFactor                  = pSource->lineStippleFactor,
                .lineStipplePattern                 = pSource->lineStipplePattern
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_PROVOKING_VERTEX_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRasterizationProvokingVertexStateCreateInfoEXT              * pDestination,
            Type ( PipelineRasterizationProvokingVertexStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineRasterizationProvokingVertexStateCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_PROVOKING_VERTEX_STATE_CREATE_INFO_EXT,
                .pNext                              = nullptr,
                .provokingVertexMode                = static_cast < VkProvokingVertexModeEXT > ( pSource->provokingVertexMode )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_AMD_RASTERIZATION_ORDER_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRasterizationStateRasterizationOrderAMD              * pDestination,
            Type ( PipelineRasterizationStateRasterizationOrderAMD ) const * pSource
    ) noexcept -> VkPipelineRasterizationStateRasterizationOrderAMD * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD,
                .pNext                              = nullptr,
                .rasterizationOrder                 = static_cast < VkRasterizationOrderAMD > ( pSource->rasterizationOrder )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_TRANSFORM_FEEDBACK_AVAILABLE
    auto toVulkanFormat (
            VkPipelineRasterizationStateStreamCreateInfoEXT              * pDestination,
            Type ( PipelineRasterizationStateStreamCreateInfo ) const * pSource
    ) noexcept -> VkPipelineRasterizationStateStreamCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .rasterizationStream                = pSource->rasterizationStream
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineMultisampleStateCreateInfo              * pDestination,
            Type ( PipelineMultisampleStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineMultisampleStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .rasterizationSamples               = static_cast < VkSampleCountFlagBits > ( pSource->rasterizationSamples ),
                .sampleShadingEnable                = pSource->sampleShadingEnable,
                .minSampleShading                   = pSource->minSampleShading,
                .pSampleMask                        = pSource->pSampleMask,
                .alphaToCoverageEnable              = pSource->alphaToCoverageEnable,
                .alphaToOneEnable                   = pSource->alphaToOneEnable
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAMEBUFFER_MIXED_SAMPLES_AVAILABLE
    auto toVulkanFormat (
            VkPipelineCoverageModulationStateCreateInfoNV              * pDestination,
            Type ( PipelineCoverageModulationStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineCoverageModulationStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .coverageModulationMode             = static_cast < VkCoverageModulationModeNV > ( pSource->coverageModulationMode ),
                .coverageModulationTableEnable      = pSource->coverageModulationTableEnable,
                .coverageModulationTableCount       = pSource->coverageModulationTableCount,
                .pCoverageModulationTable           = pSource->pCoverageModulationTable
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_COVERAGE_REDUCTION_MODE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineCoverageReductionStateCreateInfoNV              * pDestination,
            Type ( PipelineCoverageReductionStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineCoverageReductionStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .coverageReductionMode              = static_cast < VkCoverageReductionModeNV > ( pSource->coverageReductionMode )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_FRAGMENT_COVERAGE_TO_COLOR_AVAILABLE
    auto toVulkanFormat (
            VkPipelineCoverageToColorStateCreateInfoNV              * pDestination,
            Type ( PipelineCoverageToColorStateCreateInfoNVidia ) const * pSource
    ) noexcept -> VkPipelineCoverageToColorStateCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .coverageToColorEnable              = pSource->coverageToColorEnable,
                .coverageToColorLocation            = pSource->coverageToColorLocation
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_SAMPLE_LOCATIONS_AVAILABLE
    auto toVulkanFormat (
            VkPipelineSampleLocationsStateCreateInfoEXT              * pDestination,
            Type ( PipelineSampleLocationsStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineSampleLocationsStateCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT,
                .pNext                              = nullptr,
                .sampleLocationsEnable              = pSource->sampleLocationsEnable,
                .sampleLocationsInfo                = {
                        .sType                              = VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT,
                        .pNext                              = nullptr,
                        .sampleLocationsPerPixel            = static_cast < VkSampleCountFlagBits > ( pSource->sampleLocationsInfo.sampleLocationsPerPixel ),
                        .sampleLocationGridSize             = {
                                .width                              = pSource->sampleLocationsInfo.sampleLocationGridSize.width,
                                .height                             = pSource->sampleLocationsInfo.sampleLocationGridSize.height
                        },
                        .sampleLocationsCount               = pSource->sampleLocationsInfo.sampleLocationsCount,
                        .pSampleLocations                   = nullptr
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineDepthStencilStateCreateInfo              * pDestination,
            Type ( PipelineDepthStencilStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineDepthStencilStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .depthTestEnable                    = pSource->depthTestEnable,
                .depthWriteEnable                   = pSource->depthWriteEnable,
                .depthCompareOp                     = static_cast < VkCompareOp > ( pSource->depthCompareOperation ),
                .depthBoundsTestEnable              = pSource->depthBoundsTestEnable,
                .stencilTestEnable                  = pSource->stencilTestEnable,
                .front                              = {
                        .failOp                             = static_cast < VkStencilOp > ( pSource->front.failOperation ),
                        .passOp                             = static_cast < VkStencilOp > ( pSource->front.passOperation ),
                        .depthFailOp                        = static_cast < VkStencilOp > ( pSource->front.depthFailOperation ),
                        .compareOp                          = static_cast < VkCompareOp > ( pSource->front.compareOperation ),
                        .compareMask                        = pSource->front.compareMask,
                        .writeMask                          = pSource->front.writeMask,
                        .reference                          = pSource->front.reference
                },
                .back                               = {
                        .failOp                             = static_cast < VkStencilOp > ( pSource->back.failOperation ),
                        .passOp                             = static_cast < VkStencilOp > ( pSource->back.passOperation ),
                        .depthFailOp                        = static_cast < VkStencilOp > ( pSource->back.depthFailOperation ),
                        .compareOp                          = static_cast < VkCompareOp > ( pSource->back.compareOperation ),
                        .compareMask                        = pSource->back.compareMask,
                        .writeMask                          = pSource->back.writeMask,
                        .reference                          = pSource->back.reference
                },
                .minDepthBounds                     = pSource->minDepthBounds,
                .maxDepthBounds                     = pSource->maxDepthBounds
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineColorBlendStateCreateInfo              * pDestination,
            Type ( PipelineColorBlendStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineColorBlendStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .logicOpEnable                      = pSource->logicOperationEnable,
                .logicOp                            = static_cast < VkLogicOp > ( pSource->logicOperation ),
                .attachmentCount                    = pSource->attachmentCount,
                .pAttachments                       = nullptr,
                .blendConstants                     = {
                        pSource->blendConstants[0],
                        pSource->blendConstants[1],
                        pSource->blendConstants[2],
                        pSource->blendConstants[3]
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BLEND_OPERATION_ADVANCED_AVAILABLE
    auto toVulkanFormat (
            VkPipelineColorBlendAdvancedStateCreateInfoEXT              * pDestination,
            Type ( PipelineColorBlendAdvancedStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineColorBlendAdvancedStateCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT,
                .pNext                              = nullptr,
                .srcPremultiplied                   = pSource->sourcePremultiplied,
                .dstPremultiplied                   = pSource->destinationPremultiplied,
                .blendOverlap                       = static_cast < VkBlendOverlapEXT > ( pSource->blendOverlap )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_COLOR_WRITE_ENABLE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineColorWriteCreateInfoEXT              * pDestination,
            Type ( PipelineColorWriteCreateInfo ) const * pSource
    ) noexcept -> VkPipelineColorWriteCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_COLOR_WRITE_CREATE_INFO_EXT,
                .pNext                              = nullptr,
                .attachmentCount                    = pSource->attachmentCount,
                .pColorWriteEnables                 = pSource->pColorWriteEnables
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineColorBlendAttachmentState              * pDestination,
            Type ( PipelineColorBlendAttachmentState ) const * pSource
    ) noexcept -> VkPipelineColorBlendAttachmentState * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .blendEnable            = pSource->blendEnable,
                .srcColorBlendFactor    = static_cast < VkBlendFactor > ( pSource->sourceColorBlendFactor ),
                .dstColorBlendFactor    = static_cast < VkBlendFactor > ( pSource->destinationColorBlendFactor ),
                .colorBlendOp           = static_cast < VkBlendOp > ( pSource->colorBlendOperation ),
                .srcAlphaBlendFactor    = static_cast < VkBlendFactor > ( pSource->sourceAlphaBlendFactor ),
                .dstAlphaBlendFactor    = static_cast < VkBlendFactor > ( pSource->destinationAlphaBlendFactor ),
                .alphaBlendOp           = static_cast < VkBlendOp > ( pSource->alphaBlendOperation ),
                .colorWriteMask         = pSource->colorWriteMask
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineDynamicStateCreateInfo              * pDestination,
            Type ( PipelineDynamicStateCreateInfo ) const * pSource
    ) noexcept -> VkPipelineDynamicStateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .dynamicStateCount  = pSource->dynamicStateCount,
                .pDynamicStates     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto extractContext (
            cds :: uint32                                count,
            Type ( GraphicsPipelineCreateInfo )  const * pCreateInfos,
            CreateGraphicsPipelineContext        const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( count == 0U || pCreateInfos == nullptr || pContext == nullptr ) {
            return;
        }

#endif

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pNext );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

                    case StructureTypePipelineCreationFeedbackCreateInfo: {
                        auto pFeedbackCreateInfo = reinterpret_cast < Type ( PipelineCreationFeedbackCreateInfo ) const * > ( pCurrent );

                        if ( pFeedbackCreateInfo->pPipelineCreationFeedback != nullptr ) {
                            (void) fromVulkanFormat ( pFeedbackCreateInfo->pPipelineCreationFeedback, & pContext->pipelineCreationFeedbacks[i] );
                        }

                        for ( cds :: uint32 j = 0U; j < pFeedbackCreateInfo->pipelineStageCreationFeedbackCount; ++ j ) {
                            (void) fromVulkanFormat ( & pFeedbackCreateInfo->pPipelineStageCreationFeedbacks[j], & pContext->pipelineCreationStageFeedbacks[i][j] );
                        }

                        break;
                    }

#endif

                    default:
                        break;
                }

                pCurrent = pCurrent->pNext;
            }
        }
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto extractContext (
            cds :: uint32                                count,
            Type ( RayTracingPipelineCreateInfoNVidia )  const * pCreateInfos,
            CreateRayTracingPipelineNVidiaContext        const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( count == 0U || pCreateInfos == nullptr || pContext == nullptr ) {
            return;
        }

#endif

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pNext );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

                    case StructureTypePipelineCreationFeedbackCreateInfo: {
                        auto pFeedbackCreateInfo = reinterpret_cast < Type ( PipelineCreationFeedbackCreateInfo ) const * > ( pCurrent );

                        if ( pFeedbackCreateInfo->pPipelineCreationFeedback != nullptr ) {
                            (void) fromVulkanFormat ( pFeedbackCreateInfo->pPipelineCreationFeedback, & pContext->pipelineCreationFeedbacks[i] );
                        }

                        for ( cds :: uint32 j = 0U; j < pFeedbackCreateInfo->pipelineStageCreationFeedbackCount; ++ j ) {
                            (void) fromVulkanFormat ( & pFeedbackCreateInfo->pPipelineStageCreationFeedbacks[j], & pContext->pipelineCreationStageFeedbacks[i][j] );
                        }

                        break;
                    }

#endif

                    default:
                        break;
                }

                pCurrent = pCurrent->pNext;
            }
        }
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto prepareContext (
            CreateRayTracingPipelineNVidiaContext             * pContext,
            cds :: uint32                                       count,
            Type ( RayTracingPipelineCreateInfoNVidia ) const * pCreateInfos
    ) noexcept -> VkRayTracingPipelineCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pCreateInfos == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: rayTracingPipelineCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: rayTracingPipelineCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: rayTracingPipelineCount,
                    count
            ))

            count = engine :: vulkan :: config :: rayTracingPipelineCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfos[i], & pCreateInfos[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

                    case StructureTypePipelineCreationFeedbackCreateInfo: {
                        auto pFeedbackCreateInfo = reinterpret_cast < Type ( PipelineCreationFeedbackCreateInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->pipelineCreationFeedbackCreateInfos[i],
                                        pFeedbackCreateInfo
                                )
                        );

                        if ( pFeedbackCreateInfo->pPipelineCreationFeedback != nullptr ) {
                            pContext->pipelineCreationFeedbackCreateInfos[i].pPipelineCreationFeedback = toVulkanFormat (
                                    & pContext->pipelineCreationFeedbacks[i],
                                    pFeedbackCreateInfo->pPipelineCreationFeedback
                            );
                        }

                        pContext->pipelineCreationFeedbackCreateInfos[i].pPipelineStageCreationFeedbacks = & pContext->pipelineCreationStageFeedbacks[i][0];

                        if ( pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount > engine :: vulkan :: config :: rayTracingPipelineStageCreationFeedbackCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: rayTracingPipelineStageCreationFeedbackCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: rayTracingPipelineStageCreationFeedbackCount,
                                    pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount
                            ))

                            pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount = engine :: vulkan :: config :: rayTracingPipelineStageCreationFeedbackCount;
                        }

                        for ( uint32 j = 0U; j < pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount; ++ j ) {
                            (void) toVulkanFormat ( & pContext->pipelineCreationStageFeedbacks[i][j], & pFeedbackCreateInfo->pPipelineStageCreationFeedbacks[j] );
                        }

                        break;
                    }

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;

            pContext->createInfos[i].pStages = & pContext->shaderStageCreateInfos[i][0];

            if ( pContext->createInfos[i].stageCount > engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                        "config :: rayTracingPipelineShaderStageCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: rayTracingPipelineShaderStageCount,
                        pContext->createInfos[i].stageCount
                ))

                pContext->createInfos[i].stageCount = engine :: vulkan :: config :: rayTracingPipelineShaderStageCount;
            }

            for ( uint32 j = 0U; j < pContext->createInfos[i].stageCount; ++ j ) {
                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pStages[j].pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->shaderStageCreateInfos[i][j], & pCreateInfos->pStages[j] ) );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                        case StructureTypePipelineShaderStageRequiredSubgroupSizeCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->requiredSubgroupSizeCreateInfos[i][j],
                                            reinterpret_cast < Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                if ( pCreateInfos[i].pStages[j].pSpecializationInfo != nullptr ) {
                    pContext->shaderStageCreateInfos[i][j].pSpecializationInfo = toVulkanFormat (
                            & pContext->shaderStageSpecializationInfos[i][j],
                            pCreateInfos[i].pStages[j].pSpecializationInfo
                    );

                    pContext->shaderStageSpecializationInfos[i][j].pMapEntries = & pContext->shaderStageSpecializationMapEntries[i][j][0];

                    if ( pContext->shaderStageSpecializationInfos[i][j].mapEntryCount > engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: graphicsPipelineSpecializationMapEntryCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount,
                                pContext->shaderStageSpecializationInfos[i][j].mapEntryCount
                        ))

                        pContext->shaderStageSpecializationInfos[i][j].mapEntryCount = engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount;
                    }

                    for ( uint32 k = 0U; k < pContext->shaderStageSpecializationInfos[i][j].mapEntryCount; ++ k ) {
                        (void) toVulkanFormat ( & pContext->shaderStageSpecializationMapEntries[i][j][k], & pCreateInfos[i].pStages[j].pSpecializationInfo->pMapEntries[k] );
                    }
                }

                pCurrentVk->pNext = nullptr;
            }

            pContext->createInfos[i].pGroups = & pContext->shaderGroupCreateInfos[i][0];

            if ( pContext->createInfos[i].groupCount > engine :: vulkan :: config :: rayTracingPipelineShaderGroupCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                        "config :: rayTracingPipelineShaderGroupCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: rayTracingPipelineShaderGroupCount,
                        pContext->createInfos[i].groupCount
                ))

                pContext->createInfos[i].groupCount = engine :: vulkan :: config :: rayTracingPipelineShaderGroupCount;
            }

            for ( uint32 j = 0U; j < pContext->createInfos[i].groupCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->shaderGroupCreateInfos[i][j], & pCreateInfos[i].pGroups[j] );
            }
        }

        return & pContext->createInfos[0];
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto toVulkanFormat (
            VkRayTracingPipelineCreateInfoNV              * pDestination,
            Type ( RayTracingPipelineCreateInfoNVidia ) const * pSource
    ) noexcept -> VkRayTracingPipelineCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .stageCount         = pSource->stageCount,
                .pStages            = nullptr,
                .groupCount         = pSource->groupCount,
                .pGroups            = nullptr,
                .maxRecursionDepth  = pSource->maxRecursionDepth,
                .layout             = pSource->layout,
                .basePipelineHandle = pSource->basePipelineHandle,
                .basePipelineIndex  = pSource->basePipelineIndex
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto toVulkanFormat (
            VkRayTracingShaderGroupCreateInfoNV                  * pDestination,
            Type ( RayTracingShaderGroupCreateInfoNVidia ) const * pSource
    ) noexcept -> VkRayTracingShaderGroupCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV,
                .pNext              = nullptr,
                .type               = static_cast < VkRayTracingShaderGroupTypeKHR > ( pSource->type ),
                .generalShader      = pSource->generalShader,
                .closestHitShader   = pSource->closestHitShader,
                .anyHitShader       = pSource->anyHitShader,
                .intersectionShader = pSource->intersectionShader
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    auto extractContext (
            cds :: uint32                                  count,
            Type ( RayTracingPipelineCreateInfo )  const * pCreateInfos,
            CreateRayTracingPipelineContext        const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( count == 0U || pCreateInfos == nullptr || pContext == nullptr ) {
            return;
        }

#endif

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pNext );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

                    case StructureTypePipelineCreationFeedbackCreateInfo: {
                        auto pFeedbackCreateInfo = reinterpret_cast < Type ( PipelineCreationFeedbackCreateInfo ) const * > ( pCurrent );

                        if ( pFeedbackCreateInfo->pPipelineCreationFeedback != nullptr ) {
                            (void) fromVulkanFormat ( pFeedbackCreateInfo->pPipelineCreationFeedback, & pContext->pipelineCreationFeedbacks[i] );
                        }

                        for ( cds :: uint32 j = 0U; j < pFeedbackCreateInfo->pipelineStageCreationFeedbackCount; ++ j ) {
                            (void) fromVulkanFormat ( & pFeedbackCreateInfo->pPipelineStageCreationFeedbacks[j], & pContext->pipelineCreationStageFeedbacks[i][j] );
                        }

                        break;
                    }

#endif

                    default:
                        break;
                }

                pCurrent = pCurrent->pNext;
            }
        }
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    auto prepareContext (
            CreateRayTracingPipelineContext             * pContext,
            cds :: uint32                                 count,
            Type ( RayTracingPipelineCreateInfo ) const * pCreateInfos
    ) noexcept -> VkRayTracingPipelineCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pCreateInfos == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: rayTracingPipelineCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: rayTracingPipelineCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: rayTracingPipelineCount,
                    count
            ))

            count = engine :: vulkan :: config :: rayTracingPipelineCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfos[i], & pCreateInfos[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_PIPELINE_CREATION_FEEDBACK_AVAILABLE

                    case StructureTypePipelineCreationFeedbackCreateInfo: {
                        auto pFeedbackCreateInfo = reinterpret_cast < Type ( PipelineCreationFeedbackCreateInfo ) const * > ( pCurrent );
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->pipelineCreationFeedbackCreateInfos[i],
                                        pFeedbackCreateInfo
                                )
                        );

                        if ( pFeedbackCreateInfo->pPipelineCreationFeedback != nullptr ) {
                            pContext->pipelineCreationFeedbackCreateInfos[i].pPipelineCreationFeedback = toVulkanFormat (
                                    & pContext->pipelineCreationFeedbacks[i],
                                    pFeedbackCreateInfo->pPipelineCreationFeedback
                            );
                        }

                        pContext->pipelineCreationFeedbackCreateInfos[i].pPipelineStageCreationFeedbacks = & pContext->pipelineCreationStageFeedbacks[i][0];

                        if ( pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount > engine :: vulkan :: config :: rayTracingPipelineStageCreationFeedbackCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: rayTracingPipelineStageCreationFeedbackCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: rayTracingPipelineStageCreationFeedbackCount,
                                    pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount
                            ))

                            pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount = engine :: vulkan :: config :: rayTracingPipelineStageCreationFeedbackCount;
                        }

                        for ( uint32 j = 0U; j < pContext->pipelineCreationFeedbackCreateInfos[i].pipelineStageCreationFeedbackCount; ++ j ) {
                            (void) toVulkanFormat ( & pContext->pipelineCreationStageFeedbacks[i][j], & pFeedbackCreateInfo->pPipelineStageCreationFeedbacks[j] );
                        }

                        break;
                    }

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;

            pContext->createInfos[i].pStages = & pContext->shaderStageCreateInfos[i][0];

            if ( pContext->createInfos[i].stageCount > engine :: vulkan :: config :: rayTracingPipelineShaderStageCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                        "config :: rayTracingPipelineShaderStageCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: rayTracingPipelineShaderStageCount,
                        pContext->createInfos[i].stageCount
                ))

                pContext->createInfos[i].stageCount = engine :: vulkan :: config :: rayTracingPipelineShaderStageCount;
            }

            for ( uint32 j = 0U; j < pContext->createInfos[i].stageCount; ++ j ) {
                pCurrent    = reinterpret_cast < Type ( GenericInStructure ) const * > ( pCreateInfos[i].pStages[j].pNext );
                pCurrentVk  = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->shaderStageCreateInfos[i][j], & pCreateInfos->pStages[j] ) );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_SUBGROUP_SIZE_CONTROL_AVAILABLE || __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE

                        case StructureTypePipelineShaderStageRequiredSubgroupSizeCreateInfo:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->requiredSubgroupSizeCreateInfos[i][j],
                                            reinterpret_cast < Type ( PipelineShaderStageRequiredSubgroupSizeCreateInfo ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                if ( pCreateInfos[i].pStages[j].pSpecializationInfo != nullptr ) {
                    pContext->shaderStageCreateInfos[i][j].pSpecializationInfo = toVulkanFormat (
                            & pContext->shaderStageSpecializationInfos[i][j],
                            pCreateInfos[i].pStages[j].pSpecializationInfo
                    );

                    pContext->shaderStageSpecializationInfos[i][j].pMapEntries = & pContext->shaderStageSpecializationMapEntries[i][j][0];

                    if ( pContext->shaderStageSpecializationInfos[i][j].mapEntryCount > engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: graphicsPipelineSpecializationMapEntryCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount,
                                pContext->shaderStageSpecializationInfos[i][j].mapEntryCount
                        ))

                        pContext->shaderStageSpecializationInfos[i][j].mapEntryCount = engine :: vulkan :: config :: graphicsPipelineSpecializationMapEntryCount;
                    }

                    for ( uint32 k = 0U; k < pContext->shaderStageSpecializationInfos[i][j].mapEntryCount; ++ k ) {
                        (void) toVulkanFormat ( & pContext->shaderStageSpecializationMapEntries[i][j][k], & pCreateInfos[i].pStages[j].pSpecializationInfo->pMapEntries[k] );
                    }
                }

                pCurrentVk->pNext = nullptr;
            }

            pContext->createInfos[i].pGroups = & pContext->shaderGroupCreateInfos[i][0];

            if ( pContext->createInfos[i].groupCount > engine :: vulkan :: config :: rayTracingPipelineShaderGroupCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                        "config :: rayTracingPipelineShaderGroupCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: rayTracingPipelineShaderGroupCount,
                        pContext->createInfos[i].groupCount
                ))

                pContext->createInfos[i].groupCount = engine :: vulkan :: config :: rayTracingPipelineShaderGroupCount;
            }

            for ( uint32 j = 0U; j < pContext->createInfos[i].groupCount; ++ j ) {
                (void) toVulkanFormat ( & pContext->shaderGroupCreateInfos[i][j], & pCreateInfos[i].pGroups[j] );
            }

            if ( pCreateInfos[i].pLibraryInfo != nullptr ) {
                pContext->createInfos[i].pLibraryInfo = toVulkanFormat (
                        & pContext->libraryCreateInfos[i],
                        pCreateInfos[i].pLibraryInfo
                );
            }

            if ( pCreateInfos[i].pLibraryInterface != nullptr ) {
                pContext->createInfos[i].pLibraryInterface = toVulkanFormat (
                        & pContext->interfaceCreateInfos[i],
                        pCreateInfos[i].pLibraryInterface
                );
            }

            if ( pCreateInfos[i].pDynamicState != nullptr ) {
                pContext->createInfos[i].pDynamicState = toVulkanFormat (
                        & pContext->dynamicStateCreateInfos[i],
                        pCreateInfos[i].pDynamicState
                );

                pContext->dynamicStateCreateInfos[i].pDynamicStates = & pContext->dynamicStateStates[i][0];

                if ( pContext->dynamicStateCreateInfos[i].dynamicStateCount > engine :: vulkan :: config :: rayTracingPipelineDynamicStateCount ) {
                    __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                            "config :: rayTracingPipelineDynamicStateCount = %d. Minimum Required = %d",
                            engine :: vulkan :: config :: rayTracingPipelineDynamicStateCount,
                            pContext->dynamicStateCreateInfos[i].dynamicStateCount
                    ))

                    pContext->dynamicStateCreateInfos[i].dynamicStateCount = engine :: vulkan :: config :: rayTracingPipelineDynamicStateCount;
                }

                for ( uint32 j = 0U; j < pContext->dynamicStateCreateInfos[i].dynamicStateCount; ++ j ) {
                    pContext->dynamicStateStates[i][j] = static_cast < VkDynamicState > ( pCreateInfos[i].pDynamicState->pDynamicStates[j] );
                }
            }
        }

        return & pContext->createInfos[0];
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    auto toVulkanFormat (
            VkRayTracingPipelineCreateInfoKHR                  * pDestination,
            Type ( RayTracingPipelineCreateInfo ) const * pSource
    ) noexcept -> VkRayTracingPipelineCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR,
                .pNext                          = nullptr,
                .flags                          = pSource->flags,
                .stageCount                     = pSource->stageCount,
                .pStages                        = nullptr,
                .groupCount                     = pSource->groupCount,
                .pGroups                        = nullptr,
                .maxPipelineRayRecursionDepth   = pSource->maxPipelineRayRecursionDepth,
                .pLibraryInfo                   = nullptr,
                .pLibraryInterface              = nullptr,
                .pDynamicState                  = nullptr,
                .layout                         = pSource->layout,
                .basePipelineHandle             = pSource->basePipelineHandle,
                .basePipelineIndex              = pSource->basePipelineIndex
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    auto toVulkanFormat (
            VkRayTracingShaderGroupCreateInfoKHR                  * pDestination,
            Type ( RayTracingShaderGroupCreateInfo ) const * pSource
    ) noexcept -> VkRayTracingShaderGroupCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
                .pNext                              = nullptr,
                .type                               = static_cast < VkRayTracingShaderGroupTypeKHR > ( pSource->type ),
                .generalShader                      = pSource->generalShader,
                .closestHitShader                   = pSource->closestHitShader,
                .anyHitShader                       = pSource->anyHitShader,
                .intersectionShader                 = pSource->intersectionShader,
                .pShaderGroupCaptureReplayHandle    = pSource->pShaderGroupCaptureReplayHandle
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    auto toVulkanFormat (
            VkPipelineLibraryCreateInfoKHR                  * pDestination,
            Type ( PipelineLibraryCreateInfo ) const * pSource
    ) noexcept -> VkPipelineLibraryCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR,
                .pNext                              = nullptr,
                .libraryCount                       = pSource->libraryCount,
                .pLibraries                         = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_RAY_TRACING_PIPELINE_AVAILABLE
    auto toVulkanFormat (
            VkRayTracingPipelineInterfaceCreateInfoKHR                  * pDestination,
            Type ( RayTracingPipelineInterfaceCreateInfo ) const * pSource
    ) noexcept -> VkRayTracingPipelineInterfaceCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_INTERFACE_CREATE_INFO_KHR,
                .pNext                              = nullptr,
                .maxPipelineRayPayloadSize          = pSource->maxPipelineRayPayloadSize,
                .maxPipelineRayHitAttributeSize     = pSource->maxPipelineRayHitAttributeSize
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreatePipelineCacheContext                * pContext,
            Type ( PipelineCacheCreateInfo )    const * pSource
    ) noexcept -> VkPipelineCacheCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->createInfo, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineCacheCreateInfo                  * pDestination,
            Type ( PipelineCacheCreateInfo ) const * pSource
    ) noexcept -> VkPipelineCacheCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO,
                .pNext                              = nullptr,
                .flags                              = pSource->flags,
                .initialDataSize                    = pSource->initialDataSize,
                .pInitialData                       = pSource->pInitialData
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto toVulkanFormat (
            VkPipelineInfoKHR           * pDestination,
            Type ( PipelineInfo ) const * pSource
    ) noexcept -> VkPipelineInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_INFO_KHR,
                .pNext                              = nullptr,
                .pipeline                           = pSource->pipeline
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto fromVulkanFormat (
            Type ( PipelineExecutableProperties )         * pDestination,
            VkPipelineExecutablePropertiesKHR       const * pSource
    ) noexcept -> Type ( PipelineExecutableProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePipelineExecutableProperties;
        pDestination->pNext         = nullptr;
        pDestination->stages        = pSource->stages;
        pDestination->subgroupSize  = pSource->subgroupSize;

        (void) std :: memcpy ( & pDestination->name[0],         & pSource->name[0],         VK_MAX_DESCRIPTION_SIZE * sizeof ( pDestination->name[0] ) );
        (void) std :: memcpy ( & pDestination->description[0],  & pSource->description[0],  VK_MAX_DESCRIPTION_SIZE * sizeof ( pDestination->description[0] ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto prepareContext (
            GetPipelinePropertiesContext  * pContext,
            Type ( PipelineInfo )   const * pSource
    ) noexcept -> VkPipelineInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->info, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto extractContext (
            cds :: uint32                                   count,
            Type ( PipelineExecutableProperties )         * pProperties,
            GetPipelinePropertiesContext            const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pProperties == nullptr ) {
            return;
        }

#endif

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) fromVulkanFormat ( & pProperties[i], & pContext->properties[i] );
        }
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto toVulkanFormat (
            VkPipelineExecutableInfoKHR           * pDestination,
            Type ( PipelineExecutableInfo ) const * pSource
    ) noexcept -> VkPipelineExecutableInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                              = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INFO_KHR,
                .pNext                              = nullptr,
                .pipeline                           = pSource->pipeline,
                .executableIndex                    = pSource->executableIndex
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto fromVulkanFormat (
            Type ( PipelineExecutableStatistic )         * pDestination,
            VkPipelineExecutableStatisticKHR       const * pSource
    ) noexcept -> Type ( PipelineExecutableStatistic ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePipelineExecutableStatistic;
        pDestination->pNext         = nullptr;

        (void) std :: memcpy ( & pDestination->name[0],         & pSource->name[0],         VK_MAX_DESCRIPTION_SIZE * sizeof ( pDestination->name[0] ) );
        (void) std :: memcpy ( & pDestination->description[0],  & pSource->description[0],  VK_MAX_DESCRIPTION_SIZE * sizeof ( pDestination->description[0] ) );

        pDestination->format        = static_cast < Type ( PipelineExecutableStatisticFormat ) > ( pSource->format );

        switch ( pSource->format ) {
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_BOOL32_KHR:    pDestination->value.b   = pSource->value.b32;   break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_FLOAT64_KHR:   pDestination->value.f64 = pSource->value.f64;   break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_INT64_KHR:     pDestination->value.s64 = pSource->value.i64;   break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_UINT64_KHR:    pDestination->value.u64 = pSource->value.u64;   break;
            default:
                break;
        }

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto fromVulkanFormat (
            Type ( PipelineExecutableInternalRepresentation )         * pDestination,
            VkPipelineExecutableInternalRepresentationKHR       const * pSource
    ) noexcept -> Type ( PipelineExecutableInternalRepresentation ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePipelineExecutableInternalRepresentation;
        pDestination->pNext         = nullptr;
        pDestination->isText        = pSource->isText;
        pDestination->dataSize      = pSource->dataSize;
        pDestination->pData         = pSource->pData;

        (void) std :: memcpy ( & pDestination->name[0],         & pSource->name[0],         VK_MAX_DESCRIPTION_SIZE * sizeof ( pDestination->name[0] ) );
        (void) std :: memcpy ( & pDestination->description[0],  & pSource->description[0],  VK_MAX_DESCRIPTION_SIZE * sizeof ( pDestination->description[0] ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto prepareContext (
            GetPipelineStatisticsContext            * pContext,
            Type ( PipelineExecutableInfo )   const * pSource
    ) noexcept -> VkPipelineExecutableInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->info, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto prepareContext (
            GetPipelineInternalRepresentationsContext   * pContext,
            Type ( PipelineExecutableInfo )       const * pSource
    ) noexcept -> VkPipelineExecutableInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->info, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto extractContext (
            cds :: uint32                                  count,
            Type ( PipelineExecutableStatistic )         * pProperties,
            GetPipelineStatisticsContext           const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pProperties == nullptr ) {
            return;
        }

#endif

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) fromVulkanFormat ( & pProperties[i], & pContext->statistics[i] );
        }
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto extractContext (
            cds :: uint32                                               count,
            Type ( PipelineExecutableInternalRepresentation )         * pProperties,
            GetPipelineInternalRepresentationsContext           const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pProperties == nullptr ) {
            return;
        }

#endif

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) fromVulkanFormat ( & pProperties[i], & pContext->internalRepresentations[i] );
        }
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PIPELINE_EXECUTABLE_PROPERTIES_AVAILABLE
    auto prepareContext (
            GetPipelineInternalRepresentationsContext                     * pContext,
            uint32                                                          count,
            Type ( PipelineExecutableInternalRepresentation )             * pSource
    ) noexcept -> VkPipelineExecutableInternalRepresentationKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        for ( uint32 i = 0U; i < count; ++ i ) {
            pContext->internalRepresentations[i].sType      = VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INTERNAL_REPRESENTATION_KHR;
            pContext->internalRepresentations[i].isText     = pSource[i].isText;
            pContext->internalRepresentations[i].dataSize   = pSource[i].dataSize;
            pContext->internalRepresentations[i].pData      = pSource[i].pData;
        }

        return & pContext->internalRepresentations[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto fromVulkanFormat (
            Type ( PhysicalDeviceMemoryProperties )         * pDestination,
            VkPhysicalDeviceMemoryProperties          const * pSource
    ) noexcept -> Type ( PhysicalDeviceMemoryProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->memoryTypeCount = pSource->memoryTypeCount;
        pDestination->memoryHeapCount = pSource->memoryHeapCount;

        (void) std :: memcpy ( & pDestination->memoryTypes[0], & pSource->memoryTypes[0], sizeof ( pDestination->memoryTypes[0] ) * VK_MAX_MEMORY_TYPES );
        (void) std :: memcpy ( & pDestination->memoryHeaps[0], & pSource->memoryHeaps[0], sizeof ( pDestination->memoryHeaps[0] ) * VK_MAX_MEMORY_HEAPS );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto prepareContext (
            GetPhysicalDeviceMemoryPropertiesContext          * pContext,
            Type ( PhysicalDeviceMemoryProperties2 )    const * pSource
    ) noexcept -> VkPhysicalDeviceMemoryProperties2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->properties2, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE

                case StructureTypePhysicalDeviceMemoryBudgetProperties:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->budgetProperties,
                                    reinterpret_cast < Type ( PhysicalDeviceMemoryBudgetProperties ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->properties2;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPhysicalDeviceMemoryProperties              * pDestination,
            Type ( PhysicalDeviceMemoryProperties ) const * pSource
    ) noexcept -> VkPhysicalDeviceMemoryProperties * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->memoryTypeCount   = pSource->memoryTypeCount;
        pDestination->memoryHeapCount   = pSource->memoryHeapCount;

        (void) std :: memcpy ( & pDestination->memoryTypes[0], & pSource->memoryTypes[0], sizeof ( pDestination->memoryTypes[0] ) * VK_MAX_MEMORY_TYPES );
        (void) std :: memcpy ( & pDestination->memoryHeaps[0], & pSource->memoryHeaps[0], sizeof ( pDestination->memoryHeaps[0] ) * VK_MAX_MEMORY_HEAPS );


        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkPhysicalDeviceMemoryProperties2              * pDestination,
            Type ( PhysicalDeviceMemoryProperties2 ) const * pSource
    ) noexcept -> VkPhysicalDeviceMemoryProperties2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
        pDestination->pNext = nullptr;
        (void) toVulkanFormat ( & pDestination->memoryProperties, & pSource->properties );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE
    auto toVulkanFormat (
            VkPhysicalDeviceMemoryBudgetPropertiesEXT           * pDestination,
            Type ( PhysicalDeviceMemoryBudgetProperties ) const * pSource
    ) noexcept -> VkPhysicalDeviceMemoryBudgetPropertiesEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
        pDestination->pNext = nullptr;

        (void) std :: memcpy ( & pDestination->heapBudget[0],   & pSource->heapBudget[0],   sizeof ( pDestination->heapBudget[0] ) * VK_MAX_MEMORY_HEAPS );
        (void) std :: memcpy ( & pDestination->heapUsage[0],    & pSource->heapUsage[0],    sizeof ( pDestination->heapUsage[0] ) * VK_MAX_MEMORY_HEAPS );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto extractContext (
            Type ( PhysicalDeviceMemoryProperties2 )          * pDestination,
            GetPhysicalDeviceMemoryPropertiesContext    const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pContext == nullptr ) {
            return;
        }

#endif

        auto pCurrent = reinterpret_cast < Type ( GenericOutStructure ) * > ( fromVulkanFormat ( pDestination, & pContext->properties2 )->pNext );

        while ( pCurrent->pNext != nullptr ) {

            switch ( pCurrent->pNext->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE

                case StructureTypePhysicalDeviceMemoryBudgetProperties:
                    pCurrent->pNext = reinterpret_cast < Type ( GenericOutStructure ) * > (
                            fromVulkanFormat (
                                    reinterpret_cast < Type ( PhysicalDeviceMemoryBudgetProperties ) * > ( pCurrent->pNext ),
                                    & pContext->budgetProperties
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrent = pCurrent->pNext;
        }
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto fromVulkanFormat (
            Type ( PhysicalDeviceMemoryProperties2 )         * pDestination,
            VkPhysicalDeviceMemoryProperties2          const * pSource
    ) noexcept -> Type ( PhysicalDeviceMemoryProperties2 ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMemoryProperties;

        (void) fromVulkanFormat ( & pDestination->properties, & pSource->memoryProperties );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_BUDGET_AVAILABLE
    auto fromVulkanFormat (
            Type ( PhysicalDeviceMemoryBudgetProperties )         * pDestination,
            VkPhysicalDeviceMemoryBudgetPropertiesEXT          const * pSource
    ) noexcept -> Type ( PhysicalDeviceMemoryBudgetProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypePhysicalDeviceMemoryBudgetProperties;

        (void) std :: memcpy ( & pDestination->heapBudget[0],   & pSource->heapBudget[0],   sizeof ( pDestination->heapBudget[0] ) * VK_MAX_MEMORY_HEAPS );
        (void) std :: memcpy ( & pDestination->heapUsage[0],    & pSource->heapUsage[0],    sizeof ( pDestination->heapUsage[0] ) * VK_MAX_MEMORY_HEAPS );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            AllocateMemoryContext                * pContext,
            Type ( MemoryAllocateInfo )    const * pSource
    ) noexcept -> VkMemoryAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->info, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE

                case StructureTypeDedicatedAllocationMemoryAllocateInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->dedicatedInfoNVidia,
                                    reinterpret_cast < Type ( DedicatedAllocationMemoryAllocateInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeExportMemoryAllocateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->exportInfo,
                                    reinterpret_cast < Type ( ExportMemoryAllocateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

                case StructureTypeMemoryAllocateFlagsInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->flagsInfo,
                                    reinterpret_cast < Type ( MemoryAllocateFlagsInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

                case StructureTypeMemoryDedicatedAllocateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->dedicatedInfo,
                                    reinterpret_cast < Type ( MemoryDedicatedAllocateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeMemoryOpaqueCaptureAddressAllocateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->opaqueCaptureAddressInfo,
                                    reinterpret_cast < Type ( MemoryOpaqueCaptureAddressAllocateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE

                case StructureTypeMemoryPriorityAllocateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->priorityInfo,
                                    reinterpret_cast < Type ( MemoryPriorityAllocateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE

                case StructureTypeExportMemoryAllocateInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->exportInfoNVidia,
                                    reinterpret_cast < Type ( ExportMemoryAllocateInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE

                case StructureTypeExportMemoryWin32HandleInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->exportInfoWin32,
                                    reinterpret_cast < Type ( ExportMemoryWin32HandleInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

                case StructureTypeImportMemoryWin32HandleInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->importInfoWin32,
                                    reinterpret_cast < Type ( ImportMemoryWin32HandleInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE

                case StructureTypeExportMemoryWin32HandleInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->exportInfoWin32NVidia,
                                    reinterpret_cast < Type ( ExportMemoryWin32HandleInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

                case StructureTypeImportMemoryWin32HandleInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->importInfoWin32NVidia,
                                    reinterpret_cast < Type ( ImportMemoryWin32HandleInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE

                case StructureTypeImportMemoryFdInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->importInfoFd,
                                    reinterpret_cast < Type ( ImportMemoryFdInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE

                case StructureTypeImportMemoryHostPointerInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->importHostInfo,
                                    reinterpret_cast < Type ( ImportMemoryHostPointerInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

                case StructureTypeImportAndroidHardwareBufferInfoAndroid:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->importHardwareBufferAndroid,
                                    reinterpret_cast < Type ( ImportAndroidHardwareBufferInfoAndroid ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE

                case StructureTypeImportMemoryBufferCollectionFuchsia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->importBufferCollectionFuchsia,
                                    reinterpret_cast < Type ( ImportMemoryBufferCollectionFuchsia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE

                case StructureTypeImportMemoryZirconHandleInfoFuchsia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->importInfoFuchsia,
                                    reinterpret_cast < Type ( ImportMemoryZirconHandleInfoFuchsia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->info;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
    auto toVulkanFormat (
            VkDedicatedAllocationMemoryAllocateInfoNV                  * pDestination,
            Type ( DedicatedAllocationMemoryAllocateInfoNVidia ) const * pSource
    ) noexcept -> VkDedicatedAllocationMemoryAllocateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType      = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV,
            .pNext      = nullptr,
            .image      = pSource->image,
            .buffer     = pSource->buffer
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkExportMemoryAllocateInfo              * pDestination,
            Type ( ExportMemoryAllocateInfo ) const * pSource
    ) noexcept -> VkExportMemoryAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO,
            .pNext          = nullptr,
            .handleTypes    = pSource->handleTypes
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
    auto toVulkanFormat (
            VkExportMemoryAllocateInfoNV                  * pDestination,
            Type ( ExportMemoryAllocateInfoNVidia ) const * pSource
    ) noexcept -> VkExportMemoryAllocateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV,
            .pNext          = nullptr,
            .handleTypes    = pSource->handleTypes
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkExportMemoryWin32HandleInfoKHR           * pDestination,
            Type ( ExportMemoryWin32HandleInfo ) const * pSource
    ) noexcept -> VkExportMemoryWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR,
            .pNext          = nullptr,
            .pAttributes    = pSource->pAttributes,
            .dwAccess       = pSource->dwAccess,
            .name           = pSource->name
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
    auto toVulkanFormat (
            VkImportMemoryFdInfoKHR           * pDestination,
            Type ( ImportMemoryFdInfo ) const * pSource
    ) noexcept -> VkImportMemoryFdInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR,
            .pNext          = nullptr,
            .handleType     = static_cast < VkExternalMemoryHandleTypeFlagBits > ( pSource->handleType ),
            .fd             = pSource->fd
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkImportMemoryWin32HandleInfoKHR           * pDestination,
            Type ( ImportMemoryWin32HandleInfo ) const * pSource
    ) noexcept -> VkImportMemoryWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR,
            .pNext          = nullptr,
            .handleType     = static_cast < VkExternalMemoryHandleTypeFlagBits > ( pSource->handleType ),
            .handle         = pSource->handle,
            .name           = pSource->name
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkExportMemoryWin32HandleInfoNV           * pDestination,
            Type ( ExportMemoryWin32HandleInfoNVidia ) const * pSource
    ) noexcept -> VkExportMemoryWin32HandleInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV,
            .pNext          = nullptr,
            .pAttributes    = pSource->pAttributes,
            .dwAccess       = pSource->dwAccess
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkImportMemoryWin32HandleInfoNV           * pDestination,
            Type ( ImportMemoryWin32HandleInfoNVidia ) const * pSource
    ) noexcept -> VkImportMemoryWin32HandleInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV,
            .pNext          = nullptr,
            .handleType     = static_cast < VkExternalMemoryHandleTypeFlagBits > ( pSource->handleType ),
            .handle         = pSource->handle
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
    auto toVulkanFormat (
            VkImportAndroidHardwareBufferInfoANDROID              * pDestination,
            Type ( ImportAndroidHardwareBufferInfoAndroid ) const * pSource
    ) noexcept -> VkImportAndroidHardwareBufferInfoANDROID * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID,
            .pNext          = nullptr,
            .buffer         = pSource->buffer
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
    auto toVulkanFormat (
            VkImportMemoryBufferCollectionFUCHSIA              * pDestination,
            Type ( ImportMemoryBufferCollectionFuchsia ) const * pSource
    ) noexcept -> VkImportMemoryBufferCollectionFUCHSIA * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_IMPORT_MEMORY_BUFFER_COLLECTION_FUCHSIA,
            .pNext          = nullptr,
            .collection     = pSource->collection,
            .index          = pSource->index
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
    auto toVulkanFormat (
            VkImportMemoryHostPointerInfoEXT           * pDestination,
            Type ( ImportMemoryHostPointerInfo ) const * pSource
    ) noexcept -> VkImportMemoryHostPointerInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT,
            .pNext          = nullptr,
            .handleType     = static_cast < VkExternalMemoryHandleTypeFlagBits > ( pSource->handleType ),
            .pHostPointer   = pSource->pHostPointer
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_EXTERNAL_MEMORY_AVAILABLE
    auto toVulkanFormat (
            VkImportMemoryZirconHandleInfoFUCHSIA           * pDestination,
            Type ( ImportMemoryZirconHandleInfoFuchsia ) const * pSource
    ) noexcept -> VkImportMemoryZirconHandleInfoFUCHSIA * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_IMPORT_MEMORY_ZIRCON_HANDLE_INFO_FUCHSIA,
            .pNext          = nullptr,
            .handleType     = static_cast < VkExternalMemoryHandleTypeFlagBits > ( pSource->handleType ),
            .handle         = pSource->handle
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkMemoryAllocateFlagsInfo              * pDestination,
            Type ( MemoryAllocateFlagsInfo ) const * pSource
    ) noexcept -> VkMemoryAllocateFlagsInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
            .pNext          = nullptr,
            .flags          = pSource->flags,
            .deviceMask     = pSource->deviceMask
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkMemoryDedicatedAllocateInfo              * pDestination,
            Type ( MemoryDedicatedAllocateInfo ) const * pSource
    ) noexcept -> VkMemoryDedicatedAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType          = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO,
            .pNext          = nullptr,
            .image          = pSource->image,
            .buffer         = pSource->buffer
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkMemoryOpaqueCaptureAddressAllocateInfo              * pDestination,
            Type ( MemoryOpaqueCaptureAddressAllocateInfo ) const * pSource
    ) noexcept -> VkMemoryOpaqueCaptureAddressAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType                  = VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO,
            .pNext                  = nullptr,
            .opaqueCaptureAddress   = pSource->opaqueCaptureAddress,
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_MEMORY_PRIORITY_AVAILABLE
    auto toVulkanFormat (
            VkMemoryPriorityAllocateInfoEXT           * pDestination,
            Type ( MemoryPriorityAllocateInfo ) const * pSource
    ) noexcept -> VkMemoryPriorityAllocateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType                  = VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO,
            .pNext                  = nullptr,
            .priority               = pSource->priority,
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkMemoryAllocateInfo              * pDestination,
            Type ( MemoryAllocateInfo ) const * pSource
    ) noexcept -> VkMemoryAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType                  = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .pNext                  = nullptr,
            .allocationSize         = pSource->allocationSize,
            .memoryTypeIndex        = pSource->memoryTypeIndex
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
    auto toVulkanFormat (
            VkMemoryGetWin32HandleInfoKHR           * pDestination,
            Type ( MemoryGetWin32HandleInfo ) const * pSource
    ) noexcept -> VkMemoryGetWin32HandleInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType                  = VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR,
            .pNext                  = nullptr,
            .memory                 = pSource->memory,
            .handleType             = static_cast < VkExternalMemoryHandleTypeFlagBits > ( pSource->handleType )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_WIN32_AVAILABLE
    auto fromVulkanFormat (
            Type ( MemoryWin32HandleProperties )     * pDestination,
            VkMemoryWin32HandlePropertiesKHR   const * pSource
    ) noexcept -> Type ( MemoryWin32HandleProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .structureType          = StructureTypeMemoryWin32HandleProperties,
            .pNext                  = nullptr,
            .memoryTypeBits         = pSource->memoryTypeBits
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
    auto toVulkanFormat (
            VkMemoryGetFdInfoKHR           * pDestination,
            Type ( MemoryGetFdInfo ) const * pSource
    ) noexcept -> VkMemoryGetFdInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .sType                  = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR,
            .pNext                  = nullptr,
            .memory                 = pSource->memory,
            .handleType             = static_cast < VkExternalMemoryHandleTypeFlagBits > ( pSource->handleType )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_EXTERNAL_MEMORY_FD_AVAILABLE
    auto fromVulkanFormat (
            Type ( MemoryFdProperties )     * pDestination,
            VkMemoryFdPropertiesKHR   const * pSource
    ) noexcept -> Type ( MemoryFdProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .structureType          = StructureTypeMemoryFdProperties,
            .pNext                  = nullptr,
            .memoryTypeBits         = pSource->memoryTypeBits
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_EXTERNAL_MEMORY_HOST_AVAILABLE
    auto fromVulkanFormat (
            Type ( MemoryHostPointerProperties )     * pDestination,
            VkMemoryHostPointerPropertiesEXT   const * pSource
    ) noexcept -> Type ( MemoryHostPointerProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
            .structureType          = StructureTypeMemoryHostPointerProperties,
            .pNext                  = nullptr,
            .memoryTypeBits         = pSource->memoryTypeBits
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_RDMA_AVAILABLE
    auto toVulkanFormat (
            VkMemoryGetRemoteAddressInfoNV                  * pDestination,
            Type ( MemoryGetRemoteAddressInfoNVidia ) const * pSource
    ) noexcept -> VkMemoryGetRemoteAddressInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_MEMORY_GET_REMOTE_ADDRESS_INFO_NV,
                .pNext                  = nullptr,
                .memory                 = pSource->memory,
                .handleType             = static_cast < VkExternalMemoryHandleTypeFlagBits > ( pSource->handleType )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            FlushMappedMemoryRangesContext        * pContext,
            cds :: uint32                           count,
            Type ( MappedMemoryRange )      const * pRanges
    ) noexcept -> VkMappedMemoryRange * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pRanges == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: flushMappedRangeCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: flushMappedRangeCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: flushMappedRangeCount,
                    count
            ))

            count = engine :: vulkan :: config :: flushMappedRangeCount;
        }

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->ranges[0], & pRanges[0] );
        }

        return & pContext->ranges[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkMappedMemoryRange              * pDestination,
            Type ( MappedMemoryRange ) const * pSource
    ) noexcept -> VkMappedMemoryRange * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
                .pNext                  = nullptr,
                .memory                 = pSource->memory,
                .offset                 = pSource->offset,
                .size                   = pSource->size
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkDeviceMemoryOpaqueCaptureAddressInfo              * pDestination,
            Type ( DeviceMemoryOpaqueCaptureAddressInfo ) const * pSource
    ) noexcept -> VkDeviceMemoryOpaqueCaptureAddressInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO,
                .pNext                  = nullptr,
                .memory                 = pSource->memory
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateBufferContext                  * pContext,
            Type ( BufferCreateInfo )      const * pSource
    ) noexcept -> VkBufferCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeExternalMemoryBufferCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->externalMemoryCreateInfo,
                                    reinterpret_cast < Type ( ExternalMemoryBufferCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeBufferOpaqueCaptureAddressCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->opaqueCaptureAddressCreateInfo,
                                    reinterpret_cast < Type ( BufferOpaqueCaptureAddressCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE

                case StructureTypeBufferCollectionBufferCreateInfoFuchsia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->bufferCollectionCreateInfo,
                                    reinterpret_cast < Type ( BufferCollectionBufferCreateInfoFuchsia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE

                case StructureTypeBufferDeviceAddressCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->deviceAddressCreateInfo,
                                    reinterpret_cast < Type ( BufferDeviceAddressCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE

                case StructureTypeDedicatedAllocationBufferCreateInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->dedicatedAllocationCreateInfo,
                                    reinterpret_cast < Type ( DedicatedAllocationBufferCreateInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE

                case StructureTypeVideoDecodeH264Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->decodeH264Profile,
                                    reinterpret_cast < Type ( VideoDecodeH264Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE

                case StructureTypeVideoDecodeH265Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->decodeH265Profile,
                                    reinterpret_cast < Type ( VideoDecodeH265Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE

                case StructureTypeVideoEncodeH264Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->encodeH264Profile,
                                    reinterpret_cast < Type ( VideoEncodeH264Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE

                case StructureTypeVideoEncodeH265Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->encodeH265Profile,
                                    reinterpret_cast < Type ( VideoEncodeH265Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

                case StructureTypeVideoProfile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->videoProfile,
                                    reinterpret_cast < Type ( VideoProfile ) const * > ( pCurrent )
                            )
                    );
                    break;

                case StructureTypeVideoProfiles: {
                    auto pVideoProfiles = reinterpret_cast < Type ( VideoProfiles ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->videoProfiles,
                                    pVideoProfiles
                            )
                    );

                    pContext->videoProfiles.pProfiles = & pContext->videoProfilesProfiles[0];

                    if ( pContext->videoProfiles.profileCount > engine :: vulkan :: config :: videoProfileCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: videoProfileCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: videoProfileCount,
                                pContext->videoProfiles.profileCount
                        ))

                        pContext->videoProfiles.profileCount = engine :: vulkan :: config :: videoProfileCount;
                    }

                    for ( uint32 i = 0U; i < pContext->videoProfiles.profileCount; ++ i ) {
                        (void) toVulkanFormat ( & pContext->videoProfilesProfiles[i], & pVideoProfiles->pProfiles[i] );
                    }

                    break;
                }

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkBufferCreateInfo              * pDestination,
            Type ( BufferCreateInfo ) const * pSource
    ) noexcept -> VkBufferCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .size                   = pSource->size,
                .usage                  = pSource->usage,
                .sharingMode            = static_cast < VkSharingMode > ( pSource->sharingMode ),
                .queueFamilyIndexCount  = pSource->queueFamilyIndexCount,
                .pQueueFamilyIndices    = pSource->pQueueFamilyIndices
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkExternalMemoryBufferCreateInfo              * pDestination,
            Type ( ExternalMemoryBufferCreateInfo ) const * pSource
    ) noexcept -> VkExternalMemoryBufferCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO_KHR,
                .pNext                  = nullptr,
                .handleTypes            = pSource->handleTypes
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkBufferOpaqueCaptureAddressCreateInfo              * pDestination,
            Type ( BufferOpaqueCaptureAddressCreateInfo ) const * pSource
    ) noexcept -> VkBufferOpaqueCaptureAddressCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO,
                .pNext                  = nullptr,
                .opaqueCaptureAddress   = pSource->opaqueCaptureAddress
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
    auto toVulkanFormat (
            VkBufferCollectionBufferCreateInfoFUCHSIA              * pDestination,
            Type ( BufferCollectionBufferCreateInfoFuchsia ) const * pSource
    ) noexcept -> VkBufferCollectionBufferCreateInfoFUCHSIA * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_BUFFER_CREATE_INFO_FUCHSIA,
                .pNext                  = nullptr,
                .collection             = pSource->collection,
                .index                  = pSource->index
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BUFFER_DEVICE_ADDRESS_AVAILABLE
    auto toVulkanFormat (
            VkBufferDeviceAddressCreateInfoEXT           * pDestination,
            Type ( BufferDeviceAddressCreateInfo ) const * pSource
    ) noexcept -> VkBufferDeviceAddressCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT,
                .pNext                  = nullptr,
                .deviceAddress          = pSource->deviceAddress
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
    auto toVulkanFormat (
            VkDedicatedAllocationBufferCreateInfoNV                  * pDestination,
            Type ( DedicatedAllocationBufferCreateInfoNVidia ) const * pSource
    ) noexcept -> VkDedicatedAllocationBufferCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .dedicatedAllocation    = pSource->dedicatedAllocation
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE
    auto toVulkanFormat (
            VkVideoDecodeH264ProfileEXT           * pDestination,
            Type ( VideoDecodeH264Profile ) const * pSource
    ) noexcept -> VkVideoDecodeH264ProfileEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_EXT,
                .pNext                  = nullptr,
                .stdProfileIdc          = pSource->stdProfileIdc,
                .pictureLayout          = pSource->pictureLayout
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE
    auto toVulkanFormat (
            VkVideoDecodeH265ProfileEXT           * pDestination,
            Type ( VideoDecodeH265Profile ) const * pSource
    ) noexcept -> VkVideoDecodeH265ProfileEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_EXT,
                .pNext                  = nullptr,
                .stdProfileIdc          = pSource->stdProfileIdc
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE
    auto toVulkanFormat (
            VkVideoEncodeH264ProfileEXT           * pDestination,
            Type ( VideoEncodeH264Profile ) const * pSource
    ) noexcept -> VkVideoEncodeH264ProfileEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PROFILE_EXT,
                .pNext                  = nullptr,
                .stdProfileIdc          = pSource->stdProfileIdc
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE
    auto toVulkanFormat (
            VkVideoEncodeH265ProfileEXT           * pDestination,
            Type ( VideoEncodeH265Profile ) const * pSource
    ) noexcept -> VkVideoEncodeH265ProfileEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_PROFILE_EXT,
                .pNext                  = nullptr,
                .stdProfileIdc          = pSource->stdProfileIdc
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    auto toVulkanFormat (
            VkVideoProfileKHR           * pDestination,
            Type ( VideoProfile ) const * pSource
    ) noexcept -> VkVideoProfileKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_VIDEO_PROFILE_KHR,
                .pNext                  = nullptr,
                .videoCodecOperation    = static_cast < VkVideoCodecOperationFlagBitsKHR > ( pSource->videoCodecOperation ),
                .chromaSubsampling      = pSource->chromaSubsampling,
                .lumaBitDepth           = pSource->lumaBitDepth,
                .chromaBitDepth         = pSource->chromaBitDepth
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE
    auto toVulkanFormat (
            VkVideoProfilesKHR           * pDestination,
            Type ( VideoProfiles ) const * pSource
    ) noexcept -> VkVideoProfilesKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_VIDEO_PROFILES_KHR,
                .pNext                  = nullptr,
                .profileCount           = pSource->profileCount,
                .pProfiles              = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkBufferViewCreateInfo              * pDestination,
            Type ( BufferViewCreateInfo ) const * pSource
    ) noexcept -> VkBufferViewCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .buffer                 = pSource->buffer,
                .format                 = static_cast < VkFormat > ( pSource->format ),
                .offset                 = pSource->offset,
                .range                  = pSource->range
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateImageContext                  * pContext,
            Type ( ImageCreateInfo )      const * pSource
    ) noexcept -> VkImageCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeExternalMemoryImageCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->externalMemoryCreateInfo,
                                    reinterpret_cast < Type ( ExternalMemoryImageCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE

                case StructureTypeImageSwapChainCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->swapchainCreateInfo,
                                    reinterpret_cast < Type ( ImageSwapChainCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeImageFormatListCreateInfo: {
                    auto pImageFormatListCreateInfo = reinterpret_cast < Type ( ImageFormatListCreateInfo ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->formatListCreateInfo,
                                    pImageFormatListCreateInfo
                            )
                    );

                    pContext->formatListCreateInfo.pViewFormats = & pContext->formatListFormats[0];

                    if ( pContext->formatListCreateInfo.viewFormatCount > engine :: vulkan :: config :: imageFormatListFormatCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: imageFormatListFormatCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: imageFormatListFormatCount,
                                pContext->formatListCreateInfo.viewFormatCount
                        ))

                        pContext->formatListCreateInfo.viewFormatCount = engine :: vulkan :: config :: imageFormatListFormatCount;
                    }

                    for ( uint32 i = 0U; i < pContext->formatListCreateInfo.viewFormatCount; ++ i ) {
                        pContext->formatListFormats[i] = static_cast < VkFormat > ( pImageFormatListCreateInfo->pViewFormats[i] );
                    }

                    break;
                }

                case StructureTypeImageStencilUsageCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->stencilUsageCreateInfo,
                                    reinterpret_cast < Type ( ImageStencilUsageCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE

                case StructureTypeExternalMemoryImageCreateInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->externalMemoryCreateInfoNVidia,
                                    reinterpret_cast < Type ( ExternalMemoryImageCreateInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE

                case StructureTypeBufferCollectionImageCreateInfoFuchsia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->bufferCollectionImageCreateInfo,
                                    reinterpret_cast < Type ( BufferCollectionImageCreateInfoFuchsia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE

                case StructureTypeDedicatedAllocationImageCreateInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->dedicatedAllocationImageCreateInfo,
                                    reinterpret_cast < Type ( DedicatedAllocationImageCreateInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

                case StructureTypeExternalFormatAndroid:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->externalFormat,
                                    reinterpret_cast < Type ( ExternalFormatAndroid ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE

                case StructureTypeImageDRMFormatModifierExplicitCreateInfo: {
                    auto pImageDrmFormatModifierExplicitCreateInfo = reinterpret_cast < Type ( ImageDrmFormatModifierExplicitCreateInfo ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->drmFormatModifierExplicitCreateInfo,
                                    pImageDrmFormatModifierExplicitCreateInfo
                            )
                    );

                    pContext->drmFormatModifierExplicitCreateInfo.pPlaneLayouts = & pContext->drmFormatSubresourceLayouts[0];

                    if ( pContext->drmFormatModifierExplicitCreateInfo.drmFormatModifierPlaneCount > engine :: vulkan :: config :: imageDrmFormatSubresourceLayoutCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: imageDrmFormatSubresourceLayoutCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: imageDrmFormatSubresourceLayoutCount,
                                pContext->drmFormatModifierExplicitCreateInfo.drmFormatModifierPlaneCount
                        ))

                        pContext->drmFormatModifierExplicitCreateInfo.drmFormatModifierPlaneCount = engine :: vulkan :: config :: imageDrmFormatSubresourceLayoutCount;
                    }

                    for ( uint32 i = 0U; i < pContext->drmFormatModifierExplicitCreateInfo.drmFormatModifierPlaneCount; ++ i ) {
                        (void) toVulkanFormat ( & pContext->drmFormatSubresourceLayouts[i], & pImageDrmFormatModifierExplicitCreateInfo->pPlaneLayouts[i] );
                    }

                    break;
                }

                case StructureTypeImageDRMFormatModifierListCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->drmFormatModifierListCreateInfo,
                                    reinterpret_cast < Type ( ImageDrmFormatModifierListCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE

                case StructureTypeVideoDecodeH264Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->decodeH264Profile,
                                    reinterpret_cast < Type ( VideoDecodeH264Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE

                case StructureTypeVideoDecodeH265Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->decodeH265Profile,
                                    reinterpret_cast < Type ( VideoDecodeH265Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE

                case StructureTypeVideoEncodeH264Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->encodeH264Profile,
                                    reinterpret_cast < Type ( VideoEncodeH264Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE

                case StructureTypeVideoEncodeH265Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->encodeH265Profile,
                                    reinterpret_cast < Type ( VideoEncodeH265Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

                case StructureTypeVideoProfile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->videoProfile,
                                    reinterpret_cast < Type ( VideoProfile ) const * > ( pCurrent )
                            )
                    );
                    break;

                case StructureTypeVideoProfiles: {
                    auto pVideoProfiles = reinterpret_cast < Type ( VideoProfiles ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->videoProfiles,
                                    pVideoProfiles
                            )
                    );

                    pContext->videoProfiles.pProfiles = & pContext->videoProfilesProfiles[0];

                    if ( pContext->videoProfiles.profileCount > engine :: vulkan :: config :: videoProfileCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: videoProfileCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: videoProfileCount,
                                pContext->videoProfiles.profileCount
                        ))

                        pContext->videoProfiles.profileCount = engine :: vulkan :: config :: videoProfileCount;
                    }

                    for ( uint32 i = 0U; i < pContext->videoProfiles.profileCount; ++ i ) {
                        (void) toVulkanFormat ( & pContext->videoProfilesProfiles[i], & pVideoProfiles->pProfiles[i] );
                    }

                    break;
                }

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkImageCreateInfo              * pDestination,
            Type ( ImageCreateInfo ) const * pSource
    ) noexcept -> VkImageCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                .pNext                  = nullptr,
                .flags                  = pSource->flags,
                .imageType              = static_cast < VkImageType > ( pSource->imageType ),
                .format                 = static_cast < VkFormat > ( pSource->format ),
                .extent                 = {
                        .width                  = pSource->extent.width,
                        .height                 = pSource->extent.height,
                        .depth                  = pSource->extent.depth
                },
                .mipLevels              = pSource->mipLevels,
                .arrayLayers            = pSource->arrayLayers,
                .samples                = static_cast < VkSampleCountFlagBits > ( pSource->samples ),
                .tiling                 = static_cast < VkImageTiling > ( pSource->tiling ),
                .usage                  = pSource->usage,
                .sharingMode            = static_cast < VkSharingMode > ( pSource->sharingMode ),
                .queueFamilyIndexCount  = pSource->queueFamilyIndexCount,
                .pQueueFamilyIndices    = pSource->pQueueFamilyIndices,
                .initialLayout          = static_cast < VkImageLayout > ( pSource->initialLayout )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkExternalMemoryImageCreateInfo              * pDestination,
            Type ( ExternalMemoryImageCreateInfo ) const * pSource
    ) noexcept -> VkExternalMemoryImageCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO,
                .pNext                  = nullptr,
                .handleTypes            = pSource->handleTypes
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_EXTERNAL_MEMORY_AVAILABLE
    auto toVulkanFormat (
            VkExternalMemoryImageCreateInfoNV              * pDestination,
            Type ( ExternalMemoryImageCreateInfoNVidia ) const * pSource
    ) noexcept -> VkExternalMemoryImageCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV,
                .pNext                  = nullptr,
                .handleTypes            = pSource->handleTypes
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE && __C_ENG_VULKAN_API_EXTENSION_KHRONOS_SWAP_CHAIN_AVAILABLE
    auto toVulkanFormat (
            VkImageSwapchainCreateInfoKHR              * pDestination,
            Type ( ImageSwapChainCreateInfo ) const * pSource
    ) noexcept -> VkImageSwapchainCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR,
                .pNext                  = nullptr,
                .swapchain              = pSource->swapchain
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkImageStencilUsageCreateInfo              * pDestination,
            Type ( ImageStencilUsageCreateInfo ) const * pSource
    ) noexcept -> VkImageStencilUsageCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO,
                .pNext                  = nullptr,
                .stencilUsage           = pSource->stencilUsage
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_GOOGLE_FUCHSIA_BUFFER_COLLECTION_AVAILABLE
    auto toVulkanFormat (
            VkBufferCollectionImageCreateInfoFUCHSIA              * pDestination,
            Type ( BufferCollectionImageCreateInfoFuchsia ) const * pSource
    ) noexcept -> VkBufferCollectionImageCreateInfoFUCHSIA * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_BUFFER_COLLECTION_IMAGE_CREATE_INFO_FUCHSIA,
                .pNext                  = nullptr,
                .collection             = pSource->collection,
                .index                  = pSource->index
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
    auto toVulkanFormat (
            VkImageDrmFormatModifierExplicitCreateInfoEXT              * pDestination,
            Type ( ImageDrmFormatModifierExplicitCreateInfo ) const * pSource
    ) noexcept -> VkImageDrmFormatModifierExplicitCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT,
                .pNext                          = nullptr,
                .drmFormatModifier              = pSource->drmFormatModifier,
                .drmFormatModifierPlaneCount    = pSource->drmFormatModifierPlaneCount,
                .pPlaneLayouts                  = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkSubresourceLayout              * pDestination,
            Type ( SubresourceLayout ) const * pSource
    ) noexcept -> VkSubresourceLayout * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .offset     = pSource->offset,
                .size       = pSource->size,
                .rowPitch   = pSource->rowPitch,
                .arrayPitch = pSource->arrayPitch,
                .depthPitch = pSource->depthPitch
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
    auto toVulkanFormat (
            VkImageDrmFormatModifierListCreateInfoEXT              * pDestination,
            Type ( ImageDrmFormatModifierListCreateInfo ) const * pSource
    ) noexcept -> VkImageDrmFormatModifierListCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT,
                .pNext                          = nullptr,
                .drmFormatModifierCount         = pSource->drmFormatModifierCount,
                .pDrmFormatModifiers            = reinterpret_cast < uint64_t const * > ( pSource->pDrmFormatModifiers )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_DEDICATED_ALLOCATION_AVAILABLE
    auto toVulkanFormat (
            VkDedicatedAllocationImageCreateInfoNV              * pDestination,
            Type ( DedicatedAllocationImageCreateInfoNVidia ) const * pSource
    ) noexcept -> VkDedicatedAllocationImageCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV,
                .pNext                          = nullptr,
                .dedicatedAllocation            = pSource->dedicatedAllocation
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE
    auto toVulkanFormat (
            VkExternalFormatANDROID              * pDestination,
            Type ( ExternalFormatAndroid ) const * pSource
    ) noexcept -> VkExternalFormatANDROID * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_EXTERNAL_FORMAT_ANDROID,
                .pNext                          = nullptr,
                .externalFormat                 = pSource->externalFormat
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkImageSubresource              * pDestination,
            Type ( ImageSubresource ) const * pSource
    ) noexcept -> VkImageSubresource * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .aspectMask     = pSource->aspectMask,
                .mipLevel       = pSource->mipLevel,
                .arrayLayer     = pSource->arrayLayer
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto fromVulkanFormat (
            Type ( SubresourceLayout )       * pDestination,
            VkSubresourceLayout        const * pSource
    ) noexcept -> Type ( SubresourceLayout ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .offset     = pSource->offset,
                .size       = pSource->size,
                .rowPitch   = pSource->rowPitch,
                .arrayPitch = pSource->arrayPitch,
                .depthPitch = pSource->depthPitch
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_IMAGE_DRM_FORMAT_MODIFIER_AVAILABLE
    auto fromVulkanFormat (
            Type ( ImageDrmFormatModifierProperties )       * pDestination,
            VkImageDrmFormatModifierPropertiesEXT     const * pSource
    ) noexcept -> Type ( ImageDrmFormatModifierProperties ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType      = StructureTypeImageDRMFormatModifierProperties,
                .pNext              = nullptr,
                .drmFormatModifier  = pSource->drmFormatModifier
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto prepareContext (
            CreateAccelerationStructureNVidiaContext              * pContext,
            Type ( AccelerationStructureCreateInfoNVidia )  const * pSource
    ) noexcept -> VkAccelerationStructureCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->createInfo, pSource );

        pContext->createInfo.info.pGeometries = & pContext->geometries[0];

        if ( pContext->createInfo.info.geometryCount > engine :: vulkan :: config :: accelerationStructureNVidiaGeometryCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: accelerationStructureNVidiaGeometryCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: accelerationStructureNVidiaGeometryCount,
                    pContext->createInfo.info.geometryCount
            ))

            pContext->createInfo.info.geometryCount = engine :: vulkan :: config :: accelerationStructureNVidiaGeometryCount;
        }

        for ( uint32 i = 0U; i < pContext->createInfo.info.geometryCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->geometries[i], & pSource->info.pGeometries[i] );
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureCreateInfoNV                  * pDestination,
            Type ( AccelerationStructureCreateInfoNVidia ) const * pSource
    ) noexcept -> VkAccelerationStructureCreateInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV,
                .pNext          = nullptr,
                .compactedSize  = pSource->compactedSize,
                .info           = {
                        .sType          = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV,
                        .pNext          = nullptr,
                        .type           = static_cast < VkAccelerationStructureTypeNV > ( pSource->info.type ),
                        .flags          = pSource->info.flags,
                        .instanceCount  = pSource->info.instanceCount,
                        .geometryCount  = pSource->info.geometryCount,
                        .pGeometries    = nullptr
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto toVulkanFormat (
            VkGeometryNV                  * pDestination,
            Type ( GeometryNVidia ) const * pSource
    ) noexcept -> VkGeometryNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_GEOMETRY_NV,
                .pNext              = nullptr,
                .geometryType       = static_cast < VkGeometryTypeKHR > ( pSource->geometryType ),
                .geometry           = {
                        .triangles          = {
                                .sType              = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV,
                                .pNext              = nullptr,
                                .vertexData         = pSource->geometry.triangles.vertexData,
                                .vertexOffset       = pSource->geometry.triangles.vertexOffset,
                                .vertexCount        = pSource->geometry.triangles.vertexCount,
                                .vertexStride       = pSource->geometry.triangles.vertexStride,
                                .vertexFormat       = static_cast < VkFormat > ( pSource->geometry.triangles.vertexFormat ),
                                .indexData          = pSource->geometry.triangles.indexData,
                                .indexOffset        = pSource->geometry.triangles.indexOffset,
                                .indexCount         = pSource->geometry.triangles.indexCount,
                                .indexType          = static_cast < VkIndexType > ( pSource->geometry.triangles.indexType ),
                                .transformData      = pSource->geometry.triangles.transformData,
                                .transformOffset    = pSource->geometry.triangles.transformOffset
                        },
                        .aabbs              = {
                                .sType              = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV,
                                .pNext              = nullptr,
                                .aabbData           = pSource->geometry.aabbs.aabbData,
                                .numAABBs           = pSource->geometry.aabbs.numAABBs,
                                .stride             = pSource->geometry.aabbs.stride,
                                .offset             = pSource->geometry.aabbs.offset
                        }
                },
                .flags              = pSource->flags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto prepareContext (
            CreateAccelerationStructureKhronosContext       * pContext,
            Type ( AccelerationStructureCreateInfo )  const * pSource
    ) noexcept -> VkAccelerationStructureCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

                case StructureTypeAccelerationStructureMotionInfoNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->motionInfo,
                                    reinterpret_cast < Type ( AccelerationStructureMotionInfoNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureCreateInfoKHR           * pDestination,
            Type ( AccelerationStructureCreateInfo ) const * pSource
    ) noexcept -> VkAccelerationStructureCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR,
                .pNext              = nullptr,
                .createFlags        = pSource->flags,
                .buffer             = pSource->buffer,
                .offset             = pSource->offset,
                .size               = pSource->size,
                .type               = static_cast < VkAccelerationStructureTypeKHR > ( pSource->type ),
                .deviceAddress      = pSource->deviceAddress
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureMotionInfoNV                  * pDestination,
            Type ( AccelerationStructureMotionInfoNVidia ) const * pSource
    ) noexcept -> VkAccelerationStructureMotionInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MOTION_INFO_NV,
                .pNext              = nullptr,
                .maxInstances       = pSource->maxInstances,
                .flags              = pSource->flags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    static auto accelerationStructureBuildSizesContextOnDelete (
            GenericContext * pGenericContext
    ) noexcept -> void {
        delete [] reinterpret_cast < GetAccelerationStructureBuildSizesContext * > ( pGenericContext )->pDynamicGeometries;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto prepareContext (
            GetAccelerationStructureBuildSizesContext              * pContext,
            Type ( AccelerationStructureBuildGeometryInfo )  const * pSource
    ) noexcept -> VkAccelerationStructureBuildGeometryInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        if ( pSource->geometryCount != 0U && pSource->ppGeometries != nullptr ) {
            pContext->common.ruleSet.onDelete   = & accelerationStructureBuildSizesContextOnDelete;
            pContext->pDynamicGeometries        = new VkAccelerationStructureGeometryKHR [ pSource->geometryCount ];
        }

        (void) toVulkanFormat ( & pContext->geometryInfo, pSource );

        if ( pSource->geometryCount != 0U && pSource->pGeometries != nullptr ) {
            pContext->geometryInfo.pGeometries = & pContext->geometries[0];

            if ( pContext->geometryInfo.geometryCount > engine :: vulkan :: config :: accelerationStructureGeometryCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                        "config :: accelerationStructureGeometryCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: accelerationStructureGeometryCount,
                        pContext->geometryInfo.geometryCount
                ))

                pContext->geometryInfo.geometryCount = engine :: vulkan :: config :: accelerationStructureGeometryCount;
            }

            for ( uint32 i = 0U; i < pContext->geometryInfo.geometryCount; ++ i ) {
                auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pGeometries[i].pNext );
                auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->geometries[i], & pSource->pGeometries[i] ) );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

                        case StructureTypeAccelerationStructureGeometryMotionTrianglesDataNVidia:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->trianglesData[i],
                                            reinterpret_cast < Type ( AccelerationStructureGeometryMotionTrianglesDataNVidia ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }
        } else {
            pContext->geometryInfo.ppGeometries = & pContext->geometryPointers[0];

            if ( pContext->geometryInfo.geometryCount > engine :: vulkan :: config :: accelerationStructureGeometryCount ) {
                __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                        "config :: accelerationStructureGeometryCount = %d. Minimum Required = %d",
                        engine :: vulkan :: config :: accelerationStructureGeometryCount,
                        pContext->geometryInfo.geometryCount
                ))

                pContext->geometryInfo.geometryCount = engine :: vulkan :: config :: accelerationStructureGeometryCount;
            }

            for ( uint32 i = 0U; i < pContext->geometryInfo.geometryCount; ++ i ) {
                pContext->geometryPointers[i] = & pContext->pDynamicGeometries[i];

                auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pGeometries[i].pNext );
                auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->pDynamicGeometries[i], pSource->ppGeometries[i] ) );

                while ( pCurrent != nullptr ) {

                    switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE

                        case StructureTypeAccelerationStructureGeometryMotionTrianglesDataNVidia:
                            pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                    toVulkanFormat (
                                            & pContext->trianglesData[i],
                                            reinterpret_cast < Type ( AccelerationStructureGeometryMotionTrianglesDataNVidia ) const * > ( pCurrent )
                                    )
                            );
                            break;

#endif

                        default:
                            break;
                    }

                    pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                    pCurrent    = pCurrent->pNext;
                }

                pCurrentVk->pNext = nullptr;
            }
        }

        return & pContext->geometryInfo;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureBuildGeometryInfoKHR           * pDestination,
            Type ( AccelerationStructureBuildGeometryInfo ) const * pSource
    ) noexcept -> VkAccelerationStructureBuildGeometryInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                      = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
        pDestination->pNext                      = nullptr;
        pDestination->type                       = static_cast < VkAccelerationStructureTypeKHR > ( pSource->type );
        pDestination->flags                      = pSource->flags;
        pDestination->mode                       = static_cast < VkBuildAccelerationStructureModeKHR > ( pSource->mode );
        pDestination->srcAccelerationStructure   = pSource->source;
        pDestination->dstAccelerationStructure   = pSource->destination;
        pDestination->geometryCount              = pSource->geometryCount;
        pDestination->pGeometries                = nullptr;
        pDestination->ppGeometries               = nullptr;

        (void) std :: memcpy ( & pDestination->scratchData, & pSource->scratchData, sizeof ( VkDeviceOrHostAddressKHR ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureGeometryKHR           * pDestination,
            Type ( AccelerationStructureGeometry ) const * pSource
    ) noexcept -> VkAccelerationStructureGeometryKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType                      = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
        pDestination->pNext                      = nullptr;
        pDestination->geometryType               = static_cast < VkGeometryTypeKHR > ( pSource->geometryType );
        pDestination->flags                      = pSource->flags;

        switch ( pDestination->geometryType ) {
            case VK_GEOMETRY_TYPE_AABBS_KHR:
                (void) toVulkanFormat ( & pDestination->geometry.aabbs, & pSource->geometry.aabbs );
                break;
            case VK_GEOMETRY_TYPE_TRIANGLES_KHR:
                (void) toVulkanFormat ( & pDestination->geometry.triangles, & pSource->geometry.triangles );
                break;
            case VK_GEOMETRY_TYPE_INSTANCES_KHR:
                (void) toVulkanFormat ( & pDestination->geometry.instances, & pSource->geometry.instances );
                break;
            default:
                break;
        }

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureGeometryTrianglesDataKHR           * pDestination,
            Type ( AccelerationStructureGeometryTrianglesData ) const * pSource
    ) noexcept -> VkAccelerationStructureGeometryTrianglesDataKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType             = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
        pDestination->pNext             = nullptr;
        pDestination->vertexFormat      = static_cast < VkFormat > ( pSource->vertexFormat );
        pDestination->vertexStride      = pSource->vertexStride;
        pDestination->maxVertex         = pSource->maxVertex;
        pDestination->indexType         = static_cast < VkIndexType > ( pSource->indexType );

        (void) std :: memcpy ( & pDestination->vertexData,      & pSource->vertexData,      sizeof ( VkDeviceOrHostAddressConstKHR ) );
        (void) std :: memcpy ( & pDestination->indexData,       & pSource->indexData,       sizeof ( VkDeviceOrHostAddressConstKHR ) );
        (void) std :: memcpy ( & pDestination->transformData,   & pSource->transformData,   sizeof ( VkDeviceOrHostAddressConstKHR ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureGeometryAabbsDataKHR           * pDestination,
            Type ( AccelerationStructureGeometryAabbsData ) const * pSource
    ) noexcept -> VkAccelerationStructureGeometryAabbsDataKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType             = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR;
        pDestination->pNext             = nullptr;
        pDestination->stride            = pSource->stride;

        (void) std :: memcpy ( & pDestination->data, & pSource->data, sizeof ( VkDeviceOrHostAddressConstKHR ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureGeometryInstancesDataKHR           * pDestination,
            Type ( AccelerationStructureGeometryInstancesData ) const * pSource
    ) noexcept -> VkAccelerationStructureGeometryInstancesDataKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType             = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR;
        pDestination->pNext             = nullptr;
        pDestination->arrayOfPointers   = pSource->arrayOfPointers;

        (void) std :: memcpy ( & pDestination->data, & pSource->data, sizeof ( VkDeviceOrHostAddressConstKHR ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_MOTION_BLUR_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureGeometryMotionTrianglesDataNV                  * pDestination,
            Type ( AccelerationStructureGeometryMotionTrianglesDataNVidia ) const * pSource
    ) noexcept -> VkAccelerationStructureGeometryMotionTrianglesDataNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType             = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MOTION_TRIANGLES_DATA_NV;
        pDestination->pNext             = nullptr;

        (void) std :: memcpy ( & pDestination->vertexData, & pSource->vertexData, sizeof ( VkDeviceOrHostAddressConstKHR ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto fromVulkanFormat (
            Type ( AccelerationStructureBuildSizesInfo )       * pDestination,
            VkAccelerationStructureBuildSizesInfoKHR     const * pSource
    ) noexcept -> Type ( AccelerationStructureBuildSizesInfo ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType              = StructureTypeAccelerationStructureBuildSizesInfo,
                .pNext                      = nullptr,
                .accelerationStructureSize  = pSource->accelerationStructureSize,
                .updateScratchSize          = pSource->updateScratchSize,
                .buildScratchSize           = pSource->buildScratchSize
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureMemoryRequirementsInfoNV                  * pDestination,
            Type ( AccelerationStructureMemoryRequirementsInfoNVidia ) const * pSource
    ) noexcept -> VkAccelerationStructureMemoryRequirementsInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                  = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV,
                .pNext                  = nullptr,
                .type                   = static_cast < VkAccelerationStructureMemoryRequirementsTypeNV > ( pSource->type ),
                .accelerationStructure  = pSource->accelerationStructure
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto prepareContext (
            GetAccelerationStructureMemoryRequirementsContext              * pContext,
            Type ( MemoryRequirements2 )                             const * pSource
    ) noexcept -> VkMemoryRequirements2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->requirements2, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

                case StructureTypeMemoryDedicatedRequirements:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->dedicatedRequirements,
                                    reinterpret_cast < Type ( MemoryDedicatedRequirements ) const * > ( pCurrent )
                            )
                    );
                    break;

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->requirements2;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkMemoryRequirements2              * pDestination,
            Type ( MemoryRequirements2 ) const * pSource
    ) noexcept -> VkMemoryRequirements2 * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
        pDestination->pNext = nullptr;

        (void) toVulkanFormat ( & pDestination->memoryRequirements, & pSource->memoryRequirements );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkMemoryRequirements              * pDestination,
            Type ( MemoryRequirements ) const * pSource
    ) noexcept -> VkMemoryRequirements * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .size           = pSource->size,
                .alignment      = pSource->alignment,
                .memoryTypeBits = pSource->memoryTypeBits
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkMemoryDedicatedRequirements              * pDestination,
            Type ( MemoryDedicatedRequirements ) const * pSource
    ) noexcept -> VkMemoryDedicatedRequirements * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS,
                .pNext                          = nullptr,
                .prefersDedicatedAllocation     = pSource->prefersDedicatedAllocation,
                .requiresDedicatedAllocation    = pSource->requiresDedicatedAllocation
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto extractContext (
            Type ( MemoryRequirements2 )                                   * pDestination,
            GetAccelerationStructureMemoryRequirementsContext        const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pDestination == nullptr ) {
            return;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericOutStructure ) * > ( fromVulkanFormat ( pDestination, & pContext->requirements2 ) );

        while ( pCurrent->pNext != nullptr ) {

            switch ( pCurrent->pNext->structureType ) {

                case StructureTypeMemoryDedicatedRequirements:
                    pCurrent->pNext = reinterpret_cast < Type ( GenericOutStructure ) * > (
                            fromVulkanFormat (
                                    reinterpret_cast < Type ( MemoryDedicatedRequirements * ) > ( pCurrent->pNext ),
                                    & pContext->dedicatedRequirements
                            )
                    );
                    break;

                default:
                    break;
            }

            pCurrent    = pCurrent->pNext;
        }
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto fromVulkanFormat (
            Type ( MemoryRequirements2 )    * pDestination,
            VkMemoryRequirements2     const * pSource
    ) noexcept -> Type ( MemoryRequirements2 ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->structureType = StructureTypeMemoryRequirements;
        (void) fromVulkanFormat ( & pDestination->memoryRequirements, & pSource->memoryRequirements );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto fromVulkanFormat (
            Type ( MemoryDedicatedRequirements )    * pDestination,
            VkMemoryDedicatedRequirements     const * pSource
    ) noexcept -> Type ( MemoryDedicatedRequirements ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType                  = StructureTypeMemoryDedicatedRequirements,
                .pNext                          = nullptr,
                .prefersDedicatedAllocation     = pSource->prefersDedicatedAllocation,
                .requiresDedicatedAllocation    = pSource->requiresDedicatedAllocation
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto fromVulkanFormat (
            Type ( MemoryRequirements )    * pDestination,
            VkMemoryRequirements     const * pSource
    ) noexcept -> Type ( MemoryRequirements ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .size           = pSource->size,
                .alignment      = pSource->alignment,
                .memoryTypeBits = pSource->memoryTypeBits
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto prepareContext (
            BindAccelerationStructureMemoryContext                    * pContext,
            cds :: uint32                                               count,
            Type ( BindAccelerationStructureMemoryInfoNVidia )  const * pInfos
    ) noexcept -> VkBindAccelerationStructureMemoryInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || count == 0U || pInfos == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: bindAccelerationStructureCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: bindAccelerationStructureCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: bindAccelerationStructureCount,
                    count
            ))

            count = engine :: vulkan :: config :: bindAccelerationStructureCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->infos[i], & pInfos[i] );
        }

        return & pContext->infos[0];
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto toVulkanFormat (
            VkBindAccelerationStructureMemoryInfoNV                  * pDestination,
            Type ( BindAccelerationStructureMemoryInfoNVidia ) const * pSource
    ) noexcept -> VkBindAccelerationStructureMemoryInfoNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV,
                .pNext                          = nullptr,
                .accelerationStructure          = pSource->accelerationStructure,
                .memory                         = pSource->memory,
                .memoryOffset                   = pSource->memoryOffset,
                .deviceIndexCount               = pSource->deviceIndexCount,
                .pDeviceIndices                 = pSource->pDeviceIndices
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto toVulkanFormat (
            VkAccelerationStructureDeviceAddressInfoKHR                  * pDestination,
            Type ( AccelerationStructureDeviceAddressInfo ) const * pSource
    ) noexcept -> VkAccelerationStructureDeviceAddressInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR,
                .pNext                          = nullptr,
                .accelerationStructure          = pSource->accelerationStructure
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateSamplerContext              * pContext,
            Type ( SamplerCreateInfo )  const * pSource
    ) noexcept -> VkSamplerCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE

                case StructureTypeSamplerBorderColorComponentMappingCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->borderColorComponentMappingCreateInfo,
                                    reinterpret_cast < Type ( SamplerBorderColorComponentMappingCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE

                case StructureTypeSamplerCustomBorderColorCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->customBorderColorCreateInfo,
                                    reinterpret_cast < Type ( SamplerCustomBorderColorCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeSamplerReductionModeCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->reductionModeCreateInfo,
                                    reinterpret_cast < Type ( SamplerReductionModeCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE

                case StructureTypeSamplerYCBCRConversionInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->ycbcrConversionInfo,
                                    reinterpret_cast < Type ( SamplerYCBCRConversionInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkSamplerCreateInfo              * pDestination,
            Type ( SamplerCreateInfo ) const * pSource
    ) noexcept -> VkSamplerCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .magFilter                  = static_cast < VkFilter > ( pSource->magFilter ),
                .minFilter                  = static_cast < VkFilter > ( pSource->minFilter ),
                .mipmapMode                 = static_cast < VkSamplerMipmapMode > ( pSource->mipmapMode ),
                .addressModeU               = static_cast < VkSamplerAddressMode > ( pSource->addressModeU ),
                .addressModeV               = static_cast < VkSamplerAddressMode > ( pSource->addressModeV ),
                .addressModeW               = static_cast < VkSamplerAddressMode > ( pSource->addressModeW ),
                .mipLodBias                 = pSource->mipLodBias,
                .anisotropyEnable           = pSource->anisotropyEnable,
                .maxAnisotropy              = pSource->maxAnisotropy,
                .compareEnable              = pSource->compareEnable,
                .compareOp                  = static_cast < VkCompareOp > ( pSource->compareOperation ),
                .minLod                     = pSource->minLod,
                .maxLod                     = pSource->maxLod,
                .borderColor                = static_cast < VkBorderColor > ( pSource->borderColor ),
                .unnormalizedCoordinates    = pSource->unnormalizedCoordinates
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkSamplerReductionModeCreateInfo              * pDestination,
            Type ( SamplerReductionModeCreateInfo ) const * pSource
    ) noexcept -> VkSamplerReductionModeCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO,
                .pNext                      = nullptr,
                .reductionMode              = static_cast < VkSamplerReductionMode > ( pSource->reductionMode )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_BORDER_COLOR_SWIZZLE_AVAILABLE
    auto toVulkanFormat (
            VkSamplerBorderColorComponentMappingCreateInfoEXT           * pDestination,
            Type ( SamplerBorderColorComponentMappingCreateInfo ) const * pSource
    ) noexcept -> VkSamplerBorderColorComponentMappingCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_SAMPLER_BORDER_COLOR_COMPONENT_MAPPING_CREATE_INFO_EXT,
                .pNext                      = nullptr,
                .components                 = {
                        .r                          = static_cast < VkComponentSwizzle > ( pSource->components.r ),
                        .g                          = static_cast < VkComponentSwizzle > ( pSource->components.g ),
                        .b                          = static_cast < VkComponentSwizzle > ( pSource->components.b ),
                        .a                          = static_cast < VkComponentSwizzle > ( pSource->components.a )
                },
                .srgb                       = pSource->srgb
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_CUSTOM_BORDER_COLOR_AVAILABLE
    auto toVulkanFormat (
            VkSamplerCustomBorderColorCreateInfoEXT           * pDestination,
            Type ( SamplerCustomBorderColorCreateInfo ) const * pSource
    ) noexcept -> VkSamplerCustomBorderColorCreateInfoEXT * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif


        pDestination->sType     = VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT;
        pDestination->pNext     = nullptr;
        pDestination->format    = static_cast < VkFormat > ( pSource->format );

        (void) std :: memcpy ( & pDestination->customBorderColor, & pSource->customBorderColor, sizeof ( VkClearColorValue ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto prepareContext (
            CreateSamplerContext                             * pContext,
            Type ( SamplerYCBCRConversionCreateInfo )  const * pSource
    ) noexcept -> VkSamplerYcbcrConversionCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->ycbcrConversionCreateInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_AVAILABLE

                case StructureTypeExternalFormatAndroid:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->externalFormat,
                                    reinterpret_cast < Type ( ExternalFormatAndroid ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->ycbcrConversionCreateInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkSamplerYcbcrConversionCreateInfo              * pDestination,
            Type ( SamplerYCBCRConversionCreateInfo ) const * pSource
    ) noexcept -> VkSamplerYcbcrConversionCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO,
                .pNext                          = nullptr,
                .format                         = static_cast < VkFormat > ( pSource->format ),
                .ycbcrModel                     = static_cast < VkSamplerYcbcrModelConversion > ( pSource->ycbcrModel ),
                .ycbcrRange                     = static_cast < VkSamplerYcbcrRange > ( pSource->ycbcrRange ),
                .components                     = {
                        .r                              = static_cast < VkComponentSwizzle > ( pSource->components.r ),
                        .g                              = static_cast < VkComponentSwizzle > ( pSource->components.g ),
                        .b                              = static_cast < VkComponentSwizzle > ( pSource->components.b ),
                        .a                              = static_cast < VkComponentSwizzle > ( pSource->components.a )
                },
                .xChromaOffset                  = static_cast < VkChromaLocation > ( pSource->xChromaOffset ),
                .yChromaOffset                  = static_cast < VkChromaLocation > ( pSource->yChromaOffset ),
                .chromaFilter                   = static_cast < VkFilter > ( pSource->chromaFilter ),
                .forceExplicitReconstruction    = pSource->forceExplicitReconstruction
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateDescriptorSetLayoutContext              * pContext,
            Type ( DescriptorSetLayoutCreateInfo )  const * pSource
    ) noexcept -> VkDescriptorSetLayoutCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeDescriptorSetLayoutBindingFlagsCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->bindingFlagsCreateInfo,
                                    reinterpret_cast < Type ( DescriptorSetLayoutBindingFlagsCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

                case StructureTypeMutableDescriptorTypeCreateInfoValve: {
                    auto pMutableDescriptorTypeCreateInfo = reinterpret_cast < Type ( MutableDescriptorTypeCreateInfoValve ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->mutableDescriptorTypeCreateInfo,
                                    pMutableDescriptorTypeCreateInfo
                            )
                    );

                    pContext->mutableDescriptorTypeCreateInfo.pMutableDescriptorTypeLists = & pContext->mutableDescriptorTypeLists[0];

                    if ( pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount > engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: descriptorSetMutableDescriptorTypeListCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount,
                                pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount
                        ))

                        pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount = engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount;
                    }

                    for ( uint32 i = 0U; i < pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount; ++ i ) {
                        (void) toVulkanFormat ( & pContext->mutableDescriptorTypeLists[i], & pMutableDescriptorTypeCreateInfo->pMutableDescriptorTypeLists[i] );

                        pContext->mutableDescriptorTypeLists[i].pDescriptorTypes = & pContext->mutableDescriptorListEntries[i][0];

                        if ( pContext->mutableDescriptorTypeLists[i].descriptorTypeCount > engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: descriptorSetMutableDescriptorListItemCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount,
                                    pContext->mutableDescriptorTypeLists[i].descriptorTypeCount
                            ))

                            pContext->mutableDescriptorTypeLists[i].descriptorTypeCount = engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount;
                        }

                        for ( uint32 j = 0U; j < pContext->mutableDescriptorTypeLists[i].descriptorTypeCount; ++ j ) {
                            pContext->mutableDescriptorListEntries[i][j] = static_cast < VkDescriptorType > ( pMutableDescriptorTypeCreateInfo->pMutableDescriptorTypeLists[i].pDescriptorTypes[j] );
                        }
                    }

                    break;
                }

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        pContext->createInfo.pBindings = & pContext->bindings[0];

        if ( pContext->createInfo.bindingCount > engine :: vulkan :: config :: descriptorSetLayoutBindingCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: descriptorSetLayoutBindingCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: descriptorSetLayoutBindingCount,
                    pContext->createInfo.bindingCount
            ))

            pContext->createInfo.bindingCount = engine :: vulkan :: config :: descriptorSetLayoutBindingCount;
        }

        for ( uint32 i = 0U; i < pContext->createInfo.bindingCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->bindings[i], & pSource->pBindings[i] );
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorSetLayoutCreateInfo              * pDestination,
            Type ( DescriptorSetLayoutCreateInfo ) const * pSource
    ) noexcept -> VkDescriptorSetLayoutCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                .pNext                          = nullptr,
                .flags                          = pSource->flags,
                .bindingCount                   = pSource->bindingCount,
                .pBindings                      = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorSetLayoutBinding              * pDestination,
            Type ( DescriptorSetLayoutBinding ) const * pSource
    ) noexcept -> VkDescriptorSetLayoutBinding * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .binding            = pSource->binding,
                .descriptorType     = static_cast < VkDescriptorType > ( pSource->descriptorType ),
                .descriptorCount    = pSource->descriptorCount,
                .stageFlags         = pSource->stageFlags,
                .pImmutableSamplers = pSource->pImmutableSamplers
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorSetLayoutBindingFlagsCreateInfo              * pDestination,
            Type ( DescriptorSetLayoutBindingFlagsCreateInfo ) const * pSource
    ) noexcept -> VkDescriptorSetLayoutBindingFlagsCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
                .pNext          = nullptr,
                .bindingCount   = pSource->bindingCount,
                .pBindingFlags  = pSource->pBindingFlags
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    auto toVulkanFormat (
            VkMutableDescriptorTypeCreateInfoVALVE              * pDestination,
            Type ( MutableDescriptorTypeCreateInfoValve ) const * pSource
    ) noexcept -> VkMutableDescriptorTypeCreateInfoVALVE * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_VALVE,
                .pNext                          = nullptr,
                .mutableDescriptorTypeListCount = pSource->mutableDescriptorTypeListCount,
                .pMutableDescriptorTypeLists    = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE
    auto toVulkanFormat (
            VkMutableDescriptorTypeListVALVE              * pDestination,
            Type ( MutableDescriptorTypeListValve ) const * pSource
    ) noexcept -> VkMutableDescriptorTypeListVALVE * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .descriptorTypeCount    = pSource->descriptorTypeCount,
                .pDescriptorTypes       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto prepareContext (
            GetDescriptorSetLayoutSupportContext          * pContext,
            Type ( DescriptorSetLayoutCreateInfo )  const * pSource
    ) noexcept -> VkDescriptorSetLayoutCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeDescriptorSetLayoutBindingFlagsCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->bindingFlagsCreateInfo,
                                    reinterpret_cast < Type ( DescriptorSetLayoutBindingFlagsCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

                case StructureTypeMutableDescriptorTypeCreateInfoValve: {
                    auto pMutableDescriptorTypeCreateInfo = reinterpret_cast < Type ( MutableDescriptorTypeCreateInfoValve ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->mutableDescriptorTypeCreateInfo,
                                    pMutableDescriptorTypeCreateInfo
                            )
                    );

                    pContext->mutableDescriptorTypeCreateInfo.pMutableDescriptorTypeLists = & pContext->mutableDescriptorTypeLists[0];

                    if ( pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount > engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: descriptorSetMutableDescriptorTypeListCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount,
                                pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount
                        ))

                        pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount = engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount;
                    }

                    for ( uint32 i = 0U; i < pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount; ++ i ) {
                        (void) toVulkanFormat ( & pContext->mutableDescriptorTypeLists[i], & pMutableDescriptorTypeCreateInfo->pMutableDescriptorTypeLists[i] );

                        pContext->mutableDescriptorTypeLists[i].pDescriptorTypes = & pContext->mutableDescriptorListEntries[i][0];

                        if ( pContext->mutableDescriptorTypeLists[i].descriptorTypeCount > engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: descriptorSetMutableDescriptorListItemCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount,
                                    pContext->mutableDescriptorTypeLists[i].descriptorTypeCount
                            ))

                            pContext->mutableDescriptorTypeLists[i].descriptorTypeCount = engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount;
                        }

                        for ( uint32 j = 0U; j < pContext->mutableDescriptorTypeLists[i].descriptorTypeCount; ++ j ) {
                            pContext->mutableDescriptorListEntries[i][j] = static_cast < VkDescriptorType > ( pMutableDescriptorTypeCreateInfo->pMutableDescriptorTypeLists[i].pDescriptorTypes[j] );
                        }
                    }

                    break;
                }

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        pContext->createInfo.pBindings = & pContext->bindings[0];

        if ( pContext->createInfo.bindingCount > engine :: vulkan :: config :: descriptorSetLayoutBindingCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: descriptorSetLayoutBindingCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: descriptorSetLayoutBindingCount,
                    pContext->createInfo.bindingCount
            ))

            pContext->createInfo.bindingCount = engine :: vulkan :: config :: descriptorSetLayoutBindingCount;
        }

        for ( uint32 i = 0U; i < pContext->createInfo.bindingCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->bindings[i], & pSource->pBindings[i] );
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto prepareContext (
            GetDescriptorSetLayoutSupportContext       * pContext,
            Type ( DescriptorSetLayoutSupport )  const * pSource
    ) noexcept -> VkDescriptorSetLayoutSupport * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->support, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeDescriptorSetVariableDescriptorCountLayoutSupport:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->variableDescriptorCountSupport,
                                    reinterpret_cast < Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->support;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorSetLayoutSupport              * pDestination,
            Type ( DescriptorSetLayoutSupport ) const * pSource
    ) noexcept -> VkDescriptorSetLayoutSupport * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType      = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT,
                .pNext      = nullptr,
                .supported  = pSource->supported
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorSetVariableDescriptorCountLayoutSupport              * pDestination,
            Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) const * pSource
    ) noexcept -> VkDescriptorSetVariableDescriptorCountLayoutSupport * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT,
                .pNext                      = nullptr,
                .maxVariableDescriptorCount = pSource->maxVariableDescriptorCount
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto extractContext (
            Type ( DescriptorSetLayoutSupport )           * pDestination,
            GetDescriptorSetLayoutSupportContext    const * pContext
    ) noexcept -> void {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pContext == nullptr ) {
            return;
        }

#endif

        auto pCurrent = reinterpret_cast < Type ( GenericOutStructure ) * > ( fromVulkanFormat ( pDestination, & pContext->support ) );

        while ( pCurrent->pNext != nullptr ) {

            switch ( pCurrent->pNext->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE

                case StructureTypeDescriptorSetVariableDescriptorCountLayoutSupport:
                    pCurrent->pNext = reinterpret_cast < Type ( GenericOutStructure ) * > (
                            fromVulkanFormat (
                                    reinterpret_cast < Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) * > ( pCurrent->pNext ),
                                    & pContext->variableDescriptorCountSupport
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrent = pCurrent->pNext;
        }
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto fromVulkanFormat (
            Type ( DescriptorSetLayoutSupport )    * pDestination,
            VkDescriptorSetLayoutSupport     const * pSource
    ) noexcept -> Type ( DescriptorSetLayoutSupport ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType  = StructureTypeDescriptorSetLayoutSupport,
                .pNext          = nullptr,
                .supported      = pSource->supported
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto fromVulkanFormat (
            Type ( DescriptorSetVariableDescriptorCountLayoutSupport )    * pDestination,
            VkDescriptorSetVariableDescriptorCountLayoutSupport     const * pSource
    ) noexcept -> Type ( DescriptorSetVariableDescriptorCountLayoutSupport ) * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .structureType              = StructureTypeDescriptorSetVariableDescriptorCountLayoutSupport,
                .pNext                      = nullptr,
                .maxVariableDescriptorCount = pSource->maxVariableDescriptorCount
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreatePipelineLayoutContext              * pContext,
            Type ( PipelineLayoutCreateInfo )  const * pSource
    ) noexcept -> VkPipelineLayoutCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->createInfo, pSource );

        pContext->createInfo.pPushConstantRanges = & pContext->pushConstantRanges[0];

        if ( pContext->createInfo.pushConstantRangeCount > engine :: vulkan :: config :: pipelineLayoutPushConstantRangeCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: pipelineLayoutPushConstantRangeCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: pipelineLayoutPushConstantRangeCount,
                    pContext->createInfo.pushConstantRangeCount
            ))

            pContext->createInfo.pushConstantRangeCount = engine :: vulkan :: config :: pipelineLayoutPushConstantRangeCount;
        }

        for ( uint32 i = 0U; i < pContext->createInfo.pushConstantRangeCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->pushConstantRanges[i], & pSource->pPushConstantRanges[i] );
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPipelineLayoutCreateInfo              * pDestination,
            Type ( PipelineLayoutCreateInfo ) const * pSource
    ) noexcept -> VkPipelineLayoutCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .setLayoutCount             = pSource->setLayoutCount,
                .pSetLayouts                = pSource->pSetLayouts,
                .pushConstantRangeCount     = pSource->pushConstantRangeCount,
                .pPushConstantRanges        = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkPushConstantRange              * pDestination,
            Type ( PushConstantRange ) const * pSource
    ) noexcept -> VkPushConstantRange * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .stageFlags = pSource->stageFlags,
                .offset     = pSource->offset,
                .size       = pSource->size
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateDescriptorPoolContext              * pContext,
            Type ( DescriptorPoolCreateInfo )  const * pSource
    ) noexcept -> VkDescriptorPoolCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

                case StructureTypeDescriptorPoolInlineUniformBlockCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->inlineUniformBlockCreateInfo,
                                    reinterpret_cast < Type ( DescriptorPoolInlineUniformBlockCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VALVE_MUTABLE_DESCRIPTOR_TYPE_AVAILABLE

                case StructureTypeMutableDescriptorTypeCreateInfoValve: {
                    auto pMutableDescriptorTypeCreateInfo = reinterpret_cast < Type ( MutableDescriptorTypeCreateInfoValve ) const * > ( pCurrent );
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->mutableDescriptorTypeCreateInfo,
                                    pMutableDescriptorTypeCreateInfo
                            )
                    );

                    pContext->mutableDescriptorTypeCreateInfo.pMutableDescriptorTypeLists = & pContext->mutableDescriptorTypeLists[0];

                    if ( pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount > engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount ) {
                        __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                "config :: descriptorSetMutableDescriptorTypeListCount = %d. Minimum Required = %d",
                                engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount,
                                pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount
                        ))

                        pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount = engine :: vulkan :: config :: descriptorSetMutableDescriptorTypeListCount;
                    }

                    for ( uint32 i = 0U; i < pContext->mutableDescriptorTypeCreateInfo.mutableDescriptorTypeListCount; ++ i ) {
                        (void) toVulkanFormat ( & pContext->mutableDescriptorTypeLists[i], & pMutableDescriptorTypeCreateInfo->pMutableDescriptorTypeLists[i] );

                        pContext->mutableDescriptorTypeLists[i].pDescriptorTypes = & pContext->mutableDescriptorListEntries[i][0];

                        if ( pContext->mutableDescriptorTypeLists[i].descriptorTypeCount > engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount ) {
                            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                                    "config :: descriptorSetMutableDescriptorListItemCount = %d. Minimum Required = %d",
                                    engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount,
                                    pContext->mutableDescriptorTypeLists[i].descriptorTypeCount
                            ))

                            pContext->mutableDescriptorTypeLists[i].descriptorTypeCount = engine :: vulkan :: config :: descriptorSetMutableDescriptorListItemCount;
                        }

                        for ( uint32 j = 0U; j < pContext->mutableDescriptorTypeLists[i].descriptorTypeCount; ++ j ) {
                            pContext->mutableDescriptorListEntries[i][j] = static_cast < VkDescriptorType > ( pMutableDescriptorTypeCreateInfo->pMutableDescriptorTypeLists[i].pDescriptorTypes[j] );
                        }
                    }

                    break;
                }

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        pContext->createInfo.pPoolSizes = & pContext->poolSizes[0];

        if ( pContext->createInfo.poolSizeCount > engine :: vulkan :: config :: descriptorPoolSizeCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: descriptorPoolSizeCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: descriptorPoolSizeCount,
                    pContext->createInfo.poolSizeCount
            ))

            pContext->createInfo.poolSizeCount = engine :: vulkan :: config :: descriptorPoolSizeCount;
        }

        for ( uint32 i = 0U; i < pContext->createInfo.poolSizeCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->poolSizes[i], & pSource->pPoolSizes[i] );
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorPoolCreateInfo              * pDestination,
            Type ( DescriptorPoolCreateInfo ) const * pSource
    ) noexcept -> VkDescriptorPoolCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                .pNext          = nullptr,
                .flags          = pSource->flags,
                .maxSets        = pSource->maxSets,
                .poolSizeCount  = pSource->poolSizeCount,
                .pPoolSizes     = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorPoolSize              * pDestination,
            Type ( DescriptorPoolSize ) const * pSource
    ) noexcept -> VkDescriptorPoolSize * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .type               = static_cast < VkDescriptorType > ( pSource->type ),
                .descriptorCount    = pSource->descriptorCount
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorPoolInlineUniformBlockCreateInfo_t            * pDestination,
            Type ( DescriptorPoolInlineUniformBlockCreateInfo ) const * pSource
    ) noexcept -> VkDescriptorPoolInlineUniformBlockCreateInfo_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                          = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO,
#else
                .sType                          = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT,
#endif
                .pNext                          = nullptr,
                .maxInlineUniformBlockBindings  = pSource->maxInlineUniformBlockBindings
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            AllocateDescriptorSetsContext              * pContext,
            Type ( DescriptorSetAllocateInfo )   const * pSource
    ) noexcept -> VkDescriptorSetAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > (
                prepareSubcontext (
                        reinterpret_cast < CommonContext * > ( pContext ),
                        & pContext->allocateInfo,
                        pSource
                )
        );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE

                case StructureTypeDescriptorSetVariableDescriptorCountAllocateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            prepareSubcontext (
                                    reinterpret_cast < CommonContext * > ( pContext ),
                                    & pContext->variableDescriptorCount,
                                    reinterpret_cast < Type ( DescriptorSetVariableDescriptorCountAllocateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->allocateInfo.info;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareSubcontext (
            CommonContext                             * pRootContext,
            DescriptorSetAllocateInfoSubcontext       * pSubcontext,
            Type ( DescriptorSetAllocateInfo )  const * pSource
    ) noexcept -> VkDescriptorSetAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pSubcontext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pSubcontext->info, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto prepareSubcontext (
            CommonContext                                                    * pRootContext,
            DescriptorSetVariableDescriptorCountAllocateInfoSubcontext       * pSubcontext,
            Type ( DescriptorSetVariableDescriptorCountAllocateInfo )  const * pSource
    ) noexcept -> VkDescriptorSetVariableDescriptorCountAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pSubcontext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pSubcontext->info, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorSetAllocateInfo              * pDestination,
            Type ( DescriptorSetAllocateInfo ) const * pSource
    ) noexcept -> VkDescriptorSetAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                .pNext              = nullptr,
                .descriptorPool     = pSource->descriptorPool,
                .descriptorSetCount = pSource->descriptorSetCount,
                .pSetLayouts        = pSource->pSetLayouts
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorSetVariableDescriptorCountAllocateInfo              * pDestination,
            Type ( DescriptorSetVariableDescriptorCountAllocateInfo ) const * pSource
    ) noexcept -> VkDescriptorSetVariableDescriptorCountAllocateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO,
                .pNext              = nullptr,
                .descriptorSetCount = pSource->descriptorSetCount,
                .pDescriptorCounts  = pSource->pDescriptorCounts
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            UpdateDescriptorSetsContext       * pContext,
            cds :: uint32                       count,
            Type ( WriteDescriptorSet ) const * pSets
    ) noexcept -> VkWriteDescriptorSet * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: updateWriteDescriptorCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: updateWriteDescriptorCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: updateWriteDescriptorCount,
                    count
            ))

            count = engine :: vulkan :: config :: updateWriteDescriptorCount;
        }

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            pContext->writeSubcontexts[i].pWrite = & pContext->writeInfos[i];

            (void) prepareSubcontext (
                    reinterpret_cast < CommonContext * > ( pContext ),
                    & pContext->writeSubcontexts[i],
                    & pSets[i]
            );
        }

        return & pContext->writeInfos[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            UpdateDescriptorSetsContext      * pContext,
            cds :: uint32                      count,
            Type ( CopyDescriptorSet ) const * pSets
    ) noexcept -> VkCopyDescriptorSet * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: updateCopyDescriptorCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: updateCopyDescriptorCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: updateCopyDescriptorCount,
                    count
            ))

            count = engine :: vulkan :: config :: updateCopyDescriptorCount;
        }

        for ( cds :: uint32 i = 0U; i < count; ++ i ) {
            pContext->copySubcontexts[i].pCopy = & pContext->copyInfos[i];

            (void) prepareSubcontext (
                    reinterpret_cast < CommonContext * > ( pContext ),
                    & pContext->copySubcontexts[i],
                    & pSets[i]
            );
        }

        return & pContext->copyInfos[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareSubcontext (
            CommonContext                         * pRootContext,
            WriteDescriptorSetSubcontext          * pContext,
            Type ( WriteDescriptorSet )     const * pSource
    ) noexcept -> VkWriteDescriptorSet * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

        if ( pContext->pWrite == nullptr ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pRootContext, ResultErrorIllegalArgument, String :: f (
                    "Subcontext 'WriteDescriptorSetSubcontext' contains null pWrite"
            ))
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( pContext->pWrite, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE

                case StructureTypeWriteDescriptorSetAccelerationStructure:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            prepareSubcontext (
                                    pRootContext,
                                    & pContext->writeAccelerationStructure,
                                    reinterpret_cast < Type ( WriteDescriptorSetAccelerationStructure ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE

                case StructureTypeWriteDescriptorSetAccelerationStructureNVidia:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            prepareSubcontext (
                                    pRootContext,
                                    & pContext->writeAccelerationStructureNVidia,
                                    reinterpret_cast < Type ( WriteDescriptorSetAccelerationStructureNVidia ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE

                case StructureTypeWriteDescriptorSetInlineUniformBlock:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            prepareSubcontext (
                                    pRootContext,
                                    & pContext->writeInlineUniformBlock,
                                    reinterpret_cast < Type ( WriteDescriptorSetInlineUniformBlock ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrent    = pCurrent->pNext;
            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
        }

        pCurrentVk->pNext = nullptr;

        if ( pSource->pImageInfo != nullptr ) {
            pContext->pWrite->pImageInfo = toVulkanFormat (
                    & pContext->imageInfo,
                    pSource->pImageInfo
            );
        }

        if ( pSource->pBufferInfo != nullptr ) {
            pContext->pWrite->pBufferInfo = toVulkanFormat (
                    & pContext->bufferInfo,
                    pSource->pBufferInfo
            );
        }

        return pContext->pWrite;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareSubcontext (
            CommonContext                        * pRootContext,
            CopyDescriptorSetSubcontext          * pContext,
            Type ( CopyDescriptorSet )     const * pSource
    ) noexcept -> VkCopyDescriptorSet * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

        if ( pContext->pCopy == nullptr ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pRootContext, ResultErrorIllegalArgument, String :: f (
                    "Subcontext 'CopyDescriptorSetSubcontext' contains null pCopy"
            ))
        }

#endif

        return toVulkanFormat ( pContext->pCopy, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkWriteDescriptorSet              * pDestination,
            Type ( WriteDescriptorSet ) const * pSource
    ) noexcept -> VkWriteDescriptorSet * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .pNext              = nullptr,
                .dstSet             = pSource->destinationSet,
                .dstBinding         = pSource->destinationBinding,
                .dstArrayElement    = pSource->destinationArrayElement,
                .descriptorCount    = pSource->descriptorCount,
                .descriptorType     = static_cast < VkDescriptorType > ( pSource->descriptorType ),
                .pImageInfo         = nullptr,
                .pBufferInfo        = nullptr,
                .pTexelBufferView   = pSource->pTexelBufferView
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    extern auto prepareSubcontext (
            CommonContext                                              *,
            WriteDescriptorSetAccelerationStructureSubcontext          * pContext,
            Type ( WriteDescriptorSetAccelerationStructure )     const * pSource
    ) noexcept -> VkWriteDescriptorSetAccelerationStructureKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->accelerationStructure, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    extern auto prepareSubcontext (
            CommonContext                                                    *,
            WriteDescriptorSetAccelerationStructureSubcontextNVidia          * pContext,
            Type ( WriteDescriptorSetAccelerationStructureNVidia )     const * pSource
    ) noexcept -> VkWriteDescriptorSetAccelerationStructureNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->accelerationStructure, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
    extern auto prepareSubcontext (
            CommonContext                                           *,
            WriteDescriptorSetInlineUniformBlockSubcontext          * pContext,
            Type ( WriteDescriptorSetInlineUniformBlock )     const * pSource
    ) noexcept -> VkWriteDescriptorSetInlineUniformBlock_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->inlineUniformBlock, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorImageInfo              * pDestination,
            Type ( DescriptorImageInfo ) const * pSource
    ) noexcept -> VkDescriptorImageInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sampler        = pSource->sampler,
                .imageView      = pSource->imageView,
                .imageLayout    = static_cast < VkImageLayout > ( pSource->imageLayout )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorBufferInfo              * pDestination,
            Type ( DescriptorBufferInfo ) const * pSource
    ) noexcept -> VkDescriptorBufferInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .buffer = pSource->buffer,
                .offset = pSource->offset,
                .range  = pSource->range
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkCopyDescriptorSet              * pDestination,
            Type ( CopyDescriptorSet ) const * pSource
    ) noexcept -> VkCopyDescriptorSet * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET,
                .pNext              = nullptr,
                .srcSet             = pSource->sourceSet,
                .srcBinding         = pSource->sourceBinding,
                .srcArrayElement    = pSource->sourceArrayElement,
                .dstSet             = pSource->destinationSet,
                .dstBinding         = pSource->destinationBinding,
                .dstArrayElement    = pSource->destinationArrayElement,
                .descriptorCount    = pSource->descriptorCount
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_ACCELERATION_STRUCTURE_AVAILABLE
    auto toVulkanFormat (
            VkWriteDescriptorSetAccelerationStructureKHR           * pDestination,
            Type ( WriteDescriptorSetAccelerationStructure ) const * pSource
    ) noexcept -> VkWriteDescriptorSetAccelerationStructureKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR,
                .pNext                      = nullptr,
                .accelerationStructureCount = pSource->accelerationStructureCount,
                .pAccelerationStructures    = pSource->pAccelerationStructures
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_NVIDIA_RAY_TRACING_AVAILABLE
    auto toVulkanFormat (
            VkWriteDescriptorSetAccelerationStructureNV                  * pDestination,
            Type ( WriteDescriptorSetAccelerationStructureNVidia ) const * pSource
    ) noexcept -> VkWriteDescriptorSetAccelerationStructureNV * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV,
                .pNext                      = nullptr,
                .accelerationStructureCount = pSource->accelerationStructureCount,
                .pAccelerationStructures    = pSource->pAccelerationStructures
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_INLINE_UNIFORM_BLOCK_AVAILABLE
    auto toVulkanFormat (
            VkWriteDescriptorSetInlineUniformBlock_t            * pDestination,
            Type ( WriteDescriptorSetInlineUniformBlock ) const * pSource
    ) noexcept -> VkWriteDescriptorSetInlineUniformBlock_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType                      = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK,
#else
                .sType                      = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT,
#endif
                .pNext                      = nullptr,
                .dataSize                   = pSource->dataSize,
                .pData                      = pSource->pData
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto prepareContext (
            CreateDescriptorUpdateTemplateContext             * pContext,
            Type ( DescriptorUpdateTemplateCreateInfo ) const * pSource
    ) noexcept -> VkDescriptorUpdateTemplateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->createInfo, pSource );

        pContext->createInfo.pDescriptorUpdateEntries = & pContext->entries[0];

        if ( pContext->createInfo.descriptorUpdateEntryCount > engine :: vulkan :: config :: descriptorUpdateTemplateEntryCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: descriptorUpdateTemplateEntryCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: descriptorUpdateTemplateEntryCount,
                    pContext->createInfo.descriptorUpdateEntryCount
            ))

            pContext->createInfo.descriptorUpdateEntryCount = engine :: vulkan :: config :: descriptorUpdateTemplateEntryCount;
        }

        for ( uint32 i = 0U; i < pContext->createInfo.descriptorUpdateEntryCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->entries[i], & pSource->pDescriptorUpdateEntries[i] );
        }

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorUpdateTemplateCreateInfo              * pDestination,
            Type ( DescriptorUpdateTemplateCreateInfo ) const * pSource
    ) noexcept -> VkDescriptorUpdateTemplateCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                      = VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO,
                .pNext                      = nullptr,
                .flags                      = pSource->flags,
                .descriptorUpdateEntryCount = pSource->descriptorUpdateEntryCount,
                .pDescriptorUpdateEntries   = nullptr,
                .templateType               = static_cast < VkDescriptorUpdateTemplateType > ( pSource->templateType ),
                .descriptorSetLayout        = pSource->descriptorSetLayout,
                .pipelineBindPoint          = static_cast < VkPipelineBindPoint > ( pSource->pipelineBindPoint ),
                .pipelineLayout             = pSource->pipelineLayout,
                .set                        = pSource->set
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_1_AVAILABLE
    auto toVulkanFormat (
            VkDescriptorUpdateTemplateEntry              * pDestination,
            Type ( DescriptorUpdateTemplateEntry ) const * pSource
    ) noexcept -> VkDescriptorUpdateTemplateEntry * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .dstBinding         = pSource->destinationBinding,
                .dstArrayElement    = pSource->destinationArrayElement,
                .descriptorCount    = pSource->descriptorCount,
                .descriptorType     = static_cast < VkDescriptorType > ( pSource->descriptorType ),
                .offset             = pSource->offset,
                .stride             = pSource->stride
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto prepareContext (
            GetDeviceBufferAddressContext          * pContext,
            Type ( BufferDeviceAddressInfo ) const * pSource
    ) noexcept -> VkBufferDeviceAddressInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return toVulkanFormat ( & pContext->info, pSource );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_2_AVAILABLE
    auto toVulkanFormat (
            VkBufferDeviceAddressInfo              * pDestination,
            Type ( BufferDeviceAddressInfo ) const * pSource
    ) noexcept -> VkBufferDeviceAddressInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType  = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
                .pNext  = nullptr,
                .buffer = pSource->buffer
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CreateQueryPoolContext             * pContext,
            Type ( QueryPoolCreateInfo ) const * pSource
    ) noexcept -> VkQueryPoolCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
        auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->createInfo, pSource ) );

        while ( pCurrent != nullptr ) {

            switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE

                case StructureTypeQueryPoolPerformanceCreateInfo:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->performanceQueryCreateInfo,
                                    reinterpret_cast < Type ( QueryPoolPerformanceCreateInfo ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE

                case StructureTypeQueryPoolPerformanceCreateInfoIntel:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->performanceQueryCreateInfoIntel,
                                    reinterpret_cast < Type ( QueryPoolPerformanceCreateInfoIntel ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H264_AVAILABLE

                case StructureTypeVideoDecodeH264Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->decodeH264Profile,
                                    reinterpret_cast < Type ( VideoDecodeH264Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_DECODE_H265_AVAILABLE

                case StructureTypeVideoDecodeH265Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->decodeH265Profile,
                                    reinterpret_cast < Type ( VideoDecodeH265Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H264_AVAILABLE

                case StructureTypeVideoEncodeH264Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->encodeH264Profile,
                                    reinterpret_cast < Type ( VideoEncodeH264Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_VIDEO_ENCODE_H265_AVAILABLE

                case StructureTypeVideoEncodeH265Profile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->encodeH265Profile,
                                    reinterpret_cast < Type ( VideoEncodeH265Profile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_VIDEO_QUEUE_AVAILABLE

                case StructureTypeVideoProfile:
                    pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                            toVulkanFormat (
                                    & pContext->videoProfile,
                                    reinterpret_cast < Type ( VideoProfile ) const * > ( pCurrent )
                            )
                    );
                    break;

#endif

                default:
                    break;
            }

            pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
            pCurrent    = pCurrent->pNext;
        }

        pCurrentVk->pNext = nullptr;

        return & pContext->createInfo;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkQueryPoolCreateInfo              * pDestination,
            Type ( QueryPoolCreateInfo ) const * pSource
    ) noexcept -> VkQueryPoolCreateInfo * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
                .pNext              = nullptr,
                .flags              = pSource->flags,
                .queryType          = static_cast < VkQueryType > ( pSource->queryType ),
                .queryCount         = pSource->queryCount,
                .pipelineStatistics = pSource->pipelineStatistics
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkQueryPoolPerformanceCreateInfoKHR           * pDestination,
            Type ( QueryPoolPerformanceCreateInfo ) const * pSource
    ) noexcept -> VkQueryPoolPerformanceCreateInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType              = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_CREATE_INFO_KHR,
                .pNext              = nullptr,
                .queueFamilyIndex   = pSource->queueFamilyIndex,
                .counterIndexCount  = pSource->counterIndexCount,
                .pCounterIndices    = pSource->pCounterIndices
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkQueryPoolPerformanceQueryCreateInfoINTEL         * pDestination,
            Type ( QueryPoolPerformanceCreateInfoIntel ) const * pSource
    ) noexcept -> VkQueryPoolPerformanceQueryCreateInfoINTEL * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL,
                .pNext                          = nullptr,
                .performanceCountersSampling    = static_cast < VkQueryPoolSamplingModeINTEL > ( pSource->performanceCountersSampling )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_KHRONOS_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkAcquireProfilingLockInfoKHR           * pDestination,
            Type ( AcquireProfilingLockInfo ) const * pSource
    ) noexcept -> VkAcquireProfilingLockInfoKHR * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_ACQUIRE_PROFILING_LOCK_INFO_KHR,
                .pNext                          = nullptr,
                .flags                          = pSource->flags,
                .timeout                        = pSource->timeout
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkInitializePerformanceApiInfoINTEL              * pDestination,
            Type ( InitializePerformanceAPIInfoIntel ) const * pSource
    ) noexcept -> VkInitializePerformanceApiInfoINTEL * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL,
                .pNext                          = nullptr,
                .pUserData                      = pSource->pUserData
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkPerformanceMarkerInfoINTEL              * pDestination,
            Type ( PerformanceMarkerInfoIntel ) const * pSource
    ) noexcept -> VkPerformanceMarkerInfoINTEL * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL,
                .pNext                          = nullptr,
                .marker                         = pSource->marker
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkPerformanceStreamMarkerInfoINTEL              * pDestination,
            Type ( PerformanceStreamMarkerInfoIntel ) const * pSource
    ) noexcept -> VkPerformanceStreamMarkerInfoINTEL * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL,
                .pNext                          = nullptr,
                .marker                         = pSource->marker
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkPerformanceOverrideInfoINTEL              * pDestination,
            Type ( PerformanceOverrideInfoIntel ) const * pSource
    ) noexcept -> VkPerformanceOverrideInfoINTEL * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL,
                .pNext                          = nullptr,
                .type                           = static_cast < VkPerformanceOverrideTypeINTEL > ( pSource->type ),
                .enable                         = pSource->enable,
                .parameter                      = pSource->parameter
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_INTEL_PERFORMANCE_QUERY_AVAILABLE
    auto toVulkanFormat (
            VkPerformanceConfigurationAcquireInfoINTEL              * pDestination,
            Type ( PerformanceConfigurationAcquireInfoIntel ) const * pSource
    ) noexcept -> VkPerformanceConfigurationAcquireInfoINTEL * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType                          = VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL,
                .pNext                          = nullptr,
                .type                           = static_cast < VkPerformanceConfigurationTypeINTEL > ( pSource->type ),
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            ClearColorImageContext         * pContext,
            Type ( ClearColorValue ) const * pSource
    ) noexcept -> VkClearColorValue * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) std :: memcpy ( & pContext->color, pSource, sizeof ( VkClearColorValue ) );

        return & pContext->color;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            ClearColorImageContext                * pContext,
            uint32                                  count,
            Type ( ImageSubresourceRange )  const * pSource
    ) noexcept -> VkImageSubresourceRange * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: clearImageSubresourceRangeCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: clearImageSubresourceRangeCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: clearImageSubresourceRangeCount,
                    count
            ))

            count = engine :: vulkan :: config :: clearImageSubresourceRangeCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            pContext->ranges[i] = {
                    .aspectMask     = pSource->aspectMask,
                    .baseMipLevel   = pSource->baseMipLevel,
                    .levelCount     = pSource->levelCount,
                    .baseArrayLayer = pSource->baseArrayLayer,
                    .layerCount     = pSource->layerCount
            };
        }

        return & pContext->ranges[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            ClearDepthStencilImageContext         * pContext,
            Type ( ClearDepthStencilValue ) const * pSource
    ) noexcept -> VkClearDepthStencilValue * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pContext->depthStencil = {
                .depth      = pSource->depth,
                .stencil    = pSource->stencil
        };

        return & pContext->depthStencil;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            ClearDepthStencilImageContext         * pContext,
            uint32                                  count,
            Type ( ImageSubresourceRange )  const * pSource
    ) noexcept -> VkImageSubresourceRange * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: clearImageSubresourceRangeCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: clearImageSubresourceRangeCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: clearImageSubresourceRangeCount,
                    count
            ))

            count = engine :: vulkan :: config :: clearImageSubresourceRangeCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            pContext->ranges[i] = {
                    .aspectMask     = pSource->aspectMask,
                    .baseMipLevel   = pSource->baseMipLevel,
                    .levelCount     = pSource->levelCount,
                    .baseArrayLayer = pSource->baseArrayLayer,
                    .layerCount     = pSource->layerCount
            };
        }

        return & pContext->ranges[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            ClearAttachmentsContext         * pContext,
            uint32                            count,
            Type ( ClearAttachment )  const * pSource
    ) noexcept -> VkClearAttachment * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: clearAttachmentCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: clearAttachmentCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: clearAttachmentCount,
                    count
            ))

            count = engine :: vulkan :: config :: clearAttachmentCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->attachments[i], & pSource[i] );
        }

        return & pContext->attachments[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            ClearAttachmentsContext         * pContext,
            uint32                            count,
            Type ( ClearRect )        const * pSource
    ) noexcept -> VkClearRect * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: clearRectCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: clearRectCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: clearRectCount,
                    count
            ))

            count = engine :: vulkan :: config :: clearRectCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->rects[i], & pSource[i] );
        }

        return & pContext->rects[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkClearAttachment              * pDestination,
            Type ( ClearAttachment ) const * pSource
    ) noexcept -> VkClearAttachment * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        pDestination->aspectMask        = pSource->aspectMask;
        pDestination->colorAttachment   = pSource->colorAttachment;
        (void) std :: memcpy ( & pDestination->clearValue, & pSource->clearValue, sizeof ( VkClearValue ) );

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkClearRect              * pDestination,
            Type ( ClearRect ) const * pSource
    ) noexcept -> VkClearRect * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .rect           = {
                        .offset         = {
                                .x              = pSource->rect.offset.x,
                                .y              = pSource->rect.offset.y
                        },
                        .extent         = {
                                .width          = pSource->rect.extent.width,
                                .height         = pSource->rect.extent.height,
                        }
                },
                .baseArrayLayer = pSource->baseArrayLayer,
                .layerCount     = pSource->layerCount
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CopyBufferContext               * pContext,
            uint32                            count,
            Type ( BufferCopy )       const * pSource
    ) noexcept -> VkBufferCopy * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: bufferCopyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: bufferCopyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: bufferCopyCount,
                    count
            ))

            count = engine :: vulkan :: config :: bufferCopyCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->copies[i], & pSource[i] );
        }

        return & pContext->copies[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkBufferCopy              * pDestination,
            Type ( BufferCopy ) const * pSource
    ) noexcept -> VkBufferCopy * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .srcOffset  = pSource->sourceOffset,
                .dstOffset  = pSource->destinationOffset,
                .size       = pSource->size
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareContext (
            CopyBuffer2Context               * pContext,
            Type ( CopyBufferInfo2 )   const * pSource
    ) noexcept -> VkCopyBufferInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return prepareSubcontext (
                reinterpret_cast < CommonContext * > ( pContext ),
                & pContext->info,
                pSource
        );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareSubcontext (
            CommonContext                   * pRootContext,
            CopyBufferInfo2Subcontext       * pContext,
            Type ( CopyBufferInfo2 )  const * pSource
    ) noexcept -> VkCopyBufferInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->info, pSource );

        pContext->info.pRegions = & pContext->copies[0];

        if ( pContext->info.regionCount > engine :: vulkan :: config :: bufferCopyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pRootContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: bufferCopyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: bufferCopyCount,
                    pContext->info.regionCount
            ))

            pContext->info.regionCount = engine :: vulkan :: config :: bufferCopyCount;
        }

        for ( uint32 i = 0U; i < pContext->info.regionCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->copies[i], & pSource->pRegions[i] );
        }

        return & pContext->info;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkBufferCopy2_t            * pDestination,
            Type ( BufferCopy2 ) const * pSource
    ) noexcept -> VkBufferCopy2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType      = VK_STRUCTURE_TYPE_BUFFER_COPY_2,
#else
                .sType      = VK_STRUCTURE_TYPE_BUFFER_COPY_2_KHR,
#endif
                .pNext      = nullptr,
                .srcOffset  = pSource->sourceOffset,
                .dstOffset  = pSource->destinationOffset,
                .size       = pSource->size
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkCopyBufferInfo2_t              * pDestination,
            Type ( CopyBufferInfo2 )   const * pSource
    ) noexcept -> VkCopyBufferInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType          = VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2,
#else
                .sType          = VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2_KHR,
#endif
                .pNext          = nullptr,
                .srcBuffer      = pSource->sourceBuffer,
                .dstBuffer      = pSource->destinationBuffer,
                .regionCount    = pSource->regionCount,
                .pRegions       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CopyImageContext                * pContext,
            uint32                            count,
            Type ( ImageCopy )        const * pSource
    ) noexcept -> VkImageCopy * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: imageCopyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: imageCopyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: imageCopyCount,
                    count
            ))

            count = engine :: vulkan :: config :: imageCopyCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->copies[i], & pSource[i] );
        }

        return & pContext->copies[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkImageCopy              * pDestination,
            Type ( ImageCopy ) const * pSource
    ) noexcept -> VkImageCopy * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .srcSubresource = {
                        .aspectMask     = pSource->sourceSubresource.aspectMask,
                        .mipLevel       = pSource->sourceSubresource.mipLevel,
                        .baseArrayLayer = pSource->sourceSubresource.baseArrayLayer,
                        .layerCount     = pSource->sourceSubresource.layerCount
                },
                .srcOffset      = {
                        .x              = pSource->sourceOffset.x,
                        .y              = pSource->sourceOffset.y,
                        .z              = pSource->sourceOffset.z
                },
                .dstSubresource = {
                        .aspectMask     = pSource->destinationSubresource.aspectMask,
                        .mipLevel       = pSource->destinationSubresource.mipLevel,
                        .baseArrayLayer = pSource->destinationSubresource.baseArrayLayer,
                        .layerCount     = pSource->destinationSubresource.layerCount
                },
                .dstOffset      = {
                    .x                  = pSource->destinationOffset.x,
                    .y                  = pSource->destinationOffset.y,
                    .z                  = pSource->destinationOffset.z
                },
                .extent         = {
                        .width          = pSource->extent.width,
                        .height         = pSource->extent.height,
                        .depth          = pSource->extent.depth
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareContext (
            CopyImage2Context               * pContext,
            Type ( CopyImageInfo2 )   const * pSource
    ) noexcept -> VkCopyImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return prepareSubcontext (
                reinterpret_cast < CommonContext * > ( pContext ),
                & pContext->info,
                pSource
        );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareSubcontext (
            CommonContext                  * pRootContext,
            CopyImageInfo2Subcontext       * pContext,
            Type ( CopyImageInfo2 )  const * pSource
    ) noexcept -> VkCopyImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->info, pSource );

        pContext->info.pRegions = & pContext->copies[0];

        if ( pContext->info.regionCount > engine :: vulkan :: config :: imageCopyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pRootContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: imageCopyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: imageCopyCount,
                    pContext->info.regionCount
            ))

            pContext->info.regionCount = engine :: vulkan :: config :: imageCopyCount;
        }

        for ( uint32 i = 0U; i < pContext->info.regionCount; ++ i ) {
            (void) toVulkanFormat ( & pContext->copies[i], & pSource->pRegions[i] );
        }

        return & pContext->info;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkImageCopy2_t            * pDestination,
            Type ( ImageCopy2 ) const * pSource
    ) noexcept -> VkImageCopy2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType          = VK_STRUCTURE_TYPE_IMAGE_COPY_2,
#else
                .sType          = VK_STRUCTURE_TYPE_IMAGE_COPY_2_KHR,
#endif
                .pNext          = nullptr,
                .srcSubresource = {
                        .aspectMask     = pSource->sourceSubresource.aspectMask,
                        .mipLevel       = pSource->sourceSubresource.mipLevel,
                        .baseArrayLayer = pSource->sourceSubresource.baseArrayLayer,
                        .layerCount     = pSource->sourceSubresource.layerCount
                },
                .srcOffset      = {
                        .x              = pSource->sourceOffset.x,
                        .y              = pSource->sourceOffset.y,
                        .z              = pSource->sourceOffset.z
                },
                .dstSubresource = {
                        .aspectMask     = pSource->destinationSubresource.aspectMask,
                        .mipLevel       = pSource->destinationSubresource.mipLevel,
                        .baseArrayLayer = pSource->destinationSubresource.baseArrayLayer,
                        .layerCount     = pSource->destinationSubresource.layerCount
                },
                .dstOffset      = {
                        .x              = pSource->destinationOffset.x,
                        .y              = pSource->destinationOffset.y,
                        .z              = pSource->destinationOffset.z
                },
                .extent         = {
                        .width          = pSource->extent.width,
                        .height         = pSource->extent.height,
                        .depth          = pSource->extent.depth
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkCopyImageInfo2_t              * pDestination,
            Type ( CopyImageInfo2 )   const * pSource
    ) noexcept -> VkCopyImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType          = VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2,
#else
                .sType          = VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2_KHR,
#endif
                .pNext          = nullptr,
                .srcImage       = pSource->sourceImage,
                .srcImageLayout = static_cast < VkImageLayout > ( pSource->sourceImageLayout ),
                .dstImage       = pSource->destinationImage,
                .dstImageLayout = static_cast < VkImageLayout > ( pSource->destinationImageLayout ),
                .regionCount    = pSource->regionCount,
                .pRegions       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            CopyBufferToImageOrImageToBufferContext   * pContext,
            uint32                                      count,
            Type ( BufferImageCopy )            const * pSource
    ) noexcept -> VkBufferImageCopy * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: bufferImageCopyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: bufferImageCopyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: bufferImageCopyCount,
                    count
            ))

            count = engine :: vulkan :: config :: bufferImageCopyCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->copies[i], & pSource[i] );
        }

        return & pContext->copies[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkBufferImageCopy              * pDestination,
            Type ( BufferImageCopy ) const * pSource
    ) noexcept -> VkBufferImageCopy * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .bufferOffset       = pSource->bufferOffset,
                .bufferRowLength    = pSource->bufferRowLength,
                .bufferImageHeight  = pSource->bufferImageHeight,
                .imageSubresource   = {
                        .aspectMask         = pSource->imageSubresource.aspectMask,
                        .mipLevel           = pSource->imageSubresource.mipLevel,
                        .baseArrayLayer     = pSource->imageSubresource.baseArrayLayer,
                        .layerCount         = pSource->imageSubresource.layerCount
                },
                .imageOffset        = {
                        .x                  = pSource->imageOffset.x,
                        .y                  = pSource->imageOffset.y,
                        .z                  = pSource->imageOffset.z
                },
                .imageExtent        = {
                        .width              = pSource->imageExtent.width,
                        .height             = pSource->imageExtent.height,
                        .depth              = pSource->imageExtent.depth
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareContext (
            CopyBufferToImageOrImageToBuffer2Context              * pContext,
            Type ( CopyBufferToImageInfo2 )                 const * pSource
    ) noexcept -> VkCopyBufferToImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return prepareSubcontext (
                reinterpret_cast < CommonContext * > ( pContext ),
                & pContext->info,
                pSource
        );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareContext (
            CopyBufferToImageOrImageToBuffer2Context              * pContext,
            Type ( CopyImageToBufferInfo2 )                 const * pSource
    ) noexcept -> VkCopyImageToBufferInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return prepareSubcontext (
                reinterpret_cast < CommonContext * > ( pContext ),
                & pContext->info,
                pSource
        );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareSubcontext (
            CommonContext                                     * pRootContext,
            CopyBufferToImageOrImageToBuffer2Subcontext       * pContext,
            Type ( CopyBufferToImageInfo2 )             const * pSource
    ) noexcept -> VkCopyBufferToImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->bufferToImage, pSource );

        pContext->bufferToImage.pRegions = & pContext->copies[0];

        if ( pContext->bufferToImage.regionCount > engine :: vulkan :: config :: bufferImageCopyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pRootContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: bufferImageCopyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: bufferImageCopyCount,
                    pContext->bufferToImage.regionCount
            ))

            pContext->bufferToImage.regionCount = engine :: vulkan :: config :: bufferImageCopyCount;
        }

        for ( uint32 i = 0U; i < pContext->bufferToImage.regionCount; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->copies[i], & pSource->pRegions[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE

                    case StructureTypeCopyCommandTransformInfoQualcomm:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->copyCommandsTransforms[i],
                                        reinterpret_cast < Type ( CopyCommandTransformInfoQualcomm ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        return & pContext->bufferToImage;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareSubcontext (
            CommonContext                                     * pRootContext,
            CopyBufferToImageOrImageToBuffer2Subcontext       * pContext,
            Type ( CopyImageToBufferInfo2 )             const * pSource
    ) noexcept -> VkCopyImageToBufferInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->imageToBuffer, pSource );

        pContext->imageToBuffer.pRegions = & pContext->copies[0];

        if ( pContext->imageToBuffer.regionCount > engine :: vulkan :: config :: bufferImageCopyCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pRootContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: bufferImageCopyCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: bufferImageCopyCount,
                    pContext->imageToBuffer.regionCount
            ))

            pContext->imageToBuffer.regionCount = engine :: vulkan :: config :: bufferImageCopyCount;
        }

        for ( uint32 i = 0U; i < pContext->imageToBuffer.regionCount; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->copies[i], & pSource->pRegions[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE

                    case StructureTypeCopyCommandTransformInfoQualcomm:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->copyCommandsTransforms[i],
                                        reinterpret_cast < Type ( CopyCommandTransformInfoQualcomm ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        return & pContext->imageToBuffer;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkBufferImageCopy2_t            * pDestination,
            Type ( BufferImageCopy2 ) const * pSource
    ) noexcept -> VkBufferImageCopy2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType              = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2,
#else
                .sType              = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2_KHR,
#endif
                .pNext              = nullptr,
                .bufferOffset       = pSource->bufferOffset,
                .bufferRowLength    = pSource->bufferRowLength,
                .bufferImageHeight  = pSource->bufferImageHeight,
                .imageSubresource   = {
                        .aspectMask         = pSource->imageSubresource.aspectMask,
                        .mipLevel           = pSource->imageSubresource.mipLevel,
                        .baseArrayLayer     = pSource->imageSubresource.baseArrayLayer,
                        .layerCount         = pSource->imageSubresource.layerCount
                },
                .imageOffset        = {
                        .x                  = pSource->imageOffset.x,
                        .y                  = pSource->imageOffset.y,
                        .z                  = pSource->imageOffset.z
                },
                .imageExtent        = {
                        .width              = pSource->imageExtent.width,
                        .height             = pSource->imageExtent.height,
                        .depth              = pSource->imageExtent.depth
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkCopyBufferToImageInfo2_t              * pDestination,
            Type ( CopyBufferToImageInfo2 )   const * pSource
    ) noexcept -> VkCopyBufferToImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType          = VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2,
#else
                .sType          = VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2_KHR,
#endif
                .pNext          = nullptr,
                .srcBuffer      = pSource->sourceBuffer,
                .dstImage       = pSource->destinationImage,
                .dstImageLayout = static_cast < VkImageLayout > ( pSource->destinationImageLayout ),
                .regionCount    = pSource->regionCount,
                .pRegions       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkCopyImageToBufferInfo2_t              * pDestination,
            Type ( CopyImageToBufferInfo2 )   const * pSource
    ) noexcept -> VkCopyImageToBufferInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType          = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2,
#else
                .sType          = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2_KHR,
#endif
                .pNext          = nullptr,
                .srcImage       = pSource->sourceImage,
                .srcImageLayout = static_cast < VkImageLayout > ( pSource->sourceImageLayout ),
                .dstBuffer      = pSource->destinationBuffer,
                .regionCount    = pSource->regionCount,
                .pRegions       = nullptr
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkCopyCommandTransformInfoQCOM              * pDestination,
            Type ( CopyCommandTransformInfoQualcomm )   const * pSource
    ) noexcept -> VkCopyCommandTransformInfoQCOM * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .sType          = VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM,
                .pNext          = nullptr,
                .transform      = static_cast < VkSurfaceTransformFlagBitsKHR > ( pSource->transform )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            BlitImageContext                * pContext,
            uint32                            count,
            Type ( ImageBlit )        const * pSource
    ) noexcept -> VkImageBlit * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: imageBlitCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: imageBlitCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: imageBlitCount,
                    count
            ))

            count = engine :: vulkan :: config :: imageBlitCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->blits[i], & pSource[i] );
        }

        return & pContext->blits[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkImageBlit              * pDestination,
            Type ( ImageBlit ) const * pSource
    ) noexcept -> VkImageBlit * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .srcSubresource = {
                        .aspectMask     = pSource->sourceSubresource.aspectMask,
                        .mipLevel       = pSource->sourceSubresource.mipLevel,
                        .baseArrayLayer = pSource->sourceSubresource.baseArrayLayer,
                        .layerCount     = pSource->sourceSubresource.layerCount
                },
                .srcOffsets     = {
                        {
                               .x              = pSource->sourceOffsets[0].x,
                               .y              = pSource->sourceOffsets[0].y,
                               .z              = pSource->sourceOffsets[0].z
                        },
                        {
                               .x              = pSource->sourceOffsets[1].x,
                               .y              = pSource->sourceOffsets[1].y,
                               .z              = pSource->sourceOffsets[1].z
                        }
                },
                .dstSubresource = {
                        .aspectMask     = pSource->destinationSubresource.aspectMask,
                        .mipLevel       = pSource->destinationSubresource.mipLevel,
                        .baseArrayLayer = pSource->destinationSubresource.baseArrayLayer,
                        .layerCount     = pSource->destinationSubresource.layerCount
                },
                .dstOffsets     = {
                        {
                                .x              = pSource->destinationOffsets[0].x,
                                .y              = pSource->destinationOffsets[0].y,
                                .z              = pSource->destinationOffsets[0].z
                        },
                        {
                                .x              = pSource->destinationOffsets[1].x,
                                .y              = pSource->destinationOffsets[1].y,
                                .z              = pSource->destinationOffsets[1].z
                        }
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareContext (
            BlitImage2Context               * pContext,
            Type ( BlitImageInfo2 )   const * pSource
    ) noexcept -> VkBlitImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        return prepareSubcontext (
                reinterpret_cast < CommonContext * > ( pContext ),
                & pContext->info,
                pSource
        );
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto prepareSubcontext (
            CommonContext                  * pRootContext,
            BlitImageInfo2Subcontext       * pContext,
            Type ( BlitImageInfo2 )  const * pSource
    ) noexcept -> VkBlitImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pRootContext == nullptr || pContext == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        (void) toVulkanFormat ( & pContext->info, pSource );

        pContext->info.pRegions = & pContext->blits[0];

        if ( pContext->info.regionCount > engine :: vulkan :: config :: imageBlitCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pRootContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: imageBlitCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: imageBlitCount,
                    pContext->info.regionCount
            ))

            pContext->info.regionCount = engine :: vulkan :: config :: imageBlitCount;
        }

        for ( uint32 i = 0U; i < pContext->info.regionCount; ++ i ) {

            auto pCurrent   = reinterpret_cast < Type ( GenericInStructure ) const * > ( pSource->pNext );
            auto pCurrentVk = reinterpret_cast < VkBaseOutStructure * > ( toVulkanFormat ( & pContext->blits[i], & pSource->pRegions[i] ) );

            while ( pCurrent != nullptr ) {

                switch ( pCurrent->structureType ) {

#if __C_ENG_VULKAN_API_EXTENSION_QUALCOMM_ROTATED_COPY_COMMANDS_AVAILABLE

                    case StructureTypeCopyCommandTransformInfoQualcomm:
                        pCurrentVk->pNext = reinterpret_cast < VkBaseOutStructure * > (
                                toVulkanFormat (
                                        & pContext->copyCommandTransforms[i],
                                        reinterpret_cast < Type ( CopyCommandTransformInfoQualcomm ) const * > ( pCurrent )
                                )
                        );
                        break;

#endif

                    default:
                        break;
                }

                pCurrentVk  = pCurrentVk->pNext == nullptr ? pCurrentVk : pCurrentVk->pNext;
                pCurrent    = pCurrent->pNext;
            }

            pCurrentVk->pNext = nullptr;
        }

        return & pContext->info;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkImageBlit2_t            * pDestination,
            Type ( ImageBlit2 ) const * pSource
    ) noexcept -> VkImageBlit2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType          = VK_STRUCTURE_TYPE_IMAGE_BLIT_2,
#else
                .sType          = VK_STRUCTURE_TYPE_IMAGE_BLIT_2_KHR,
#endif
                .pNext          = nullptr,
                .srcSubresource = {
                        .aspectMask     = pSource->sourceSubresource.aspectMask,
                        .mipLevel       = pSource->sourceSubresource.mipLevel,
                        .baseArrayLayer = pSource->sourceSubresource.baseArrayLayer,
                        .layerCount     = pSource->sourceSubresource.layerCount
                },
                .srcOffsets     = {
                        {
                                .x              = pSource->sourceOffsets[0].x,
                                .y              = pSource->sourceOffsets[0].y,
                                .z              = pSource->sourceOffsets[0].z
                        },
                        {
                                .x              = pSource->sourceOffsets[1].x,
                                .y              = pSource->sourceOffsets[1].y,
                                .z              = pSource->sourceOffsets[1].z
                        }
                },
                .dstSubresource = {
                        .aspectMask     = pSource->destinationSubresource.aspectMask,
                        .mipLevel       = pSource->destinationSubresource.mipLevel,
                        .baseArrayLayer = pSource->destinationSubresource.baseArrayLayer,
                        .layerCount     = pSource->destinationSubresource.layerCount
                },
                .dstOffsets     = {
                        {
                                .x              = pSource->destinationOffsets[0].x,
                                .y              = pSource->destinationOffsets[0].y,
                                .z              = pSource->destinationOffsets[0].z
                        },
                        {
                                .x              = pSource->destinationOffsets[1].x,
                                .y              = pSource->destinationOffsets[1].y,
                                .z              = pSource->destinationOffsets[1].z
                        }
                }
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE || __C_ENG_VULKAN_API_EXTENSION_KHRONOS_COPY_COMMANDS_AVAILABLE
    auto toVulkanFormat (
            VkBlitImageInfo2_t              * pDestination,
            Type ( BlitImageInfo2 )   const * pSource
    ) noexcept -> VkBlitImageInfo2_t * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
#if __C_ENG_VULKAN_API_VERSION_1_3_AVAILABLE
                .sType          = VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2,
#else
                .sType          = VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2_KHR,
#endif
                .pNext          = nullptr,
                .srcImage       = pSource->sourceImage,
                .srcImageLayout = static_cast < VkImageLayout > ( pSource->sourceImageLayout ),
                .dstImage       = pSource->destinationImage,
                .dstImageLayout = static_cast < VkImageLayout > ( pSource->destinationImageLayout ),
                .regionCount    = pSource->regionCount,
                .pRegions       = nullptr,
                .filter         = static_cast < VkFilter > ( pSource->filter )
        };

        return pDestination;
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto prepareContext (
            ResolveImageContext                * pContext,
            uint32                               count,
            Type ( ImageResolve )        const * pSource
    ) noexcept -> VkImageResolve * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pContext == nullptr ) {
            return nullptr;
        }

#endif

        if ( count > engine :: vulkan :: config :: imageResolveCount ) {
            __C_ENG_DIAG_SET_CONTEXT_ERROR ( pContext, ResultErrorConfigurationArraySizeSmall, String :: f (
                    "config :: imageResolveCount = %d. Minimum Required = %d",
                    engine :: vulkan :: config :: imageResolveCount,
                    count
            ))

            count = engine :: vulkan :: config :: imageResolveCount;
        }

        for ( uint32 i = 0U; i < count; ++ i ) {
            (void) toVulkanFormat ( & pContext->resolves[i], & pSource[i] );
        }

        return & pContext->resolves[0];
    }
#endif

#if __C_ENG_VULKAN_API_VERSION_1_0_AVAILABLE
    auto toVulkanFormat (
            VkImageResolve              * pDestination,
            Type ( ImageResolve ) const * pSource
    ) noexcept -> VkImageResolve * {

#if __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

#endif

        * pDestination = {
                .srcSubresource = {
                        .aspectMask     = pSource->sourceSubresource.aspectMask,
                        .mipLevel       = pSource->sourceSubresource.mipLevel,
                        .baseArrayLayer = pSource->sourceSubresource.baseArrayLayer,
                        .layerCount     = pSource->sourceSubresource.layerCount
                },
                .srcOffset      = {
                        .x              = pSource->sourceOffset.x,
                        .y              = pSource->sourceOffset.y,
                        .z              = pSource->sourceOffset.z
                },
                .dstSubresource = {
                        .aspectMask     = pSource->destinationSubresource.aspectMask,
                        .mipLevel       = pSource->destinationSubresource.mipLevel,
                        .baseArrayLayer = pSource->destinationSubresource.baseArrayLayer,
                        .layerCount     = pSource->destinationSubresource.layerCount
                },
                .dstOffset      = {
                        .x              = pSource->destinationOffset.x,
                        .y              = pSource->destinationOffset.y,
                        .z              = pSource->destinationOffset.z
                },
                .extent         = {
                        .width          = pSource->extent.width,
                        .height         = pSource->extent.height,
                        .depth          = pSource->extent.depth
                }
        };

        return pDestination;
    }
#endif


} // namespace vulkan :: engine
