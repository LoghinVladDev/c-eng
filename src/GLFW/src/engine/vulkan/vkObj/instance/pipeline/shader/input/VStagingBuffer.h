//
// Created by loghin on 9/5/20.
//

#ifndef ENG1_VSTAGINGBUFFER_H
#define ENG1_VSTAGINGBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/input/VVertex.h>
#include <vkObj/instance/pipeline/shader/input/VBuffer.h>

namespace engine {

    template < class T >
    class VStagingBuffer : public VBuffer {
        friend class VVertexBuffer;
        friend class VIndexBuffer16;
        friend class VIndexBuffer32;
    private:
        //// private variables
        std::vector < T > _data;

        //// private functions 

    public:
        //// public variables
        VStagingBuffer () noexcept = default;

        VulkanResult setup (
            const VLogicalDevice &,
            const std::vector < T > &,
            VulkanSharingMode = VBuffer::TRANSFER_EXCLUSIVITY,
            const uint32 * = nullptr,
            uint32 = 0U
        ) noexcept;

        VulkanResult setup (
            const VLogicalDevice &,
            uint32,
            VulkanSharingMode = VBuffer::TRANSFER_EXCLUSIVITY,
            const uint32 * = nullptr,
            uint32 = 0U
        ) noexcept;

        VulkanResult allocateMemory () noexcept;

        VulkanResult reload () noexcept;

        [[nodiscard]] const std::vector < T > & getBufferData () const noexcept {
            return this->_data;
        }

        [[nodiscard]] std::vector < T > & getBufferData () noexcept {
            return this->_data;
        }

        void free () noexcept override;
        void cleanup () noexcept override;

        //// public functions

    };

}

template <class T>
void engine::VStagingBuffer<T>::free() noexcept {
    return VBuffer::free();
}

template <class T>
void engine::VStagingBuffer<T>::cleanup() noexcept {
    return VBuffer::cleanup();
}

template <class T>
VulkanResult engine::VStagingBuffer<T>::allocateMemory() noexcept {
    VulkanResult allocateResult = VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    return this->reload();
}

template <class T>
VulkanResult engine::VStagingBuffer<T>::reload() noexcept {
    return VBuffer::load(
        static_cast < const void * > ( this->_data.data() ),
        static_cast < std::size_t > ( this->_data.size() * sizeof ( T ) )
    );
}

template <class T>
VulkanResult engine::VStagingBuffer<T>::setup(
    const VLogicalDevice  & device,
    uint32                  size,
    VulkanSharingMode       sharingMode,
    const uint32          * pQueueFamilyIndices,
    uint32                  queueFamilyIndexCount
) noexcept {
    this->_data.resize ( size );
    this->setElementCount( size );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( sizeof ( T ) * size ),
        VBuffer::STAGING_BUFFER_CPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}

template <class T>
VulkanResult engine::VStagingBuffer<T>::setup(
    const VLogicalDevice & device,
    const std::vector<T> & data,
    VulkanSharingMode      sharingMode,
    const uint32         * pQueueFamilyIndices,
    uint32                 queueFamilyIndexCount
) noexcept {
    this->_data = data;
    this->setElementCount( data.size() );

    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( sizeof ( T ) * data.size() ),
        VBuffer::STAGING_BUFFER_CPU_LOCAL,
        sharingMode,
        pQueueFamilyIndices,
        queueFamilyIndexCount
    );
}


#endif //ENG1_VSTAGINGBUFFER_H
