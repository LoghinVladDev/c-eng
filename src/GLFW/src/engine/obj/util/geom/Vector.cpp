//
// Created by vladl on 05/07/2020.
//

#include "Vector.h"

[[maybe_unused]] inline VectorF::VectorF() noexcept = default;

//[[maybe_unused]] inline VectorF::VectorF(const VectorF & vector) noexcept = default;

[[maybe_unused]] [[nodiscard]] inline bool VectorF::isNull() const noexcept {
    return this->_x == 0 && this->_y == 0 && this->_z == 0;
}

[[maybe_unused]] [[nodiscard]] inline std::string VectorF::toString() const noexcept {
    return
        std::string("VectorF { x = ") +
        std::to_string(this->_x) +
        ", y = " +
        std::to_string(this->_y) +
        ", z = " +
        std::to_string(this->_z) +
        " }";
}

[[maybe_unused]] VectorF::operator std::string() const {
    return this->toString();
}

[[maybe_unused]] inline VectorD::VectorD() noexcept = default;

[[maybe_unused]] inline VectorD::VectorD(double x, double y, double z) noexcept :
        _x(x), _y(y), _z(z) {

}

[[maybe_unused]] inline VectorD::VectorD(const VectorD & vector) noexcept = default;

[[maybe_unused]] [[nodiscard]] inline bool VectorD::isNull() const noexcept {
    return this->_x == 0 && this->_y == 0 && this->_z == 0;
}

[[maybe_unused]] inline VectorD& VectorD::setX(double x) noexcept {
    this->_x = x;
    return *this;
}

[[maybe_unused]] inline VectorD &VectorD::setY(double y) noexcept{
    this->_y = y;
    return *this;
}

[[maybe_unused]] inline VectorD &VectorD::setZ(double z) noexcept {
    this->_z = z;
    return *this;
}

[[maybe_unused]] [[nodiscard]] inline double VectorD::getX() const noexcept {
    return this->_x;
}

[[maybe_unused]] [[nodiscard]] inline double VectorD::getY() const noexcept {
    return this->_y;
}

[[maybe_unused]] [[nodiscard]] inline double VectorD::getZ() const noexcept {
    return this->_z;
}

[[maybe_unused]] [[nodiscard]] inline std::string VectorD::toString() const noexcept {
    return
            std::string("VectorD { x = ") +
            std::to_string(this->_x) +
            ", y = " +
            std::to_string(this->_y) +
            ", z = " +
            std::to_string(this->_z) +
            " }";
}

[[maybe_unused]] VectorD::operator std::string() const {
    return this->toString();
}

VectorF operator+ (const VectorF& a ,const VectorF& b) noexcept {
    VectorF r;
    r._x = a._x + b._x;
    r._y = a._y + b._y;
    r._z = a._z + b._z;
    return r;
}

VectorF operator- (const VectorF& a, const VectorF& b) noexcept {
    VectorF r;
    r._x = a._x - b._x;
    r._y = a._y - b._y;
    r._z = a._z - b._z;
    return r;
}

VectorF operator*(const VectorF& a, float b) noexcept {
    VectorF r;
    r._x = a._x * b;
    r._y = a._y * b;
    r._z = a._z * b;
    return r;
}

VectorF operator*(const VectorF& a, int b) noexcept {
    return operator*(a, (float)b);
}

VectorF operator/(const VectorF& a, float b) noexcept(false) {
    if( b == 0.0f )
        throw EngineVectorDivByZero();

    VectorF r;
    r._x = a._x / b;
    r._y = a._y / b;
    r._z = a._z / b;
    return r;
}

VectorF operator/(const VectorF& a, int b) noexcept(false) {
    return operator/(a, (float)b);
}

VectorF operator^(const VectorF& a, float b) noexcept {
    VectorF r;
    r._x = powf(a._x, b);
    r._y = powf(a._y, b);
    r._z = powf(a._z, b);
    return r;
}

VectorF operator^(const VectorF& a, int b) noexcept {
    return operator^(a, (float)b);
}

VectorF& VectorF::operator=(const VectorF& obj) noexcept {
    if( this == &obj )
        return *this;

    this->_x = obj._x;
    this->_y = obj._y;
    this->_z = obj._z;
    return *this;
}

VectorF& VectorF::operator+=(const VectorF& obj) noexcept {
    this->_x += obj._x;
    this->_y += obj._y;
    this->_z += obj._z;
    return *this;
}

VectorF& VectorF::operator-=(const VectorF& obj) noexcept {
    this->_x -= obj._x;
    this->_y -= obj._y;
    this->_z -= obj._z;
    return *this;
}

VectorF& VectorF::operator*=(float op) noexcept {
    this->_x *= op;
    this->_y *= op;
    this->_z *= op;
    return *this;
}

VectorF& VectorF::operator*=(int op) noexcept {
    return this->operator*=((float)op);
}

VectorF& VectorF::operator/=(float op) noexcept(false) {
    if( op == 0.0f )
        throw EngineVectorDivByZero();

    this->_x /= op;
    this->_y /= op;
    this->_z /= op;
    return *this;
}

