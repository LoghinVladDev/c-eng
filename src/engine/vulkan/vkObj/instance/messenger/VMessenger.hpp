//
// Created by vladl on 06/08/2020.
//

#ifndef ENG1_VMESSENGER_HPP
#define ENG1_VMESSENGER_HPP

#include <VRenderObject.hpp>
#include <VInstance.hpp>
#include <exception>
#include <CDS/String>

namespace engine {

    /// pre-declaration of class to avoid circular / recursive includes
    class VInstance;

    /**
     * @class engine::EngineVMessengerProvideVInstance, inherits std::exception
     *
     * @brief Thrown When a Messenger is created without a Vulkan Instance
     */
    class EngineVMessengerProvideVInstance : public std::exception {
    public:

        /**
         * @brief Getter function for exception message
         *
         * @exceptsafe
         *
         * @return String Literal = Exception Message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "A VInstance must be provided to the messenger, either on construct or by passing in setInstance";
        };
    };

    /**
     * @class engine::VMessenger, derived from VRenderObject
     *
     * VRenderObject derivation might not seem ideal at first, but remember that VMessenger is primarily
     *      the ValidationLayer error callback and will be extended to GPU printf
     *
     * @brief Represents the Debug Messenger. Contains the callback ( and callback passthrough ) of Vulkan Errors and Vulkan Validation Layer Errors
     *
     * The Debug Messenger is a Vulkan Core API extension. If Validation Layers exist, Messenger Extension exists
     */
    class VMessenger : public VRenderObject {
    private:
        //// private variables

        /// Vulkan Handler for the Messenger
        VulkanDebugMessenger    _debugMessenger {nullptr};

        /// Address to Instance the Debug attaches to
        engine::VInstance      * _vulkanInstance {nullptr};

        //// private functions

    public:
        //// public variables

        /// default message severity filter
        constexpr static VulkanFlags DEFAULT_DEBUG_MESSAGE_SEVERITY =
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | /// notes
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | /// warnings
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;    /// errors

        /// default message type filter
        constexpr static VulkanFlags DEFAULT_DEBUG_MESSAGE_TYPE =
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |     /// general messages
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |  /// validation layer messages
                (VulkanFlags) VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;  /// performance issues messages

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VMessenger() noexcept = default;

        /**
         * @brief Constructor based off of an Instance
         *
         * @param instance : engine::VInstance ptr = Address of Vulkan Instance
         *
         * @exceptsafe
         */
        explicit VMessenger( engine::VInstance * instance ) noexcept : VRenderObject() {
            this->_vulkanInstance = instance;
        }

        /**
         * @brief Setter for the Instance
         *
         * @param instance : engine::VInstance ptr = Address of Vulkan Instance
         *
         * @deprecated
         *
         * @exceptsafe
         *
         * @return engine::VMessenger ref = Reference to Modified Object
         */
        auto setInstance( engine::VInstance * instance ) noexcept -> VMessenger & {
            this->_vulkanInstance = instance;
            return * this;
        }

        /**
         * @brief setup function for the messenger. Binds it to Instance
         *
         * @throws engine::EngineVMessengerProvideVInstance if
         *      Instance given to Messenger or that existed before setup is Invalid
         *
         * @return VulkanResult::VK_SUCCESS if Messenger was Initialised OK OR
         * @return VulkanResult different from VulkanResult::VK_SUCCESS returned by createDebugMessengerExtension - vulkan function
         */
        auto setup ( engine::VInstance * = nullptr ) noexcept (false) -> VulkanResult;

        /**
         * @brief Getter for Messenger Vulkan Handle
         *
         * @exceptsafe
         *
         * @return VulkanDebugMessenger cref = Constant Reference to Vulkan Handle
         */
        [[nodiscard]] constexpr auto data() const noexcept -> VulkanDebugMessenger const & {
            return this->_debugMessenger;
        }

        /**
         * @brief Function used to de-allocate Vulkan Handle
         *
         * @exceptsafe
         */
        auto clear() noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & o );
            if ( p == nullptr ) return false;

            return this->_debugMessenger == p->_debugMessenger;
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(reinterpret_cast<AddressValueType>(this->_debugMessenger));
        }

        [[nodiscard]] auto copy () const noexcept -> VMessenger * override {
            return new VMessenger(* this);
        }
    };

}


#endif //ENG1_VMESSENGER_HPP
