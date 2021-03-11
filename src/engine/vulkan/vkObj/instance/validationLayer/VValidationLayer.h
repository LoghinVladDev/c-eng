//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_VVALIDATIONLAYER_H
#define ENG1_VVALIDATIONLAYER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>

#include <vector>

#ifdef NDEBUG
    constexpr bool enableValidationLayers = false;
#else
    constexpr bool enableValidationLayers = true;
#endif

namespace engine {

    class VValidationLayerCollection;

    class VValidationLayer {
    public:
        //// TODO : define more eventually
        typedef enum {
            LUNARG_API_DUMP,
            LUNARG_DEVICE_SIMULATION,
            LUNARG_GFX_RECONSTRUCT,
            LUNARG_MONITOR,
            LUNARG_SCREENSHOT,
            LUNARG_STANDARD_VALIDATION,

            KHRONOS_VALIDATION,

            NVIDIA_OPTIMUS,
            OBS_HOOK,

            GALAXY_OVERLAY,
            GALAXY_OVERLAY_VERBOSE,
            GALAXY_OVERLAY_DEBUG,

            STEAM_OVERLAY,
            STEAM_PIPELINE,

            EPIC_ONLINE_SERVICES_OVERLAY,

            ROCKSTAR_GAMES_SOCIAL_CLUB_OVERLAY
        } VulkanValidationLayer;

        typedef char const * VulkanValidationLayerLiteral;

        typedef VkBool32 ( * VulkanLayerDebugFunctionCallbackPointer ) (
            VulkanDebugMessageSeverityFlagBits,
            VulkanDebugMessageTypeFlags,
            const VulkanDebugMessengerCallbackData * ,
            void *
        );

    private:
        //// private vars
        static bool _layersQueried;
        static std::vector < VulkanLayerProperties > _availableValidationLayers;
        static VulkanLayerDebugFunctionCallbackPointer _debugFunctionPtr;

        VulkanValidationLayerLiteral _literal    {nullptr};

        ////private functions
        static void queryAvailableValidationLayers() noexcept;
    public:
        //// public vars

        //// public functions
        VValidationLayer()   noexcept {
            VValidationLayer::queryAvailableValidationLayers();
        }

        explicit VValidationLayer(VulkanValidationLayer layerType) noexcept {
            VValidationLayer::queryAvailableValidationLayers();
            this->setLayerType(layerType);
        }

        ~VValidationLayer()  noexcept = default;

        [[nodiscard]] VulkanValidationLayerLiteral getLiteral() const noexcept {
            return this->_literal;
        }

        VValidationLayer& setLayerType (VulkanValidationLayer layer ) noexcept;

        [[nodiscard]] static bool checkValidationLayerSupport( const VValidationLayerCollection & ) noexcept;
        static void debugPrintAvailableValidationLayers(std::ostream&) noexcept;
    };

    class VValidationLayerCollection {
    private:
        //// private vars
        std::vector < VValidationLayer > _validationLayers;

        //// private functions

    public:
        //// public vars

        //// public functions
        VValidationLayerCollection() noexcept = default;
        VValidationLayerCollection( const std::initializer_list < VValidationLayer > & ) noexcept;
        VValidationLayerCollection( const std::initializer_list < VValidationLayer::VulkanValidationLayer > & ) noexcept;

        VValidationLayerCollection& addValidationLayer( const VValidationLayer & ) noexcept;

        [[nodiscard]] const std::vector < VValidationLayer > & getValidationLayers() const noexcept {
            return this->_validationLayers;
        }

        [[nodiscard]] std::vector < VValidationLayer::VulkanValidationLayerLiteral > getValidationLayerLiterals() const noexcept;

        void clear() noexcept {
            this->_validationLayers.clear();
        }
    };
}



#endif //ENG1_VVALIDATIONLAYER_H
