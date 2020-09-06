//
// Created by Vlad on 10/08/2020.
//

#include "VLogicalDevice.h"
#include <algorithm>
#include <set>
#include <map>

#ifndef UINT32_MAX
#include <cstdint>
#endif

bool engine::VLogicalDevice::VLogicalDeviceFactory::_exceptionsToggle = false;
float engine::VLogicalDevice::_internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY = engine::VQueue::DEFAULT_QUEUE_PRIORITY;

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
    return a.getQueueFamily()->getQueueFamilyIndex() < b.getQueueFamily()->getQueueFamilyIndex();
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

engine::VLogicalDevice::VLogicalDeviceFactory & engine::VLogicalDevice::VLogicalDeviceFactory::createSwapChainToSurface(const VSurface* surface) noexcept (false) {
    if( surface == nullptr )
        return *this;

    this->_extensions.emplace ( VExtension::KHRONOS_SWAPCHAIN );
    this->_surface = surface;

    return *this;
}

[[nodiscard]] std::vector < uint32 > engine::VLogicalDevice::getQueueFamilyIndices () const noexcept {
    std::set < uint32 > uniqueQueueFamilyIndices;

    for ( const auto& queue : this->_queues )
        uniqueQueueFamilyIndices.insert( queue.getQueueFamily()->getQueueFamilyIndex() );

    std::vector < uint32 > queueFamilyIndices ( uniqueQueueFamilyIndices.begin(), uniqueQueueFamilyIndices.end() );

    return queueFamilyIndices;
}

[[nodiscard]] std::set < const engine::VQueueFamily* > engine::VLogicalDevice::getQueueFamilies() const noexcept {
    std::set < const engine::VQueueFamily * > queueFamilies;

    for ( const auto& queue : this->_queues )
        queueFamilies.insert( queue.getQueueFamily() );

    return queueFamilies;
}

