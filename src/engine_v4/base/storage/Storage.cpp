//
// Created by loghin on 20/02/23.
//

#include "Storage.hpp"
#include <CDS/exception/KeyException>
#include <CDS/exception/TypeException>

namespace engine::storage {
    using namespace cds;

    auto Node :: getInt (StringView key) const noexcept (false) -> int {
        auto data = this->get (key);

        if (data.is <nullptr_t>()) {
            throw KeyException (key);
        }

        if (! data.is <int>()) {
            throw TypeException (String::f (
                    "Value at key '%s' is not an integer",
                    key.cStr()
            ));
        }

        return data.get <int>();
    }


    auto Node :: getFloat (StringView key) const noexcept (false) -> float {
        auto data = this->get (key);

        if (data.is <nullptr_t>()) {
            throw KeyException (key);
        }

        if (! data.is <float>()) {
            throw TypeException (String::f (
                    "Value at key '%s' is not a float",
                    key.cStr()
            ));
        }

        return data.get <float>();
    }


    auto Node :: getString (StringView key) const noexcept (false) -> StringView {
        auto data = this->get (key);

        if (data.is <nullptr_t>()) {
            throw KeyException (key);
        }

        if (! data.is <StringView>()) {
            throw TypeException (String::f (
                    "Value at key '%s' is not a String",
                    key.cStr()
            ));
        }

        return data.get <StringView>();
    }


    auto Node :: getIntOrDefault (StringView key, int defaultValue) const noexcept -> int {
        auto data = this->get (key);

        if (data.is <nullptr_t>()) {
            return defaultValue;
        }

        if (! data.is <int>()) {
            return defaultValue;
        }

        return data.get <int>();
    }


    auto Node :: getFloatOrDefault (StringView key, float defaultValue) const noexcept -> float {
        auto data = this->get (key);

        if (data.is <nullptr_t>()) {
            return defaultValue;
        }

        if (! data.is <float>()) {
            return defaultValue;
        }

        return data.get <float>();
    }


    auto Node :: getStringOrDefault (StringView key, StringView defaultValue) const noexcept -> StringView {
        auto data = this->get (key);

        if (data.is <nullptr_t>()) {
            return defaultValue;
        }

        if (! data.is <StringView>()) {
            return defaultValue;
        }

        return data.get <StringView>();
    }

}
