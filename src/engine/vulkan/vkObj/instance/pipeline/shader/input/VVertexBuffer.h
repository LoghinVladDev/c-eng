//
// Created by vladl on 8/30/2020.
//

#ifndef ENG1_VVERTEXBUFFER_H
#define ENG1_VVERTEXBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/input/VVertex.h>
#include <vkObj/instance/pipeline/shader/input/VBuffer.h>
#include <vkObj/instance/pipeline/shader/input/VStagingBuffer.h>

/**
 * Redesign scenario reqs :
 * VB : setup, alloc ( GPU )
 *  setup : size, usage, sharing, qFIC, pQFI
 *  alloc : size, memType
 *
 * SVB : setup, alloc ( CPU )
 *  setup : size, usage, sharing, qFIC, pQFI
 *  alloc : size, memType
 *
 * CPY : SVB -> VB ( req CPool )
 *  copy : memcpy with ComPool
 *
 * IB : setup, alloc ( GPU )
 * SIB : setup, alloc ( CPU )
 * CPY : SIB -> IB ( req CPool )
 *
 */

namespace engine {

    class VVertexBuffer : public VBuffer {
    private:
        //// private variables
//        const std::vector < engine::VVertex > *         _pVertices                  {nullptr};

//        std::vector < engine::VVertex::SVertexPack >    _packedVertices;

        VStagingBuffer < VVertex::SVertexPack >         _stagingBuffer;
        const VCommandPool                            * _pCommandPool               {nullptr};

        //// private functions

    public:
        //// public variables
        //// public functions
        VVertexBuffer () noexcept = default;

        VulkanResult setup (
            const VLogicalDevice &,
            const std::vector < VVertex > &,
            const VCommandPool *,
            const uint32 * = nullptr,
            uint32 = 0U,
            bool = false
        ) noexcept;

        VulkanResult setup (
            const VLogicalDevice &,
            const std::vector < VVertex::SVertexPack > &,
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

        VulkanResult load (
            const std::vector < VVertex > &
        ) noexcept ;

        VulkanResult load (
            const std::vector < VVertex::SVertexPack > &
        ) noexcept ;

        VulkanResult flush () noexcept;

        VulkanResult allocateMemory () noexcept;

        [[nodiscard]] const std::vector < VVertex::SVertexPack > & getBufferData () const noexcept {
            return this->_stagingBuffer._data;
        }

        [[nodiscard]] std::vector < VVertex::SVertexPack > & getBufferData () noexcept {
            return this->_stagingBuffer._data;
        }

        void free() noexcept override;
        void cleanup () noexcept override;
    };


}


#endif //ENG1_VVERTEXBUFFER_H
