//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_API_HPP
#define C_ENG_API_HPP

#include <core/Types.hpp>
#include <core/Object.hpp>
#include <CDS/Array>

namespace engine {
class ApiComponent;
class Engine;
class Api : public Object {
public:
  enum class SourceType {
    Proprietary,
    OpenSource,
    ThirdParty
  };

  struct Info {
    char const* name;
    char const* description;
    char const* purpose;
    char const* vendor;
    cds::uint32 vendorId;
    SourceType  sourceType;
    Version     version;
  };

  [[nodiscard]] virtual auto apiInfo() const noexcept -> Info const& = 0;

  [[nodiscard]] auto engine() noexcept -> Engine*;
  [[nodiscard]] auto engine() const noexcept -> Engine const*;
  [[nodiscard]] auto components() noexcept -> cds::Array <ApiComponent*>;
  [[nodiscard]] auto components() const noexcept -> cds::Array <ApiComponent const*>;

  constexpr static cds::uint32 unknownVendorId = cds::limits::U32_MAX;
protected:
  explicit Api(Engine* parent) noexcept;
  [[nodiscard]] virtual auto getComponentList() noexcept -> cds::Array <ApiComponent*>;
};
} // namespace engine

#endif //C_ENG_API_HPP
