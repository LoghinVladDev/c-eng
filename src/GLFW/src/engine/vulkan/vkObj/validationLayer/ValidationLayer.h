//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_VALIDATIONLAYER_H
#define ENG1_VALIDATIONLAYER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>

#include <vector>

#ifdef NDEBUG
    constexpr bool enableValidationLayers = false;
#else
    constexpr bool enableValidationLayers = true;
#endif

namespace engine {

    class ValidationLayerCollection;

    class ValidationLayer {
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

        typedef const int8* VulkanValidationLayerLiteral;

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
        ValidationLayer()   noexcept {
            ValidationLayer::queryAvailableValidationLayers();
        }

        ~ValidationLayer()  noexcept = default;

        [[nodiscard]] VulkanValidationLayerLiteral getLiteral() const noexcept {
            return this->_literal;
        }

        ValidationLayer& setLayerType ( VulkanValidationLayer layer ) noexcept;

        [[nodiscard]] static VulkanLayerDebugFunctionCallbackPointer getValidationLayerDebugCallbackFunctionPointer() noexcept {
            return ValidationLayer::_debugFunctionPtr;
        }

        [[nodiscard]] static bool checkValidationLayerSupport( const ValidationLayerCollection & ) noexcept;
        static void debugPrintAvailableValidationLayers() noexcept;
    };

    class ValidationLayerCollection {
    private:
        //// private vars
        std::vector < ValidationLayer > _validationLayers;

        //// private functions

    public:
        //// public vars

        //// public functions
        ValidationLayerCollection() noexcept = default;
        ValidationLayerCollection( const std::initializer_list < ValidationLayer > & ) noexcept;

        ValidationLayerCollection& addValidationLayer( const ValidationLayer & ) noexcept;

        [[nodiscard]] const std::vector < ValidationLayer > & getValidationLayers() const noexcept {
            return this->_validationLayers;
        }

        [[nodiscard]] std::vector < ValidationLayer::VulkanValidationLayerLiteral > getValidationLayerLiterals() const noexcept;

        void clear() noexcept {
            this->_validationLayers.clear();
        }
    };
}



#endif //ENG1_VALIDATIONLAYER_H
