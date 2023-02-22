//
// Created by vladl on 06/07/2020.
//

#include "GameObject.h"

engine::GameObject::GameObject() noexcept : _transform(Transform()) { //, _tagsArray(engine::Array<std::string>()) {
//    this->_transform = Transform();
//    this->_tagsArray = EngineUtility::Array<std::string>();
}

[[maybe_unused]] engine::GameObject::GameObject(const GameObject& obj) noexcept {
    this->_transform = obj._transform;
//    this->_tagsArray = obj._tagsArray;
}

[[maybe_unused]] void engine::GameObject::realUpdate() noexcept {
    if( this->_visible ) {
        this->update();
        this->draw();
//        if(this->_enableDebugTracking)
//            std::cout << this->toString() << '\n';
//        std::cout << "update + draw\n";
    }
}

[[maybe_unused]] void engine::GameObject::addKeyListener(engine::KeyListener *listener) noexcept {
    Engine::getInstance()->addKeyListener(listener);
}

[[maybe_unused]] void engine::GameObject::addMouseListener(engine::MouseListener *listener) noexcept {
    Engine::getInstance()->addMouseListener(listener);
}

inline bool operator<(const engine::GameObject & leftOperand, const engine::GameObject & rightOperand) {
//    return leftOperand._drawPriority < rightOperand._drawPriority;
    return false;
}

inline bool operator>(const engine::GameObject & leftOperand, const engine::GameObject & rightOperand) {
//    return leftOperand._drawPriority > rightOperand._drawPriority;
    return false;
}

inline bool operator<=(const engine::GameObject & leftOperand, const engine::GameObject & rightOperand) {
//    return leftOperand._drawPriority <= rightOperand._drawPriority;
    return false;
}

inline bool operator>=(const engine::GameObject & leftOperand, const engine::GameObject & rightOperand) {
//    return leftOperand._drawPriority >= rightOperand._drawPriority;
    return false;
}

inline bool operator==(const engine::GameObject & leftOperand, const engine::GameObject & rightOperand) {
//    return leftOperand._drawPriority == rightOperand._drawPriority;
    return false;
}

[[maybe_unused]] std::string engine::GameObject::toString() noexcept {
    return " gameObject { transform = " +
        this->_transform.toString() +
        ", visible = " +
        std::to_string(this->_visible) +
        ", destroyed = " +
        std::to_string(this->_destroyed) +
//        ", tags = " +
//        this->_tagsArray.toString() +
//        ", render priority = " +
//        std::to_string(this->_drawPriority) +
        " }";
}

