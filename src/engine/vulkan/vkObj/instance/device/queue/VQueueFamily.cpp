//
// Created by vladl on 08/08/2020.
//

#include "VQueueFamily.h"
#include <vkUtils/VStdUtils.h>

auto engine::VQueueFamilyCollection::queryAvailableQueueFamilies( ) noexcept (false) -> void {
    /// if queue families were queried but no Physical Device is assigned, throw
    if ( this->_physicalDevice->data() == VK_NULL_HANDLE )
        throw engine::EngineNullVPhysicalDevice();

    /// value to store the number of queue families
    uint32 queueFamilyCount = 0;
    /// acquire queue family count
    vkGetPhysicalDeviceQueueFamilyProperties( this->_physicalDevice->data(), & queueFamilyCount, nullptr );

    /// queue family properties
    std::vector < VulkanQueueFamilyProperties > queueFamiliesProperties ( queueFamilyCount );
    /// acquire queue family properties
    vkGetPhysicalDeviceQueueFamilyProperties( this->_physicalDevice->data(), & queueFamilyCount, queueFamiliesProperties.data() );

    /// asign each family to their object
    uint32 queueGraphicsFamily = 0;
    for (const auto & queueFamilyProperties : queueFamiliesProperties)
        this->_queueFamilies.emplace_back( this, queueFamilyProperties, queueGraphicsFamily++ );
}

auto engine::VQueueFamilyCollection::unReserveAllQueueFamilies() noexcept -> void {
    for ( const auto & queueFamily : this->_queueFamilies ) { /// for each family
        this->_reservedQueuesForFamilies.emplace(queueFamily.getQueueFamilyIndex(), 0); /// reset reserved families count
        this->_reservedQueueIndicesForFamilies.emplace(queueFamily.getQueueFamilyIndex(), std::set< uint32 > ()); /// reset the indices reserved for each family
    }
}

#ifndef NDEBUG

auto engine::VQueueFamily::debugPrintQueueFamily( std::ostream & buffer, StringLiteral prefix ) const noexcept -> void {
    if ( this->_parentCollection->getPhysicalDevice().data() == VK_NULL_HANDLE ) {
        buffer << prefix << "Queue Family is Empty. No Physical Device Attached";
        return;
    }

    buffer << prefix << "Queue Family : \n";
    buffer << prefix << "\t" << "Physical Device Attached :                     " << this->_parentCollection->getPhysicalDevice().getPhysicalDeviceProperties().deviceName    << "\n";
    buffer << prefix << "\t" << "Queue Graphics Family (index in collection) :  " << this->_familyIndex                                                 << '\n';
    buffer << prefix << "\t" << "Queue Family Properties : \n";

    VQueueFamily::debugPrintQueueFamilyPropertiesStructure( this->_queueFamilyProperties, buffer, std::string(prefix).append("\t\t").c_str() );
}

#endif

#ifndef NDEBUG

auto engine::VQueueFamilyCollection::debugPrintQueueFamilies(
        std::ostream & buffer,
        StringLiteral prefix
) const noexcept -> void {
    for ( const auto & queueFamily : this->_queueFamilies ) {
        queueFamily.debugPrintQueueFamily(buffer, prefix);
    }
}

#endif

#ifndef NDEBUG

auto engine::VQueueFamily::debugPrintQueueFamilyPropertiesStructure(
        VulkanQueueFamilyProperties const & properties,
        std::ostream & buffer,
        StringLiteral prefix
) noexcept -> void {
    buffer << prefix << "Queue Count :                              " << properties.queueCount                           << '\n';
    buffer << prefix << "Queue Flags :                              " << properties.queueFlags                           << '\n';
    buffer << prefix << "Timestamp Valid Bits :                     " << properties.timestampValidBits                   << '\n';
    buffer << prefix << "Min Image Transfer Granularity Width :     " << properties.minImageTransferGranularity.width    << '\n';
    buffer << prefix << "Min Image Transfer Granularity Height :    " << properties.minImageTransferGranularity.height   << '\n';
    buffer << prefix << "Min Image Transfer Granularity Depth :     " << properties.minImageTransferGranularity.depth    << '\n';

    buffer << prefix << "Queue Flags Decoded : \n";
    VQueueFamily::debugPrintQueueFamilyPropertiesStructureQueueFlags( properties, buffer, std::string(prefix).append("\t").c_str() );
}

