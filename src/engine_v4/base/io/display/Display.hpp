//
// Created by loghin on 24/02/23.
//

#ifndef __C_ENG_DISPLAY_HPP__
#define __C_ENG_DISPLAY_HPP__

#include <CDS/Array>
#include <CDS/Optional>

#include <base/core/Core.hpp>
#include <base/core/Object.hpp>

namespace engine::io {

    class Window;


    class Display : public Object {
    public:

        struct VideoModeProperties {
            Size2D      size;
            int         refreshRateHz;
            int         redChannelDepth;
            int         greenChannelDepth;
            int         blueChannelDepth;
        };

    protected:
        explicit Display (Object const * pParent = nullptr) noexcept;

    public:
        ~Display () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "Display";
        }

        __CDS_NoDiscard virtual auto name () const noexcept -> cds::Optional <cds::String>;
        __CDS_NoDiscard virtual auto physicalSizeMm () const noexcept -> cds::Optional <engine::Size2D>;
        __CDS_NoDiscard virtual auto scale () const noexcept -> engine::Size2DF;
        __CDS_NoDiscard virtual auto area () const noexcept -> engine::Rect2D = 0;
        __CDS_NoDiscard virtual auto supportedVideoModes () const noexcept -> cds::Array <VideoModeProperties> const & = 0;
        __CDS_NoDiscard virtual auto activeVideoMode () const noexcept -> VideoModeProperties const & = 0;
    };


    class DisplayManager : public Object {
    public:

        explicit DisplayManager (Object const * pParent = nullptr) noexcept;
        ~DisplayManager () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "DisplayManager";
        }

        virtual auto displays () noexcept -> cds::Array <cds::UniquePointer <Display>> const & = 0;
        virtual auto primaryDisplay () noexcept -> cds::UniquePointer <Display> const & = 0;
        virtual auto displaysUnder (Window * pWindow) noexcept -> cds::Array <Display *> = 0;
    };

}


#endif //__C_ENG_DISPLAY_HPP__
