//
// Created by Vlad on 07/09/2020.
//

#ifndef ENG1_VUNIFORMBUFFER_H
#define ENG1_VUNIFORMBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/input/VBuffer.h>
#include <glm/glm.hpp>

namespace engine {

    typedef struct {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    } SUniformBufferObject;

    template <class T>
    class VUniformBuffer : public VBuffer {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables

        //// public functions
        VUniformBuffer () noexcept = default;

        VulkanResult setup (
            const VLogicalDevice &,
            uint32
        ) noexcept;

        [[nodiscard]] const std::vector <T> & getBufferData () const noexcept {
            return this->_data;
        }

        [[nodiscard]] std::vector <T> & getBufferData () noexcept {
            return this->_data;
        }

        VulkanResult allocateMemory () noexcept;

        VulkanResult load ( const T*, uint32 ) noexcept;

        void free () noexcept override;
        void cleanup () noexcept override;
    };

}

template <class T>
VulkanResult engine::VUniformBuffer<T>::setup(
    const VLogicalDevice & device,
    uint32 size
) noexcept {
    return VBuffer::setup(
        device,
        static_cast < std::size_t > ( size * sizeof ( T ) ),
        VBuffer::UNIFORM_BUFFER_CPU_LOCAL,
        VBuffer::TRANSFER_EXCLUSIVITY,
        nullptr,
        0U
    );
}

template <class T>
VulkanResult engine::VUniformBuffer<T>::allocateMemory() noexcept {
    return VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
}

template <class T>
VulkanResult engine::VUniformBuffer<T>::load(const T * pValues, uint32 valueCount) noexcept {
    return VBuffer::load(
        static_cast < const void * > ( pValues ),
        static_cast < std::size_t >  ( valueCount * sizeof ( T ) )
    );
}

template <class T>
void engine::VUniformBuffer<T>::free() noexcept {
    return VBuffer::free();
}

template <class T>
void engine::VUniformBuffer<T>::cleanup() noexcept {
    return VBuffer::cleanup();
}




#endif //ENG1_VUNIFORMBUFFER_H
