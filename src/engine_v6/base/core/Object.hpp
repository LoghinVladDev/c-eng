#pragma once

#include <type_traits>

namespace engine {
    template <typename T>
    class Object {
    protected:
        constexpr Object (Object * pParent = nullptr) noexcept : pParent (pParent) {}

        [[nodiscard]] constexpr auto parent () const noexcept -> Object const * {
            return pParent;
        }

    private:
        Object * pParent {nullptr};
    };
}
