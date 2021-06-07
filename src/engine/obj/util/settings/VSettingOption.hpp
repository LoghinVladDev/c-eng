//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_SETTINGOPTION_H
#define ENG1_SETTINGOPTION_H


#include <VObject.hpp>
#include <string>
#include <utility>

namespace engine {

    class VSettingOption : public VObject {
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

        explicit VSettingOption(std::string name) noexcept :
            _name (std::move( name )),
            _settingType(CUSTOM) {

        }

    public:

        //// public variables

        //// public functions
        VSettingOption() noexcept = delete;

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

        [[nodiscard]] virtual VSettingOption* clone() const noexcept = 0;
        virtual void resetToDefaultValue()                          = 0;
        ~VSettingOption() noexcept override = default;

        [[nodiscard]] auto toString () const noexcept -> String override {
            return String("VSettingOption { ") +
                "name = " + this->_name + " }";
        }

        [[nodiscard]] auto copy () const noexcept -> VSettingOption * override = 0;

        [[nodiscard]] inline auto operator == (VSettingOption const & o) const noexcept -> bool {
            if ( this == & o ) return true;
            return this->_name == o._name && this->_settingType == o._settingType;
        }

        [[nodiscard]] auto hash () const noexcept -> Index override {
            return String(this->_name).hash();
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > (& o);
            if ( p == nullptr ) return false;
            return this->operator==(*p);
        }
    };

}



#endif //ENG1_SETTINGOPTION_H

#include "SettingsSharedContainer.hpp"
