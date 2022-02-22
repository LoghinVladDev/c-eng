//
// Created by loghin on 21.12.2021.
//

#include "Monitor.hpp"

#include <Logger.hpp>
#include <Window.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


namespace globals {
    extern bool __GLFWActive; // NOLINT(bugprone-reserved-identifier)
}

extern auto __initializeGLFW () noexcept (false) -> void; // NOLINT(bugprone-reserved-identifier)


static auto monitorChangeDetectedCallback (
        __C_ENG_TYPE ( Monitor ) :: Handle,
        sint32
) noexcept -> void;


#define C_ENG_MAP_START     STRUCT ( MonitorContainer, NO_PARENT )
#include <ObjectMapping.hpp>

namespace engine {

    Struct {
        bool                                          monitorsQueried {false}; // NOLINT(clion-misra-cpp2008-11-0-1)
        Array < __C_ENG_TYPE ( Monitor ) const * >    monitors; // NOLINT(clion-misra-cpp2008-11-0-1)
        __C_ENG_TYPE ( Monitor ) const *              primaryMonitor {nullptr}; // NOLINT(clion-misra-cpp2008-11-0-1)

        Constructor () noexcept = default;

        static auto queryProperties ( __C_ENG_TYPE ( Monitor ) * pMonitor ) noexcept -> void {
            pMonitor->_availableVideoModes.clear();

            sint32 count;
            GLFWvidmode const * pModes = glfwGetVideoModes (
                    pMonitor->handle(),
                    & count
            );

            sint32 physicalWidthMM;
            sint32 physicalHeightMM;
            glfwGetMonitorPhysicalSize (
                    pMonitor->handle(),
                    & physicalWidthMM,
                    & physicalHeightMM
            );

            float contentScaleX;
            float contentScaleY;
            glfwGetMonitorContentScale (
                    pMonitor->handle(),
                    & contentScaleX,
                    & contentScaleY
            );

            sint32 workAreaXPos;
            sint32 workAreaYPos;
            sint32 workAreaWidth;
            sint32 workAreaHeight;
            glfwGetMonitorWorkarea (
                    pMonitor->handle(),
                    & workAreaXPos,
                    & workAreaYPos,
                    & workAreaWidth,
                    & workAreaHeight
            );

            GLFWgammaramp const * pGammaRamp = glfwGetGammaRamp ( pMonitor->handle() );

            for ( sint32 i = 0; i < count; ++ i ) {
                (void) pMonitor->_availableVideoModes.pushBack ( ( __C_ENG_TYPE ( MonitorVideoModeProperties ) ) {
                    .size   = ( __C_ENG_TYPE ( Size ) ) {
                        .width  = static_cast < uint32 > ( pModes[i].width ),
                        .height = static_cast < uint32 > ( pModes[i].height )
                    },
                    .colorChannelsDepth = ( __C_ENG_TYPE ( ColorChannelsDepth ) ) {
                        .red    = static_cast < uint32 > ( pModes[i].redBits ),
                        .green  = static_cast < uint32 > ( pModes[i].greenBits ),
                        .blue   = static_cast < uint32 > ( pModes[i].blueBits ),
                    },
                    .refreshRate    = static_cast < uint32 > ( pModes[i].refreshRate )
                });
            }

            GLFWvidmode const * pActiveMode = glfwGetVideoMode ( pMonitor->handle() );
            pMonitor->_properties = ( __C_ENG_TYPE ( MonitorProperties ) ) {
                .name               = glfwGetMonitorName ( pMonitor->handle() ),
                .physicalSizeMM     = ( __C_ENG_TYPE ( Size ) ) {
                    .width              = static_cast < uint32 > ( physicalWidthMM ),
                    .height             = static_cast < uint32 > ( physicalHeightMM )
                },
                .contentScale       = ( __C_ENG_TYPE ( MonitorContentScale ) ) {
                    .x                  = contentScaleX,
                    .y                  = contentScaleY
                },
                .workArea           = ( __C_ENG_TYPE ( MonitorWorkArea ) ) {
                    .position           = ( __C_ENG_TYPE ( Position ) ) {
                        .x                  = static_cast < uint32 > ( workAreaXPos ),
                        .y                  = static_cast < uint32 > ( workAreaYPos )
                    },
                    .size               = ( __C_ENG_TYPE ( Size ) ) {
                        .width              = static_cast < uint32 > ( workAreaWidth ),
                        .height             = static_cast < uint32 > ( workAreaHeight )
                    }
                },
                .gammaRamp          = ( __C_ENG_TYPE ( MonitorGammaRamp ) ) {
                    .size               = static_cast < uint32 > ( pGammaRamp->size ),
                    .red                = pGammaRamp->red,
                    .green              = pGammaRamp->green,
                    .blue               = pGammaRamp->blue
                },
                .activeVideoMode    = ( __C_ENG_TYPE ( MonitorVideoModeProperties ) ) {
                    .size               = ( __C_ENG_TYPE ( Size ) ) {
                        .width              = static_cast < uint32 > ( pActiveMode->width ),
                        .height             = static_cast < uint32 > ( pActiveMode->height )
                    },
                    .colorChannelsDepth = ( __C_ENG_TYPE ( ColorChannelsDepth ) ) {
                        .red                = static_cast < uint32 > ( pActiveMode->redBits ),
                        .green              = static_cast < uint32 > ( pActiveMode->greenBits ),
                        .blue               = static_cast < uint32 > ( pActiveMode->blueBits )
                    },
                    .refreshRate        = static_cast < uint32 > ( pActiveMode->refreshRate )
                }
            };
        }

        auto query () noexcept -> void {
            if ( ! globals :: __GLFWActive ) {
                try {
                    __initializeGLFW();
                } catch ( Exception const & ) {
                    (void) __C_ENG_TYPE ( Logger ) :: instance().fatal ( "Could not acquire monitors, GLFW could not initialize" );
                    return;
                }
            }

            sint32 monitorCount;
            auto _monitors = glfwGetMonitors ( & monitorCount );
            auto _primary = glfwGetPrimaryMonitor();

            monitors.resize(static_cast < Size > ( monitorCount ));

            for ( sint32 i = 0; i < monitorCount; ++ i ) {
                auto pMonitor = new __C_ENG_TYPE ( Monitor );
                pMonitor->_handle = _monitors[i];
                queryProperties ( pMonitor );

                if ( pMonitor->_handle == _primary ) {
                    primaryMonitor = pMonitor;
                }

                monitors[i] = pMonitor;
            }

            (void) glfwSetMonitorCallback ( & monitorChangeDetectedCallback );

            logMonitorQueryResult ();
            monitorsQueried = true;
        }

        auto logMonitorQueryResult () noexcept -> void;

        auto addMonitor (
                __C_ENG_TYPE ( Monitor ) :: Handle handle
        ) noexcept -> void {

            auto pMonitor = new __C_ENG_TYPE ( Monitor );
            pMonitor->_handle = handle;
            queryProperties( pMonitor );

            (void) monitors.pushBack ( pMonitor );

            if ( glfwGetPrimaryMonitor() == handle ) {
                primaryMonitor = pMonitor;
            }

        }

        Destructor () noexcept {
            for ( auto * e : monitors ) {
                delete e;
            }

            primaryMonitor = nullptr;
            monitors.clear();
        }
    };

