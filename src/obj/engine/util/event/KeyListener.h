//
// Created by Vlad on 03/07/2020.
//

#pragma once

#ifndef ENG1_KEYLISTENER_H
#define ENG1_KEYLISTENER_H

#include "../defs/types.h"
//#include "../obj/GameObject.h"
#include "./InputListener.h"

class GameObject;

typedef void (*ptr_KL_override) (uint16);
class KeyListener : public InputListener {
public:

protected:
    void (*_boundKeyPressedPtr) (uint16) = nullptr;
    void (*_boundKeyReleasedPtr) (uint16) = nullptr;
public:
    [[maybe_unused]] ptr_KL_override getBoundKeyPressedEvent() {
        return this->_boundKeyPressedPtr;
    }

    [[maybe_unused]] ptr_KL_override getBoundKeyReleasedEvent() {
        return this->_boundKeyReleasedPtr;
    }

    [[maybe_unused]] virtual void keyPressed(uint16) noexcept;
    [[maybe_unused]] virtual void keyReleased(uint16) noexcept;

    [[maybe_unused]] void bindKeyPressedEvent( void (*callback) (uint16) ) {
        this->_boundKeyPressedPtr = callback;
    }

    [[maybe_unused]] void bindKeyReleasedEvent( void (*callback) (uint16) ) {
        this->_boundKeyReleasedPtr = callback;
    }

    KeyListener() = default;
};

class GameObject;

//class BoundKeyListener : public KeyListener {
//protected:
//    GameObject* __parentReceiver;
//
//    explicit BoundKeyListener(GameObject* parent) : KeyListener(), __parentReceiver(parent) { }
//
//public:
//    BoundKeyListener() {}
//
//public:
//    BoundKeyListener() = delete;
//
//protected:

//    void keyPressed (uint16) noexcept override = 0;
//    void keyReleased(uint16) noexcept override = 0;
//};


#endif //ENG1_KEYLISTENER_H
