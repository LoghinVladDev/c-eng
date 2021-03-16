//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_VSWAPCHAIN_H
#define ENG1_VSWAPCHAIN_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/window/surface/VSurface.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/VImageView.h>
#include <vkObj/instance/pipeline/synchronization/VSemaphore.h>

#include <vector>

namespace engine {

    /// Pre-declaration of classes. Avoids circular / recursive includes
    class VSemaphore;
    class VLogicalDevice;
    class VImageViewCollection;

    /**
     * @class engine::VSwapChain
     *
     * @brief Represents the mechanism through which rendered images are passed from GPU to surface
     *
     * The Swap Chain is an Khronos Extension to the Vulkan Core API
     *
     * As though it might seem weird, there is a reason
     * Not all GPUs have methods of passing data directly to display ( there are GPUs without direct output ports; ex: HDMI, DisplayPort etc. )
     * In such cases, another image passthrough method has to be implemented
     */
    class VSwapChain {
    public:

        /**
         * @struct engine::VSwapChain::ImageInfo
         *
         * @brief Represents the Swap Chain's image-transfer properties.
         */
        typedef struct  {
            /// How the images are formatted
            VulkanFormat    format;
            /// The size of the images ( width x height )
            VulkanExtent2D  extent;
        } ImageInfo;

    private:
        //// private variables

        /// Swap Chain Handle. Swap Chain is a Khronos Vulkan Extension Object
        VulkanSwapChainKhronos          _handle         {VK_NULL_HANDLE};

        /// Logical Device Address. The Device owns and manages the Swap Chain
        const VLogicalDevice *          _device         {nullptr};

        /// Images used in transfer.
        std::vector < VulkanImage >     _images;

        /** Image-Transfer Properties
          * Initialised with : SRGB - Standard Red Green Blue
          *                    A8B8G8R8 - Alpha 8 bits, Blue 8 bits, Green 8 bits, Red 8 bits
          *                    PACK32 - packet of 32 bits per pixel. 1 byte per property (a/r/g/b)
          *                         AND
          *                    Default Extent. Will be acquired on creation
          */
        ImageInfo                       _imagesInfo     {VulkanFormat::VK_FORMAT_A8B8G8R8_SRGB_PACK32, { } };

        //// private functions

    public:
        //// public variables

        //// public functions

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         */
        VSwapChain() noexcept = default;

        /**
         * @brief Constructor Based on Logical Device Address
         *
         * Does not initialise, just checks compatibility
         *
         * @param device : engine::VLogicalDevice cptr = Address to constant Logical Device
         *
         * @throws engine::EngineVLogicalDeviceSwapChainIncompatible if
         *      Logical Device Attached as parameter is incompatible of supporting Swap Chain
         */
        explicit VSwapChain( VLogicalDevice const * ) noexcept (false);

        /**
         * @brief Enhanced Copy Constructor. Used to enforce Device's Swap Chain Ownership
         *
         * @param obj : engine::VSwapChain cref = Constant Reference to the Object to copy
         * @param device : engine::VLogicalDevice cptr = Address of a Logical Device. Used when passing the swapchain between devices
         *
         * @exceptsafe
         */
        explicit VSwapChain( VSwapChain const &, VLogicalDevice const * ) noexcept;

        /**
         * @brief Getter for Vulkan Internal Handle
         *
         * @exceptsafe
         *
         * @return VulkanSwapChainKhronos cref = Constant Reference to Swap Chain Handle
         */
        [[nodiscard]] auto data () const noexcept -> VulkanSwapChainKhronos const & {
            return this->_handle;
        }

        /**
         * @brief Getter for Swap Chain Image Info
         *
         * @exceptsafe
         *
         * @return engine::VSwapChain::ImageInfo cref = Constant Reference to Structure Containing Image Info
         */
        [[nodiscard]] auto getImagesInfo () const noexcept -> ImageInfo const & {
            return this->_imagesInfo;
        }

        /**
         * @brief Getter for the Image Handles of the Swap Chain
         *
         * @exceptsafe
         *
         * @return std::vector < VulkanImage > cref = Constant Reference to vector containing image handles of the Swap Chain's images
         */
        [[nodiscard]] auto getImages () const noexcept -> std::vector < VulkanImage > const & {
            return this->_images;
        }

        /**
         * @brief Getter for the Images of the SwapChain, in a Collection
         *
         * @exceptsafe
         *
         * @return engine::VImageViewCollection = new Collection containing Image Views of the Swap Chain
         */
        [[nodiscard]] auto getImageViewCollection () const noexcept -> engine::VImageViewCollection;

        /**
         * @brief setup function. Initialises Swap Chain
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if setup OK    OR
         *      VulkanResult::VK_ERROR_TOO_MANY_OBJECTS if Swap Chain was already initialised in this object
         */
        auto setup(  ) noexcept -> VulkanResult;

        /**
         * @brief setup function. Initialises Swap Chain on a given Logical Device
         *
         * @param device : engine::VLogicalDevice cptr = Address to Constant Logical Device
         *
         * @throws engine::VLogicalDeviceSwapChainIncompatible if
         *      Device Given is not Swap Chain Compatible
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if setup OK    OR
         *      VulkanResult::VK_ERROR_TOO_MANY_OBJECTS if Swap Chain was already initialised in this object
         */
        auto setup ( VLogicalDevice const * ) noexcept (false) -> VulkanResult;

        /**
         * @brief present Function. Will queue presentation image of given index when given semaphores have been signaled
         *
         * @param pWaitSemaphores : engine::VSemaphore cptr = Address to one Semaphore / an array of Semaphores to wait to be signaled until presenting the image
         * @param waitSemaphoreCount : uint32 = number of semaphores passed in the address above
         * @param imageIndex : uint32 = index of the image to be presented to the surface
         *
         * @exceptsafe
         *
         * @return VulkanResult =
         *      VulkanResult::VK_SUCCESS if image presentation was queued successfully OR
         *      VulkanResult::VK_ERROR_INITIALIZATION_FAILED if no present queue was found on the attached logical device
         */
        auto present ( VSemaphore const *, uint32, uint32 ) const noexcept -> VulkanResult;

        /**
         * @brief setter function for Logical Device owner
         *
         * @param device : engine::VLogicalDevice cptr = Address of Constant Logical Device
         *
         * @deprecated
         *
         * @exceptsafe
         */
        auto setLogicalDevice ( VLogicalDevice const * device ) noexcept -> void {
            if( this->_handle != nullptr )
                return;

            this->_device = device;
        }

        /**
         * @brief function that de-allocates any handles created through setup() function
         *
         * @exceptsafe
         */
        auto cleanup () noexcept -> void;

        /**
         * @brief getter function for the Logical Device Address ( object owner )
         *
         * @exceptsafe
         *
         * @return engine::VLogicalDevice cptr = Address of the parent Logical Device
         */
        [[nodiscard]] auto getDevice () const noexcept -> VLogicalDevice const * {
            return this->_device;
        }
    };

}


#endif //ENG1_VSWAPCHAIN_H
