set(C_ENG_GENERIC_SRC
    ./generic/engine/Engine.cpp)

add_library(c_eng_generic ${C_ENG_GENERIC_SRC})
target_include_directories(c_eng_generic PUBLIC .)
target_include_directories(c_eng_generic PRIVATE ../dependencies/cds/include)
#target_sources(c_eng_generic PUBLIC FILE_SET CXX_MODULES FILES generic/module/c_eng_generic.cxxm)

if(DEFINED C_ENG_USE_GLFW AND C_ENG_USE_GLFW)
  set(
      C_ENG_GLFW_SRC
      api/glfw/Glfw.cpp
      api/glfw/GlfwDisplayWindow.cpp
      api/glfw/GlfwEventPollingManager.cpp)

  add_library(c_eng_glfw ${C_ENG_GLFW_SRC})
  target_link_libraries(c_eng_glfw PRIVATE glfw)
  target_include_directories(c_eng_glfw PUBLIC . api/glfw)
  target_include_directories(c_eng_glfw PRIVATE ../dependencies/cds/include)
  target_include_directories(c_eng_glfw PRIVATE ../dependencies/glfw/include)
endif()

if(DEFINED C_ENG_USE_VULKAN AND C_ENG_USE_VULKAN)
  if(NOT $ENV{VULKAN_SDK} STREQUAL ""
     AND NOT $ENV{LD_LIBRARY_PATH} STREQUAL ""
     AND NOT $ENV{VK_LAYER_PATH} STREQUAL "")
    message("-- [C_ENG] TODO: Custom Vulkan path")
  elseif(Vulkan_FOUND)
    set(C_ENG_VULKAN_INCLUDE_DIRS ${Vulkan_INCLUDE_DIRS})
    set(C_ENG_VULKAN_LIB "Vulkan::Vulkan")
  endif()

  set(C_ENG_VULKAN_SRC
      api/vulkan/Vulkan.cpp
      api/vulkan/core/VulkanCore.cpp
      api/vulkan/debug/VulkanDebug.cpp
      api/vulkan/device/VulkanLogicalDevice.cpp
      api/vulkan/device/VulkanLogicalDeviceFactory.cpp
      api/vulkan/device/VulkanPhysicalDevice.cpp
      api/vulkan/device/VulkanQueue.cpp
      api/vulkan/instance/VulkanInstance.cpp
      api/vulkan/instance/VulkanLayer.cpp
      api/vulkan/renderer/VulkanRenderer.cpp
      api/vulkan/wsi/VulkanSurface.cpp
      api/vulkan/core/VulkanHandles.hpp
      api/vulkan/core/VulkanHandles.def
      api/vulkan/core/VulkanExtensions.hpp)

#  set(
#      C_ENG_VULKAN_SRC
#      api/vulkan/Vulkan.cxxm
#      api/vulkan/core/VulkanCore.cxxm
#      api/vulkan/debug/VulkanDebug.cxxm
#      api/vulkan/device/VulkanLogicalDevice.cxxm
#      api/vulkan/device/VulkanLogicalDeviceFactory.cxxm
#      api/vulkan/device/VulkanLogicalDeviceFactoryImpl.cxxm
#      api/vulkan/device/VulkanLogicalDeviceImpl.cxxm
#      api/vulkan/device/VulkanPhysicalDevice.cxxm
#      api/vulkan/device/VulkanPhysicalDeviceImpl.cxxm
#      api/vulkan/device/VulkanQueue.cxxm
#      api/vulkan/device/VulkanQueueImpl.cxxm
#      api/vulkan/instance/VulkanInstance.cxxm
#      api/vulkan/instance/VulkanLayer.cxxm
#      api/vulkan/renderer/VulkanRenderer.cxxm
#      api/vulkan/wsi/VulkanSurface.cxxm)

  add_library(c_eng_vulkan SHARED ${C_ENG_VULKAN_SRC})
  target_include_directories(c_eng_vulkan PRIVATE ${C_ENG_VULKAN_INCLUDE_DIRS})
  target_include_directories(c_eng_vulkan PRIVATE ../dependencies/cds/include)
  target_include_directories(c_eng_vulkan PUBLIC . api/vulkan)
  target_link_libraries(c_eng_vulkan PRIVATE ${C_ENG_VULKAN_LIB} c_eng_generic)
#  target_sources(c_eng_vulkan PUBLIC ${C_ENG_VULKAN_SRC})
#  target_sources(c_eng_vulkan PUBLIC FILE_SET CXX_MODULES FILES ${C_ENG_VULKAN_SRC})
endif()
