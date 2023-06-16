//
// Created by Vlad-Andrei Loghin on 15.06.23.
//

#ifndef C_ENG_UNIXSYSTEMAPICOMPONENT_HPP
#define C_ENG_UNIXSYSTEMAPICOMPONENT_HPP

#include <api/component/SystemApiComponent.hpp>

namespace engine {
class Unix;
class UnixSystemApiComponent : public SystemApiComponent {
public:
  UnixSystemApiComponent() noexcept = delete;
  UnixSystemApiComponent(UnixSystemApiComponent const&) = delete;
  UnixSystemApiComponent(UnixSystemApiComponent &&) = delete;
  auto operator = (UnixSystemApiComponent const&) = delete;
  auto operator = (UnixSystemApiComponent &&) = delete;

  explicit UnixSystemApiComponent(Unix* pParentApi) noexcept;
  ~UnixSystemApiComponent() noexcept override;
};
} // namespace engine

#endif //C_ENG_UNIXSYSTEMAPICOMPONENT_HPP
