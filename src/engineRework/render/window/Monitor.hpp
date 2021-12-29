//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_MONITOR_HPP
#define __C_ENG_MONITOR_HPP


#include <Preprocess.hpp>
#include <CDS/Object>

#include <CDS/Array>

#include <Core.hpp>


#define C_ENG_MAP_START     CLASS ( Monitor, EXTERNAL_PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Window );

    Class {
    public:
        using Handle = GLFWmonitor *;

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( Handle, handle, nullptr )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( cds :: Array < __C_ENG_TYPE ( MonitorVideoModeProperties ) const >, availableVideoModes )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( MonitorProperties ), properties )

    private:
        __C_ENG_TYPE ( Window ) mutable * _windowOnMonitor { nullptr };

        __C_ENG_FRIEND_STRUCT ( MonitorContainer );
        __C_ENG_FRIEND_CLASS ( Window );

    public:
        __C_ENG_NO_DISCARD constexpr auto windowOnMonitor () const noexcept -> __C_ENG_TYPE ( Window ) * {
            return this->_windowOnMonitor;
        }

        auto static monitors () noexcept -> cds :: Array < Self const * > const &;
        auto static primaryMonitor () noexcept -> Self const *;
        auto static initMonitorHandler () noexcept -> void;

        __C_ENG_MAYBE_UNUSED auto setGamma ( float ) noexcept -> Self &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif //__C_ENG_MONITOR_HPP
