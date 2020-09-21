//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VFRAMEBUFFER_H
#define ENG1_VFRAMEBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>

#include <vkObj/instance/pipeline/VImageView.h>
#include <vkObj/instance/pipeline/VRenderPass.h>
#include <VDepthBuffer.h>

#include <vector>

namespace engine {

    class EngineVFrameBufferInvalidRenderPass : public std::exception {
    public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Given pointer to Render Pass is either nullptr or points to invalid object";
        }
    };

    class VFrameBuffer {
    private:
        //// private variables
        const VImageView    * _pImageView   {nullptr};
        const VRenderPass   * _pRenderPass  {nullptr};
        VulkanFrameBuffer     _handle       {nullptr};

        //// private functions

    public:
        VFrameBuffer () noexcept = default;
        explicit VFrameBuffer ( const VImageView & imageView, const VRenderPass * pRenderPass ) noexcept :
            _pImageView     ( & imageView ),
            _pRenderPass    (   pRenderPass ){

        }
        //// public variables

        //// public functions
        VulkanResult setup ( const VImageView & imageView, const VRenderPass * pRenderPass, const VDepthBuffer * pDepthBuffer = nullptr ) noexcept {
            this->_pImageView = & imageView;
            this->_pRenderPass = pRenderPass;
            return this->setup( pDepthBuffer );
        }
        VulkanResult setup ( const VDepthBuffer * = nullptr ) noexcept;
        void cleanup () noexcept;

        [[nodiscard]] const VImageView * getImageViewPtr () const noexcept {
            return this->_pImageView;
        }

        [[nodiscard]] const VRenderPass * getRenderPassPtr () const noexcept {
            return this->_pRenderPass;
        }

        [[nodiscard]] const VulkanFrameBuffer & data () const noexcept {
            return this->_handle;
        }
    };

    class VFrameBufferCollection {
    private:
        //// private variables
        std::vector < VFrameBuffer > _frameBuffers;

        //// private functions

    public:
        //// public variables

        //// public functions

        VFrameBufferCollection () noexcept = default;
        VulkanResult setup ( const VRenderPass *, const VDepthBuffer * = nullptr ) noexcept (false);

        [[nodiscard]] const std::vector < VFrameBuffer > & getFrameBuffers () const noexcept {
            return this->_frameBuffers;
        }

        [[nodiscard]] uint32 size () const noexcept {
            return this->_frameBuffers.size();
        }

        void cleanup () noexcept;
    };

}


#endif //ENG1_VFRAMEBUFFER_H
