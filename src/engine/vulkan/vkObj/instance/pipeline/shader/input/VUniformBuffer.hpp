//
// Created by Vlad on 07/09/2020.
//

#ifndef ENG1_VUNIFORMBUFFER_HPP
#define ENG1_VUNIFORMBUFFER_HPP

#include <VLogicalDevice.hpp>
#include <VBuffer.hpp>
//#include <glm/glm.hpp>

namespace engine {

    typedef struct {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    } SUniformBufferObject;
//
//    typedef struct {
//        glm::mat4 view;
//        glm::mat4 projection;
//    } SUniformBufferCamera;

    template <class T>
    class VUniformBuffer : public VBuffer {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables

        //// public functions
        VUniformBuffer () noexcept = default;
        ~VUniformBuffer() noexcept override = default;

        auto setup (
            VLogicalDevice const &,
            uint32
        ) noexcept -> VulkanResult;

        [[nodiscard]] constexpr auto getBufferData () const noexcept -> std::vector <T> const & {
            return this->_data;
        }

        [[nodiscard]] constexpr auto getBufferData () noexcept -> std::vector <T> & {
            return this->_data;
        }

        auto allocateMemory () noexcept -> VulkanResult;

        auto load ( T const *, uint32 ) noexcept -> VulkanResult;

        auto free () noexcept -> void override;
        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override {
            return VBuffer::toString();
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return VBuffer::hash();
        }

        [[nodiscard]] auto copy () const noexcept -> VUniformBuffer * override {
            return new VUniformBuffer(* this);
        }

        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            return VBuffer::operator==(o);
        }
    };

}

template <class T>
auto engine::VUniformBuffer<T>::setup(
    VLogicalDevice const & device,
    uint32 size
) noexcept -> VulkanResult {
    this->setElementCount( size );
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
auto engine::VUniformBuffer<T>::allocateMemory() noexcept -> VulkanResult {
    return VBuffer::allocateMemory( VBuffer::MEMORY_CPU_BUFFER_FLAGS );
}

template <class T>
auto engine::VUniformBuffer<T>::load(T const * pValues, uint32 valueCount) noexcept -> VulkanResult {
    return VBuffer::load(
        static_cast < void const * > ( pValues ),
        static_cast < std::size_t >  ( valueCount * sizeof ( T ) )
    );
}

template <class T>
auto engine::VUniformBuffer<T>::free() noexcept -> void {
    return VBuffer::free();
}

template <class T>
auto engine::VUniformBuffer<T>::clear() noexcept -> void {
    return VBuffer::clear();
}




#endif //ENG1_VUNIFORMBUFFER_HPP
