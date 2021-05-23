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

    class EngineVFrameBufferInvalidRenderPass : public std::exception {
    public:
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Given pointer to Render Pass is either nullptr or points to invalid object";
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

        [[nodiscard]] constexpr auto getImageViewPtr () const noexcept -> VImageView const * {
            return this->_pImageView;
        }

        [[nodiscard]] constexpr auto getRenderPassPtr () const noexcept -> VRenderPass const * {
            return this->_pRenderPass;
        }

        [[nodiscard]] constexpr auto data () const noexcept -> VulkanFrameBuffer const & {
            return this->_handle;
        }

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) return false;

            return this->_handle == p->_handle;
        }

        [[nodiscard]] auto copy () const noexcept -> VFrameBuffer * override {
            return new VFrameBuffer(*this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return dataTypes::hash(
                reinterpret_cast<AddressValueType> (this->_handle) +
                reinterpret_cast<AddressValueType> (this->_pRenderPass) +
                reinterpret_cast<AddressValueType> (this->_pImageView)
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

        [[nodiscard]] constexpr auto getFrameBuffers () const noexcept -> std::vector < VFrameBuffer > const & {
            return this->_frameBuffers;
        }

        [[nodiscard]] constexpr auto size () const noexcept -> uint32 {
            return static_cast<uint32>(this->_frameBuffers.size());
        }

        auto clear () noexcept -> void override;

        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto operator == (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype(this) > (& o);
            if ( p == nullptr ) return false;

            return this->_frameBuffers == p->_frameBuffers;
        }

        [[nodiscard]] auto copy () const noexcept -> VFrameBufferCollection * override {
            return new VFrameBufferCollection(* this);
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            Index hashSum = 0;
            std::for_each(this->_frameBuffers.begin(), this->_frameBuffers.end(), [& hashSum](auto const & o){hashSum += o.hash();});
            return hashSum;
        }
    };

}


#endif //ENG1_VFRAMEBUFFER_HPP
