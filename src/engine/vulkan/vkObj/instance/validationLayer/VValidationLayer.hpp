//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_VVALIDATIONLAYER_HPP
#define ENG1_VVALIDATIONLAYER_HPP

#include <VRenderObject.hpp>

#include <vector>

#ifdef NDEBUG
    constexpr bool enableValidationLayers = false;
#else
    constexpr bool enableValidationLayers = true;
#endif

namespace engine {

    class VValidationLayerCollection;

    class VValidationLayer : public VRenderObject {
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

        using VulkanValidationLayerLiteral = char const *;

        using VulkanLayerDebugFunctionCallbackPointer = VkBool32 ( * ) (
            VulkanDebugMessageSeverityFlagBits,
            VulkanDebugMessageTypeFlags,
            VulkanDebugMessengerCallbackData const * ,
            void *
        );

    private:
        //// private vars
        static bool                                     _layersQueried;
        static std::vector < VulkanLayerProperties >    _availableValidationLayers;
        static VulkanLayerDebugFunctionCallbackPointer  _debugFunctionPtr;

        VulkanValidationLayerLiteral                    _literal    {nullptr};

        ////private functions
        static auto queryAvailableValidationLayers() noexcept -> void;
    public:
        //// public vars

        //// public functions
        VValidationLayer() noexcept : VRenderObject() {
            VValidationLayer::queryAvailableValidationLayers();
        }

        explicit VValidationLayer(VulkanValidationLayer layerType) noexcept : VRenderObject() {
            VValidationLayer::queryAvailableValidationLayers();
            this->setLayerType(layerType);
        }

        ~VValidationLayer() noexcept override = default;

        [[nodiscard]] constexpr auto getLiteral() const noexcept -> VulkanValidationLayerLiteral {
            return this->_literal;
        }

        auto setLayerType (VulkanValidationLayer layer ) noexcept -> VValidationLayer &;

        [[nodiscard]] static auto checkValidationLayerSupport( VValidationLayerCollection const & ) noexcept -> bool;
        static auto debugPrintAvailableValidationLayers(std::ostream &) noexcept -> void;

        auto clear () noexcept -> void override {}

        [[nodiscard]] auto toString () const noexcept -> String override {
            return String("VValidationLayer { ") +
                "literal = " + this->_literal + " }";
        }

        [[nodiscard]] auto copy () const noexcept -> VValidationLayer * override {
            return new VValidationLayer(*this);
        }

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) return false;

            return std::strcmp ( this->_literal, p->_literal ) == 0;
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return String(this->_literal).hash();
        }
    };

    class VValidationLayerCollection : public VRenderObject {
    private:
        //// private vars
        std::vector < VValidationLayer > _validationLayers;

        //// private functions

    public:
        //// public vars

        //// public functions
        VValidationLayerCollection() noexcept = default;
        VValidationLayerCollection( std::initializer_list < VValidationLayer > const & ) noexcept;
        VValidationLayerCollection( std::initializer_list < VValidationLayer::VulkanValidationLayer > const & ) noexcept;

        ~VValidationLayerCollection() noexcept override = default;

        auto addValidationLayer( VValidationLayer const & ) noexcept -> VValidationLayerCollection &;

        [[nodiscard]] constexpr auto getValidationLayers() const noexcept -> std::vector < VValidationLayer > const & {
            return this->_validationLayers;
        }

        [[nodiscard]] auto getValidationLayerLiterals() const noexcept -> std::vector < VValidationLayer::VulkanValidationLayerLiteral >;

        auto clear() noexcept -> void override {
            this->_validationLayers.clear();
        }

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast<decltype(this)>(&o);
            if ( p == nullptr ) return false;

            return p->_validationLayers == this->_validationLayers;
        }

        [[nodiscard]] auto copy () const noexcept -> VValidationLayerCollection * override {
            return new VValidationLayerCollection(*this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            Index hashSum = 0;
            std::for_each(this->_validationLayers.begin(), this->_validationLayers.end(), [&hashSum](auto const & e){hashSum += e.hash();});
            return hashSum;
        }
    };
}



#endif //ENG1_VVALIDATIONLAYER_HPP
