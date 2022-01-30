//
// Created by Vlad on 10/08/2020.
//

#include "VLogicalDevice.hpp"
#include <algorithm>
#include <set>
#include <map>

#ifndef UINT32_MAX
#include <cstdint>
#endif

#include <VSwapChain.hpp>
#include <VImageView.hpp>

bool engine::VLogicalDevice::Factory::_exceptionsToggle = false;
float engine::VLogicalDevice::_internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY = engine::VQueue::DEFAULT_QUEUE_PRIORITY;

/**
 * @brief internal function used to check whether a swap chain can be created or not
 *
 * Checks :
 *      Surface Validity
 *      Extension Collection - needs KHRONOS_SWAPCHAIN
 *      Swap Chain Properties - needs extent, needs present
 *
 * @param extensionCollection : engine::VExtensionCollection cref = Constant Reference to extension collection used
 * @param device : engine::VPhysicalDevice cref = Constant Reference to the GPU Object ( Physical Device ) used
 * @param surface : engine::VSurface cptr = Address to Constant Surface object
 *
 * @exceptsafe
 *
 * @static
 *
 * @return bool = true if swap chain capabilities are met, false otherwise
 */
static inline auto checkForSwapChainCapability (
        engine::VExtensionCollection    const & extensionCollection,
        engine::VPhysicalDevice         const & device,
        engine::VSurface                const * surface
) noexcept -> bool {
    if ( surface == nullptr )
        return false;

    if ( extensionCollection.empty() )
        return false;

    auto swapChainSupportDetails = device.querySwapChainOnSurfaceSupport ( surface );

#ifndef NDEBUG
    std::cout << extensionCollection.contains( engine::VExtension::KHRONOS_SWAPCHAIN ) << '\n';
#endif

    return
        ( extensionCollection.contains ( engine::VExtension::KHRONOS_SWAPCHAIN ) ) && /// must have KHRONOS_SWAPCHAIN extension
        ( ! swapChainSupportDetails.formats.empty() ) && /// must have supported formats
        ( ! swapChainSupportDetails.presentModes.empty() ); /// must have present modes
}

/**
 * @brief internal function for defaulting a float array ( memset for float )
 *
 * @param ptr : float ptr = address of the first element of the array
 * @param val : float = value to default the array with
 * @param len : uint64 = length of the array
 *
 * @static
 *
 * @exceptsafe
 */
static inline auto fArrSet( float * ptr, float val, uint64 len ) noexcept -> void {
    for( uint64 it = 0; it < len; it++ )
        ptr[it] = val;
}

/**
 * @brief comparator function for two Queues. Orders by Family
 *
 * @param a : engine::VQueue cref = Reference to one Queue
 * @param b : engine::VQueue cref = Reference to another Queue to be compared with the first
 *
 * @static
 *
 * @exceptsafe
 *
 * @return bool = true if the first Queue is ordered compared to the other, false otherwise
 */
static inline auto queueFamilyComparator ( engine::VQueue const & a, engine::VQueue const & b ) noexcept -> bool {
    return a.getQueueFamilyPtr()->getQueueFamilyIndex() < b.getQueueFamilyPtr()->getQueueFamilyIndex();
}

/**
 * @brief internal function for populating the Queue Creation Structure
 *
 * @param createInfo : VulkanDeviceQueueCreateInfo ptr = address to the structure to be populated
 * @param qFamilyIndex : uint32 = index of the queue's family
 * @param qCount : uint32 = number of queues to be allocated
 * @param qPrioritiesPtr : float cptr = address of the first element in a priorities array, representing queues priority
 *
 * @static
 *
 * @exceptsafe
 */
static inline auto populateQueueCreateInfoStructure (
        VulkanDeviceQueueCreateInfo       * createInfo,
        uint32                              qFamilyIndex,
        uint32                              qCount,
        float                       const * qPrioritiesPtr
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = (VulkanDeviceQueueCreateInfo) {
        .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext              = nullptr,
        .flags              = VULKAN_NULL_FLAGS,
        .queueFamilyIndex   = qFamilyIndex,
        .queueCount         = qCount,
        .pQueuePriorities   = qPrioritiesPtr
    };
}

/**
 * @brief internal function for populating the Logical Device Creation Structure
 *
 * @param createInfo : VulkanDeviceCreateInfo ptr = address to the structure to be populated
 * @param physicalDeviceFeatures : VulkanPhysicalDeviceFeatures cref = Reference to a structure containing the features of a Physical Device
 * @param queueCreateInfoPtr : VulkanDeviceQueueCreateInfo cptr = Address to the Structure ( or to the first Structure in an array ) containing Queues Allocation for the Device
 * @param queueCreateInfoCount : uint32 = Number of structures of Queue Create Info ( defaults to 1 if not array )
 *
 * @static
 *
 * @exceptsafe
 */
