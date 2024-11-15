//
// Created by loghin on 11/9/24.
//

#include <Glfw.hpp>

#include <sstream>

#include "GlfwDisplay.hpp"
#include "GlfwWindow.hpp"

#include <cds/experimental/Format>
#include <cds/threading/Mutex>
#include <GLFW/glfw3.h>

#include <generic/Types.hpp>
#include <generic/TypesToString.hpp>
#include <generic/lang/Range.hpp>

namespace c_eng::api::detail {
namespace {
using cds::Mutex;
using cds::Lock;
using cds::Size;
using cds::SSize;
using cds::StringView;
using cds::Vector;
using cds::impl::fwd;
using cds::impl::unreachable;
using cds::addressOf;
using cds::ignore;
using cds::makeUnique;

using cds::impl::xch;
using namespace cds::experimental::literals;

using generic::project;
using generic::DisplayVideoMode;
using generic::Area2D;
using generic::Scale2DF;
using generic::Point2D;
using generic::Rect2D;
using generic::ColorChannelsDepth;
using generic::IncompatibleDisplayException;
using generic::PersistentObjectCreatedEvent;
using generic::PersistentObjectDestroyedEvent;

namespace fn = cds::functional;

class GlfwDisplay : public Display {
public:
  explicit GlfwDisplay(GLFWmonitor* monitor) noexcept : _handle{monitor} {
    assert(!glfwGetMonitorUserPointer(monitor) && "Double initialization of identical monitor");
    glfwSetMonitorUserPointer(monitor, this);
  }

  ~GlfwDisplay() noexcept override = default;

  auto enable() noexcept -> void {
    _connected = true;
  }

  auto disable() noexcept -> void {
    _connected = false;
  }

  [[nodiscard]] auto connected() const noexcept -> bool override {
    return _connected;
  }

  [[nodiscard]] auto handle() const noexcept -> GLFWmonitor* {
    return _handle;
  }

  [[nodiscard]] static auto& fromHandle(GLFWmonitor* handle) noexcept {
    auto display = static_cast<GlfwDisplay*>(glfwGetMonitorUserPointer(handle));
    assert(display && "Invalid or unset GLFWmonitor user pointer");
    return *display;
  }

  auto setGammaScale(float scale) noexcept -> void override {
    glfwSetGamma(_handle, scale);
  }

  [[nodiscard]] auto videoModes() const noexcept -> Vector<DisplayVideoMode> override {
    int count;
    GLFWvidmode const* head = glfwGetVideoModes(_handle, &count);
    Vector<DisplayVideoMode> modes;
    modes.reserve(count);
    for (auto end = head + count; head != end; ++head) {
      modes.emplaceBack(
          Area2D{
              .width = static_cast<Size>(head->width),
              .height = static_cast<Size>(head->height)
          },
          ColorChannelsDepth{
              .redBitDepth = static_cast<Size>(head->redBits),
              .greenBitDepth = static_cast<Size>(head->greenBits),
              .blueBitDepth = static_cast<Size>(head->blueBits)
          },
          head->refreshRate
      );
    }
    return modes;
  }

  [[nodiscard]] auto currentVideoMode() const noexcept -> DisplayVideoMode override {
    auto const* mode = glfwGetVideoMode(_handle);
    return DisplayVideoMode {
        .area = {
            .width = static_cast<Size>(mode->width),
            .height = static_cast<Size>(mode->height)
        },
        .colorDepth = {
            .redBitDepth = static_cast<Size>(mode->redBits),
            .greenBitDepth = static_cast<Size>(mode->greenBits),
            .blueBitDepth = static_cast<Size>(mode->blueBits)
        },
        .refreshRate = static_cast<Size>(mode->refreshRate)
    };
  }

  [[nodiscard]] auto physicalSize() const noexcept -> Area2D {
    int width;
    int height;
    glfwGetMonitorPhysicalSize(_handle, &width, &height);
    return Area2D {
        .width = static_cast<Size>(width),
        .height = static_cast<Size>(height)
    };
  }

  [[nodiscard]] auto contentScale() const noexcept -> Scale2DF override {
    float x;
    float y;
    glfwGetMonitorContentScale(_handle, &x, &y);
    return Scale2DF {
        .x = x,
        .y = y
    };
  }

  [[nodiscard]] auto position() const noexcept -> Point2D override {
    int x;
    int y;
    glfwGetMonitorPos(_handle, &x, &y);
    return Point2D{
        .x = static_cast<SSize>(x),
        .y = static_cast<SSize>(y)
    };
  }

  [[nodiscard]] auto availableAreaRect() const noexcept -> Rect2D override {
    int x;
    int y;
    int width;
    int height;
    glfwGetMonitorWorkarea(_handle, &x, &y, &width, &height);
    return Rect2D {
        .position = {
            .x = static_cast<SSize>(x),
            .y = static_cast<SSize>(y)
        },
        .area = {
            .width = static_cast<Size>(width),
            .height = static_cast<Size>(height)
        }
    };
  }

