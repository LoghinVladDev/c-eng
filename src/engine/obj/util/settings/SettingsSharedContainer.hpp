//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_SETTINGSSHAREDCONTAINER_H
#define ENG1_SETTINGSSHAREDCONTAINER_H

#include <map>
#include "SettingOption.hpp"

namespace engine {


    class SettingsSharedContainer {
    private:
        //// private variables
        static SettingsSharedContainer _instance;

        std::map < engine::SettingOption::Setting, engine::SettingOption * > _standardSettings;
        std::map < std::string, engine::SettingOption * > _customSettings;

        //// private functions
        SettingsSharedContainer() noexcept = default;
    public:

        //// public variables

        //// public functions
        static SettingsSharedContainer & getInstance() noexcept {
            return SettingsSharedContainer::_instance;
        }

        void put ( const SettingOption * ) noexcept;

        [[nodiscard]] const SettingOption * get( const std::string& ) const noexcept;
        [[nodiscard]] const SettingOption * get( engine::SettingOption::Setting ) const noexcept;

        ~SettingsSharedContainer() noexcept {
            for ( auto & pair : this->_standardSettings ) {
                delete pair.second;
            }

            for ( auto & pair : this->_customSettings ) {
                delete pair.second;
            }
        }
    };

}


#endif //ENG1_SETTINGSSHAREDCONTAINER_H
