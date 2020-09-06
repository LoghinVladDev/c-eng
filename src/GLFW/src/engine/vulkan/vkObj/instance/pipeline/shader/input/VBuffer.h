//
// Created by loghin on 9/5/20.
//

#ifndef ENG1_VBUFFER_H
#define ENG1_VBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/command/VCommandPool.h>

namespace engine {

    class VBuffer {
    private:
        //// private variables
        VulkanBuffer                        _handle             {VK_NULL_HANDLE};
        VulkanDeviceMemory                  _memoryHandle       {VK_NULL_HANDLE};
        VulkanDeviceSize                    _memorySize         {0ULL};
        const VLogicalDevice              * _pLogicalDevice     {nullptr};

        uint32                              _elementCount       {0U};

        VulkanBufferUsageFlags              _bufferUsageFlags   {VULKAN_NULL_FLAGS};
        VulkanSharingMode                   _sharingMode        {VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE};
        VulkanMemoryPropertyFlags           _memoryPropertyFlags{VULKAN_NULL_FLAGS};

        //// private functions

    protected:
        VBuffer () noexcept = default;

        void setElementCount ( uint32 elementCount ) noexcept {
            this->_elementCount = elementCount;
        }

    public:
        //// public variables
        constexpr static VulkanMemoryPropertyFlagBits MEMORY_HOST_COHERENT = VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        constexpr static VulkanMemoryPropertyFlagBits MEMORY_CPU_WRITEABLE = VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
        constexpr static VulkanMemoryPropertyFlagBits MEMORY_GPU_LOCAL     = VulkanMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

        constexpr static VulkanMemoryPropertyFlags MEMORY_CPU_BUFFER_FLAGS =
                (VulkanBufferUsageFlags) VBuffer::MEMORY_HOST_COHERENT |
                (VulkanBufferUsageFlags) VBuffer::MEMORY_CPU_WRITEABLE;

        constexpr static VulkanMemoryPropertyFlags MEMORY_GPU_BUFFER_FLAGS =
                VBuffer::MEMORY_GPU_LOCAL;

        constexpr static VulkanBufferUsageFlagBits VERTEX_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        constexpr static VulkanBufferUsageFlagBits INDEX_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        constexpr static VulkanBufferUsageFlagBits UNIFORM_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        constexpr static VulkanBufferUsageFlagBits TRANSFER_SOURCE_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        constexpr static VulkanBufferUsageFlagBits TRANSFER_DESTINATION_BUFFER = VulkanBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_DST_BIT;

        constexpr static VulkanBufferUsageFlags VERTEX_BUFFER_GPU_LOCAL =
                (VulkanBufferUsageFlags) VBuffer::VERTEX_BUFFER |
                (VulkanBufferUsageFlags) VBuffer::TRANSFER_DESTINATION_BUFFER;
        constexpr static VulkanBufferUsageFlags INDEX_BUFFER_GPU_LOCAL =
                (VulkanBufferUsageFlags) VBuffer::INDEX_BUFFER |
                (VulkanBufferUsageFlags) VBuffer::TRANSFER_DESTINATION_BUFFER;


        constexpr static VulkanBufferUsageFlags STAGING_BUFFER_CPU_LOCAL =
                VBuffer::TRANSFER_SOURCE_BUFFER;

        constexpr static VulkanBufferUsageFlags VERTEX_BUFFER_CPU_LOCAL =
                VBuffer::VERTEX_BUFFER;

        constexpr static VulkanBufferUsageFlags UNIFORM_BUFFER_CPU_LOCAL =
                VBuffer::UNIFORM_BUFFER;

        constexpr static VulkanSharingMode TRANSFER_CONCURRENCY = VulkanSharingMode::VK_SHARING_MODE_CONCURRENT;
        constexpr static VulkanSharingMode TRANSFER_EXCLUSIVITY = VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE;

        //// public functions

        [[nodiscard]] constexpr static VulkanSharingMode getOptimalSharingMode ( bool forceExclusive, uint32 queueFamilyIndexCount, const VLogicalDevice & device ) noexcept {
            return (
                forceExclusive              ||
                queueFamilyIndexCount <= 1  ||
                device.getFirstTransferQueuePtr() == nullptr
            ) ? VBuffer::TRANSFER_EXCLUSIVITY : VBuffer::TRANSFER_CONCURRENCY;
        }

        [[nodiscard]] constexpr bool isSourceBuffer () const noexcept {
            return static_cast < bool > (this->_bufferUsageFlags & static_cast < VulkanBufferUsageFlags > ( VBuffer::TRANSFER_SOURCE_BUFFER ) );
        }

        [[nodiscard]] constexpr bool isDestinationBuffer () const noexcept {
            return static_cast < bool > (this->_bufferUsageFlags & static_cast < VulkanBufferUsageFlags > ( VBuffer::TRANSFER_DESTINATION_BUFFER ) );
        }

        virtual VulkanResult setup (
            const VLogicalDevice &,
            std::size_t,
            VulkanBufferUsageFlags,
            VulkanSharingMode,
            const uint32 *,
            uint32
        ) noexcept;

        virtual VulkanResult allocateMemory (
            VulkanMemoryPropertyFlags
        ) noexcept;

        virtual VulkanResult load (
            const void *pData,
            std::size_t
        ) noexcept;

        virtual void free() noexcept;
        virtual void cleanup() noexcept;
        VulkanResult copyFrom ( const VBuffer &, const VCommandPool &, VulkanDeviceSize = 0U ) noexcept;

        [[nodiscard]] const VulkanBuffer & data () const noexcept {
            return this->_handle;
        }

        [[nodiscard]] VulkanDeviceSize size () const noexcept {
            return this->_memorySize;
        }

        [[nodiscard]] VulkanBufferUsageFlags getBufferUsageFlags () const noexcept {
            return this->_bufferUsageFlags;
        }

        [[nodiscard]] uint32 getElementCount () const noexcept {
            return this->_elementCount;
        }

        [[nodiscard]] VulkanSharingMode getBufferSharingMode () const noexcept {
            return this->_sharingMode;
        }
    };

}


#endif //ENG1_VBUFFER_H
