//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VFRAMEBUFFER_HPP
#define ENG1_VFRAMEBUFFER_HPP

#include <VRenderObject.hpp>

#include <VImageView.hpp>
#include <VRenderPass.hpp>
#include <VDepthBuffer.hpp>

#include <vector>

namespace engine {

    class EngineVFrameBufferInvalidRenderPass : public cds :: Exception {
    public:
        inline EngineVFrameBufferInvalidRenderPass () :
                cds :: Exception ( "Given pointer to Render Pass is either nullptr or points to invalid object" ) {

        }
    };

    class VFrameBuffer : public VRenderObject {
    private:
        //// private variables
        VImageView    const * _pImageView   {nullptr};
        VRenderPass   const * _pRenderPass  {nullptr};
        VulkanFrameBuffer     _handle       {nullptr};

        //// private functions

    public:

        //// public variables

        //// public functions

        VFrameBuffer () noexcept = default;
        explicit VFrameBuffer ( VImageView const & imageView, VRenderPass const * pRenderPass ) noexcept :
            VRenderObject(),
            _pImageView     ( & imageView ),
            _pRenderPass    (   pRenderPass ){

        }
        ~VFrameBuffer () noexcept override = default;

        auto setup ( VImageView const & imageView, VRenderPass const * pRenderPass, VDepthBuffer const * pDepthBuffer = nullptr ) noexcept -> VulkanResult {
            this->_pImageView = & imageView;
            this->_pRenderPass = pRenderPass;
            return this->setup( pDepthBuffer );
        }

        auto setup ( const VDepthBuffer * = nullptr ) noexcept -> VulkanResult;
        auto clear () noexcept -> void override;

        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto getImageViewPtr () const noexcept -> VImageView const * {
            return this->_pImageView;
        }

        __CDS_NoDiscard constexpr auto getRenderPassPtr () const noexcept -> VRenderPass const * {
            return this->_pRenderPass;
        }

        __CDS_NoDiscard constexpr auto data () const noexcept -> VulkanFrameBuffer const & {
            return this->_handle;
        }

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == (VFrameBuffer const & o) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_handle == o._handle;
        }

        __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto copy () const noexcept -> VFrameBuffer * override {
            return new VFrameBuffer(*this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            return cds :: hash(
                reinterpret_cast < cds :: AddressValueType const > (this->_handle) +
                reinterpret_cast < cds :: AddressValueType const > (this->_pRenderPass) +
                reinterpret_cast < cds :: AddressValueType const > (this->_pImageView)
            );
        }
    };

    class VFrameBufferCollection : public VRenderObject {
    private:
        //// private variables
        std::vector < VFrameBuffer > _frameBuffers;

        //// private functions

    public:
        //// public variables

        //// public functions

        VFrameBufferCollection () noexcept = default;
        ~VFrameBufferCollection() noexcept override = default;

        auto setup ( VRenderPass const *, VDepthBuffer const * = nullptr ) noexcept (false) -> VulkanResult;

        __CDS_NoDiscard constexpr auto getFrameBuffers () const noexcept -> std::vector < VFrameBuffer > const & {
            return this->_frameBuffers;
        }

        __CDS_NoDiscard inline auto size () const noexcept -> cds :: uint32 {
            return static_cast < cds :: uint32 > (this->_frameBuffers.size());
        }

        auto clear () noexcept -> void override;

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        __CDS_NoDiscard auto operator == (VFrameBufferCollection const & o) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            return this->_frameBuffers == o._frameBuffers;
        }

        __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto copy () const noexcept -> VFrameBufferCollection * override {
            return new VFrameBufferCollection(* this);
        }

        __CDS_NoDiscard auto hash () const noexcept -> cds :: Index override {
            cds :: Index hashSum = 0;
            (void) std::for_each(this->_frameBuffers.begin(), this->_frameBuffers.end(), [& hashSum](auto const & o){hashSum += o.hash();});
            return hashSum;
        }
    };

}


#endif //ENG1_VFRAMEBUFFER_HPP
