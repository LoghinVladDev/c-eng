//
// Created by Vlad on 16/08/2020.
//

#include "SettingsSharedContainer.hpp"

engine::SettingsSharedContainer engine::SettingsSharedContainer::_instance;

void engine::SettingsSharedContainer::put(const engine::VSettingOption * settingOption) noexcept {
    if ( settingOption == nullptr )
        return;

    if(settingOption->getType() != VSettingOption::CUSTOM ) {
        this->_standardSettings.insert( std::make_pair( settingOption->getType(), settingOption->clone() ) );
    } else {
        this->_customSettings.insert( std::make_pair( settingOption->getName(), settingOption->clone() ) );
    }
}

const engine::VSettingOption *engine::SettingsSharedContainer::get(const std::string & settingName) const noexcept {
    for ( auto & entry : this->_standardSettings ) {
        if ( entry.second->getName() == settingName )
            return entry.second;
    }

    auto customSetting = this->_customSettings.find( settingName );

    if( customSetting == this->_customSettings.end() )
        return nullptr;

    return customSetting->second;
}

const engine::VSettingOption *engine::SettingsSharedContainer::get(engine::VSettingOption::Setting settingType) const noexcept {
    auto setting = this->_standardSettings.find( settingType );

    if( setting == this->_standardSettings.end() )
        return nullptr;
    return setting->second;
}
