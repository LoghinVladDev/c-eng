#pragma once

#include <type_traits>
#include <CDS/Object>

namespace engine {
class Object : public cds::Object {
public:
  [[nodiscard]] constexpr auto parent() const noexcept -> Object const* {
    return pParent;
  }

  [[nodiscard]] constexpr auto parent() noexcept -> Object* {
    return pParent;
  }

  constexpr auto setParent(Object* pNewParent) noexcept -> void {
    pParent = pNewParent;
  }

  explicit constexpr Object (Object* pParent = nullptr) noexcept : pParent (pParent) {}

private:
  Object * pParent {nullptr};
};
}