VectorF& VectorF::operator/=(int op) noexcept(false) {
    return this->operator/=((float)op);
}

VectorF& VectorF::operator^=(float op) noexcept {
    this->_x = powf(this->_x, op);
    this->_y = powf(this->_y, op);
    this->_z = powf(this->_z, op);
    return *this;
}

VectorF& VectorF::operator^=(int op) noexcept {
    return this->operator^=((float) op);
}

bool operator==(const VectorF& a, const VectorF& b) noexcept {
    return a._x == b._x && a._y == b._y && a._z == b._z;
}

bool operator!=(const VectorF& a, const VectorF& b) noexcept {
    return a._x != b._z || a._y != b._y || a._z != b._z;
}

VectorF::operator VectorD() const {
    return VectorD(
        (double) this->_x,
        (double) this->_y,
        (double) this->_z
    );
}

VectorF::VectorF(const VectorD &obj) noexcept {
    this->_x = (float)obj.getX();
    this->_y = (float)obj.getY();
    this->_z = (float)obj.getZ();
}

VectorF &VectorF::operator=(const VectorD & obj) noexcept {
    this->_x = (float)obj.getX();
    this->_y = (float)obj.getY();
    this->_z = (float)obj.getZ();

    return *this;
}

VectorD operator+ (const VectorD& a ,const VectorD& b) noexcept {
    VectorD r;
    r._x = a._x + b._x;
    r._y = a._y + b._y;
    r._z = a._z + b._z;
    return r;
}

VectorD operator- (const VectorD& a, const VectorD& b) noexcept {
    VectorD r;
    r._x = a._x - b._x;
    r._y = a._y - b._y;
    r._z = a._z - b._z;
    return r;
}

VectorD operator*(const VectorD& a, double b) noexcept {
    VectorD r;
    r._x = a._x * b;
    r._y = a._y * b;
    r._z = a._z * b;
    return r;
}

VectorD operator*(const VectorD& a, int b) noexcept {
    return operator*(a, (double)b);
}

VectorD operator/(const VectorD& a, double b) noexcept(false) {
    if( b == 0.0f )
        throw EngineVectorDivByZero();

    VectorD r;
    r._x = a._x / b;
    r._y = a._y / b;
    r._z = a._z / b;
    return r;
}

VectorD operator/(const VectorD& a, int b) noexcept(false) {
    return operator/(a, (double)b);
}

VectorD operator^(const VectorD& a, double b) noexcept {
    VectorD r;
    r._x = pow(a._x, b);
    r._y = pow(a._y, b);
    r._z = pow(a._z, b);
    return r;
}

VectorD operator^(const VectorD& a, int b) noexcept {
    return operator^(a, (double)b);
}

VectorD& VectorD::operator=(const VectorD& obj) noexcept {
    if( this == &obj )
        return *this;

    this->_x = obj._x;
    this->_y = obj._y;
    this->_z = obj._z;
    return *this;
}

VectorD& VectorD::operator+=(const VectorD& obj) noexcept {
    this->_x += obj._x;
    this->_y += obj._y;
    this->_z += obj._z;
    return *this;
}

VectorD& VectorD::operator-=(const VectorD& obj) noexcept {
    this->_x -= obj._x;
    this->_y -= obj._y;
    this->_z -= obj._z;
    return *this;
}

VectorD& VectorD::operator*=(double op) noexcept {
    this->_x *= op;
    this->_y *= op;
    this->_z *= op;
    return *this;
}

VectorD& VectorD::operator*=(int op) noexcept {
    return this->operator*=((double)op);
}

VectorD& VectorD::operator/=(double op) noexcept(false) {
    if( op == 0.0f )
        throw EngineVectorDivByZero();

    this->_x /= op;
    this->_y /= op;
    this->_z /= op;
    return *this;
}

VectorD& VectorD::operator/=(int op) noexcept(false) {
    return this->operator/=((double)op);
}

VectorD& VectorD::operator^=(double op) noexcept {
    this->_x = pow(this->_x, op);
    this->_y = pow(this->_y, op);
    this->_z = pow(this->_z, op);
    return *this;
}

VectorD& VectorD::operator^=(int op) noexcept {
    return this->operator^=((double) op);
}

bool operator==(const VectorD& a, const VectorD& b) noexcept {
    return a._x == b._x && a._y == b._y && a._z == b._z;
}

bool operator!=(const VectorD& a, const VectorD& b) noexcept {
    return a._x != b._z || a._y != b._y || a._z != b._z;
}

[[maybe_unused]] VectorD::VectorD(const VectorF & obj) noexcept {
    this->_x = (double)obj.getX();
    this->_y = (double)obj.getY();
    this->_z = (double)obj.getZ();
}

VectorD::operator VectorF() const {
    return VectorF(*this);
}

VectorD &VectorD::operator=(const VectorF & obj) noexcept {
    this->_x = (double)obj.getX();
    this->_y = (double)obj.getY();
    this->_z = (double)obj.getZ();

    return *this;
}
