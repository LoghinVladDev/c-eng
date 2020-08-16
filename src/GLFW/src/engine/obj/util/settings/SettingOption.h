//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_SETTINGOPTION_H
#define ENG1_SETTINGOPTION_H

#include <string>
#include <utility>

namespace engine {

    class SettingOption {
    public:
        typedef enum {
            RESOLUTION,
            CUSTOM
        } Setting;
    private:
        //// private variables

        //// private functions
    protected:
        //// protected variables
        std::string _name;
        Setting _settingType;

        //// protected functions

        explicit SettingOption(std::string name) noexcept :
            _name (std::move( name )),
            _settingType(CUSTOM) {

        }

    public:

        //// public variables

        //// public functions
        SettingOption() noexcept = delete;

        void setName ( const std::string& name ) noexcept {
            this->_name = name;
        }

        [[nodiscard]] const std::string& getName () const noexcept {
            return this->_name;
        }

        [[nodiscard]] Setting getType() const noexcept {
            return this->_settingType;
        }

#ifdef ENGINE_SETTINGS_USE_SAFE_MODE
        virtual void resetToSaveValue   () = 0;
#endif

        [[nodiscard]] virtual SettingOption* clone() const noexcept = 0;
        virtual void resetToDefaultValue()                          = 0;
        virtual ~SettingOption();
    };

}

#include "SettingsSharedContainer.h"


#endif //ENG1_SETTINGOPTION_H
