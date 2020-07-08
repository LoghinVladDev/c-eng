//
// Created by vladl on 06/07/2020.
//

#ifndef ENG1_SPHERE_H
#define ENG1_SPHERE_H

#include "../GameObject.h"
#include "../../dataStructures/Color.h"

class VectorF;

class Sphere : public GameObject {
private:
    float minH = 1.0f;
    float maxH = (rand() % 1000) / 100.0f + 2.0;
    float inc = 0.05f;

    int stage = 0;
    bool up = true;
    constexpr static float DEF_SPHERE_RADIUS = 1.0f;
    constexpr static int32 DEF_SPHERE_SLICES = 20U;
    constexpr static int32 DEF_SPHERE_STACKS = 20U;

    float _radius {DEF_SPHERE_RADIUS};
    int32 _slices {DEF_SPHERE_SLICES};
    int32 _stacks {DEF_SPHERE_STACKS};

    Color _color { Color::RED_MIN, Color::GREEN_MIN, Color::BLUE_MIN };
public:

    Sphere() = default;

    [[maybe_unused]] explicit Sphere(const Transform& transform) {
        this->_transform = transform;
    };

    [[maybe_unused]] void setRadius( float radius ) noexcept { this->_radius = radius * this->_transform.getScale().getX(); }
    [[maybe_unused]] void setSlices( int32 slices ) noexcept { this->_slices = slices * this->_transform.getScale().getY(); }
    [[maybe_unused]] void setStacks( int32 stacks ) noexcept { this->_stacks = stacks * this->_transform.getScale().getZ(); }
    [[maybe_unused]] void setColor( const Color& color ) noexcept { this->_color = color; }

    [[maybe_unused]] [[nodiscard]] float getRadius () const noexcept { return this->_radius; }
    [[maybe_unused]] [[nodiscard]] float getSlices () const noexcept { return this->_slices; }
    [[maybe_unused]] [[nodiscard]] float getStacks () const noexcept { return this->_stacks; }

    void update()   noexcept override;
    void draw()     noexcept override;
};


#endif //ENG1_SPHERE_H
