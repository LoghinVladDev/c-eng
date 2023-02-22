//
// Created by loghin on 5/1/22.
//

#ifndef __C_ENG_RAW_CONTROLLER_INPUT_ENTITY_EVENT_ADAPTER_COMPONENT_HPP__
#define __C_ENG_RAW_CONTROLLER_INPUT_ENTITY_EVENT_ADAPTER_COMPONENT_HPP__

#include <Preprocess.hpp>
#include <scene/ECM/components/eventAdapter/component/EntityEventAdapterControllerComponent.hpp>

#define C_ENG_MAP_START CLASS ( RawControllerInputEntityEventAdapterComponent, ENGINE_PARENT ( EntityEventAdapterControllerComponent ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    ClassDefs

    public:
        NoDiscard constexpr auto type () const noexcept -> Type ( EntityEventAdapterControllerComponentType ) override {
            return EntityEventAdapterControllerComponentTypeRawInput;
        }

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept -> Self & override;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & override;

        auto clear () noexcept -> Self & override;
        NoDiscard auto copy () const noexcept -> Self * override;

        Destructor () noexcept override;

        auto controllerAxisEvent ( Type ( ControllerAxisEvent ) * ) noexcept -> void override;
        auto controllerButtonPressEvent ( Type ( ControllerButtonPressEvent ) * ) noexcept -> void override;
        auto controllerButtonReleaseEvent ( Type ( ControllerButtonReleaseEvent ) * ) noexcept -> void override;
        auto controllerHatEvent ( Type ( ControllerHatEvent ) * ) noexcept -> void override;

    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_RAW_CONTROLLER_INPUT_ENTITY_EVENT_ADAPTER_COMPONENT_HPP__