#endif

#ifndef NDEBUG
auto engine::VQueueFamily::debugPrintQueueFamilyPropertiesStructureQueueFlags(
        VulkanQueueFamilyProperties const & properties,
        std::ostream & buffer,
        StringLiteral prefix
) noexcept -> void {
    buffer << prefix << "Queue Family Graphics Capable :        " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesGraphicsBit(properties) )      << '\n' ;
    buffer << prefix << "Queue Family Compute Capable :         " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesComputeBit(properties) )       << '\n' ;
    buffer << prefix << "Queue Family Transfer Capable :        " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesTransferBit(properties) )      << '\n' ;
    buffer << prefix << "Queue Family Protected Capable :       " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesProtectedBit(properties) )     << '\n' ;
    buffer << prefix << "Queue Family Sparse Binding Capable :  " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesSparseBindingBit(properties) ) << '\n' ;
}
#endif

auto engine::VQueueFamilyCollection::getFlagsCapableQueueFamilies(VulkanQueueFlags flags) const noexcept -> std::vector < engine::VQueueFamily const * > {
    auto capableQueueFamilies = std::vector < const engine::VQueueFamily * > ();

    bool checkForPresentQueues = (bool) ( flags & engine::VQueueFamily::PRESENT_FLAG ); /// look for present queues ?
    flags &= engine::VQueueFamily::STANDARD_QUEUE_PROPERTIES_MASK; /// apply mask

    for( const auto & queueFamily : this->_queueFamilies )
        if( queueFamily.isCapableOfPropertiesFlags( flags ) ) { // / if is capable of requested flags
            if (!checkForPresentQueues) /// if looking for present capabilities
                capableQueueFamilies.push_back(&queueFamily); /// add family to the queue families returned
            else {
                if ( queueFamily.isPresentCapable() )  /// if is capable of present
                    capableQueueFamilies.push_back(&queueFamily); /// add family to the queue families returned
            }
        }

    return capableQueueFamilies;
}

auto engine::VQueueFamily::reserveQueues(uint32 targetQueueCount) const noexcept -> uint32 {
    return this->_parentCollection->reserveQueues( *this, targetQueueCount );
}

auto engine::VQueueFamily::freeQueues(uint32 targetQueueCount) const noexcept -> void {
    return this->_parentCollection->freeQueues( *this, targetQueueCount);
}

auto engine::VQueueFamily::getAvailableQueueIndex() const noexcept -> uint32 {
    return this->_parentCollection->getAvailableQueueIndex( *this );
}

auto engine::VQueueFamily::freeQueueIndex(uint32 index) const noexcept -> void {
    return this->_parentCollection->freeQueueIndex( *this, index);
}

auto engine::VQueueFamilyCollection::reserveQueues( const VQueueFamily & queueFamily, uint32 targetQueueCount ) noexcept -> uint32 {
    auto searchResult = this->_reservedQueuesForFamilies.find( queueFamily.getQueueFamilyIndex() );
    uint32 reservedQueues;

    if( searchResult == this->_reservedQueuesForFamilies.end() ) {
        reservedQueues = std::min ( queueFamily.getQueueFamilyProperties().queueCount, targetQueueCount ); /// reserve the minimum between target queue count and number of queue families
        this->_reservedQueuesForFamilies.emplace ( queueFamily.getQueueFamilyIndex(), reservedQueues );
    } else {
        uint32 availableQueues = queueFamily.getQueueFamilyProperties().queueCount - searchResult->second;
        reservedQueues = std::min ( availableQueues, targetQueueCount );

        searchResult->second += reservedQueues;
    }

    return reservedQueues;
}

