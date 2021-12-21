//
// Created by vladl on 04/08/2020.
//

#ifndef ENG_DATA_PATHS_H
#define ENG_DATA_PATHS_H

/**
 * Paths for several resources
 */

__CDS_MaybeUnused constexpr const char* __PROJECT_PATH__    = "./../";                  // NOLINT(bugprone-reserved-identifier)
constexpr const char* __SHADERS_PATH__                      = "./../data/shaders/GLSL/330";     // NOLINT(bugprone-reserved-identifier)
constexpr const char* __TEXTURES_PATH__                     = "./../data/textures/";    // NOLINT(bugprone-reserved-identifier)

constexpr const char* __NO_PATH_GIVEN__                     = "./";                     // NOLINT(bugprone-reserved-identifier)
constexpr const char* __ASSETS_PATH__                       = "./../data/assets/";      // NOLINT(bugprone-reserved-identifier)

constexpr const char* __VULKAN_SHADERS_PATH__               = "./../data/shaders/GLSL/450"; // NOLINT(bugprone-reserved-identifier)

#endif //ENG_DATA_PATHS_H