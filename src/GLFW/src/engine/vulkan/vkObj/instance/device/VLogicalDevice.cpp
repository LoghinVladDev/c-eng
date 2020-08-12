//
// Created by Vlad on 10/08/2020.
//

#include "VLogicalDevice.h"
#include <vkUtils/VStdUtilsDefs.h>
#include <algorithm>
#include <set>
#include <map>

bool engine::VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle = false;

static inline void fArrSet( float * ptr, float val, uint64 len ) noexcept {
    for( uint64 it = 0; it < len; it++ )
        ptr[it] = val;
}

static inline bool queueFamilyComparator ( const engine::VQueueFamily& a, const engine::VQueueFamily& b ) noexcept {
    return a.getQueueFamilyIndex() < b.getQueueFamilyIndex();
}

static inline void populateQueueCreateInfoStructure (VulkanDeviceQueueCreateInfo * createInfo, uint32 qFamilyIndex, uint32 qCount, const float * qPrioritiesPtr) noexcept {
    if ( createInfo == nullptr )
        return;

    * createInfo = {};
    createInfo->sType                       = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    createInfo->queueFamilyIndex            = qFamilyIndex;
    createInfo->queueCount                  = qCount;
    createInfo->pQueuePriorities            = qPrioritiesPtr;
}

static inline void populateDeviceCreateInfoStructure (VulkanDeviceCreateInfo * createInfo, const VulkanPhysicalDeviceFeatures & physicalDeviceFeatures, const VulkanDeviceQueueCreateInfo * queueCreateInfoPtr, uint32 queueCreateInfoCount = 1U) noexcept {
    if ( createInfo == nullptr )
        return;

    *createInfo = {};
    createInfo->sType                       = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo->pQueueCreateInfos           = queueCreateInfoPtr;
    createInfo->queueCreateInfoCount        = queueCreateInfoCount;
    createInfo->pEnabledFeatures            = & physicalDeviceFeatures;
    createInfo->enabledExtensionCount       = 0U;
}

VulkanResult engine::VLogicalDevice::setup( const engine::VPhysicalDevice& physicalDevice ) noexcept (false) {
    std::set < uint32 > queueFamiliesIndices;
    std::map < uint32, std::vector < float > > familyIndexToQueuePriorities;

    uint32 queueCreateInfoIndex = 0U;
    for( const auto & queue : this->_queues ) {
        if (queue.getQueueFamily().getPhysicalDevice().data() != physicalDevice.data())
            throw engine::EngineVLogicalDeviceQueuePhysicalDeviceMismatch();

        uint32 familyIndex = queue.getQueueFamily().getQueueFamilyIndex();

        queueFamiliesIndices.insert( familyIndex );

        auto findResPriorities = familyIndexToQueuePriorities.find( familyIndex );
        if( findResPriorities == familyIndexToQueuePriorities.end() )
            familyIndexToQueuePriorities.insert( std::make_pair ( familyIndex, std::vector <float> { queue.getPriority() } ) );
        else
            findResPriorities->second.push_back( queue.getPriority() );
    }

    std::vector < VulkanDeviceQueueCreateInfo > queueCreateInfos ( queueFamiliesIndices.size() );

    for ( const auto& familyIndex : queueFamiliesIndices ) {
        populateQueueCreateInfoStructure(
                (&queueCreateInfos[queueCreateInfoIndex++]),
                familyIndex,
                familyIndexToQueuePriorities.find(familyIndex)->second.size(),
                familyIndexToQueuePriorities.find(familyIndex)->second.data()
        );
    }

    VulkanDeviceCreateInfo      deviceCreateInfo    {};
    std::vector < VValidationLayer::VulkanValidationLayerLiteral > layerLiterals;

    populateDeviceCreateInfoStructure( & deviceCreateInfo, physicalDevice.getPhysicalDeviceFeatures(), queueCreateInfos.data(), queueCreateInfos.size() );


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
    for( auto& queue : this->_queues ) {
        queue.setup( *this, queue.getQueueFamily().getAvailableQueueIndex() );
    }
}

engine::VLogicalDevice::VLogicalDeviceFactory & engine::VLogicalDevice::VLogicalDeviceFactory::addQueue(const VQueueFamily & queueFamily, float priority) noexcept (false) {
    uint32 reservedQueuesCount = queueFamily.reserveQueues( 1U );

    if( reservedQueuesCount == 1U )
        this->_queues.emplace_back( queueFamily, priority );
    else if ( engine::VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle )
        throw engine::EngineVQueueFamilyNoQueuesAvailable( 1U, reservedQueuesCount );
}

engine::VLogicalDevice::VLogicalDeviceFactory & engine::VLogicalDevice::VLogicalDeviceFactory::addQueues(const VQueueFamily & queueFamily, uint32 queueCount, const float * priorities) noexcept(false) {
    if( priorities == nullptr ){
        auto * newPriorities = new float[queueCount];
        fArrSet( newPriorities, engine::VQueue::DEFAULT_QUEUE_PRIORITY, queueCount );
        priorities = newPriorities;
    }

    uint32 reservedQueuesCount = queueFamily.reserveQueues( queueCount );

    if( engine::VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle && ( reservedQueuesCount < queueCount ) )
        throw engine::EngineVQueueFamilyNoQueuesAvailable( queueCount, reservedQueuesCount );

    for( uint32 i = 0; i < queueCount; i++ ) {
        this->_queues.emplace_back( queueFamily, priorities[i] );
    }
}

engine::VLogicalDevice engine::VLogicalDevice::VLogicalDeviceFactory::build ( const engine::VPhysicalDevice& physicalDevice ) noexcept (false) {

    VLogicalDevice builtObject;

    std::sort( this->_queues.begin(), this->_queues.end(), queueFamilyComparator );

    builtObject._queues                     = this->_queues;
    builtObject._validationLayerCollection  = this->_validationLayerCollection;

    if( builtObject.setup( physicalDevice ) != VK_SUCCESS )
        throw std::runtime_error ( "logical device creation failure" );

    return builtObject;
}