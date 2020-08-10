//
// Created by Vlad on 10/08/2020.
//

#include "VLogicalDevice.h"

bool engine::VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle = false;

static inline void populateQueueCreateInfoStructure (VulkanDeviceQueueCreateInfo * createInfo, uint32 qFamilyIndex, uint32 qCount, const float * qPrioritiesPtr) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = {};
    createInfo->sType                       = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    createInfo->queueFamilyIndex            = qFamilyIndex;
    createInfo->queueCount                  = qCount;
    createInfo->pQueuePriorities            = qPrioritiesPtr;
}

static inline void populateDeviceCreateInfoStructure (VulkanDeviceCreateInfo * createInfo, const VulkanPhy, const VulkanDeviceQueueCreateInfo * queueCreateInfoPtr, uint32 queueCreateInfoCount = 1U) noexcept {
    if ( createInfo == nullptr )
        return;

    *createInfo = {};
    createInfo->pQueueCreateInfos           = queueCreateInfoPtr;
    createInfo->queueCreateInfoCount        = queueCreateInfoCount;
//    createInfo->pEnabledFeatures
}

void engine::VLogicalDevice::setup( const engine::VPhysicalDevice& physicalDevice ) noexcept {
    VulkanDeviceQueueCreateInfo queueCreateInfo     {};
    VulkanDeviceCreateInfo      deviceCreateInfo    {};
}