//
// Created by vladl on 08/08/2020.
//

#include "VQueueFamily.h"
#include <vkUtils/VStdUtils.h>

void engine::VQueueFamilyCollection::queryAvailableQueueFamilies( ) noexcept (false) {
    if ( this->_physicalDevice->data() == VK_NULL_HANDLE )
        throw engine::EngineNullVPhysicalDevice();

    uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties( this->_physicalDevice->data(), & queueFamilyCount, nullptr );

    std::vector < VulkanQueueFamilyProperties > queueFamiliesProperties ( queueFamilyCount );
    vkGetPhysicalDeviceQueueFamilyProperties( this->_physicalDevice->data(), & queueFamilyCount, queueFamiliesProperties.data() );

    uint32 queueGraphicsFamily = 0;
    for (const auto & queueFamilyProperties : queueFamiliesProperties)
        this->_queueFamilies.emplace_back( this, queueFamilyProperties, queueGraphicsFamily++ );
}

void engine::VQueueFamilyCollection::unReserveAllQueueFamilies() noexcept(false) {
    for ( const auto & queueFamily : this->_queueFamilies ) {
        this->_reservedQueuesForFamilies.emplace(queueFamily.getQueueFamilyIndex(), 0);
        this->_reservedQueueIndicesForFamilies.emplace(queueFamily.getQueueFamilyIndex(), std::set< uint32 > ());
    }
}

#ifndef NDEBUG

void engine::VQueueFamily::debugPrintQueueFamily( std::ostream& buffer, const char* prefix ) const noexcept {
    if ( this->_parentCollection->getPhysicalDevice().data() == VK_NULL_HANDLE ) {
        buffer << prefix << "Queue Family is Empty. No Physical Device Attached";
        return;
    }

    buffer << prefix << "Queue Family : \n";
    buffer << prefix << "\t" << "Physical Device Attached :                     " << this->_parentCollection->getPhysicalDevice().getPhysicalDeviceProperties().deviceName    << "\n";
    buffer << prefix << "\t" << "Queue Graphics Family (index in collection) :  " << this->_familyIndex                                                 << '\n';
    buffer << prefix << "\t" << "Queue Family Properties : \n";

    VQueueFamily::debugPrintQueueFamilyPropertiesStructure( this->_queueFamilyProperties, buffer, std::string(prefix).append("\t\t").c_str() );
//    buffer << prefix << "\t\t" << this->_queueFamilyProperties.
}

#endif

#ifndef NDEBUG

void engine::VQueueFamilyCollection::debugPrintQueueFamilies( std::ostream& buffer, const char* prefix ) const noexcept {
    for ( const auto & queueFamily : this->_queueFamilies ) {
        queueFamily.debugPrintQueueFamily(buffer, prefix);
    }
}

#endif

#ifndef NDEBUG

void engine::VQueueFamily::debugPrintQueueFamilyPropertiesStructure(const VulkanQueueFamilyProperties & properties,std::ostream & buffer, const char * prefix) noexcept {
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
void engine::VQueueFamily::debugPrintQueueFamilyPropertiesStructureQueueFlags(const VulkanQueueFamilyProperties & properties,std::ostream & buffer, const char * prefix) noexcept {
    buffer << prefix << "Queue Family Graphics Capable :        " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesGraphicsBit(properties) )      << '\n' ;
    buffer << prefix << "Queue Family Compute Capable :         " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesComputeBit(properties) )       << '\n' ;
    buffer << prefix << "Queue Family Transfer Capable :        " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesTransferBit(properties) )      << '\n' ;
    buffer << prefix << "Queue Family Protected Capable :       " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesProtectedBit(properties) )     << '\n' ;
    buffer << prefix << "Queue Family Sparse Binding Capable :  " << VStandardUtils::constexprBoolAlpha ( VQueueFamily::queueFamilyPropertiesSparseBindingBit(properties) ) << '\n' ;
}
#endif

[[nodiscard]] std::vector < const engine::VQueueFamily* > engine::VQueueFamilyCollection::getFlagsCapableQueueFamilies(VulkanQueueFlags flags) const noexcept {
    auto capableQueueFamilies = std::vector < const engine::VQueueFamily * > ();

    bool checkForPresentQueues = (bool) ( flags & engine::VQueueFamily::PRESENT_FLAG );
    flags &= engine::VQueueFamily::STANDARD_QUEUE_PROPERTIES_MASK;

    for( const auto & queueFamily : this->_queueFamilies )
        if( queueFamily.isCapableOfPropertiesFlags( flags ) ) {
            if (!checkForPresentQueues)
                capableQueueFamilies.push_back(&queueFamily);
            else {
//                std::cout << queueFamily.getQueueFamilyIndex() << ", present cap : " << queueFamily.isPresentCapable() << '\n';
                if ( queueFamily.isPresentCapable() )
                    capableQueueFamilies.push_back(&queueFamily);
            }
        }

    return capableQueueFamilies;
}

