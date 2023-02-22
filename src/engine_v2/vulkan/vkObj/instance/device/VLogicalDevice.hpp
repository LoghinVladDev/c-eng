//
// Created by Vlad on 10/08/2020.
//

#ifndef ENG1_VLOGICALDEVICE_HPP
#define ENG1_VLOGICALDEVICE_HPP

#include <VRenderObject.hpp>
#include <VQueueFamily.hpp>
#include <cstring>
#include <VValidationLayer.hpp>
#include <VQueue.hpp>
#include <VExtension.hpp>

namespace engine {

    /**
     * Predeclare VQueue, VSwapChain, VImageViewCollection to avoid
     * circular importing
     */
    class VQueue;
    class VSwapChain;
    class VImageViewCollection;

    /**
     * @class engine::EngineFactoryInvalidSwapChain, inherits std::exception
     *
     * @brief throws when no valid Surface is given to LogicalDevice Creation
     */
    class EngineVLogicalDeviceFactoryInvalidSwapChain : public std::exception {
    public:

        /**
         * @brief getter function for the Exception Message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Exception Message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Given Swap Chain is not configured with a proper surface";
        }
    };

    /**
     * @class engine::EngineVLogicalDeviceQueuePhysicalDeviceMismatch, inherits std::exception
     *
     * @brief throws when Queue Families Specified are not obtained from the Physical Device attached
     */
    class EngineVLogicalDeviceQueuePhysicalDeviceMismatch : public std::exception {
    public:

        /**
         * @brief getter function for the Exception Message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Exception Message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Queue families attached are from a separate physical device";
        }
    };

    /**
     * @class engine::EngineVLogicalDeviceSwapChainIncompatible, inherits std::exception
     *
     * @brief throws when given a Physical Device incapable of Vulkan Operations
     */
    class EngineVLogicalDeviceSwapChainIncompatible : public std::exception {
    public:

        /**
         * @brief getter function for the Exception Message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Exception Message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Swap Chain Failed to Configure. Either Device is Incompatible or Instantiation Failed";
        }
    };

    /**
     * @class engine::EngineVLogicalDeviceUnsupportedExtension, inherits std::exception
     *
     * @brief throws when given an Exception that is not supported by the Physical Device
     */
    class EngineVLogicalDeviceUnsupportedExtension : public std::exception {
    private:
        /// Message of the exception
        std::string _message;
    public:

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        EngineVLogicalDeviceUnsupportedExtension () noexcept {
            this->_message = "Physical Device given to Logical Device Factory does not support given Extension";
        }

        /**
         * @brief Constructor with attached Extension that has caused the issue
         *
         * @param problematicExtension : engine::VExtension cref = Reference to the Extension that is incompatible
         *
         * @exceptsafe
         */
        explicit EngineVLogicalDeviceUnsupportedExtension ( VExtension const & problematicExtension ) noexcept {
            this->_message = std::string("Physical Device given to Logical Device Factory does not support given Extension : { Name : ")
                    .append(problematicExtension.getName())
                    .append(", spec version : ")
                    .append(std::to_string(problematicExtension.getSpecVersion()))
                    .append("} ");
        }

        /**
         * @brief getter function for the Exception Message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Exception Message
         */
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return this->_message.c_str();
        }
    };

    /**
     * @class engine::VLogicalDevice
     *
     * @brief Represents a Physical Device with Interface for Drawing Operations - SwapChain, ImageViews, Queues etc
     *
     * Physical Device = GPU
     * SwapChain = Delivery Mechanism for Images from GPU to Screen Surface
     * ImageViews - Image that is Delivered
     * Queues - Transfer Buses of Images and Data
     */
    class VLogicalDevice : public VRenderObject {
    private:
        //// private variables

        /// workaround variable for a default queue priority that is adjustable
        static float _internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY;

        /// Vulkan Handle for the Logical Device
        VulkanDevice                        _vulkanDevice               {};

        /// Queues Owned and Used by this Object
        std::vector < VQueue >              _queues;

        /// Variable specifying whether device can operate a Swap Chain or not
        bool                                _swapChainAdequate          {false};

        /// CPtr to a Validation Layer Collection to get Layers from
        VValidationLayerCollection  const *  _validationLayerCollection  {nullptr};

        /// An Extension Collection to get Extensions from
        VExtensionCollection                _enabledExtensions;

        /// CPtr to the surface to print on
        VSurface                    const *  _surfacePtr                 {nullptr};

        /// CPtr to the Logical Device ( GPU )
        VPhysicalDevice             const *  _physicalDevice             {nullptr};

