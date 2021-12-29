//
// Created by loghin on 20.12.2021.
//

#ifndef __C_ENG_EVENT_HPP
#define __C_ENG_EVENT_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <Core.hpp>


#define C_ENG_MAP_START     CLASS ( Event, EXTERNAL_PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Window );

    Class {
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( Window ) *, window, nullptr );

    protected:
        explicit Constructor (
                __C_ENG_TYPE ( Window ) * window
        ) noexcept :
                _window ( window ) {

        }

    public:
        Destructor () noexcept override = default;

        __C_ENG_NO_DISCARD constexpr virtual auto type () const noexcept -> __C_ENG_TYPE ( EventType ) {
            return __C_ENG_TYPE ( EventType ) :: EventTypeCustom;
        }

        __C_ENG_NO_DISCARD auto copy () const noexcept -> Self * override = 0;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;

        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_EVENT_HPP
