//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_SETTINGOPTIONGRAPHICS_H
#define ENG1_SETTINGOPTIONGRAPHICS_H
#include "VSettingOption.hpp"
#include <VObject.hpp>

namespace engine {

    class ResolutionSetting : public engine::VSettingOption {
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
                    VSettingOption("resolution" ),
                    _height(height),
                    _width(width),
                    _defaultWidth(width),       // TODO : read from cfg file / from process?
                _defaultHeight(height){
                VSettingOption::_settingType = RESOLUTION;
            }

            ResolutionSetting( const ResolutionSetting& obj ) noexcept :
                    VSettingOption(obj._name ),
                    _height( obj._height ),
                    _width( obj._width ),
                    _defaultWidth( obj._defaultWidth ),
                    _defaultHeight( obj._defaultHeight ){
                VSettingOption::_settingType = obj._settingType;
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

            [[nodiscard]] auto copy () const noexcept -> ResolutionSetting * override {
                return new ResolutionSetting(*this);
            }

            [[nodiscard]] auto operator == (ResolutionSetting const & o) const noexcept -> bool {
                if ( this == & o ) return true;

                return
                    this->_width == o._width &&
                    this->_height == o._height &&
                    this->_defaultWidth == o._defaultWidth &&
                    this->_defaultHeight == o._defaultHeight;
            }

            [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
                if ( this == & o ) return true;
                auto p = dynamic_cast < decltype (this) > ( & o );
                if ( p == nullptr ) return false;

                return this->VSettingOption::operator==(*p) && this->operator==(*p);
            }
        };

    }


#endif //ENG1_SETTINGOPTIONGRAPHICS_H
