//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_SETTINGOPTIONGRAPHICS_H
#define ENG1_SETTINGOPTIONGRAPHICS_H
#include "SettingOption.hpp"
#include <dataTypes.h>

namespace engine {

    class ResolutionSetting : public engine::SettingOption {
        private:
            //// private variables
            uint32 _width;
            uint32 _height;

            uint32 _defaultWidth;
            uint32 _defaultHeight;

#ifdef ENGINE_SETTINGS_USE_SAFE_MODE
            uint32 _safeModeWidth = SAFE_MODE_WIDTH;
            uint32 _safeModeHeight = SAFE_MODE_HEIGHT;
#endif

            //// private functions

        public:
            //// public variables

#ifdef ENGINE_SETTINGS_USE_SAFE_MODE
            constexpr static uint32 SAFE_MODE_WIDTH = 800U;
            constexpr static uint32 SAFE_MODE_HEIGHT = 600U;
#endif

            //// public functions
            ResolutionSetting() noexcept = delete;

            explicit ResolutionSetting(uint32 width, uint32 height) noexcept :
                SettingOption( "resolution" ),
                _height(height),
                _width(width),
                _defaultWidth(width),       // TODO : read from cfg file / from process?
                _defaultHeight(height){
                SettingOption::_settingType = RESOLUTION;
            }

            ResolutionSetting( const ResolutionSetting& obj ) noexcept :
                SettingOption( obj._name ),
                _height( obj._height ),
                _width( obj._width ),
                _defaultWidth( obj._defaultWidth ),
                _defaultHeight( obj._defaultHeight ){
                SettingOption::_settingType = obj._settingType;
            }

            [[nodiscard]] uint32 getWidth () const noexcept {
                return this->_width;
            }

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#endif

            [[nodiscard]] uint32 getHeight () const noexcept {
                return this->_height;
            }

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

#ifdef ENGINE_SETTINGS_USE_SAFE_MODE
            void resetToSaveValue() override {
                this->_height = this->_safeModeHeight;
                this->_width = this->_safeModeWidth;
            }
#endif

            

            [[nodiscard]] ResolutionSetting * clone() const noexcept override {
                return new ResolutionSetting( * this );
            }

            void resetToDefaultValue() override {
                // TODO
                this->_height = this->_defaultHeight;
                this->_width = this->_defaultWidth;
            }
        };

    }


#endif //ENG1_SETTINGOPTIONGRAPHICS_H
