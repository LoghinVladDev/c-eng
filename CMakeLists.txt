cmake_minimum_required(VERSION 3.28)
project(c-eng CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


set(C_ENG_RENDER_API_LIBS "")


find_package(Vulkan)
if (Vulkan_FOUND)
  message("-- [C_ENG] Vulkan located via CMake Package at '${Vulkan_LIBRARY}'")
else()
  message("-- [C_ENG] Vulkan was not located via CMake Package. TODO: Custom Vulkan Path")
endif()


# TODO: remove later
add_subdirectory(dependencies/cds)

if(NOT DEFINED C_ENG_USE_VULKAN)
  set(C_ENG_USE_VULKAN ON)
endif()


if(NOT DEFINED C_ENG_USE_GLFW)
  set(C_ENG_USE_GLFW ON)
endif()

set(C_ENG_LIB_LIST c_eng_generic)
if(C_ENG_USE_GLFW)
  list(APPEND C_ENG_LIB_LIST c_eng_glfw)
  add_subdirectory(dependencies/glfw)
endif()

if(C_ENG_USE_VULKAN)
  list(APPEND C_ENG_LIB_LIST c_eng_vulkan)
endif()

add_library(cds STATIC)
target_sources(cds PUBLIC FILE_SET CXX_MODULES FILES src/generic/module/cds.cxxm)
target_include_directories(cds PRIVATE dependencies/cds/include)

add_subdirectory(src)

list(APPEND C_ENG_LIB_LIST cds)
list(JOIN C_ENG_LIB_LIST " " C_ENG_LD)

add_executable(generic_scene src/target/GenericScene.cpp)

foreach(LIB IN LISTS C_ENG_LIB_LIST)
  target_link_libraries(generic_scene ${LIB})
endforeach()

target_include_directories(generic_scene PRIVATE dependencies/cds/include)
target_include_directories(generic_scene PRIVATE src)
