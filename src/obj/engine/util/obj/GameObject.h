//
// Created by vladl on 06/07/2020.
//

#pragma once

#ifndef ENG1_GAMEOBJECT_H
#define ENG1_GAMEOBJECT_H

#include "Transform.h"
#include "../dataStructures/Array.h"
#include "../event/KeyListener.h"
#include "../../Engine.h"

class [[maybe_unused]] GameObject {

protected:
    Transform _transform;
    EngineUtility::Array<std::string> _tagsArray;

    bool _destroyed { false };
    bool _visible { true };
    bool _simulatePhysics { true };

    GameObject() noexcept ;

    [[maybe_unused]] GameObject(const GameObject&) noexcept ;

public:
    virtual void draw() noexcept = 0;
    virtual void update() noexcept = 0;
    [[maybe_unused]] void realUpdate() noexcept;

    [[maybe_unused]] virtual void addKeyListener(KeyListener* listener) noexcept;

    [[maybe_unused]] EngineUtility::Array<std::string>& getTags()   noexcept { return this->_tagsArray; }
    [[maybe_unused]] Transform& getTransform()                      noexcept { return this->_transform; }

    [[maybe_unused]] virtual void destroy()                         noexcept { this->_destroyed = true; };
    [[maybe_unused]] virtual bool destroyed()                       noexcept { return this->_destroyed; }

    [[maybe_unused]] virtual bool isVisible()                       noexcept { return this->_visible; }
    [[maybe_unused]] virtual bool isHidden()                        noexcept { return ! this->_visible; }
    [[maybe_unused]] virtual void hide()                            noexcept { this->_visible = false; }
    [[maybe_unused]] virtual void show()                            noexcept { this->_visible = true; }
    [[maybe_unused]] virtual void setVisibility(bool visible)       noexcept { this->_visible = visible; }

    [[maybe_unused]] virtual void simulatePhysics(bool toggle)      noexcept { this->_simulatePhysics = toggle; }
    [[maybe_unused]] virtual bool doesSimulatePhysics()             noexcept { return this->_simulatePhysics; }
};


#endif //ENG1_GAMEOBJECT_H
