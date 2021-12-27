//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_MONITOR_HPP
#define __C_ENG_MONITOR_HPP


#include <Preprocess.hpp>
#include <CDS/Object>

#include <CDS/Array>

#include <Core.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Window );


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Monitor /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public cds :: Object {
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

        auto static monitors () noexcept -> cds :: Array < __C_ENG_SELF const * > const &;
        auto static primaryMonitor () noexcept -> __C_ENG_SELF const *;
        auto static initMonitorHandler () noexcept -> void;

        __C_ENG_MAYBE_UNUSED auto setGamma ( float ) noexcept -> __C_ENG_SELF &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}

#endif //__C_ENG_MONITOR_HPP
