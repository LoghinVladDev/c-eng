//
// Created by loghin on 01.01.2022.
//

#ifndef __C_ENG_VULKAN_CORE_CONFIG_HPP__
#define __C_ENG_VULKAN_CORE_CONFIG_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#if __CLION_IDE__
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#endif


#define __C_ENG_VULKAN_CORE_CONTEXT_COUNT   16U /* NOLINT(bugprone-reserved-identifier) */


#define __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_ENABLE_MAX_COUNT     32U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_VALIDATION_FEATURE_DISABLE_MAX_COUNT    32U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_VALIDATION_CHECK_MAX_COUNT              16U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_LAYER_MAX_COUNT  64U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_LAYER_EXTENSION_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_MAX_COUNT 8U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_SURFACE_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_PHYSICAL_DEVICE_GROUP_MAX_COUNT 8U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_QUEUE_FAMILY_QUEUE_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_QUEUE_FAMILY_PERFORMANCE_COUNTER_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_DEVICE_QUEUE_FAMILY_CREATE_INFO_MAX_COUNT __C_ENG_VULKAN_CORE_QUEUE_FAMILY_MAX_COUNT /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_SURFACE_FORMAT_MAX_COUNT 512U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_SURFACE_PRESENT_MODE_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_VIEW_FORMAT_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_SWAP_CHAIN_IMAGE_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_RENDERING_INFO_FORMATS_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_SAMPLE_COUNT_ATTACHMENT_SAMPLES_MAX_COUNT 256U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_VIEWPORT_DEPTH_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_SUBMIT_INFO_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_PIPELINE_STAGE_FLAGS_MAX_COUNT 64U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_SUBMIT_SEMAPHORE_INFO_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_SUBMIT_COMMAND_BUFFER_INFO_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_WAIT_SEMAPHORE_MAX_COUNT 128U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_MEMORY_BARRIER_MAX_COUNT 32U /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_BUFFER_MEMORY_BARRIER_MAX_COUNT __C_ENG_VULKAN_CORE_MEMORY_BARRIER_MAX_COUNT /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_IMAGE_MEMORY_BARRIER_MAX_COUNT __C_ENG_VULKAN_CORE_MEMORY_BARRIER_MAX_COUNT /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_DEPENDENCY_INFO_MEMORY_BARRIER_MAX_COUNT __C_ENG_VULKAN_CORE_MEMORY_BARRIER_MAX_COUNT /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_DEPENDENCY_INFO_BUFFER_MEMORY_BARRIER_MAX_COUNT __C_ENG_VULKAN_CORE_BUFFER_MEMORY_BARRIER_MAX_COUNT /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_VULKAN_CORE_DEPENDENCY_INFO_IMAGE_MEMORY_BARRIER_MAX_COUNT __C_ENG_VULKAN_CORE_IMAGE_MEMORY_BARRIER_MAX_COUNT /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_SAMPLE_LOCATIONS_INFO_SAMPLE_LOCATIONS_MAX_COUNT 512U /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_VULKAN_CORE_COMMAND_BUFFER_WAIT_EVENTS_DEPENDENCY_INFO_MAX_COUNT 16U /* NOLINT(bugprone-reserved-identifier) */

#if defined ( __C_ENG_USE_DEFENSIVE_PROGRAMMING ) || !defined(NDEBUG)

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED true /* NOLINT(bugprone-reserved-identifier) */

#else

#define __C_ENG_VULKAN_CORE_DEFENSIVE_PROGRAMMING_ENABLED false

#endif

#if __CLION_IDE__
#pragma clang diagnostic pop
#endif

#endif //__C_ENG_VULKAN_CORE_CONFIG_HPP__