static inline auto populateDeviceCreateInfoStructure (
        VulkanDeviceCreateInfo              * createInfo,
        VulkanPhysicalDeviceFeatures  const & physicalDeviceFeatures,
        VulkanDeviceQueueCreateInfo   const * queueCreateInfoPtr,
        uint32                                queueCreateInfoCount      = 1U
) noexcept -> void {
    if ( createInfo == nullptr )
        return;

    * createInfo = (VulkanDeviceCreateInfo) {
        .sType                  = VulkanStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = VULKAN_NULL_FLAGS,
        .queueCreateInfoCount   = queueCreateInfoCount,
        .pQueueCreateInfos      = queueCreateInfoPtr,
        .enabledExtensionCount  = 0U,
        .pEnabledFeatures       = & physicalDeviceFeatures
    };
}

auto engine::VLogicalDevice::Factory::createSwapChainToSurface (
        VSurface const * surface
) noexcept -> Factory & {
    if( surface == nullptr ) /// do nothing if given invalid surface
        return *this;

    this->_extensions.emplace ( VExtension::KHRONOS_SWAPCHAIN ); /// add swapchain extension if surface has been provided
    this->_surface = surface;

    return *this;
}

auto engine::VLogicalDevice::getQueueFamilyIndices () const noexcept -> std::vector < uint32 > {
    std::set < uint32 > uniqueQueueFamilyIndices;

    for ( const auto& queue : this->_queues )
        uniqueQueueFamilyIndices.insert( queue.getQueueFamilyPtr()->getQueueFamilyIndex() ); /// save non-duplicating queue family indices

    return { uniqueQueueFamilyIndices.begin(), uniqueQueueFamilyIndices.end() }; /// return vector of set's elements
}

auto engine::VLogicalDevice::getQueueFamilies() const noexcept -> std::set < engine::VQueueFamily const * > {
    std::set < const engine::VQueueFamily * > queueFamilies;

    for ( const auto& queue : this->_queues )
        queueFamilies.insert( queue.getQueueFamilyPtr() );

    return queueFamilies;
}