auto engine::VQueueFamilyCollection::freeQueues(const VQueueFamily & queueFamily, uint32 targetQueueCount ) noexcept -> void {
    auto searchResult = this->_reservedQueuesForFamilies.find( queueFamily.getQueueFamilyIndex() );

    if( searchResult == this->_reservedQueuesForFamilies.end() ) {
        this->_reservedQueuesForFamilies.emplace( queueFamily.getQueueFamilyIndex(), 0U ); /// if no map-entry exists, do not free any, reset to 0 reserved
    } else {
        searchResult->second = ( targetQueueCount > searchResult->second ) ? ( 0U ) : ( searchResult->second - targetQueueCount ); /// set reserved count to 0, if freed more that were allocated, or reserved count - freed count
    }
}

auto engine::VQueueFamilyCollection::getAvailableQueueIndex(const VQueueFamily & queueFamily) noexcept -> uint32 {
    uint32 firstAvailableIndex = 0U;

    auto searchResult = this->_reservedQueueIndicesForFamilies.find( queueFamily.getQueueFamilyIndex() );

    if( searchResult == this->_reservedQueueIndicesForFamilies.end() )
        this->_reservedQueueIndicesForFamilies.emplace( queueFamily.getQueueFamilyIndex(), std::set < uint32 > {firstAvailableIndex} );
    else {
        while ( searchResult->second.find( firstAvailableIndex ) != searchResult->second.end() )
            firstAvailableIndex++;
        searchResult->second.insert( firstAvailableIndex );
    }

    return firstAvailableIndex;
}

auto engine::VQueueFamilyCollection::freeQueueIndex(const VQueueFamily & queueFamily, uint32 index) noexcept -> void {
    auto searchResult = this->_reservedQueueIndicesForFamilies.find( queueFamily.getQueueFamilyIndex() );

    if ( searchResult != this->_reservedQueueIndicesForFamilies.end() )
        searchResult->second.extract( index );
}

#ifndef NDEBUG

auto engine::VQueueFamily::debugPrintQueueFamilyReservation( std::ostream & buffer, StringLiteral prefix ) const noexcept -> void {
    buffer << prefix << this->_parentCollection->getReservedQueueFamiliesMap()
        .find( this->_familyIndex )
        ->second
        << " out of " << this->_queueFamilyProperties.queueCount << " queue(s) in family with index " << this->_familyIndex << " are reserved\n";
}

#endif

#ifndef NDEBUG

auto engine::VQueueFamilyCollection::debugPrintQueueFamiliesReservations(std::ostream & buffer, StringLiteral prefix) const noexcept -> void {
    buffer << prefix << "Collection queue families reservations : \n";
    for(const auto & queueFamily : this->_queueFamilies) {
        queueFamily.debugPrintQueueFamilyReservation( buffer, std::string(prefix).append("\t").c_str() );
    }
}

#endif

auto engine::VQueueFamilyCollection::getQueueFamilyIndices() const noexcept -> std::vector < uint32 > {
    std::vector < uint32 > queueFamilyIndices;

    for ( const auto & queueFamily : this->_queueFamilies )
        queueFamilyIndices.push_back( queueFamily.getQueueFamilyIndex() );

    return queueFamilyIndices;
}

auto engine::VQueueFamily::getPhysicalDevice() const noexcept -> engine::VPhysicalDevice const & {
    return this->_parentCollection->getPhysicalDevice();
}

auto engine::VQueueFamily::syncWithSurface(engine::VSurface const & surface) noexcept -> void {
    vkGetPhysicalDeviceSurfaceSupportKHR( this->_parentCollection->getPhysicalDevice().data(), this->getQueueFamilyIndex(), surface.data(), & this->_presentSupport );
}
