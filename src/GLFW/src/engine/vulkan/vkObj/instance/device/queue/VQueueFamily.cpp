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
    for ( const auto & queueFamily : this->_queueFamilies )
        this->_reservedQueuesForFamilies.emplace( queueFamily.getQueueFamilyIndex(), 0 );
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

[[nodiscard]] std::vector < engine::VQueueFamily > engine::VQueueFamilyCollection::getFlagsCapableQueueFamilies(VulkanQueueFlags flags) const noexcept {
    auto capableQueueFamilies = std::vector < engine::VQueueFamily > ();

    for( const auto & queueFamily : this->_queueFamilies )
        if( queueFamily.queueFamilyIsCapableOf( flags ) )
            capableQueueFamilies.push_back( queueFamily );

    return capableQueueFamilies;
}

[[nodiscard]] uint32 engine::VQueueFamily::reserveQueues(uint32 targetQueueCount) const noexcept {
    return this->_parentCollection->reserveQueues( *this, targetQueueCount );
}

void engine::VQueueFamily::freeQueues(uint32 targetQueueCount) const noexcept {
    return this->_parentCollection->freeQueues( *this, targetQueueCount);
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