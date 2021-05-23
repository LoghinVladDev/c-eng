//
// Created by vladl on 05/08/2020.
//

#include "VValidationLayer.hpp"
#include <cstring>
#include <vkDefs/VInstanceDefinitions.h>

bool engine::VValidationLayer::_layersQueried = false;

std::vector < VulkanLayerProperties > engine::VValidationLayer::_availableValidationLayers = std::vector < VulkanLayerProperties > ();

auto engine::VValidationLayer::debugPrintAvailableValidationLayers(std::ostream& buffer) noexcept -> void {
    VValidationLayer::queryAvailableValidationLayers();
    buffer << "Available Validation Layers : \n";

    for( const auto & validationLayer : VValidationLayer::_availableValidationLayers ) {
        buffer << "\tName : " << validationLayer.layerName << '\n';
        buffer << "\t\tDescription : " << validationLayer.description << '\n';
        buffer << "\t\tImplementation Version : " << validationLayer.implementationVersion << '\n';
        buffer << "\t\tSpecification Version : " << validationLayer.specVersion << '\n';
    }
}

static auto getValidationLayerLiteral(engine::VValidationLayer::VulkanValidationLayer layer ) noexcept -> engine::VValidationLayer::VulkanValidationLayerLiteral {
    switch ( layer ) {

        case engine::VValidationLayer::LUNARG_API_DUMP:                      return __VULKAN_LAYER_LUNARG_API_DUMP;
        case engine::VValidationLayer::LUNARG_DEVICE_SIMULATION:             return __VULKAN_LAYER_DEVICE_SIMULATION;
        case engine::VValidationLayer::LUNARG_GFX_RECONSTRUCT:               return __VULKAN_LAYER_GFX_RECONSTRUCT_CAPTURE;
        case engine::VValidationLayer::LUNARG_MONITOR:                       return __VULKAN_LAYER_LUNARG_EXECUTION_MONITOR;
        case engine::VValidationLayer::LUNARG_SCREENSHOT:                    return __VULKAN_LAYER_LUNARG_IMAGE_CAPTURE;
        case engine::VValidationLayer::LUNARG_STANDARD_VALIDATION:           return __VULKAN_LAYER_LUNARG_STANDARD_VALIDATION;
        case engine::VValidationLayer::KHRONOS_VALIDATION:                   return __VULKAN_LAYER_KHRONOS_GROUP_VALIDATION;
        case engine::VValidationLayer::NVIDIA_OPTIMUS:                       return __VULKAN_LAYER_NVIDIA_OPTIMUS;
        case engine::VValidationLayer::OBS_HOOK:                             return __VULKAN_LAYER_OBS_HOOK;
        case engine::VValidationLayer::GALAXY_OVERLAY:                       return __VULKAN_LAYER_GOG_GALAXY_OVERLAY;
        case engine::VValidationLayer::GALAXY_OVERLAY_VERBOSE:               return __VULKAN_LAYER_GOG_GALAXY_OVERLAY_VERBOSE;
        case engine::VValidationLayer::GALAXY_OVERLAY_DEBUG:                 return __VULKAN_LAYER_GOG_GALAXY_OVERLAY_DEBUG;
        case engine::VValidationLayer::STEAM_OVERLAY:                        return __VULKAN_LAYER_VALVE_STEAM_OVERLAY;
        case engine::VValidationLayer::STEAM_PIPELINE:                       return __VULKAN_LAYER_VALVE_STEAM_PIPELINE;
        case engine::VValidationLayer::EPIC_ONLINE_SERVICES_OVERLAY:         return __VULKAN_LAYER_EPIC_ONLINE_SERVICES;
        case engine::VValidationLayer::ROCKSTAR_GAMES_SOCIAL_CLUB_OVERLAY:   return __VULKAN_LAYER_ROCKSTAR_GAMES_SOCIAL_CLUB;

        default:                                                            return __VULKAN_LAYER_UNDEFINED;
    }
}

auto engine::VValidationLayer::setLayerType(VulkanValidationLayer layer) noexcept -> engine::VValidationLayer &  {
    this->_literal = getValidationLayerLiteral( layer );
    return *this;
}

auto engine::VValidationLayerCollection::addValidationLayer( engine::VValidationLayer const & layer) noexcept -> engine::VValidationLayerCollection & {
    for( const auto & existingLayer : this->_validationLayers ) {
        if( std::strcmp( layer.getLiteral(), existingLayer.getLiteral() ) == 0 ) {
            return *this;
        }
    }

    this->_validationLayers.push_back( layer );

    return *this;
}

auto engine::VValidationLayer::queryAvailableValidationLayers() noexcept -> void {
    if( VValidationLayer::_layersQueried )
        return;

    uint32 layerCount;

    vkEnumerateInstanceLayerProperties( & layerCount, nullptr );

    VValidationLayer::_availableValidationLayers = std::vector < VulkanLayerProperties > (layerCount );
    vkEnumerateInstanceLayerProperties(& layerCount, VValidationLayer::_availableValidationLayers.data() );

    VValidationLayer::_layersQueried = true;
}

engine::VValidationLayerCollection::VValidationLayerCollection(const std::initializer_list < engine::VValidationLayer > & list) noexcept : VRenderObject() {
    for( const auto & layer : list ) {
        this->addValidationLayer( layer );
    }
}

engine::VValidationLayerCollection::VValidationLayerCollection(const std::initializer_list<VValidationLayer::VulkanValidationLayer> & list) noexcept : VRenderObject() {
    for( const auto & layerType : list ) {
        this->addValidationLayer( engine::VValidationLayer(layerType ) );
    }
}

[[nodiscard]] auto engine::VValidationLayerCollection::getValidationLayerLiterals() const noexcept -> std::vector < engine::VValidationLayer::VulkanValidationLayerLiteral > {
    std::vector < engine::VValidationLayer::VulkanValidationLayerLiteral > layerLiterals;

    for ( const auto & layer : this->_validationLayers ) {
        layerLiterals.push_back( layer.getLiteral() );
    }

    return layerLiterals;
}

[[nodiscard]] auto engine::VValidationLayer::checkValidationLayerSupport(const VValidationLayerCollection & layerCollection) noexcept -> bool {
    VValidationLayer::queryAvailableValidationLayers();

    for ( const auto & layer : layerCollection.getValidationLayers() ) {
        bool layerFound = false;

        for( const auto & availableLayer : VValidationLayer::_availableValidationLayers ) {
            if( std::strcmp( layer.getLiteral(), availableLayer.layerName ) == 0 ) {
                layerFound = true;
                break;
            }
        }

        if( ! layerFound )
            return false;
    }

    return true;
}

#include <sstream>

auto engine::VValidationLayerCollection::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "VValidationLayerCollection = { layers = [ ";

    for (const auto &item : this->_validationLayers)
        oss << item.toString() << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}