    static Self monitorContainer;

}

auto Self :: logMonitorQueryResult () noexcept -> void {
    (void) __C_ENG_TYPE ( Logger ) :: instance().info (
            "Found "_s + monitors.size() + " monitors"
    );

    Index i = 0;
    for ( auto & monitor : monitors ) {
        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\tMonitor "_s + i
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\thandle = "_s + :: toString ( monitor->handle() )
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\tname = "_s + monitor->properties().name
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\tphysicalSize = "_s + monitor->properties().physicalSizeMM.width + "x" +
                monitor->properties().physicalSizeMM.height + " mm (millimeters)"
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\tcontentScale = x: "_s + monitor->properties().contentScale.x +
                ", y: " + monitor->properties().contentScale.y
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\tworkArea = x: "_s + monitor->properties().workArea.position.x +
                ", y: " + monitor->properties().workArea.position.y +
                ", width: " + monitor->properties().workArea.size.width +
                ", height: " + monitor->properties().workArea.size.height
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\tgammaRamp:"
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\tsize = "_s + monitor->properties().gammaRamp.size
        );

        static auto gammaRampAsString = [](uint16 const * pRamp, uint32 size) noexcept {
            String rampAsStr = "";

            for ( uint32 i = 0U; i < size; ++ i ) {
                rampAsStr += String ( pRamp[i] ) + ", ";
            }

            return rampAsStr.removeSuffix(", ");
        };

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\tredGammaRamp = "_s + gammaRampAsString ( monitor->properties().gammaRamp.red, monitor->properties().gammaRamp.size )
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\tgreenGammaRamp = "_s + gammaRampAsString ( monitor->properties().gammaRamp.green, monitor->properties().gammaRamp.size )
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\tblueGammaRamp = "_s + gammaRampAsString ( monitor->properties().gammaRamp.blue, monitor->properties().gammaRamp.size )
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\tactiveVideoMode:"
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\twidth = "_s + monitor->properties().activeVideoMode.size.width
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\theight = "_s + monitor->properties().activeVideoMode.size.height
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\tredChannelBitDepth = "_s + monitor->properties().activeVideoMode.colorChannelsDepth.red
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\tgreenChannelBitDepth = "_s + monitor->properties().activeVideoMode.colorChannelsDepth.green
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\tblueChannelBitDepth = "_s + monitor->properties().activeVideoMode.colorChannelsDepth.blue
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\t\trefreshRate = "_s + monitor->properties().activeVideoMode.refreshRate
        );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "\t\tavailableVideoModes: "
        );

        for ( auto & vm : monitor->availableVideoModes() ) {
            (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                    "\t\t\t"_s +
                    "width: "           + vm.size.width +
                    ", height: "        + vm.size.height +
                    ", red: "           + vm.colorChannelsDepth.red +
                    ", green: "         + vm.colorChannelsDepth.green +
                    ", blue: "          + vm.colorChannelsDepth.blue +
                    ", refreshRate: "   + vm.refreshRate
            );
        }
    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#define C_ENG_MAP_START     CLASS ( Monitor, PARENT ( Object ) )
