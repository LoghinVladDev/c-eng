//
// Created by vladl on 06/07/2020.
//

#include "GameObject.h"

GameObject::GameObject() noexcept {
    this->_transform = Transform();
    this->_tagsArray = EngineUtility::Array<std::string>();
}

[[maybe_unused]] GameObject::GameObject(const GameObject& obj) noexcept {
    this->_transform = obj._transform;
    this->_tagsArray = obj._tagsArray;
}

[[maybe_unused]] void GameObject::realUpdate() noexcept {
    if( this->_visible ) {
        this->update();
        this->draw();
//        std::cout << "update + draw\n";
    }
}

[[maybe_unused]] void GameObject::addKeyListener(KeyListener *listener) noexcept {
    Engine::getInstance()->addKeyListener(listener);
}