        /// Ptr to the created swap chain
        VSwapChain                        *  _swapChain                  {nullptr};

        /// Ptr to the Image View Collection
        VImageViewCollection              *  _imageViewCollection        {nullptr};

        //// private functions

        /**
         * @brief Private setup function used by the Logical Device Factory to setup the created Device
         *
         * @param physicalDevice : engine::PhysicalDevice cref = Reference to the Base Physical Device
         *
         * @throws engine::EngineVLogicalDeviceQueuePhysicalDeviceMismatch if
         *      given Queue Families to the Builder do not come from the given Physical Device
         * @throws engine::EngineVLogicalDeviceSwapChainIncompatible if
         *      this object is not able to produce a swap chain, extension not present
         *
         * @return VulkanResult::VK_SUCCESS if Logical Device setup was successful OR
         * @return VulkanResult returned from vkCreateDevice - Internal Vulkan Function - different from VulkanResult::VK_SUCCESS OR
         * @return VulkanResult::VK_ERROR_TOO_MANY_OBJECTS if a SwapChain already existed on the Logical Device
         * @return VulkanResult returned from vkCreateImageView - Internal Vulkan Function - different from VulkanResult::VK_SUCCESS
         */
        auto setup( VPhysicalDevice const & ) noexcept (false) -> VulkanResult;

        /**
         * @brief Private setup function used by the Logical Device Factory to setup the Queues
         *
         * Assigns the Queues from the QueueFamilies given
         *
         * @exceptsafe
         */
        auto setupQueues () noexcept -> void;
    public:

        /**
         * @class engine::VLogicalDevice::Factory
         *
         * @brief Factory Pattern Class for Logical Devices, used as they have a lot of parameters to set up
         */
        class [[maybe_unused]] Factory : public VObject {
        private:
            //// private variables

            /// variable used to enable exceptions thrown by the Factory
            static bool                         _exceptionsToggle;

            /// CPtr to the Validation Layer Collection
            VValidationLayerCollection const *  _validationLayerCollection  {nullptr};

            /// Queues that will be attached to the device
            std::vector < VQueue >              _queues;

            /// Extensions that will be enabled on the device
            VExtensionCollection                _extensions;

            /// CPtr to the Surface that the Device's Swap Chain will Present on
            VSurface                   const *  _surface                    {nullptr};

        public:
            //// public variables

            //// public functions

            /**
             * @brief function used to enable/disable exceptions globally on device factory
             *
             * @param toggle : bool = if true, enables exceptions, if false, disables them
             *
             * @static
             *
             * @exceptsafe
             */
            static auto setExceptionEnableStatus ( bool toggle ) noexcept -> void {
                VLogicalDevice::Factory::_exceptionsToggle = toggle;
            }

            /**
             * @brief function used to enable exceptions globally on device factory
             *
             * @static
             *
             * @exceptsafe
             */
            static auto enableExceptions ( ) noexcept -> void {
                VLogicalDevice::Factory::_exceptionsToggle = true;
            }

            /**
             * @brief function used to disable exceptions globally on device factory
             *
             * @static
             *
             * @exceptsafe
             */
            static auto disableExceptions ( ) noexcept -> void {
                VLogicalDevice::Factory::_exceptionsToggle = false;
            }

            /**
             * @brief add validation layers to the current device in-build
             *
             * @param collection : engine::VValidationLayerCollection cref = Reference to validation layer collection
             *
             * @exceptsafe
             *
             * @return engine::VLogicalDevice::Factory ref = Reference to newly modified object
             */
            auto withValidationLayers ( VValidationLayerCollection const & collection ) noexcept -> Factory & {
                this->_validationLayerCollection = ( & collection );
                return *this;
            }

            /**
             * @brief function adds a Queue to the current in-build object
             *
             * @param queueFamily : engine::VQueueFamily cref = Reference to the Queue Family to allocate a Queue from
             * @param priority : float = Priority of the Operations done on this Queue
             *
             * @throws engine::EngineVQueueFamilyNoQueuesAvailable if
             *      exceptions are enabled AND did not manage to reserve any queues from the Physical Device
             *
             * @return engine::VLogicalDevice::Factory ref = Reference to the newly modified object
             */
            auto addQueue ( VQueueFamily const &, float = _internal_explicitWrapper_DEFAULT_QUEUE_PRIORITY) noexcept (false) -> Factory &;

