//
// Created by Vlad on 17/08/2020.
//

#ifndef ENG1_VIMAGEVIEW_H
#define ENG1_VIMAGEVIEW_H

#include <engineVulkanPreproc.h>
#include <vector>
#include <vkObj/instance/device/VSwapChain.h>

namespace engine {

    class VSwapChain;

    class VImageView {
    private:
        //// private variables
        VulkanImageView     _handle     {};
        uint32              _index      {0U};

        const VSwapChain  * _pSwapChain { nullptr };

        //// private functions

    public:
        //// public variables

        //// public functions
        VImageView () noexcept = default;
        explicit VImageView ( const engine::VImageView *, const engine::VSwapChain * ) noexcept;

        VulkanResult setup( const engine::VSwapChain *, uint32 ) noexcept;

        void cleanup() noexcept;
    };


    class VImageViewCollection {
    private:
        //// private variables
        std::vector < VImageView > _imageViews;

        //// private functions

    public:
        //// public variables

        //// public functions
        VImageViewCollection () noexcept = default;
//        explicit VImageViewCollection ( const engine::VSwapChain& ) noexcept;
        explicit VImageViewCollection ( const engine::VImageViewCollection *, const engine::VSwapChain * ) noexcept;

        VulkanResult setup ( const engine::VSwapChain * ) noexcept;

        void cleanup () noexcept;
    };

}


#endif //ENG1_VIMAGEVIEW_H
