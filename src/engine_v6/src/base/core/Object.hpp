#pragma once

#include <type_traits>

namespace engine {
class Object {
public:
  [[nodiscard]] constexpr auto parent() const noexcept -> Object const* {
    return pParent;
  }

  [[nodiscard]] constexpr auto parent() noexcept -> Object* {
    return pParent;
  }

  explicit constexpr Object (Object* pParent = nullptr) noexcept : pParent (pParent) {}

private:
  Object * pParent {nullptr};
};
}
