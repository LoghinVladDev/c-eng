//
// Created by vladl on 05/08/2020.
//

#include "VValidationLayer.hpp"
#include <cstring>
#include <vkDefs/VInstanceDefinitions.h>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

bool VValidationLayer :: _layersQueried = false;

std :: vector < VulkanLayerProperties > VValidationLayer :: _availableValidationLayers = std::vector < VulkanLayerProperties > ();

auto VValidationLayer :: debugPrintAvailableValidationLayers (
        std :: ostream & buffer
) noexcept -> void {

    VValidationLayer :: queryAvailableValidationLayers();
    buffer << "Available Validation Layers : \n";

    for( const auto & validationLayer : VValidationLayer::_availableValidationLayers ) {
        buffer << "\tName : "                       << String ( validationLayer.layerName ) << '\n';
        buffer << "\t\tDescription : "              << String ( validationLayer.description ) << '\n';
        buffer << "\t\tImplementation Version : "   << validationLayer.implementationVersion << '\n';
        buffer << "\t\tSpecification Version : "    << validationLayer.specVersion << '\n';
    }
}

static auto getValidationLayerLiteral (
        VValidationLayer :: VulkanValidationLayer layer
) noexcept -> VValidationLayer :: VulkanValidationLayerLiteral {

    switch ( layer ) {

        case VValidationLayer :: LUNARG_API_DUMP:                      return __VULKAN_LAYER_LUNARG_API_DUMP;             // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: LUNARG_DEVICE_SIMULATION:             return __VULKAN_LAYER_DEVICE_SIMULATION;           // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: LUNARG_GFX_RECONSTRUCT:               return __VULKAN_LAYER_GFX_RECONSTRUCT_CAPTURE;     // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: LUNARG_MONITOR:                       return __VULKAN_LAYER_LUNARG_EXECUTION_MONITOR;    // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: LUNARG_SCREENSHOT:                    return __VULKAN_LAYER_LUNARG_IMAGE_CAPTURE;        // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: LUNARG_STANDARD_VALIDATION:           return __VULKAN_LAYER_LUNARG_STANDARD_VALIDATION;  // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: KHRONOS_VALIDATION:                   return __VULKAN_LAYER_KHRONOS_GROUP_VALIDATION;    // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: NVIDIA_OPTIMUS:                       return __VULKAN_LAYER_NVIDIA_OPTIMUS;              // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: OBS_HOOK:                             return __VULKAN_LAYER_OBS_HOOK;                    // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: GALAXY_OVERLAY:                       return __VULKAN_LAYER_GOG_GALAXY_OVERLAY;          // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: GALAXY_OVERLAY_VERBOSE:               return __VULKAN_LAYER_GOG_GALAXY_OVERLAY_VERBOSE;  // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: GALAXY_OVERLAY_DEBUG:                 return __VULKAN_LAYER_GOG_GALAXY_OVERLAY_DEBUG;    // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: STEAM_OVERLAY:                        return __VULKAN_LAYER_VALVE_STEAM_OVERLAY;         // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: STEAM_PIPELINE:                       return __VULKAN_LAYER_VALVE_STEAM_PIPELINE;        // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: EPIC_ONLINE_SERVICES_OVERLAY:         return __VULKAN_LAYER_EPIC_ONLINE_SERVICES;        // NOLINT(clion-misra-cpp2008-6-4-5)
        case VValidationLayer :: ROCKSTAR_GAMES_SOCIAL_CLUB_OVERLAY:   return __VULKAN_LAYER_ROCKSTAR_GAMES_SOCIAL_CLUB;  // NOLINT(clion-misra-cpp2008-6-4-5)

        default:                                                       return __VULKAN_LAYER_UNDEFINED;                    // NOLINT(clion-misra-cpp2008-6-4-5)
    }
}

auto VValidationLayer :: setLayerType (
        VulkanValidationLayer layer
) noexcept -> VValidationLayer & {

    this->_literal = getValidationLayerLiteral( layer );
    return * this;
}

auto VValidationLayerCollection :: addValidationLayer(
        VValidationLayer const & layer
) noexcept -> VValidationLayerCollection & {

    for( auto const & existingLayer : this->_validationLayers ) {
        if( std::strcmp( layer.getLiteral(), existingLayer.getLiteral() ) == 0 ) {
            return * this;
        }
    }

    this->_validationLayers.push_back( layer );

    return *this;
}

auto VValidationLayer :: queryAvailableValidationLayers() noexcept -> void {
    if( VValidationLayer::_layersQueried ) {
        return;
    }

    uint32 layerCount;

    (void) vkEnumerateInstanceLayerProperties( & layerCount, nullptr );

    VValidationLayer::_availableValidationLayers = std::vector < VulkanLayerProperties > (layerCount );
    (void) vkEnumerateInstanceLayerProperties( & layerCount, VValidationLayer::_availableValidationLayers.data() );

    VValidationLayer::_layersQueried = true;
}

__CDS_MaybeUnused VValidationLayerCollection :: VValidationLayerCollection (
        std :: initializer_list < VValidationLayer > const & list
) noexcept :
        VRenderObject() {

    for ( auto const & layer : list ) {
        (void) this->addValidationLayer( layer );
    }
}

__CDS_MaybeUnused VValidationLayerCollection :: VValidationLayerCollection (
        std :: initializer_list < VValidationLayer :: VulkanValidationLayer > const & list
) noexcept :
        VRenderObject() {

    for ( auto const & layerType : list ) {
        (void) this->addValidationLayer( VValidationLayer(layerType ) );
    }
}

__CDS_NoDiscard auto VValidationLayerCollection :: getValidationLayerLiterals() const noexcept -> std :: vector < VValidationLayer :: VulkanValidationLayerLiteral > {
    std::vector < VValidationLayer :: VulkanValidationLayerLiteral > layerLiterals;

    for ( auto const & layer : this->_validationLayers ) {
        layerLiterals.push_back( layer.getLiteral() );
    }

    return layerLiterals;
}

__CDS_NoDiscard auto VValidationLayer :: checkValidationLayerSupport (
        VValidationLayerCollection const & layerCollection
) noexcept -> bool {

    VValidationLayer :: queryAvailableValidationLayers();

    for ( auto const & layer : layerCollection.getValidationLayers() ) {
        bool layerFound = false;

        for ( auto const & availableLayer : VValidationLayer::_availableValidationLayers ) {
            if ( std::strcmp ( layer.getLiteral(), availableLayer.layerName ) == 0 ) { // NOLINT(clion-misra-cpp2008-5-2-12)
                layerFound = true;
                break;
            }
        }

        if( ! layerFound ) {
            return false;
        }
    }

    return true;
}

#include <sstream>

auto VValidationLayerCollection :: toString() const noexcept -> String {

    std::stringstream oss;
    oss << "VValidationLayerCollection = { layers = [ ";

    for ( auto const & item : this->_validationLayers ) {
        oss << item.toString() << ", ";
    }

    auto s = oss.str();
    return s.substr(s.size() - 2U).append(" ]}");
}