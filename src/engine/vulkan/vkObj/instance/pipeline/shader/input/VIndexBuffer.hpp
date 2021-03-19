//
// Created by vladl on 9/5/2020.
//

#ifndef ENG1_VINDEXBUFFER_HPP
#define ENG1_VINDEXBUFFER_HPP

#include <engineVulkanPreproc.hpp>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.hpp>
#include <vkObj/instance/pipeline/shader/input/VVertex.hpp>
#include <vkObj/instance/pipeline/shader/input/VBuffer.hpp>
#include <vkObj/instance/pipeline/shader/input/VStagingBuffer.hpp>

namespace engine {

    class VIndexBufferBase : public VBuffer {
    protected:
        //// protected variables
//        VStagingBuffer  _stagingBuffer;
        const VCommandPool * _pCommandPool {nullptr};

        //// protected functions
        VIndexBufferBase () noexcept = default;

    public:
        //// public variables
        constexpr static VulkanIndexType TYPE_16_BIT = VulkanIndexType::VK_INDEX_TYPE_UINT16;
        constexpr static VulkanIndexType TYPE_32_BIT = VulkanIndexType::VK_INDEX_TYPE_UINT32;

        //// public functions

        virtual VulkanResult flush () noexcept = 0;

        [[nodiscard]] virtual VulkanIndexType getIndexType () const noexcept = 0;

        virtual VulkanResult allocateMemory () noexcept = 0;

        virtual void free () noexcept override;
        virtual void cleanup () noexcept override;
    };

    class VIndexBuffer16 : public VIndexBufferBase {
    private:
        //// private variables
        VStagingBuffer < uint16 > _stagingBuffer;

        //// private functions

    public:
        //// public variables

        //// public functions
        VIndexBuffer16 () noexcept = default;

        VulkanResult setup (
            const VLogicalDevice &,
            const std::vector < uint16 > &,
            const VCommandPool *,
            const uint32 * = nullptr,
            uint32 = 0U,
            bool = false
        ) noexcept;

        VulkanResult setup (
           const VLogicalDevice &,
           uint32,
           const VCommandPool *,
           const uint32 * = nullptr,
           uint32 = 0U,
           bool = false
        ) noexcept;

        VulkanResult load ( const std::vector < uint16 > & ) noexcept;

        [[nodiscard]] const std::vector < uint16 > & getBufferData () const noexcept {
            return this->_stagingBuffer._data;
        }

        VulkanResult allocateMemory() noexcept override;
        VulkanResult flush() noexcept override;
        void cleanup() noexcept override;
        void free() noexcept override;
        [[nodiscard]] VulkanIndexType getIndexType() const noexcept override {
            return VIndexBufferBase::TYPE_16_BIT;
        }
    };

    class VIndexBuffer32 : public VIndexBufferBase {
    private:
        //// private variables
        VStagingBuffer < uint32 > _stagingBuffer;

        //// private functions

    public:
        //// public variables

        //// public functions
        VIndexBuffer32 () noexcept = default;

        VulkanResult setup (
            const VLogicalDevice &,
            const std::vector < uint32 > &,
            const VCommandPool *,
            const uint32 * = nullptr,
            uint32 = 0U,
            bool = false
        ) noexcept;

        VulkanResult setup (
           const VLogicalDevice &,
           uint32,
           const VCommandPool *,
           const uint32 * = nullptr,
           uint32 = 0U,
           bool = false
        ) noexcept;

        VulkanResult load ( const std::vector < uint32 > & ) noexcept;

        [[nodiscard]] const std::vector < uint32 > & getBufferData () const noexcept {
            return this->_stagingBuffer._data;
        }

        VulkanResult allocateMemory() noexcept override;
        VulkanResult flush() noexcept override;
        void cleanup() noexcept override;
        void free() noexcept override;
        [[nodiscard]] VulkanIndexType getIndexType() const noexcept override {
            return VIndexBufferBase::TYPE_32_BIT;
        }
    };

    typedef VIndexBuffer16 VIndexBuffer;
}


#endif //ENG1_VINDEXBUFFER_HPP
