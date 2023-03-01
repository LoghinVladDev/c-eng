//
// Created by loghin on 26/02/23.
//

#ifndef __C_ENG_GLFWDISPLAY_HPP__
#define __C_ENG_GLFWDISPLAY_HPP__

#include <CDS/Array>
#include <CDS/memory/UniquePointer>

#include <GLFW/glfw3.h>
#include <base/io/display/Display.hpp>

namespace engine::io {

    class GlfwDisplay : public Display {
    private:
        GLFWmonitor           * _pHandle        {nullptr};

        char            const * _pName          {nullptr};
        int                     _widthMm        {0};
        int                     _heightMm       {0};
        float                   _contentScaleX  {0.0F};
        float                   _contentScaleY  {0.0F};
        int                     _posX           {0};
        int                     _posY           {0};
        int                     _workAreaX      {0};
        int                     _workAreaY      {0};
        int                     _workAreaWidth  {0};
        int                     _workAreaHeight {0};
        int                     _videoModeCount {0};
        GLFWvidmode     const * _pVideoModes    {nullptr};
        GLFWgammaramp   const * _pGammaRamp     {nullptr};

    public:

        explicit GlfwDisplay (GLFWmonitor * pHandle, Object const * pParent = nullptr) noexcept;
        ~GlfwDisplay () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "GlfwDisplay";
        }

        __CDS_NoDiscard constexpr auto handle () const noexcept -> GLFWmonitor * {
            return this->_pHandle;
        }

        __CDS_NoDiscard auto name () const noexcept -> cds::StringView override;
        __CDS_NoDiscard auto physicalSizeMm () const noexcept -> engine::Size2D override;
        __CDS_NoDiscard auto scale () const noexcept -> engine::Scale2DF override;
        __CDS_NoDiscard auto position () const noexcept -> engine::Point2D override;
        __CDS_NoDiscard auto workArea () const noexcept -> engine::Rect2D override;
        __CDS_NoDiscard auto supportedVideoModes () const noexcept -> cds::Array <VideoModeProperties> override;
        __CDS_NoDiscard auto activeVideoMode () const noexcept -> VideoModeProperties override;
    };


    class GlfwDisplayManager : public DisplayManager {
    private:
        cds::Array <cds::UniquePointer <GlfwDisplay>> _displays;

    public:

        explicit GlfwDisplayManager (Object const * pParent = nullptr) noexcept;
        ~GlfwDisplayManager () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "GlfwDisplayManager";
        }

        __CDS_NoDiscard auto displays () const noexcept -> cds::Array <Display const *> override;
        __CDS_NoDiscard auto primaryDisplay () const noexcept -> Display const * override;
        __CDS_NoDiscard auto displaysUnder (Window const * pWindow) const noexcept -> cds::Array <Display const *> override;

        auto addDisplay (GLFWmonitor * pDisplayHandle) noexcept -> void;
        auto removeDisplay (GLFWmonitor * pDisplayHandle) noexcept -> void;
    };

}

#endif //__C_ENG_GLFWDISPLAY_HPP__
