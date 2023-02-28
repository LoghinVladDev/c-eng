//
// Created by loghin on 26/02/23.
//

#include "GlfwDisplay.hpp"
#include <CDS/Long>

namespace engine::io {

    using namespace cds;
    using namespace cds::literals;


    GlfwDisplay :: GlfwDisplay (GLFWmonitor * pHandle, Object const * pParent) noexcept :
            Display (pParent),
            _pHandle (pHandle) {

        __C_ENG_OBJ_LOG (
                Debug,
                "Initializing GlfwDisplay with handle 0x"_s +
                Long(reinterpret_cast <cds::uint64>(this->_pHandle)).toString(16)
        );

        glfwSetMonitorUserPointer (this->_pHandle, static_cast <void *> (this));

        glfwGetMonitorPhysicalSize (this->_pHandle, & this->_widthMm, & this->_heightMm);
        glfwGetMonitorContentScale (this->_pHandle, & this->_contentScaleX, & this->_contentScaleY);
        glfwGetMonitorWorkarea (this->_pHandle, & this->_workAreaX, & this->_workAreaY, & this->_workAreaWidth, & this->_workAreaHeight);
        glfwGetMonitorPos (this->_pHandle, & this->_posX, & this->_posY);
        this->_pName        = glfwGetMonitorName (this->_pHandle);
        this->_pVideoModes  = glfwGetVideoModes (this->_pHandle, & this->_videoModeCount);
        this->_pGammaRamp   = glfwGetGammaRamp (this->_pHandle);
    }


    auto GlfwDisplay :: name () const noexcept -> StringView {
        return this->_pName;
    }


    auto GlfwDisplay :: physicalSizeMm () const noexcept -> engine::Size2D {
        return {
                .width  = this->_widthMm,
                .height = this->_heightMm
        };
    }


    auto GlfwDisplay :: scale () const noexcept -> engine::Size2DF {
        return {
                .width  = this->_contentScaleX,
                .height = this->_contentScaleY
        };
    }


    auto GlfwDisplay :: position () const noexcept -> engine::Point2D {
        return {
                .x  = this->_posX,
                .y  = this->_posY
        };
    }


    auto GlfwDisplay :: workArea () const noexcept -> engine::Rect2D {
        return {
                .position = {
                        .x  = this->_workAreaX,
                        .y  = this->_workAreaY
                },
                .size = {
                        .width  = this->_workAreaWidth,
                        .height = this->_workAreaHeight
                }
        };
    }


    auto GlfwDisplay :: supportedVideoModes () const noexcept -> Array <VideoModeProperties> {

        Array <VideoModeProperties> videoModeProperties;
        for (int index = 0; index < this->_videoModeCount; ++ index) {

            auto const * pCurrentVideoMode = & this->_pVideoModes [index];
            videoModeProperties.pushBack ({
                    .size   = {
                            .width  = pCurrentVideoMode->width,
                            .height = pCurrentVideoMode->height
                    },
                    .refreshRateHz      = pCurrentVideoMode->refreshRate,
                    .redChannelDepth    = pCurrentVideoMode->redBits,
                    .greenChannelDepth  = pCurrentVideoMode->greenBits,
                    .blueChannelDepth   = pCurrentVideoMode->blueBits
            });
        }

        return videoModeProperties;
    }


    auto GlfwDisplay :: activeVideoMode () const noexcept -> VideoModeProperties {

        auto const * pActiveVideoMode = glfwGetVideoMode(this->_pHandle);
        return {
                .size   = {
                        .width  = pActiveVideoMode->width,
                        .height = pActiveVideoMode->height
                },
                .refreshRateHz      = pActiveVideoMode->refreshRate,
                .redChannelDepth    = pActiveVideoMode->redBits,
                .greenChannelDepth  = pActiveVideoMode->greenBits,
                .blueChannelDepth   = pActiveVideoMode->blueBits
        };
    }


    GlfwDisplayManager :: GlfwDisplayManager (Object const * pParent) noexcept : DisplayManager (pParent) {

        __C_ENG_OBJ_LOG(Info, "Initializing GlfwDisplayManager");

        int displayCount;
        auto * pDisplayHandles = glfwGetMonitors (& displayCount);
        __C_ENG_OBJ_LOG(Debug, "Detected "_s + displayCount + " displays");

        for (int index = 0; index < displayCount; ++ index) {
            this->_displays.emplaceBack (new GlfwDisplay (pDisplayHandles [index], this));
        }
    }


    auto GlfwDisplayManager :: displays () const noexcept -> Array <Display const *> {

        Array <Display const *> displays;
        for (auto const & display : this->_displays) {
            displays.pushBack (display);
        }

        return displays;
    }


    auto GlfwDisplayManager :: primaryDisplay () const noexcept -> Display const * {

        auto * pPrimaryHandle = glfwGetPrimaryMonitor();
        for (auto const & display : this->_displays) {

            if (display->handle() == pPrimaryHandle) {
                return display;
            }
        }

        return this->_displays [0];
    }


    auto GlfwDisplayManager :: displaysUnder (Window const * pWindow) const noexcept -> Array <Display const *> {

        /* TODO - logic after GlfwWindow is available */
        return {};
    }


    auto GlfwDisplayManager :: addDisplay (GLFWmonitor * pDisplayHandle) noexcept -> void {

        __C_ENG_OBJ_LOG(
                Debug,
                "Display with handle 0x"_s +
                Long(reinterpret_cast<uint64>(pDisplayHandle)).toString(16) +
                " connected"
        );

        this->_displays.emplaceBack (new GlfwDisplay (pDisplayHandle, this));
        /* TODO - after GlfwWindow is available, logic of changing window display
         * if new primary display connected */
    }


    auto GlfwDisplayManager :: removeDisplay (GLFWmonitor * pDisplayHandle) noexcept -> void {

        __C_ENG_OBJ_LOG(
                Debug,
                "Display with handle 0x"_s +
                Long(reinterpret_cast<uint64>(pDisplayHandle)).toString(16) +
                " disconnected"
        );

        /* TODO - after GlfwWindow is available, logic of changing window from disconnected display */
        this->_displays.removeFirstThat ([&](auto & display){ return display->handle() == pDisplayHandle; });
    }

}