            /**
             * @brief function adds multiple Queues to the current in-build object
             *
             * @param queueFamily : engine::VQueueFamily cref = Reference to the Queue Family to allocate Queues from
             * @param queueCount : uint32 = Number of Queues to allocate on this Device
             * @param priorities : float cptr ( array ) = Array of priorities, each having a value for a queue, representing the priority of said queue
             *
             * If priorities is nullptr (default value), all queues allocated are created with maximum priority
             *
             * @throws engine::EngineVQueueFamilyNoQueuesAvailable if
             *      exceptions are enabled AND did not manage to reserve the specified number of queues desired from the Physical Device
             *
             * @return engine::VLogicalDevice::Factory ref = Reference to the newly modified object
             */
            auto addQueues ( VQueueFamily const &, uint32, const float * = nullptr ) noexcept (false) -> Factory &;

            /**
             * @brief function adds an Extension to the in-build Device
             *
             * @param extension : engine::VExtension cref = Reference to the Extension to be added
             *
             * @exceptsafe
             *
             * @return engine::VLogicalDevice::Factory ref = Reference to the newly modified object
             */
            auto addExtension ( VExtension const & ) noexcept ->  Factory &;

            /**
             * @brief function adds multiple Extensions to the in-build Device
             *
             * @param collection : engine::VExtensionCollection cref = Reference to the Extension Collection to be added
             *
             * @exceptsafe
             *
             * @return engine::VLogicalDevice::Factory ref = Reference to the newly modified object
             */
            auto addExtensions ( VExtensionCollection const & ) noexcept -> Factory &;

            /**
             * @brief function adds a surface ptr to create the swapchain to
             *
             * @param surface : engine::VSurface cptr = Constant Address to the Surface to pass to the Swap Chain
             *
             * @exceptsafe
             *
             * @return engine::VLogicalDevice::Factory ref = Reference to the newly modified object
             */
            auto createSwapChainToSurface ( VSurface const * ) noexcept -> Factory &;

            /**
             * @brief function builds the Logical Device with the parameters specified to the factory
             *
             * @param physicalDevice : engine::VPhysicalDevice cref = Reference to the Physical Device to build the Logical Device from
             *
             * @throws engine::EngineVLogicalDeviceUnsupportedExtension if
             *          exceptions are enabled and given extension to the builder is not supported by the physical device
             *
             * @return VLogicalDevice = newly built logical device
             */
            auto build ( VPhysicalDevice const & ) noexcept (false) -> VLogicalDevice;

            /**
             * @brief Destructor for the factory, defaulted
             *
             * @exceptsafe
             */
            ~Factory() noexcept override = default;

            [[nodiscard]] auto toString () const noexcept -> String override;
            [[nodiscard]] auto operator == (Factory const &) const noexcept -> bool;
            [[nodiscard]] auto equals (Object const &) const noexcept -> bool override;
            [[nodiscard]] auto hash () const noexcept -> Index override;
            [[nodiscard]] auto copy () const noexcept -> Factory * override;
        };

        //// public variables

        //// public functions

        /**
         * @brief Constructor for Logical Device, defaulted
         *
         * @exceptsafe
         */
        VLogicalDevice ( ) noexcept = default;

        /**
         * @brief Copy Constructor for Logical Device, required as it has internal allocated memory
         *
         * @param obj : engine::VLogicalDevice cref = Constant Reference to the Logical Device to copy
         *
         * @exceptsafe
         */
        VLogicalDevice ( VLogicalDevice const & ) noexcept;

        /**
         * @brief Operator = overload for Logical Device, required as it has internal allocated memory
         *
         * @param obj : engine::VLogicalDevice cref = Constant Reference to the Logical Device to copy
         *
         * @overload
         *
         * @exceptsafe
         *
         * @return engine::VLogicalDevice ref = Reference to the newly modified object
         */
        VLogicalDevice & operator = ( VLogicalDevice const & ) noexcept;

        /**
         * @brief getter function for the first Queue capable of Present Operations
         *
         * @exceptsafe
         *
         * @return engine::VQueue cptr = Address to Constant Queue allocated to the Logical Device
         */
        [[nodiscard]] auto getFirstPresentQueuePtr () const noexcept -> VQueue const *;

        /**
         * @brief getter function for the first Queue capable of Graphics Operations
         *
         * @exceptsafe
         *
         * @return engine::VQueue cptr = Address to Constant Queue allocated to the Logical Device
         */
        [[nodiscard]] auto getFirstGraphicsQueuePtr () const noexcept -> VQueue const *;

        /**
         * @brief getter function for the first Queue capable of Transfer Operations
         *
         * @exceptsafe
         *
         * @return engine::VQueue cptr = Address to Constant Queue allocated to the Logical Device
         */
        [[nodiscard]] auto getFirstTransferQueuePtr () const noexcept -> VQueue const *;

