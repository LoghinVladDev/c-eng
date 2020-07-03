//
// Created by Vlad on 03/07/2020.
//

#pragma once

#ifndef ENG1_KEYLISTENER_H
#define ENG1_KEYLISTENER_H

#include "../defs/types.h"

class KeyListener {
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

private:
    KeyModifier keyModifier {KeyModifier::NONE};

public:
    [[maybe_unused]] [[nodiscard]] inline KeyModifier getKeyModifier() noexcept { return this->keyModifier; }

    [[maybe_unused]] virtual void keyPressed(uint16 keyCode);
    [[maybe_unused]] virtual void keyReleased(uint16 keyCode);

protected:
    KeyListener() = default;
};


#endif //ENG1_KEYLISTENER_H
