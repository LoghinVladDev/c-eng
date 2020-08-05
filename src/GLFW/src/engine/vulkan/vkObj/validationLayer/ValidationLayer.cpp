//
// Created by vladl on 05/08/2020.
//

#include "ValidationLayer.h"
#include <cstring>
#include <vkDefs/vkDefinitions.h>

bool engine::ValidationLayer::_layersQueried = false;

std::vector < VulkanLayerProperties > engine::ValidationLayer::_availableValidationLayers = std::vector < VulkanLayerProperties > ();

static VULKAN_API_ATTRIBUTE VulkanBool32 VULKAN_API_CALL staticLayerDebugCallback(
    VulkanDebugMessageSeverityFlagBits          messageSeverity,
    VulkanDebugMessageTypeFlags                 messageType,
    const VulkanDebugMessengerCallbackData     *callbackDataPtr,
    void                                       *userDataPtr
) {

    if( messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT ) {
        std::cerr << "[LAYER DEBUG CALLBACK] validation layer: " << callbackDataPtr->pMessage << '\n';
    }

    return VULKAN_FALSE;
}

engine::ValidationLayer::VulkanLayerDebugFunctionCallbackPointer engine::ValidationLayer::_debugFunctionPtr = staticLayerDebugCallback;

void engine::ValidationLayer::debugPrintAvailableValidationLayers() noexcept {
    ValidationLayer::queryAvailableValidationLayers();
    std::cout << "Available Validation Layers : \n";

    for( const auto & validationLayer : ValidationLayer::_availableValidationLayers ) {
        std::cout << "\tName : " << validationLayer.layerName << '\n';
        std::cout << "\t\tDescription : " << validationLayer.description << '\n';
        std::cout << "\t\tImplementation Version : " << validationLayer.implementationVersion << '\n';
        std::cout << "\t\tSpecification Version : " << validationLayer.specVersion << '\n';
    }
}

static engine::ValidationLayer::VulkanValidationLayerLiteral getValidationLayerLiteral( engine::ValidationLayer::VulkanValidationLayer layer ) noexcept {
    switch ( layer ) {

        case engine::ValidationLayer::LUNARG_API_DUMP:                      return __VULKAN_LAYER_LUNARG_API_DUMP;
        case engine::ValidationLayer::LUNARG_DEVICE_SIMULATION:             return __VULKAN_LAYER_DEVICE_SIMULATION;
        case engine::ValidationLayer::LUNARG_GFX_RECONSTRUCT:               return __VULKAN_LAYER_GFX_RECONSTRUCT_CAPTURE;
        case engine::ValidationLayer::LUNARG_MONITOR:                       return __VULKAN_LAYER_LUNARG_EXECUTION_MONITOR;
        case engine::ValidationLayer::LUNARG_SCREENSHOT:                    return __VULKAN_LAYER_LUNARG_IMAGE_CAPTURE;
        case engine::ValidationLayer::LUNARG_STANDARD_VALIDATION:           return __VULKAN_LAYER_LUNARG_STANDARD_VALIDATION;
        case engine::ValidationLayer::KHRONOS_VALIDATION:                   return __VULKAN_LAYER_KHRONOS_GROUP_VALIDATION;
        case engine::ValidationLayer::NVIDIA_OPTIMUS:                       return __VULKAN_LAYER_NVIDIA_OPTIMUS;
        case engine::ValidationLayer::OBS_HOOK:                             return __VULKAN_LAYER_OBS_HOOK;
        case engine::ValidationLayer::GALAXY_OVERLAY:                       return __VULKAN_LAYER_GOG_GALAXY_OVERLAY;
        case engine::ValidationLayer::GALAXY_OVERLAY_VERBOSE:               return __VULKAN_LAYER_GOG_GALAXY_OVERLAY_VERBOSE;
        case engine::ValidationLayer::GALAXY_OVERLAY_DEBUG:                 return __VULKAN_LAYER_GOG_GALAXY_OVERLAY_DEBUG;
        case engine::ValidationLayer::STEAM_OVERLAY:                        return __VULKAN_LAYER_VALVE_STEAM_OVERLAY;
        case engine::ValidationLayer::STEAM_PIPELINE:                       return __VULKAN_LAYER_VALVE_STEAM_PIPELINE;
        case engine::ValidationLayer::EPIC_ONLINE_SERVICES_OVERLAY:         return __VULKAN_LAYER_EPIC_ONLINE_SERVICES;
        case engine::ValidationLayer::ROCKSTAR_GAMES_SOCIAL_CLUB_OVERLAY:   return __VULKAN_LAYER_ROCKSTAR_GAMES_SOCIAL_CLUB;

        default:                                                            return __VULKAN_LAYER_UNDEFINED;
    }
}

engine::ValidationLayer& engine::ValidationLayer::setLayerType(VulkanValidationLayer layer) noexcept {
    this->_literal = getValidationLayerLiteral( layer );
    return *this;
}

engine::ValidationLayerCollection& engine::ValidationLayerCollection::addValidationLayer( const engine::ValidationLayer& layer) noexcept {
    for( const auto & existingLayer : this->_validationLayers ) {
        if( std::strcmp( layer.getLiteral(), existingLayer.getLiteral() ) == 0 ) {
            return *this;
        }
    }

    this->_validationLayers.push_back( layer );

    return *this;
}

void engine::ValidationLayer::queryAvailableValidationLayers() noexcept {
    if( ValidationLayer::_layersQueried )
        return;
    else
        ValidationLayer::_layersQueried = true;

    uint32 layerCount;

    vkEnumerateInstanceLayerProperties( & layerCount, nullptr );

    ValidationLayer::_availableValidationLayers = std::vector < VulkanLayerProperties > ( layerCount );
    vkEnumerateInstanceLayerProperties( & layerCount, ValidationLayer::_availableValidationLayers.data() );
}

engine::ValidationLayerCollection::ValidationLayerCollection(const std::initializer_list < engine::ValidationLayer > & list) noexcept {
    for( const auto & layer : list ) {
        this->addValidationLayer( layer );
    }
}

[[nodiscard]] std::vector < engine::ValidationLayer::VulkanValidationLayerLiteral > engine::ValidationLayerCollection::getValidationLayerLiterals() const noexcept {
    std::vector < engine::ValidationLayer::VulkanValidationLayerLiteral > layerLiterals;

    for ( const auto & layer : this->_validationLayers ) {
        layerLiterals.push_back( layer.getLiteral() );
    }

    return layerLiterals;
}

[[nodiscard]] bool engine::ValidationLayer::checkValidationLayerSupport(const ValidationLayerCollection & layerCollection) noexcept {
    ValidationLayer::queryAvailableValidationLayers();

    for ( const auto & layer : layerCollection.getValidationLayers() ) {
        bool layerFound = false;

        for( const auto & availableLayer : ValidationLayer::_availableValidationLayers ) {
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