        /**
         * @brief getter function for the Address of the Physical Device used by the Logical Device
         *
         * @exceptsafe
         *
         * @return engine::VPhysicalDevice cptr = Address to Constant Physical Device
         */
        [[nodiscard]] auto getBasePhysicalDevice () const noexcept -> VPhysicalDevice const * {
            return this->_physicalDevice;
        }

        /**
         * @brief getter for Surface used by Swap Chain
         *
         * @exceptsafe
         *
         * @return engine::VSurface cptr = Address of Surface OR
         *                                 nullptr if device does not have a swap chain configured
         */
        [[nodiscard]] auto getSwapChainSurface() const noexcept -> VSurface const * {
            return this->_surfacePtr;
        }

        /**
         * @brief getter for Swap Chain on the Logical Device
         *
         * @exceptsafe
         *
         * @return engine::VSwapChain cptr = Address of Swap Chain OR
         *                                   nullptr if device does not have a swap chain configured
         */
        [[nodiscard]] auto getSwapChain() const noexcept -> VSwapChain const * {
            return this->_swapChain;
        }

        /**
         * @brief getter for Image View Collection used by Swap Chain
         *
         * @exceptsafe
         *
         * @return engine::VImageViewCollection cptr = Address of Image View Collection OR
         *                                             nullptr if device does not have a swap chain configured
         */
        [[nodiscard]] auto getImageViewCollection () const noexcept -> VImageViewCollection const * {
            return this->_imageViewCollection;
        }

        /**
         * @brief getter for the Queue array, queues used by Logical Device
         *
         * @exceptsafe
         *
         * @return std::vector < engine::VQueue > cref = Constant Reference to vector of Queues
         */
        [[nodiscard]] auto getQueues() const noexcept -> std::vector < VQueue > const & {
            return this->_queues;
        }

        /**
         * @brief getter for the queue families of the Queues allocated to Logical Device
         *
         * @exceptsafe
         *
         * @return std::set < engine::VQueueFamily cptr > = Vector of Addresses to Constant Queue Family
         */
        [[nodiscard]] auto getQueueFamilies () const noexcept -> std::set < VQueueFamily const * >;

        /**
         * @brief getter for the queue family indices of the Queues allocated to Logical Device
         *
         * @exceptsafe
         *
         * @return std::vector < uint32 > = Vector of indices of QueueFamily of Queues
         */
        [[nodiscard]] auto getQueueFamilyIndices () const noexcept -> std::vector < uint32 >;

        /**
         * @brief getter for Vulkan Handler of Logical Device
         *
         * @exceptsafe
         *
         * @return VulkanDevice cref = Reference to Handler
         */
        [[nodiscard]] constexpr auto data() const noexcept -> VulkanDevice const & {
            return this->_vulkanDevice;
        }

        /**
         * @brief getter function for swapChainAdequate property
         *
         * @exceptsafe
         *
         * @return true if Logical Device can have a Swap Chain, false otherwise
         */
        [[nodiscard]] constexpr auto isSwapChainAdequate () const noexcept -> bool {
            return this->_swapChainAdequate;
        }

        /**
         * @brief function used to cleanup the swapchain of the Device
         *
         * @exceptsafe
         */
        auto cleanupSwapChain () noexcept -> void;

        /**
         * @brief function used to recreate the swapchain of the device
         *
         * @exceptsafe
         *
         * @return VulkanResult::VK_SUCCESS if recreation was successful                                        OR
         * @return VulkanResult::VK_ERROR_TOO_MANY_OBJECTS if Logical Device has a SwapChain configured already OR
         * @return Return Value of vkCreateImageView - internal Vulkan function - if it is not VulkanResult::VK_SUCCESS
         */
        auto recreateSwapChain () noexcept -> VulkanResult;

        /**
         * @brief function used to cleanup the Logical Device
         *
         * @exceptsafe
         */
        auto clear () noexcept -> void override;

        /**
         * @brief destructor of Logical Device
         *
         * @exceptsafe
         */
        ~VLogicalDevice() noexcept override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (VLogicalDevice const &) const noexcept -> bool;
        [[nodiscard]] auto equals (Object const &) const noexcept -> bool override;
        [[nodiscard]] auto hash () const noexcept -> Index override;
        [[nodiscard]] auto copy () const noexcept -> VLogicalDevice * override;
    };

}


#endif //ENG1_VLOGICALDEVICE_HPP
