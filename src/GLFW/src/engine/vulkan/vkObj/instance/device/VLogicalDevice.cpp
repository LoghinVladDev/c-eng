//
// Created by Vlad on 10/08/2020.
//

#include "VLogicalDevice.h"
#include <vkUtils/VStdUtilsDefs.h>

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

static inline void populateDeviceCreateInfoStructure (VulkanDeviceCreateInfo * createInfo, const VulkanPhysicalDeviceFeatures & physicalDeviceFeatures, const VulkanDeviceQueueCreateInfo & queueCreateInfoPtr, uint32 queueCreateInfoCount = 1U) noexcept {
    if ( createInfo == nullptr )
        return;

    *createInfo = {};
    createInfo->sType                       = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo->pQueueCreateInfos           = & queueCreateInfoPtr;
    createInfo->queueCreateInfoCount        = queueCreateInfoCount;
    createInfo->pEnabledFeatures            = & physicalDeviceFeatures;
    createInfo->enabledExtensionCount       = 0U;
}

VulkanResult engine::VLogicalDevice::setup( const engine::VPhysicalDevice& physicalDevice ) noexcept {
    VulkanDeviceQueueCreateInfo queueCreateInfo     {};
    VulkanDeviceCreateInfo      deviceCreateInfo    {};
    std::vector < VValidationLayer::VulkanValidationLayerLiteral > layerLiterals;

    populateQueueCreateInfoStructure( & queueCreateInfo, this->_queueFamily->getQueueFamilyIndex(), this->_queueCount, this->_queuePriorities );
    populateDeviceCreateInfoStructure( & deviceCreateInfo, physicalDevice.getPhysicalDeviceFeatures(), queueCreateInfo );


    if( this->_validationLayerCollection != nullptr ) {
        layerLiterals = this->_validationLayerCollection->getValidationLayerLiterals();
        deviceCreateInfo.enabledLayerCount      = static_cast <uint32> (layerLiterals.size());
        deviceCreateInfo.ppEnabledLayerNames    = layerLiterals.data();
    } else {
        deviceCreateInfo.enabledLayerCount = 0U;
    }

    return vkCreateDevice ( physicalDevice.data(), & deviceCreateInfo, nullptr, & this->_vulkanDevice );
}

void engine::VLogicalDevice::setupQueues() noexcept {
    for( uint32 it = 0; it < this->_queueCount; it ++ ) {
        this->_queues.emplace_back( *this, it );
    }
}