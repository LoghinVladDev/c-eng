//
// Created by Vlad on 9/13/2020.
//

#ifndef ENG1_VTEXTUREDEFS_H
#define ENG1_VTEXTUREDEFS_H

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
#endif

#define IMAGE_BYTE_PER_PIXEL_VALUE_RGBA 4U
#define IMAGE_BYTE_PER_PIXEL_VALUE_RGB  3U

#define __IMAGE_BYTE_PER_PIXEL(_stbiValue) \
    ( ( (_stbiValue) == STBI_rgb_alpha ) ? ( IMAGE_BYTE_PER_PIXEL_VALUE_RGBA ) : (IMAGE_BYTE_PER_PIXEL_VALUE_RGB) )

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

#endif //ENG1_VTEXTUREDEFS_H