  [[nodiscard]] auto name() const noexcept -> StringView {
    return glfwGetMonitorName(_handle);
  }

private:
  GLFWmonitor* _handle{nullptr};
  bool _connected {true};
};

auto displayEvent(GLFWmonitor* displayHandle, int glfwEvent) noexcept -> void;

class GlfwDisplayManagerInstance : public DisplayManagerApiComponent {
public:
  explicit GlfwDisplayManagerInstance(LoggerRef logger) noexcept : _logger{logger}, _displays{}, _primary{nullptr} {
    int displayCount = 0;
    GLFWmonitor** displayHandles = glfwGetMonitors(&displayCount);
    _displays.reserve(displayCount);
    // first index is primary
    _primary = &_displays.emplaceBack(displayHandles[0]);
    for (auto idx = 1; idx < displayCount; ++idx) {
      _displays.emplaceBack(GlfwDisplay{displayHandles[idx]});
    }

    glfwSetMonitorCallback(&displayEvent);
    unsigned idx = 0;
    logger() << _logger.invoke("Initialized GLFW Display Manager. Detected {} displays:"_f, _displays.size());
    for (auto const& disp : _displays) {
      logger() << _logger.invoke("\tDisplay {}: {}"_f, idx++, disp);
    }
  }

  ~GlfwDisplayManagerInstance() noexcept override = default;

  [[nodiscard]] auto primaryDisplay() const noexcept -> Display const* override {
    return _primary;
  }

  [[nodiscard]] auto displays() const noexcept -> Vector<Display const*> override {
    return Vector<Display const*>{project(_displays, [](auto const& display) { return &display; })};
  }

  auto connect(GLFWmonitor* monitor) noexcept -> void {
    if (_displays.findFirst(monitor, fn::memFn(&GlfwDisplay::handle)) == _displays.end()) {
      _displays.emplaceBack(monitor);
    }
    auto& display = GlfwDisplay::fromHandle(monitor);
    display.enable();
    _logger() << _logger.invoke("GlfwDisplayManager: Display {} connected."_f, display);
  }

  auto disconnect(GLFWmonitor* monitor) noexcept -> void {
    if (auto it = _displays.findFirst(monitor, fn::memFn(&GlfwDisplay::handle));
        it != _displays.end()) {
      it->disable();
    }
    auto& display = GlfwDisplay::fromHandle(monitor);
    _logger() << _logger.invoke("GlfwDisplayManager: Display {} disconnected."_f, display);
    display.disable();
  }

private:
  LoggerRef _logger;
  Vector<GlfwDisplay> _displays;
  GlfwDisplay const* _primary;
};

auto accessInstance(bool lock, LoggerRef logger = {}) noexcept -> GlfwDisplayManagerInstance* {
  static Mutex sync;
  static GlfwDisplayManagerInstance instance {logger};

  if (lock) {
    sync.lock();
    return &instance;
  }

  sync.unlock();
  return nullptr;
}

class InstanceAccessor {
public:
  explicit InstanceAccessor(LoggerRef logger = {}) noexcept {
    _instance = accessInstance(true, logger);
  }

  ~InstanceAccessor() noexcept {
    accessInstance(false);
  }

  [[nodiscard]] auto& instance() const noexcept {
    return *_instance;
  }

private:
  GlfwDisplayManagerInstance* _instance {nullptr};
};

template <typename Fn> decltype(auto) synchronizedInstance(Fn&& fn, LoggerRef logger = {}) {
  InstanceAccessor accessor{logger};
  return fn::invoke(fwd<Fn>(fn), accessor.instance());
}

auto dispEv(int glfwEvent) {
  switch (glfwEvent) {
    case GLFW_CONNECTED:
      return fn::memFn(&GlfwDisplayManagerInstance::connect);
    case GLFW_DISCONNECTED:
      return fn::memFn(&GlfwDisplayManagerInstance::disconnect);
    default:
      assert(false && "Unhandled GLFWmonitor callback event");
      unreachable();
  }
}

auto displayEvent(GLFWmonitor* displayHandle, int glfwEvent) noexcept -> void {
  synchronizedInstance([displayHandle, mem = dispEv(glfwEvent)](GlfwDisplayManagerInstance& instance) {
    fn::invoke(mem, instance, displayHandle);
  });
}

auto onWindowClose(GLFWwindow* handle) -> void;

class GlfwWindow : public Window {
public:
  explicit GlfwWindow(GlfwWindowManager& windowManager, GLFWwindow* handle) noexcept :
      _handle{handle}, _manager{windowManager} {
    glfwSetWindowUserPointer(handle, this);
    glfwSetWindowCloseCallback(handle, &onWindowClose);
  }