auto engine::VLogicalDevice::setup( const engine::VPhysicalDevice& physicalDevice ) noexcept (false) -> VulkanResult {
    std::set < uint32 > queueFamiliesIndices;
    std::map < uint32, std::vector < float > > familyIndexToQueuePriorities; /// each family with their own priorities

    this->_physicalDevice = & physicalDevice; /// save physical device address

    uint32 queueCreateInfoIndex = 0U;
    for( const auto & queue : this->_queues ) {
        if (queue.getQueueFamilyPtr()->getPhysicalDevicePtr()->data() != physicalDevice.data()) /// if queue comes from another device handle
            throw engine::EngineVLogicalDeviceQueuePhysicalDeviceMismatch(); /// throw

        uint32 familyIndex = queue.getQueueFamilyPtr()->getQueueFamilyIndex();

        queueFamiliesIndices.insert( familyIndex ); /// save index of queue family

        auto findResPriorities = familyIndexToQueuePriorities.find( familyIndex ); /// either create new priority vector, or append
        if( findResPriorities == familyIndexToQueuePriorities.end() )
            familyIndexToQueuePriorities.insert( std::make_pair ( familyIndex, std::vector <float> { queue.getPriority() } ) );
        else
            findResPriorities->second.push_back( queue.getPriority() );
    }

    std::vector < VulkanDeviceQueueCreateInfo > queueCreateInfos ( queueFamiliesIndices.size() ); /// one queue create info per family used

    for ( const auto& familyIndex : queueFamiliesIndices ) { /// for each family
        populateQueueCreateInfoStructure(
            ( & queueCreateInfos [ queueCreateInfoIndex ++ ] ), /// pass address and move onto the next
            familyIndex, /// queue's family index
            static_cast < uint32 > ( familyIndexToQueuePriorities.find(familyIndex)->second.size() ), /// get priorities size
            familyIndexToQueuePriorities.find(familyIndex)->second.data() /// get priorities
        );
    }

    VulkanDeviceCreateInfo deviceCreateInfo {};
    std::vector < VValidationLayer::VulkanValidationLayerLiteral > layerLiterals;

    populateDeviceCreateInfoStructure(
            & deviceCreateInfo, /// structure's address to populate
            physicalDevice.getPhysicalDeviceFeatures(), /// features of device
            queueCreateInfos.data(), /// pass all queue create infos
            static_cast<uint32>(queueCreateInfos.size())
    );


    if( this->_validationLayerCollection != nullptr ) { /// if using validation layers
        layerLiterals                           = this->_validationLayerCollection->getValidationLayerLiterals(); /// get layers lames
        deviceCreateInfo.enabledLayerCount      = static_cast <uint32> (layerLiterals.size()); /// number of enabled layers
        deviceCreateInfo.ppEnabledLayerNames    = layerLiterals.data(); /// layer names
    } else {
        deviceCreateInfo.enabledLayerCount = 0U; /// no layers
    }

    auto requiredExtensionsProperties = this->_enabledExtensions.getExtensionNames (); /// extensions used

    if( ! requiredExtensionsProperties.empty() ) { /// if using extensions, add to create info
        deviceCreateInfo.enabledExtensionCount =  static_cast <uint32> ( requiredExtensionsProperties.size() );
        deviceCreateInfo.ppEnabledExtensionNames = requiredExtensionsProperties.data();
    }

    /// check swapchain capability
    this->_swapChainAdequate = checkForSwapChainCapability(
            this->_enabledExtensions,
            physicalDevice,
            this->_surfacePtr
    );

    /// if a surface was attached at creation
    if ( this->_surfacePtr != nullptr ) {
        if (!this->_swapChainAdequate) /// and device cannot pass to surface
            throw engine::EngineVLogicalDeviceSwapChainIncompatible(); /// throw
        else {
            this->_swapChain            = new VSwapChain( this ); /// create swapchain and image views
            this->_imageViewCollection  = new VImageViewCollection;
        }
    }

    /// create logical device
    VulkanResult createDeviceResult = vkCreateDevice (
            physicalDevice.data(), /// with this Physical Device Handler ( GPU )
            & deviceCreateInfo,    /// with the parameters in this structure
            nullptr,     /// no custom allocator
            & this->_vulkanDevice  /// save handler here
    );

    if( createDeviceResult != VK_SUCCESS ) { /// if creation unsuccessful
        delete this->_swapChain;
        delete this->_imageViewCollection;
        this->_swapChain = nullptr;
        this->_imageViewCollection = nullptr;

        return createDeviceResult;
    }

    VulkanResult createSwapChainResult = this->_swapChain->setup();
    if( createSwapChainResult != VK_SUCCESS ) { /// if swap chain setup unsuccessful
        delete this->_swapChain;
        delete this->_imageViewCollection;
        this->_swapChain = nullptr;
        this->_imageViewCollection = nullptr;

        return createSwapChainResult;
    }

    VulkanResult createImageViewCollectionResult = this->_imageViewCollection->setup( this->_swapChain );
    if( createImageViewCollectionResult != VK_SUCCESS ) { /// if image view creation unsuccessful
        delete this->_imageViewCollection;
        this->_imageViewCollection = nullptr;

        return createImageViewCollectionResult;
    }

    return VulkanResult::VK_SUCCESS;
}

auto engine::VLogicalDevice::setupQueues() noexcept -> void {
    for( auto& queue : this->_queues ) { /// setup each queue individually
        queue.setup( *this, queue.getQueueFamilyPtr()->getAvailableQueueIndex() );
    }
}

auto engine::VLogicalDevice::Factory::addQueue(
        VQueueFamily const & queueFamily,
        float priority
) noexcept (false) -> Factory & {
    uint32 reservedQueuesCount = queueFamily.reserveQueues( 1U ); /// add one queue => reserve 1 in advance

    if( reservedQueuesCount == 1U )
        this->_queues.emplace_back( queueFamily, priority );
    else if ( engine::VLogicalDevice::Factory::_exceptionsToggle ) /// if none avaiable, throw
        throw engine::EngineVQueueFamilyNoQueuesAvailable( 1U, reservedQueuesCount );

    return *this;
}

