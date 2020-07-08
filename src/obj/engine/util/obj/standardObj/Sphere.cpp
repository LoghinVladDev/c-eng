//
// Created by vladl on 06/07/2020.
//

#include "Sphere.h"

void Sphere::draw() noexcept {
    glPushMatrix();

    VectorF location(this->_transform.getLocation());
    VectorF scale(this->_transform.getScale());
    this->_color.setAsDrawColor();

//    if(this->_enableDebugTracking)
//        std::cout << location.toString() << '\n';

//    glPushMatrix();
    glTranslatef( location.getX(), location.getY(), location.getZ() );
//    std::cout << this->_color.toString() << '\n';
    glScalef( scale.getX(), scale.getY(), scale.getZ() );

    if(this->_wireDraw)
        glutWireSphere(this->_radius, this->_slices, this->_stacks);
    else
        glutSolidSphere(this->_radius, this->_slices, this->_stacks);

    glPopMatrix();
}



void Sphere::update() noexcept {
    if (up) {
        float y = this->_transform.getLocation().getY();
        this->_transform.getLocation().setY(y + inc);
        if( y >= maxH )
            up = false;
    } else {
        float y= this->_transform.getLocation().getY();
        this->_transform.getLocation().setY( y - inc );
        if ( y <= minH )
            up = true;
    }

}