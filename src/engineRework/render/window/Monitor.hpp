//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_MONITOR_HPP__
#define __C_ENG_MONITOR_HPP__


#include <Preprocess.hpp>
#include <CDS/Object>

#include <CDS/Array>

#include <Core.hpp>


#define C_ENG_MAP_START     CLASS ( Monitor, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Window );

    Class {
    public:
        using Handle = GLFWmonitor *;

        Field ( PRIMITIVE_TYPE ( Handle ),                                                      handle,                 DEFAULT_VALUE ( nullptr ),  GET_DEFAULT, SET_NONE )
        Field ( TYPE ( cds :: Array < __C_ENG_TYPE ( MonitorVideoModeProperties ) const > ),    availableVideoModes,    NO_INIT,                    GET_DEFAULT, SET_NONE )
        Field ( ENGINE_TYPE ( MonitorProperties ),                                              properties,             NO_INIT,                    GET_DEFAULT, SET_NONE )

    private:
        __C_ENG_TYPE ( Window ) mutable * _windowOnMonitor { nullptr };

        __C_ENG_FRIEND_STRUCT ( MonitorContainer );
        __C_ENG_FRIEND_CLASS ( Window );

    public:
        __C_ENG_NO_DISCARD constexpr auto windowOnMonitor () const noexcept -> __C_ENG_TYPE ( Window ) * {
            return this->_windowOnMonitor;
        }

        auto static monitors () noexcept -> cds :: Array < Self const * > const &;
        __C_ENG_MAYBE_UNUSED auto static primaryMonitor () noexcept -> Self const *;
        __C_ENG_MAYBE_UNUSED auto static initMonitorHandler () noexcept -> void;

        __C_ENG_MAYBE_UNUSED auto setGamma ( float ) noexcept -> Self &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_MONITOR_HPP__
