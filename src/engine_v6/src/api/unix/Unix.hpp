//
// Created by Vlad-Andrei Loghin on 15.06.23.
//

#ifndef C_ENG_UNIX_HPP
#define C_ENG_UNIX_HPP

#include <api/Api.hpp>
#include "component/UnixSystemApiComponent.hpp"

#include <CDS/memory/UniquePointer>

namespace engine {
class Unix : public Api {
public:
  [[nodiscard]] auto apiInfo() const noexcept -> Info const& override;

  explicit Unix(Engine* pParent) noexcept(false);
private:
  [[nodiscard]] auto getComponentList() noexcept -> cds::Array <ApiComponent*> override;

  cds::UniquePointer <UnixSystemApiComponent> systemComponent = cds::makeUnique <UnixSystemApiComponent>(this);
};
} // namespace engine

#endif //C_ENG_UNIX_HPP
