//
// Created by loghin on 20.12.2021.
//

#ifndef C_ENG_EVENT_HPP
#define C_ENG_EVENT_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <Core.hpp>

namespace engine {

    class C_ENG_TYPE ( Window );

    class C_ENG_CLASS ( Event ) : public cds :: Object {
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Window ) *, window, nullptr );

    protected:
        explicit C_ENG_CONSTRUCTOR ( Event ) ( C_ENG_TYPE ( Window ) * window ) noexcept :
                _window ( window ) {

        }

    public:
        C_ENG_DESTRUCTOR ( Event ) () noexcept override = default;

        C_ENG_NO_DISCARD constexpr virtual auto type () const noexcept -> EventType {
            return EventType :: EventTypeCustom;
        }
    };

}

#endif //C_ENG_EVENT_HPP
