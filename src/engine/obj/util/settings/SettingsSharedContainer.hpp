//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_SETTINGSSHAREDCONTAINER_H
#define ENG1_SETTINGSSHAREDCONTAINER_H

#include <map>
#include "VSettingOption.hpp"

namespace engine {


    class SettingsSharedContainer {
    private:
        //// private variables
        static SettingsSharedContainer _instance;

        std::map < engine::VSettingOption::Setting, engine::VSettingOption * > _standardSettings;
        std::map < std::string, engine::VSettingOption * > _customSettings;

        //// private functions
        SettingsSharedContainer() noexcept = default;
    public:

        //// public variables

        //// public functions
        static SettingsSharedContainer & getInstance() noexcept {
            return SettingsSharedContainer::_instance;
        }

        void put ( const VSettingOption * ) noexcept;

        [[nodiscard]] const VSettingOption * get(const std::string& ) const noexcept;
        [[nodiscard]] const VSettingOption * get(engine::VSettingOption::Setting ) const noexcept;

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