[[nodiscard]] uint32 engine::VQueueFamily::reserveQueues(uint32 targetQueueCount) const noexcept {
    return this->_parentCollection->reserveQueues( *this, targetQueueCount );
}

void engine::VQueueFamily::freeQueues(uint32 targetQueueCount) const noexcept {
    return this->_parentCollection->freeQueues( *this, targetQueueCount);
}

[[nodiscard]] uint32 engine::VQueueFamily::getAvailableQueueIndex() const noexcept {
    return this->_parentCollection->getAvailableQueueIndex( *this );
}

void engine::VQueueFamily::freeQueueIndex(uint32 index) const noexcept {
    return this->_parentCollection->freeQueueIndex( *this, index);
}

[[nodiscard]] uint32 engine::VQueueFamilyCollection::reserveQueues( const VQueueFamily & queueFamily, uint32 targetQueueCount ) noexcept {
    auto searchResult = this->_reservedQueuesForFamilies.find( queueFamily.getQueueFamilyIndex() );
    uint32 reservedQueues;

    if( searchResult == this->_reservedQueuesForFamilies.end() ) {
        reservedQueues = std::min ( queueFamily.getQueueFamilyProperties().queueCount, targetQueueCount );
        this->_reservedQueuesForFamilies.emplace ( queueFamily.getQueueFamilyIndex(), reservedQueues );
    } else {
        uint32 availableQueues = queueFamily.getQueueFamilyProperties().queueCount - searchResult->second;
        reservedQueues = std::min ( availableQueues, targetQueueCount );

        searchResult->second += reservedQueues;
    }

    return reservedQueues;
}

void engine::VQueueFamilyCollection::freeQueues(const VQueueFamily & queueFamily, uint32 targetQueueCount ) noexcept {
    auto searchResult = this->_reservedQueuesForFamilies.find( queueFamily.getQueueFamilyIndex() );

    if( searchResult == this->_reservedQueuesForFamilies.end() ) {
        this->_reservedQueuesForFamilies.emplace( queueFamily.getQueueFamilyIndex(), 0U );
    } else {
        searchResult->second = ( targetQueueCount > searchResult->second ) ? ( 0U ) : ( searchResult->second - targetQueueCount );
    }
}

[[nodiscard]] uint32 engine::VQueueFamilyCollection::getAvailableQueueIndex(const VQueueFamily & queueFamily) noexcept {
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

void engine::VQueueFamilyCollection::freeQueueIndex(const VQueueFamily & queueFamily, uint32 index) noexcept {
    auto searchResult = this->_reservedQueueIndicesForFamilies.find( queueFamily.getQueueFamilyIndex() );

    if ( searchResult != this->_reservedQueueIndicesForFamilies.end() )
        searchResult->second.extract( index );
}

#ifndef NDEBUG

void engine::VQueueFamily::debugPrintQueueFamilyReservation( std::ostream& buffer, const char* prefix ) const noexcept {
    buffer << prefix << this->_parentCollection->getReservedQueueFamiliesMap()
        .find( this->_familyIndex )
        ->second
        << " out of " << this->_queueFamilyProperties.queueCount << " queue(s) in family with index " << this->_familyIndex << " are reserved\n";
}

#endif

#ifndef NDEBUG

void engine::VQueueFamilyCollection::debugPrintQueueFamiliesReservations(std::ostream & buffer, const char * prefix) const noexcept {
    buffer << prefix << "Collection queue families reservations : \n";
    for(const auto & queueFamily : this->_queueFamilies) {
        queueFamily.debugPrintQueueFamilyReservation( buffer, std::string(prefix).append("\t").c_str() );
    }
}

#endif

const engine::VPhysicalDevice & engine::VQueueFamily::getPhysicalDevice() const noexcept {
    return this->_parentCollection->getPhysicalDevice();
}

void engine::VQueueFamily::syncWithSurface(const engine::VSurface & surface) noexcept {
    vkGetPhysicalDeviceSurfaceSupportKHR( this->_parentCollection->getPhysicalDevice().data(), this->getQueueFamilyIndex(), surface.data(), & this->_presentSupport );
}
