//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_MONITOR_HPP
#define C_ENG_MONITOR_HPP


#include <Preprocess.hpp>
#include <CDS/Object>

#include <CDS/Array>

#include <Core.hpp>

namespace engine {

    class C_ENG_CLASS ( Window );

    class C_ENG_CLASS ( Monitor ) : public cds :: Object {
    public:
        using Handle = GLFWmonitor *;

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( Handle, handle, nullptr )

    private:
        C_ENG_TYPE ( Window ) mutable * _windowOnMonitor { nullptr };

        friend struct MonitorContainer;
        friend class C_ENG_CLASS ( Window );

    private:
        cds :: Array < MonitorVideoModeProperties const >   _availableVideoModes;
        MonitorProperties                                   _properties;

    public:
        C_ENG_NO_DISCARD constexpr auto windowOnMonitor () const noexcept -> C_ENG_TYPE ( Window ) * {
            return this->_windowOnMonitor;
        }

        C_ENG_NO_DISCARD constexpr auto availableVideoModes () const noexcept -> cds :: Array < MonitorVideoModeProperties const > const & {
            return this->_availableVideoModes;
        }

        C_ENG_NO_DISCARD constexpr auto properties () const noexcept -> MonitorProperties const & {
            return this->_properties;
        }

        auto static monitors () noexcept -> cds :: Array < C_ENG_TYPE ( Monitor ) const * > const &;
        auto static primaryMonitor () noexcept -> C_ENG_TYPE ( Monitor ) const *;

        C_ENG_MAYBE_UNUSED auto setGamma ( float ) noexcept -> C_ENG_TYPE ( Monitor ) &;

    };

}

#endif //C_ENG_MONITOR_HPP
