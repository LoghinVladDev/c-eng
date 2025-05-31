//
// Created by loghin on 1/7/25.
//

#pragma once

#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#elif defined(__linux)
#include <X11/Xlib.h>
#include <wayland-client.h>
#elif defined(__APPLE__)
#else
#error Undefined native window system.
#endif

namespace c_eng::native::detail {
enum class NativeWindowInfoType {
#if defined(WIN32)
  Win32,
#elif defined(__linux)
  X11,
  Wayland,
#elif defined(__APPLE__)
  Cocoa,
#else
#error Undefined native window system.
#endif
};

struct NativeWindowData {
  NativeWindowInfoType type;
};

#if defined(WIN32)
struct NativeWin32WindowData : NativeWindowData {
  HINSTANCE instanceHandle;
  HWND windowHandle;
};
#elif defined(__linux)
struct NativeX11WindowData : NativeWindowData {
  Display* display;
  Window window;
};

struct NativeWaylandWindowData : NativeWindowData {
  wl_display* display;
  wl_surface* surface;
};
#elif defined(__APPLE__)
struct NativeCocoaWindowData : NativeWindowData {
  void* view;
  void* window;
};
#else
#error Undefined native window system.
#endif
} // namespace c_eng::native::detail

namespace c_eng::native {
using detail::NativeWindowData;
using detail::NativeWindowInfoType;

#if defined(WIN32)
using detail::NativeWin32WindowData;
#elif defined(__linux)
using detail::NativeX11WindowData;
using detail::NativeWaylandWindowData;
#elif defined(__APPLE__)
using detail::NativeCocoaWindowData;
#else
#error Undefined native window system.
#endif
} // namespace c_eng::native
