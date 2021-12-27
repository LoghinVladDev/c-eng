//
// Created by loghin on 20.12.2021.
//

#include "KeyEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( KeyEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( KeyEvent ) ) " "
           "{ base = "      + this->__C_ENG_TYPE(Event)::toString() +
           ", key = "       + :: toString ( this->key() ) +
           ", modifiers = " + keyModifiersToString ( this->modifiers() ) +
           " }";
}

auto __C_ENG_TYPE ( KeyEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( KeyEvent ) const * > ( & object );

    return this->key() == pEvent->key() && this->modifiers() == pEvent->modifiers();
}