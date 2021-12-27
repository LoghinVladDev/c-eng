//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_WINDOWCONTENTSCALEEVENT_HPP
#define __C_ENG_WINDOWCONTENTSCALEEVENT_HPP


#include <WindowEvent.hpp>

namespace engine {

    __C_ENG_CLASS ( WindowContentScaleEvent ) : public __C_ENG_TYPE ( WindowEvent ) {

        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( WindowContentScale ), scale, 0.0f, 0.0f )

    public:
        __C_ENG_DESTRUCTOR ( WindowContentScaleEvent ) () noexcept override = default;

        __C_ENG_CONSTRUCTOR ( WindowContentScaleEvent ) (
                __C_ENG_TYPE ( Window )                   * window,
                __C_ENG_TYPE ( WindowContentScale ) const & scale
        ) noexcept :
                __C_ENG_CONSTRUCTOR ( WindowEvent ) ( window ),
                _scale ( scale ) {

        }

        __C_ENG_NO_DISCARD constexpr auto type () const noexcept -> __C_ENG_TYPE ( EventType ) override {
            return __C_ENG_TYPE ( EventType ) :: EventTypeWindowContentScaleEvent;
        }

        __C_ENG_NO_DISCARD inline auto copy () const noexcept -> __C_ENG_TYPE ( WindowContentScaleEvent ) * override {
            return new __C_ENG_TYPE ( WindowContentScaleEvent ) ( * this );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}


#endif //__C_ENG_WINDOWCONTENTSCALEEVENT_HPP
