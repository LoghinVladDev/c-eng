//
// Created by vladl on 06/07/2020.
//

#pragma once

#ifndef ENG1_CAMERA_H
#define ENG1_CAMERA_H

#include "../GameObject.h"
#include <cmath>

class [[maybe_unused]] Camera : public GameObject {
protected:
    float angle {0.0f};
    float deltaMove{ 0.0f };
    float deltaAngle{ 0.0f };
public:
    Camera();

    [[maybe_unused]] explicit Camera(const Transform&);

    void update() noexcept override;
    void draw() noexcept override;
};

#endif //ENG1_CAMERA_H