auto engine::VLogicalDevice::Factory::addQueues(
        VQueueFamily const & queueFamily,
        uint32 queueCount,
        float const * priorities
) noexcept(false) -> Factory & {
    float const * prioritiesAllocatedHere = nullptr; /// tracking for in-place allocated priorities

    if( priorities == nullptr ){ /// if no priorities given
        auto * newPriorities = new float[queueCount];

        prioritiesAllocatedHere = newPriorities; /// track allocation

        fArrSet( newPriorities, engine::VQueue::DEFAULT_QUEUE_PRIORITY, queueCount ); /// default priorities
        priorities = newPriorities;
    }

    uint32 reservedQueuesCount = queueFamily.reserveQueues( queueCount ); /// reserve the required queue count

    if(engine::VLogicalDevice::Factory::_exceptionsToggle && (reservedQueuesCount < queueCount ) )
        throw engine::EngineVQueueFamilyNoQueuesAvailable( queueCount, reservedQueuesCount ); /// if cannot reserve and exceptions enabled, throw

    for( uint32 i = 0; i < queueCount; i++ ) {
        this->_queues.emplace_back( queueFamily, priorities[i] );
    }

    delete [] prioritiesAllocatedHere; /// delete internally allocated priorities

    return *this;
}

auto engine::VLogicalDevice::Factory::addExtension (
        engine::VExtension const & extension
) noexcept ->  Factory & {
    this->_extensions.add ( extension ); /// add extension to enabled extensions
    return *this;
}

auto engine::VLogicalDevice::Factory::addExtensions (
        engine::VExtensionCollection const & collection
) noexcept -> Factory & {
    this->_extensions.add ( collection ); /// add all extensions to enabled extensions
    return *this;
}

auto engine::VLogicalDevice::Factory::build (
        engine::VPhysicalDevice const & physicalDevice
) noexcept (false) -> VLogicalDevice {

    VLogicalDevice builtObject; ///start from empty object

    std::sort( this->_queues.begin(), this->_queues.end(), queueFamilyComparator ); /// sort queues

    builtObject._queues                     = this->_queues; /// add queues from factory to device
    builtObject._validationLayerCollection  = this->_validationLayerCollection; /// add validation layers from factory to device
    builtObject._surfacePtr                 = this->_surface; /// add surface from factory to device

    if ( engine::VLogicalDevice::Factory::_exceptionsToggle ) { /// if exceptions enabled
        for ( auto & extension : this->_extensions.getExtensions() )  /// check for unsupported exceptions
            if ( ! physicalDevice.supportsExtension( extension ) )
                throw engine::EngineVLogicalDeviceUnsupportedExtension( extension ); /// throw if unsupported
    } else {
        VExtensionCollection filteredExtensions; /// else just filter unsupported exceptions
        for ( auto & extension : this->_extensions.getExtensions() )
            if( physicalDevice.supportsExtension ( extension ) )
                filteredExtensions.add( extension );

        this->_extensions = filteredExtensions;
    }

    builtObject._enabledExtensions = this->_extensions; /// pass exceptions from Factory to Object

    if( builtObject.setup( physicalDevice ) != VK_SUCCESS ) /// setup physical device
        throw std::runtime_error ( "logical device creation failure" ); /// if failed, throw

    builtObject.setupQueues(); /// setup queues

    return builtObject;
}

void engine::VLogicalDevice::clear() noexcept {
    for( auto & queue : this->_queues ) /// cleanup queues
        queue.clear();

    if( this->_swapChain != nullptr ) { /// cleanup image views and swapchain
        this->_imageViewCollection->clear();
        this->_swapChain->clear();
    }

    vkDestroyDevice( this->_vulkanDevice, nullptr ); /// destroy logical device hanldes
}

engine::VLogicalDevice::~VLogicalDevice() noexcept { /// on destruction, free dynamically allocated objects
    delete this->_imageViewCollection;
    delete this->_swapChain;
}

engine::VLogicalDevice::VLogicalDevice(engine::VLogicalDevice const & obj) noexcept {
    this->_vulkanDevice                 = obj._vulkanDevice;                /// pass handle
    this->_queues                       = obj._queues;                      /// pass queues
    this->_swapChainAdequate            = obj._swapChainAdequate;           /// copy swap chain adequacy
    this->_validationLayerCollection    = obj._validationLayerCollection;   /// pass validation layer collection
    this->_enabledExtensions            = obj._enabledExtensions;           /// pass enabled extensions
    this->_surfacePtr                   = obj._surfacePtr;                  /// pass surface ptr
    this->_physicalDevice               = obj._physicalDevice;              /// pass physical device address

    if( obj._swapChain != nullptr ) {
        this->_swapChain            = new VSwapChain(*obj._swapChain, this);/// construct new swapchain of existing
        this->_imageViewCollection  = new VImageViewCollection ( obj._imageViewCollection, this->_swapChain ); /// construct new image view collection
//        this->_swapChain->setLogicalDevice( this ); cannot because upon copy ctr call, obj is initialized
//                                                           set of logical device works before init. Same for img collection
    }
    else {
        this->_swapChain            = nullptr;
        this->_imageViewCollection  = nullptr;
    }
}