#include <ObjectMapping.hpp>

auto Self :: monitors () noexcept -> Array < Self const * > const & {
    if ( ! monitorContainer.monitorsQueried || ! globals :: __GLFWActive ) {
        monitorContainer.query();
    }

    return monitorContainer.monitors;
}

__C_ENG_MAYBE_UNUSED auto Self :: primaryMonitor () noexcept -> Self const * {
    if ( ! monitorContainer.monitorsQueried || ! globals :: __GLFWActive ) {
        monitorContainer.query();
    }

    return monitorContainer.primaryMonitor;
}

__C_ENG_MAYBE_UNUSED auto Self :: initMonitorHandler () noexcept -> void {
    if ( ! monitorContainer.monitorsQueried || ! globals :: __GLFWActive ) {
        monitorContainer.query();
    }
}

static auto monitorChangeDetectedCallback (
        Self :: Handle  handle,
        sint32                  event
) noexcept -> void {

    if ( event == GLFW_CONNECTED ) {

        monitorContainer.addMonitor( handle );

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "Monitor with handle " +
                :: toString ( handle ) +
                " connected"
        );

    } else if ( event == GLFW_DISCONNECTED ) {

        (void) __C_ENG_TYPE ( Logger ) :: instance().info (
                "Monitor with handle " +
                :: toString ( handle ) +
                " disconnected"
        );

        Self const * pMonitor = nullptr;
        for ( auto * pActiveMonitor : monitorContainer.monitors ) {
            if ( pActiveMonitor->handle() == handle ) {
                pMonitor = pActiveMonitor;
            }
        }

        if ( pMonitor == nullptr ) {
            (void) __C_ENG_TYPE ( Logger ) :: instance().warning (
                    "Monitor change detected, handle " +
                    :: toString ( handle ) +
                    " disconnected, but did not previously exist"
            );
        } else {
            (void) monitorContainer.monitors.removeAll ( pMonitor );
            if ( monitorContainer.primaryMonitor == pMonitor ) {

                Self :: Handle newPrimaryMonitorHandle = glfwGetPrimaryMonitor();
                Self const * newPrimaryMonitor = nullptr;

                for ( auto const * pActiveMonitor : monitorContainer.monitors ) {
                    if ( pActiveMonitor->handle() == newPrimaryMonitorHandle ) {
                        newPrimaryMonitor = pActiveMonitor;
                    }
                }

                if ( newPrimaryMonitor == nullptr ) {

                    (void) __C_ENG_TYPE ( Logger ) :: instance().warning (
                            "Monitor change successful, could not acquire new primary monitor"
                    );

                } else {
                    monitorContainer.primaryMonitor = newPrimaryMonitor;
                }

            }

            if ( pMonitor->windowOnMonitor() != nullptr ) {
                (void) pMonitor->windowOnMonitor()->monitorDisconnectedEvent();
            }

            delete pMonitor;
        }

    } else {
        // do nothing
    }

}

__C_ENG_MAYBE_UNUSED auto Self :: setGamma (
        float gammaValue
) noexcept -> Self & {

    glfwSetGamma ( this->handle(), gammaValue );
    return * this;
}

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ handle = "_s              + :: toString ( this->handle() ) +
           "{ windowOnMonitor = "_s     + :: toString ( this->windowOnMonitor() ) +
           ", properties = "            + :: toString ( this->properties() ) +
           ", availableVideoModes = "   + this->availableVideoModes().toString() +
           " }";
}

auto Self :: equals (
        Object const & object
) const noexcept -> bool {

    if ( this == & object ) {
        return true;
    }

    auto pMonitor = dynamic_cast < decltype ( this ) > ( & object );
    if ( pMonitor == nullptr ) {
        return false;
    }

    return this->handle() == pMonitor->handle();
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>