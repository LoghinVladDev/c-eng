//
// Created by Vlad on 03/07/2020.
//

#pragma once

#ifndef ENG1_KEYLISTENER_H
#define ENG1_KEYLISTENER_H

//#include <enginePreproc.h>
//#include <src/glfw_src/include/GLFW/glfw3.h>
//#include "../obj/GameObject.h"
#include "InputListener.h"

//class GameObject;

namespace engine {

    class KeyListener : public InputListener {
    public:

    protected:
    //    void (*_boundKeyPressedPtr) (uint16) = nullptr;
    //    void (*_boundKeyReleasedPtr) (uint16) = nullptr;
    public:

        constexpr static uint8 KEY_PRESSED   = GLFW_PRESS;
        constexpr static uint8 KEY_RELEASED  = GLFW_RELEASE;
        constexpr static uint8 KEY_HELD      = GLFW_REPEAT;

    //    [[maybe_unused]] ptr_KL_override getBoundKeyPressedEvent() {
    //        return this->_boundKeyPressedPtr;
    //    }
    //
    //    [[maybe_unused]] ptr_KL_override getBoundKeyReleasedEvent() {
    //        return this->_boundKeyReleasedPtr;
    //    }

        [[maybe_unused]] virtual void keyPressed(int key, int scanCode, KeyListener::KeyModifier mods) noexcept;
        [[maybe_unused]] virtual void keyReleased(int key, int scanCode, KeyListener::KeyModifier mods) noexcept;
        [[maybe_unused]] virtual void keyHeld(int key, int scanCode, KeyListener::KeyModifier mods) noexcept;

    //    [[maybe_unused]] void bindKeyPressedEvent( void (*callback) (uint16) ) {
    //        this->_boundKeyPressedPtr = callback;
    //    }
    //
    //    [[maybe_unused]] void bindKeyReleasedEvent( void (*callback) (uint16) ) {
    //        this->_boundKeyReleasedPtr = callback;
    //    }

        KeyListener() = default;
    };

}

//class GameObject;

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