engine::VLogicalDevice &engine::VLogicalDevice::operator=( engine::VLogicalDevice const & obj ) noexcept {
    if( this == & obj )
        return *this;

    if ( this->_vulkanDevice != VulkanDevice() ) // if device existed here
        this->clear(); /// cleanup
    delete this->_swapChain;

    this->_vulkanDevice                 = obj._vulkanDevice; /// same as copy ctor
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

auto engine::VLogicalDevice::getFirstPresentQueuePtr() const noexcept -> VQueue const * {
    for( const auto & queue : this->_queues )
        if ( queue.getQueueFamilyPtr()->isPresentCapable() )
            return ( & queue ); /// return address of queue
    return nullptr;
}

auto engine::VLogicalDevice::getFirstGraphicsQueuePtr() const noexcept -> VQueue const * {
    for( const auto & queue : this->_queues )
        if ( queue.getQueueFamilyPtr()->isGraphicsCapable() )
            return ( & queue );
    return nullptr;
}

auto engine::VLogicalDevice::getFirstTransferQueuePtr() const noexcept -> VQueue const * {
    const VQueue * pGraphicsQueue = nullptr;

    for ( const auto & queue : this->_queues )
        if ( queue.getQueueFamilyPtr()->isTransferCapable() )
            return ( & queue );
        else if ( queue.getQueueFamilyPtr()->isGraphicsCapable() )
            pGraphicsQueue = ( & queue );

    return pGraphicsQueue;
}

auto engine::VLogicalDevice::cleanupSwapChain() noexcept -> void {
    this->_imageViewCollection->clear();
    this->_swapChain->clear();
}

auto engine::VLogicalDevice::recreateSwapChain() noexcept -> VulkanResult {
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

auto engine::VLogicalDevice::Factory::operator==(Factory const &o) const noexcept -> bool {
    if ( this == & o ) return true;

    return
            this->_surface                      == o._surface                      &&
            this->_validationLayerCollection    == o._validationLayerCollection    &&
            this->_queues                       == o._queues                       &&
            this->_extensions                   == o._extensions;
}

auto engine::VLogicalDevice::Factory::equals(Object const &o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype(this) > (& o);
    if ( p == nullptr ) return false;

    return this->operator==(* p);
}

auto engine::VLogicalDevice::Factory::hash() const noexcept -> Index {
    return 0;
}

auto engine::VLogicalDevice::Factory::copy() const noexcept -> Factory * {
    return new Factory ( * this );
}

auto engine::VLogicalDevice::operator==(VLogicalDevice const & o) const noexcept -> bool {
    if ( this == & o ) return true;

    return this->_vulkanDevice == o._vulkanDevice;
}

auto engine::VLogicalDevice::equals(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype(this) > (& o);
    if ( p == nullptr ) return false;

    return this->operator==(*p);
}

auto engine::VLogicalDevice::hash() const noexcept -> Index {
    return
        dataTypes::hash(reinterpret_cast<AddressValueType>(this->_vulkanDevice));
}

auto engine::VLogicalDevice::copy() const noexcept -> VLogicalDevice * {
    return new VLogicalDevice(* this);
}

#include <sstream>

auto engine::VLogicalDevice::Factory::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VLogicalDevice::Factory " <<
        "{ pValidationLayerCollection = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_validationLayerCollection) <<
        ", pSurface = 0x" << reinterpret_cast<AddressValueType>(this->_surface) <<
        ", extensions = " << this->_extensions.toString() <<
        ", queues = [ ";

    for (auto const & item : this->_queues)
        oss << item.toString() << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}

auto engine::VLogicalDevice::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "VLogicalDevice " <<
        "{ handle = 0x" << std::hex << reinterpret_cast<AddressValueType>(this->_vulkanDevice) <<
        ", isSwapChainAdequate = " << std::boolalpha << this->_swapChainAdequate <<
        ", pSurface = 0x" << reinterpret_cast<AddressValueType>(this->_surfacePtr) <<
        ", pValidationLayerCollection = 0x" << reinterpret_cast<AddressValueType>(this->_validationLayerCollection) <<
        ", pPhysicalDevice = 0x" << reinterpret_cast<AddressValueType>(this->_physicalDevice) <<
        ", pSwapChain = 0x" << reinterpret_cast<AddressValueType>(this->_swapChain) <<
        ", pImageViewCollection = 0x" << reinterpret_cast<AddressValueType>(this->_imageViewCollection) <<
        ", queues = [ ";

    for (auto const & item : this->_queues)
        oss << item.toString() << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}