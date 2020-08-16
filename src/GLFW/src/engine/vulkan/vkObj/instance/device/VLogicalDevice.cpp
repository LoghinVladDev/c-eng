//
// Created by Vlad on 10/08/2020.
//

#include "VLogicalDevice.h"
#include <vkUtils/VStdUtilsDefs.h>
#include <algorithm>
#include <set>
#include <map>
#include "VSwapChainDefs.h"

#ifndef UINT32_MAX
#include <cstdint>
#endif

#include <obj/util/settings/SettingOptionGraphics.h>

bool engine::VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle = false;
float engine::VLogicalDevice::_internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY = engine::VQueue::DEFAULT_QUEUE_PRIORITY;

static inline VulkanSurfaceFormatKhronos chooseSwapSurfaceFormat ( const std::vector < VulkanSurfaceFormatKhronos > & availableFormats ) noexcept {
    for ( const auto & availableFormat : availableFormats ) {
        if (
            availableFormat.format      == __VK_FORMAT_8BIT_BGRA_SRGB &&
            availableFormat.colorSpace  == __VK_COLORSPACE_NONLINEAR_SRGB
        )
            return availableFormat;
    }

    return availableFormats[0];
}

static inline VulkanPresentModeKhronos chooseSwapPresentMode ( const std::vector < VulkanPresentModeKhronos > & availablePresentModes ) noexcept {

    for ( const auto & availablePresentMode : availablePresentModes )
        if ( availablePresentMode == __VK_PRESENT_MODE_VSYNC_TRIPLE_BUFFER )
            return availablePresentMode;

    return __VK_PRESENT_MODE_VSYNC_DOUBLE_BUFFER;
}

static inline const engine::ResolutionSetting * getSharedResolutionSetting () noexcept {

    const auto * pSetting = engine::SettingsSharedContainer::getInstance().get( engine::SettingOption::RESOLUTION );

    if ( pSetting != nullptr ) {
        const auto * pResolutionSetting = dynamic_cast < engine::ResolutionSetting const * >( pSetting );

        if( pResolutionSetting != nullptr )
            return pResolutionSetting;
    }

    return nullptr;
}

static inline VulkanExtent2D chooseSwapExtent ( const VulkanSurfaceCapabilitiesKhronos & capabilites ) noexcept ( false ) {
    if ( capabilites.currentExtent.width != UINT32_MAX )
        return capabilites.currentExtent;

    const auto * sharedResolutionSetting = getSharedResolutionSetting();

    if( sharedResolutionSetting == nullptr )
        throw std::runtime_error( "No Resolution Set in SettingsSharedContainer" );

    VulkanExtent2D actualExtent = {
        sharedResolutionSetting->getWidth(),
        sharedResolutionSetting->getHeight()
    };

    actualExtent.width = std::max (
        capabilites.minImageExtent.width,
        std::min (
            capabilites.maxImageExtent.width,
            actualExtent.width
        )
    );

    actualExtent.height = std::max (
        capabilites.minImageExtent.height,
        std::min (
            capabilites.maxImageExtent.height,
            actualExtent.height
        )
    );

    return actualExtent;
}

static inline bool checkForSwapChainCapability ( const engine::VExtensionCollection& extensionCollection, const engine::VPhysicalDevice& device, const engine::VSurface *surface ) noexcept {
    if ( surface == nullptr )
        return false;

    if ( extensionCollection.empty() )
        return false;

    auto swapChainSupportDetails = device.querySwapChainOnSurfaceSupport ( surface );

    std::cout << extensionCollection.contains( engine::VExtension::KHRONOS_SWAPCHAIN ) << '\n';

    return ( extensionCollection.contains ( engine::VExtension::KHRONOS_SWAPCHAIN ) ) && ( ! swapChainSupportDetails.formats.empty() ) && ( ! swapChainSupportDetails.presentModes.empty() );
}

static inline void fArrSet( float * ptr, float val, uint64 len ) noexcept {
    for( uint64 it = 0; it < len; it++ )
        ptr[it] = val;
}

static inline bool queueFamilyComparator ( const engine::VQueue& a, const engine::VQueue& b ) noexcept {
    return a.getQueueFamily().getQueueFamilyIndex() < b.getQueueFamily().getQueueFamilyIndex();
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

engine::VLogicalDevice::VLogicalDeviceFactory & engine::VLogicalDevice::VLogicalDeviceFactory::addSwapChainToSurface ( const VSurface* surface ) noexcept {
    this->_extensions.add ( VExtension( VExtension::KHRONOS_SWAPCHAIN ) );
    this->_surface = surface;

    return * this;
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

    auto requiredExtensionsProperties = this->_enabledExtensions.getExtensionNames ();

    if( ! requiredExtensionsProperties.empty() ) {
        deviceCreateInfo.enabledExtensionCount =  static_cast <uint32> ( requiredExtensionsProperties.size() );
        deviceCreateInfo.ppEnabledExtensionNames = requiredExtensionsProperties.data();
    }

    this->_swapChainAdequate = checkForSwapChainCapability( this->_enabledExtensions, physicalDevice, this->_surfacePtr );

    if ( this->_surfacePtr != nullptr && ! this->_swapChainAdequate )
        throw engine::EngineVLogicalDeviceSwapChainIncompatible();

    const auto * res = getSharedResolutionSetting();

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

    return *this;
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

    return *this;
}

engine::VLogicalDevice::VLogicalDeviceFactory & engine::VLogicalDevice::VLogicalDeviceFactory::addExtension ( const engine::VExtension& extension ) noexcept {
    this->_extensions.add ( extension );
    return *this;
}

engine::VLogicalDevice::VLogicalDeviceFactory & engine::VLogicalDevice::VLogicalDeviceFactory::addExtensions ( const engine::VExtensionCollection& collection ) noexcept {
    this->_extensions.add ( collection );
    return *this; 
}

engine::VLogicalDevice engine::VLogicalDevice::VLogicalDeviceFactory::build ( const engine::VPhysicalDevice& physicalDevice ) noexcept (false) {

    VLogicalDevice builtObject;

    std::sort( this->_queues.begin(), this->_queues.end(), queueFamilyComparator );

    builtObject._queues                     = this->_queues;
    builtObject._validationLayerCollection  = this->_validationLayerCollection;
    builtObject._surfacePtr                 = this->_surface;

    if ( engine::VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle ) {
        for ( auto & extension : this->_extensions.getExtensions() ) 
            if ( ! physicalDevice.supportsExtension( extension ) )
                throw engine::EngineVLogicalDeviceUnsupportedExtension( extension );
    } else {
        VExtensionCollection filteredExtensions;
        for ( auto & extension : this->_extensions.getExtensions() )
            if( physicalDevice.supportsExtension ( extension ) )
                filteredExtensions.add( extension );

        this->_extensions = filteredExtensions;
    }

    builtObject._enabledExtensions = this->_extensions;

    if( builtObject.setup( physicalDevice ) != VK_SUCCESS )
        throw std::runtime_error ( "logical device creation failure" );

    builtObject.setupQueues();

    return builtObject;
}

void engine::VLogicalDevice::cleanup() noexcept {
    for( auto & queue : this->_queues )
        queue.cleanup();

    vkDestroyDevice( this->_vulkanDevice, nullptr );
}