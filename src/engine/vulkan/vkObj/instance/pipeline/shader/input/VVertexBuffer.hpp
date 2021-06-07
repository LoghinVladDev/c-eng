//
// Created by vladl on 8/30/2020.
//

#ifndef ENG1_VVERTEXBUFFER_HPP
#define ENG1_VVERTEXBUFFER_HPP

#include <VLogicalDevice.hpp>
#include <VVertex.hpp>
#include <VBuffer.hpp>
#include <VStagingBuffer.hpp>

namespace engine {

    class VVertexBuffer : public VBuffer {
    private:
        //// private variables
        VStagingBuffer < VVertex::SVertexPack >         _stagingBuffer;
        VCommandPool                            const * _pCommandPool   {nullptr};

        //// private functions

    public:
        //// public variables
        //// public functions
        VVertexBuffer () noexcept = default;
        ~VVertexBuffer() noexcept override = default;

        auto setup (
            VLogicalDevice          const &,
            std::vector < VVertex > const &,
            VCommandPool            const *,
            uint32                  const * = nullptr,
            uint32                          = 0U,
            bool                            = false
        ) noexcept -> VulkanResult;

        auto setup (
            VLogicalDevice                          const &,
            std::vector < VVertex::SVertexPack >    const &,
            VCommandPool                            const *,
            uint32                                  const * = nullptr,
            uint32                                          = 0U,
            bool                                            = false
        ) noexcept -> VulkanResult;

        auto setup (
            VLogicalDevice  const &,
            uint32,
            VCommandPool    const *,
            uint32          const * = nullptr,
            uint32                  = 0U,
            bool                    = false
        ) noexcept -> VulkanResult;

        auto load (
            std::vector < VVertex > const &
        ) noexcept -> VulkanResult;

        auto load (
            std::vector < VVertex::SVertexPack > const &
        ) noexcept -> VulkanResult;

        auto flush () noexcept -> VulkanResult;

        auto allocateMemory () noexcept -> VulkanResult;

        [[nodiscard]] constexpr auto getBufferData () const noexcept -> std::vector < VVertex::SVertexPack > const & {
            return this->_stagingBuffer._data;
        }

        [[nodiscard]] constexpr auto getBufferData () noexcept -> std::vector < VVertex::SVertexPack > & {
            return this->_stagingBuffer._data;
        }

        auto free() noexcept -> void override;
        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            return VBuffer::equals(o);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return VBuffer::hash() + this->_stagingBuffer.hash();
        }

        [[nodiscard]] auto copy () const noexcept -> VVertexBuffer * override {
            return new VVertexBuffer(* this);
        }
    };


}


#endif //ENG1_VVERTEXBUFFER_HPP