VulkanResult engine::VLogicalDevice::setup( const engine::VPhysicalDevice& physicalDevice ) noexcept (false) {
    std::set < uint32 > queueFamiliesIndices;
    std::map < uint32, std::vector < float > > familyIndexToQueuePriorities;

    this->_physicalDevice = & physicalDevice;

    uint32 queueCreateInfoIndex = 0U;
    for( const auto & queue : this->_queues ) {
        if (queue.getQueueFamily()->getPhysicalDevice().data() != physicalDevice.data())
            throw engine::EngineVLogicalDeviceQueuePhysicalDeviceMismatch();

        uint32 familyIndex = queue.getQueueFamily()->getQueueFamilyIndex();

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

    if ( this->_surfacePtr != nullptr ) {
        if (!this->_swapChainAdequate)
            throw engine::EngineVLogicalDeviceSwapChainIncompatible();
        else {
            this->_swapChain            = new VSwapChain( this );
            this->_imageViewCollection  = new VImageViewCollection;
        }
    }

    VulkanResult createDeviceResult = vkCreateDevice ( physicalDevice.data(), & deviceCreateInfo, nullptr, & this->_vulkanDevice );
    if( createDeviceResult != VK_SUCCESS ) {
        delete this->_swapChain;
        delete this->_imageViewCollection;
        this->_swapChain = nullptr;
        this->_imageViewCollection = nullptr;

        return createDeviceResult;
    }

    VulkanResult createSwapChainResult = this->_swapChain->setup();
    if( createSwapChainResult != VK_SUCCESS ) {
        delete this->_swapChain;
        delete this->_imageViewCollection;
        this->_swapChain = nullptr;
        this->_imageViewCollection = nullptr;

        return createSwapChainResult;
    }

    VulkanResult createImageViewCollectionResult = this->_imageViewCollection->setup( this->_swapChain );
    if( createImageViewCollectionResult != VK_SUCCESS ) {
        delete this->_imageViewCollection;
        this->_imageViewCollection = nullptr;

        return createImageViewCollectionResult;
    }

    return VulkanResult::VK_SUCCESS;
}

void engine::VLogicalDevice::setupQueues() noexcept {
    for( auto& queue : this->_queues ) {
        queue.setup( *this, queue.getQueueFamily()->getAvailableQueueIndex() );
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
//    builtObject._swapChain                  = this->_swapChain;

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

    if( this->_swapChain != nullptr ) {
        this->_imageViewCollection->cleanup();
        this->_swapChain->cleanup();
    }

    vkDestroyDevice( this->_vulkanDevice, nullptr );
}

engine::VLogicalDevice::~VLogicalDevice() noexcept {
    delete this->_imageViewCollection;
    delete this->_swapChain;
}

engine::VLogicalDevice::VLogicalDevice(const engine::VLogicalDevice & obj) noexcept {
    this->_vulkanDevice                 = obj._vulkanDevice;
    this->_queues                       = obj._queues;
    this->_swapChainAdequate            = obj._swapChainAdequate;
    this->_validationLayerCollection    = obj._validationLayerCollection;
    this->_enabledExtensions            = obj._enabledExtensions;
    this->_surfacePtr                   = obj._surfacePtr;
    this->_physicalDevice               = obj._physicalDevice;

    if( obj._swapChain != nullptr ) {
        this->_swapChain            = new VSwapChain(*obj._swapChain, this);
        this->_imageViewCollection  = new VImageViewCollection ( obj._imageViewCollection, this->_swapChain );
//        this->_swapChain->setLogicalDevice( this ); cannot because upon copy ctr call, obj is initialized
//                                                           set of logical device works before init. Same for img collection
    }
    else {
        this->_swapChain            = nullptr;
        this->_imageViewCollection  = nullptr;
    }
}

engine::VLogicalDevice &engine::VLogicalDevice::operator=(const engine::VLogicalDevice & obj) noexcept {
    if( this == & obj )
        return *this;

    if ( this->_vulkanDevice != VulkanDevice() )
        this->cleanup();
    delete this->_swapChain;

    this->_vulkanDevice                 = obj._vulkanDevice;
    this->_queues                       = obj._queues;
    this->_swapChainAdequate            = obj._swapChainAdequate;
    this->_validationLayerCollection    = obj._validationLayerCollection;
    this->_enabledExtensions            = obj._enabledExtensions;
    this->_surfacePtr                   = obj._surfacePtr;
    this->_physicalDevice               = obj._physicalDevice;

    if( obj._swapChain != nullptr ) {
        this->_swapChain            = new VSwapChain(*obj._swapChain, this);
        this->_imageViewCollection  = new VImageViewCollection ( obj._imageViewCollection, this->_swapChain );
//        this->_swapChain->setLogicalDevice( this );
    }
    else {
        this->_swapChain            = nullptr;
        this->_imageViewCollection  = nullptr;
    }

    return *this;
}

const engine::VQueue * engine::VLogicalDevice::getFirstPresentQueuePtr() const noexcept {
    for( const auto & queue : this->_queues )
        if ( queue.getQueueFamily()->isPresentCapable() )
            return ( & queue );
    return nullptr;
}

const engine::VQueue * engine::VLogicalDevice::getFirstGraphicsQueuePtr() const noexcept {
    for( const auto & queue : this->_queues )
        if ( queue.getQueueFamily()->isGraphicsCapable() )
            return ( & queue );
    return nullptr;
}

const engine::VQueue * engine::VLogicalDevice::getFirstTransferQueuePtr() const noexcept {
    const VQueue * pGraphicsQueue = nullptr;

    for ( const auto & queue : this->_queues )
        if ( queue.getQueueFamily()->isTransferCapable() )
            return ( & queue );
        else if ( queue.getQueueFamily()->isGraphicsCapable() )
            pGraphicsQueue = ( & queue );

    return pGraphicsQueue;
}

void engine::VLogicalDevice::cleanupSwapChain() noexcept {
    this->_imageViewCollection->cleanup();
    this->_swapChain->cleanup();
}

VulkanResult engine::VLogicalDevice::recreateSwapChain() noexcept {
    VulkanResult createSwapChainResult = this->_swapChain->setup( this );
    if ( createSwapChainResult != VulkanResult::VK_SUCCESS ) {
        delete this->_swapChain;
        delete this->_imageViewCollection;
        this->_swapChain = nullptr;
        this->_imageViewCollection = nullptr;

        return createSwapChainResult;
    }

    VulkanResult createImageViewCollectionResult = this->_imageViewCollection->setup( this->_swapChain );
    if ( createImageViewCollectionResult != VulkanResult::VK_SUCCESS ) {
        delete this->_imageViewCollection;
        this->_imageViewCollection = nullptr;

        return createImageViewCollectionResult;
    }

    return VulkanResult::VK_SUCCESS;
}
