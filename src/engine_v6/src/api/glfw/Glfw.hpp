//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#ifndef C_ENG_GLFW_H
#define C_ENG_GLFW_H

#include <api/Api.hpp>
#include <logging/Logger.hpp>

namespace engine {
class Glfw : public Api {
public:
  constexpr static auto const loggerName = "GlfwLogger";

  Glfw() = delete;
  Glfw(Glfw const&) = delete;
  Glfw(Glfw &&) = delete;
  auto operator =(Glfw const&) = delete;
  auto operator =(Glfw&&) = delete;

  explicit Glfw(Engine* pParent) noexcept(false);
  ~Glfw() noexcept override;

  [[nodiscard]] auto apiInfo() const noexcept -> Info const& override;

private:
  [[nodiscard]] auto getComponentList() noexcept -> cds::Array <ApiComponent*> override;

  Info _apiInfo;

  static inline auto& logger = Logger::getLogger(loggerName);
};
} // namespace engine

#endif //C_ENG_GLFW_H
