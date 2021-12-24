//
// Created by loghin on 20.12.2021.
//

#include "KeyEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( KeyEvent ) :: toString () const noexcept -> String {
    return "KeyEvent "
           "{ Event = "     + this->C_ENG_CLASS(Event)::toString() +
           ", key = "       + :: toString ( this->key() ) +
           ", modifiers = " + keyModifiersToString ( this->modifiers() ) +
           " }";
}

auto C_ENG_CLASS ( KeyEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( KeyEvent ) const * > ( & object );

    return this->key() == pEvent->key() && this->modifiers() == pEvent->modifiers();
}