//
// Created by vladl on 06/07/2020.
//

#include "Sphere.h"

void Sphere::draw() noexcept {
    this->_color.setAsDrawColor();

    VectorF location = this->_transform.getLocation();

    glTranslatef( location.getX(), location.getY(), location.getZ() );

    if(this->_wireDraw)
        glutWireSphere(this->_radius, this->_slices, this->_stacks);
}