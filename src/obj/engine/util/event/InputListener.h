//
// Created by vladl on 08/07/2020.
//
#pragma once

#ifndef ENG1_INPUTLISTENER_H
#define ENG1_INPUTLISTENER_H

#include "../defs/types.h"

class InputListener {
public:
    enum KeyModifier{
        NONE            [[maybe_unused]] = MODIFIER_ACTIVE_NONE,
        SHIFT           [[maybe_unused]] = MODIFIER_ACTIVE_SHIFT,
        CTRL            [[maybe_unused]] = MODIFIER_ACTIVE_CTRL,
        ALT             [[maybe_unused]] = MODIFIER_ACTIVE_ALT,
        CTRL_SHIFT      [[maybe_unused]] = MODIFIER_ACTIVE_CTRL_SHIFT,
        CTRL_ALT        [[maybe_unused]] = MODIFIER_ACTIVE_CTRL_ALT,
        ALT_SHIFT       [[maybe_unused]] = MODIFIER_ACTIVE_ALT_SHIFT,
        CTRL_ALT_SHIFT  [[maybe_unused]] = MODIFIER_ACTIVE_CTRL_ALT_SHIFT
    };
protected:
    KeyModifier keyModifier {KeyModifier::NONE};
    [[maybe_unused]] [[nodiscard]] KeyModifier getKeyModifier() noexcept;
    InputListener() = default;

public:
    [[maybe_unused]] void setParent( void* parent ) noexcept{
        this->_parent = parent;
    }

    [[maybe_unused]] void updateKeyModifiers() noexcept;

    [[maybe_unused]] void* getParent () noexcept;

    void* _parent {nullptr};
};


#endif //ENG1_INPUTLISTENER_H