  ~GlfwWindow() noexcept override {
    if (_handle) {
      glfwDestroyWindow(xch(_handle, nullptr));
    }
  }

  [[nodiscard]] auto& manager() const noexcept {
    return _manager;
  }

private:
  GLFWwindow* _handle;
  GlfwWindowManager& _manager;
};

auto onWindowClose(GLFWwindow* handle) -> void {
  auto window = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(handle));
  assert(window && "Invalid/Unset GLFWwindow UserPointer");
  window->manager().close(window);
}
} // namespace

auto GlfwDisplayManager::primaryDisplay() const noexcept -> const Display* {
  return synchronizedInstance([](GlfwDisplayManagerInstance const& instance) {
    return instance.primaryDisplay();
  }, _logger);
}

auto GlfwDisplayManager::displays() const noexcept -> Vector<Display const*> {
  return synchronizedInstance([](GlfwDisplayManagerInstance const& instance) {
    return instance.displays();
  }, _logger);
}

GlfwDisplayManager::GlfwDisplayManager(GlfwInstance const* instance, LoggerRef logger) noexcept :
    _logger{logger}, _instance{instance} {
  synchronizedInstance([](auto const& managerInstance) {
    ignore = managerInstance;
  }, logger);
}

auto GlfwWindowManager::GlfwWindowBuilder::build() const noexcept(false) -> Window* {
  using enum GlfwPlatform;
  _manager._logger()
      << _manager._logger.invoke("Requested creation of{} {}, of dimensions {}, titled '{}'"_f,
                                 windowedFullscreenRequested() ? " borderless" : "",
                                 display() ? "fullscreen window" : "window",
                                 rect().area, title());

  auto const nativeDisplay = [this]() -> GLFWmonitor* {
    if (!display()) {
      return nullptr;
    }

    if (auto const native = dynamic_cast<GlfwDisplay const*>(display())) {
      return native->handle();
    }
    throw IncompatibleDisplayException("GlfwDisplay");
  };

  auto usedSize = rect().area;
  if (windowedFullscreenRequested()) {
    auto const mode = display()->currentVideoMode();
    glfwWindowHint(GLFW_RED_BITS, static_cast<int>(mode.colorDepth.redBitDepth));
    glfwWindowHint(GLFW_GREEN_BITS, static_cast<int>(mode.colorDepth.greenBitDepth));
    glfwWindowHint(GLFW_BLUE_BITS, static_cast<int>(mode.colorDepth.blueBitDepth));
    glfwWindowHint(GLFW_REFRESH_RATE, static_cast<int>(mode.refreshRate));
    usedSize = mode.area;
  }

  if (_manager._controller->instance().platform() == Wayland) {
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, title().data());
  }

  auto handle = glfwCreateWindow(
      static_cast<int>(usedSize.width),
      static_cast<int>(usedSize.height),
      title().data(),
      nativeDisplay(),
      nullptr
  );

  if (!handle) {
    return nullptr;
  }

  auto window = _manager._windows.emplaceBack(makeUnique<GlfwWindow>(_manager, handle)).get();
  PersistentObjectCreatedEvent event{window};
  _manager.notify(event);
  return window;
}

GlfwWindowManager::GlfwWindowManager(GlfwController const* instance, LoggerRef logger) :
    _controller{instance}, _logger{logger} {
  logger() << "Initialized GLFW Window Manager.";
  ignore = instance;
}

auto GlfwWindowManager::windowBuilder() noexcept -> GlfwWindowBuilder {
  return GlfwWindowBuilder(*this);
}

auto GlfwWindowManager::abstractWindowBuilder() noexcept -> UniquePtr<AbstractWindowBuilder> {
  return makeUnique<GlfwWindowBuilder>(windowBuilder());
}

auto GlfwWindowManager::close(Window* window) noexcept -> void {
  PersistentObjectDestroyedEvent event{window};
  notify(event);
  _windows.remove(_windows.findFirst(window));
}

} // namespace c_eng::api::detail

using cds::U64;
using cds::bitCast;
using std::hex;
using std::stringstream;
using c_eng::generic::detail::addressAsString;
using c_eng::api::detail::GlfwDisplay;

template <> struct cds::experimental::impl::Formatter<GlfwDisplay> {
  template <typename S> auto operator()(S& string, GlfwDisplay const& display) const noexcept -> void {
    string += "Display{{handle={}, name='{}', currentVideoMode={}, physicalSize={}, "
              "contentScale={}, position={}, availableArea={}}}"_f(
        addressAsString(&display), display.name(), display.currentVideoMode(), display.physicalSize(),
        display.contentScale(), display.position(), display.availableAreaRect()
    );
  }
};
