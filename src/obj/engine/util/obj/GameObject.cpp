//
// Created by vladl on 06/07/2020.
//

#include "GameObject.h"

GameObject::GameObject() noexcept : _transform(Transform()), _tagsArray(EngineUtility::Array<std::string>()) {
//    this->_transform = Transform();
//    this->_tagsArray = EngineUtility::Array<std::string>();
}

[[maybe_unused]] GameObject::GameObject(const GameObject& obj) noexcept {
    this->_transform = obj._transform;
    this->_tagsArray = obj._tagsArray;
}

[[maybe_unused]] void GameObject::realUpdate() noexcept {
    if( this->_visible ) {
        this->update();
        this->draw();
//        if(this->_enableDebugTracking)
//            std::cout << this->toString() << '\n';
//        std::cout << "update + draw\n";
    }
}

[[maybe_unused]] void GameObject::addKeyListener(KeyListener *listener) noexcept {
    Engine::getInstance()->addKeyListener(listener);
}

[[maybe_unused]] void GameObject::addMouseListener(MouseListener *listener) noexcept {
    Engine::getInstance()->addMouseListener(listener);
}

inline bool operator<(const GameObject & leftOperand, const GameObject & rightOperand) {
    return leftOperand._drawPriority < rightOperand._drawPriority;
}

inline bool operator>(const GameObject & leftOperand, const GameObject & rightOperand) {
    return leftOperand._drawPriority > rightOperand._drawPriority;
}

inline bool operator<=(const GameObject & leftOperand, const GameObject & rightOperand) {
    return leftOperand._drawPriority <= rightOperand._drawPriority;
}

inline bool operator>=(const GameObject & leftOperand, const GameObject & rightOperand) {
    return leftOperand._drawPriority >= rightOperand._drawPriority;
}

inline bool operator==(const GameObject & leftOperand, const GameObject & rightOperand) {
    return leftOperand._drawPriority == rightOperand._drawPriority;
}

[[maybe_unused]] std::string GameObject::toString() noexcept {
    return " gameObject { transform = " +
        this->_transform.toString() +
        ", visible = " +
        std::to_string(this->_visible) +
        ", destroyed = " +
        std::to_string(this->_destroyed) +
        ", tags = " +
        this->_tagsArray.toString() +
        ", render priority = " +
        std::to_string(this->_drawPriority) +
        " }";
}

