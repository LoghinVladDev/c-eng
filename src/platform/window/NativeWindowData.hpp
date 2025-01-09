//
// Created by loghin on 1/7/25.
//

#pragma once

#ifdef WIN32
#include <windef.h>
#elifdef __linux
#include <X11/Xlib.h>
#include <wayland-client.h>
#else
#error Undefined native window system.
#endif

namespace c_eng::native::detail {
enum class NativeWindowInfoType {
#ifdef WIN32
  Win32,
#elifdef __linux
  X11,
  Wayland,
#else
#error Undefined native window system.
#endif
};

struct NativeWindowData {
  NativeWindowInfoType type;
};

#ifdef WIN32
struct NativeWin32WindowData {
  NativeWindowInfoType type;
  HINSTANCE instanceHandle;
  HWND windowHandle;
};
#elifdef __linux
struct NativeX11WindowData {
  NativeWindowInfoType type;
  Display* display;
  Window window;
};

struct NativeWaylandWindowData {
  NativeWindowInfoType type;
  wl_display* display;
  wl_surface* surface;
};
#else
#error Undefined native window system.
#endif
} // namespace c_eng::native::detail

namespace c_eng::native {
struct NativeWindowData : detail::NativeWindowData {};
using detail::NativeWindowInfoType;

#ifdef WIN32
using detail::NativeWin32WindowData;
#elifdef __linux
using detail::NativeX11WindowData;
using detail::NativeWaylandWindowData;
#else
#error Undefined native window system.
#endif
} // namespace c_eng::native
