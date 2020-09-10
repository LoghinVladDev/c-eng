//
// Created by Vlad on 9/11/2020.
//

#include <bits/ios_base.h>
#include "VTexture.h"

//// TODO : implement internal staging buffer for images
engine::VTexture::VTexture(const char * path) noexcept {
    this->load(path);
}

void engine::VTexture::load(const char * path, int desiredChannels) noexcept(false) {
    int32 textureWidth;
    int32 textureHeight;
    int32 textureChannels;

    this->_pImagePixelData = stbi_load( path, & textureWidth, & textureHeight, & textureChannels, desiredChannels );

    if ( this->_pImagePixelData == nullptr )
        throw std::runtime_error ("Image file load failure");

    this->_textureWidth     = static_cast < uint32 > ( textureWidth );
    this->_textureHeight    = static_cast < uint32 > ( textureHeight );
    this->_textureChannels  = static_cast < uint32 > ( textureChannels );
}

