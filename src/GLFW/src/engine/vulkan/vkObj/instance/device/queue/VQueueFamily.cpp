//
// Created by vladl on 08/08/2020.
//

#include "VQueueFamily.h"
#include <vkUtils/VStdUtils.h>

void engine::VQueueFamilyCollection::queryAvailableQueueFamilies( ) noexcept {
    uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties( this->_physicalDevice.data(), & queueFamilyCount, nullptr );

    std::vector < VulkanQueueFamilyProperties > queueFamiliesProperties ( queueFamilyCount );
    vkGetPhysicalDeviceQueueFamilyProperties( this->_physicalDevice.data(), & queueFamilyCount, queueFamiliesProperties.data() );

    for (const auto & queueFamilyProperties : queueFamiliesProperties) {
        this->_queueFamilies.emplace_back( this->_physicalDevice, queueFamilyProperties );
    }
}

#ifndef NDEBUG

void engine::VQueueFamily::debugPrintQueueFamily( std::ostream& buffer, const char* prefix ) const noexcept {
    if ( this->_physicalDevice == nullptr ) {
        buffer << prefix << "Queue Family is Empty. No Physical Device Attached";
        return;
    }

    buffer << prefix << "Queue Family : \n";
    buffer << prefix << "\t" << "Physical Device Attached : " << this->_physicalDevice->getPhysicalDeviceProperties().deviceName << "\n";
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

    //VK_QUEUE_TRANSFER_BIT
    //VK_QUEUE_GRAPHICS_BIT
    //VK_QUEUE_COMPUTE_BIT
    //VK_QUEUE_PROTECTED_BIT
    //VK_QUEUE_SPARSE_BINDING_BIT
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