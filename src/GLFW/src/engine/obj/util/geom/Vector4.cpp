//
// Created by vladl on 05/07/2020.
//

#include "Vector4.h"

[[maybe_unused]] engine::Vector4F engine::Vector4F::nullVector = Vector4F(0.0f, 0.0f, 0.0f, 0.0f);
[[maybe_unused]] engine::Vector4D engine::Vector4D::nullVector = Vector4D(0.0,  0.0,  0.0, 0.0);
[[maybe_unused]] inline engine::Vector4F::Vector4F() noexcept = default;

//[[maybe_unused]] inline Vector4F::Vector4F(const Vector4F & vector) noexcept = default;

[[maybe_unused]] [[nodiscard]] inline bool engine::Vector4F::isNull() const noexcept {
    return this->_x == 0.0f && this->_y == 0.0f && this->_z == 0.0f && this->_t == 0.0f;
}

[[maybe_unused]] [[nodiscard]] inline std::string engine::Vector4F::toString() const noexcept {
    return
        std::string("Vector4F { x = ") +
        std::to_string(this->_x) +
        ", y = " +
        std::to_string(this->_y) +
        ", z = " +
        std::to_string(this->_z) +
        ", t = " +
        std::to_string(this->_t) +
        " }";
}

[[maybe_unused]] engine::Vector4F::operator std::string() const {
    return this->toString();
}

[[maybe_unused]] inline engine::Vector4D::Vector4D() noexcept = default;

[[maybe_unused]] inline engine::Vector4D::Vector4D(double x, double y, double z, double t) noexcept :
        _x(x), _y(y), _z(z), _t(t) {

}

[[maybe_unused]] inline engine::Vector4D::Vector4D(const Vector4D & vector) noexcept = default;

[[maybe_unused]] [[nodiscard]] inline bool engine::Vector4D::isNull() const noexcept {
    return this->_x == 0 && this->_y == 0 && this->_z == 0;
}

[[maybe_unused]] inline engine::Vector4D& engine::Vector4D::setX(double x) noexcept {
    this->_x = x;
    return *this;
}

[[maybe_unused]] inline engine::Vector4D &engine::Vector4D::setY(double y) noexcept{
    this->_y = y;
    return *this;
}

[[maybe_unused]] inline engine::Vector4D &engine::Vector4D::setZ(double z) noexcept {
    this->_z = z;
    return *this;
}

[[maybe_unused]] inline engine::Vector4D &engine::Vector4D::setT(double t) noexcept {
    this->_t = t;
    return *this;
}

[[maybe_unused]] [[nodiscard]] inline double engine::Vector4D::getX() const noexcept {
    return this->_x;
}

[[maybe_unused]] [[nodiscard]] inline double engine::Vector4D::getY() const noexcept {
    return this->_y;
}

[[maybe_unused]] [[nodiscard]] inline double engine::Vector4D::getZ() const noexcept {
    return this->_z;
}

[[maybe_unused]] [[nodiscard]] inline double engine::Vector4D::getT() const noexcept {
    return this->_t;
}

[[maybe_unused]] [[nodiscard]] inline std::string engine::Vector4D::toString() const noexcept {
    return
            std::string("Vector4D { x = ") +
            std::to_string(this->_x) +
            ", y = " +
            std::to_string(this->_y) +
            ", z = " +
            std::to_string(this->_z) +
            ", t = " +
            std::to_string(this->_t) +
            " }";
}

[[maybe_unused]] engine::Vector4D::operator std::string() const {
    return this->toString();
}

engine::Vector4F operator+ (const engine::Vector4F& a ,const engine::Vector4F& b) noexcept {
    engine::Vector4F r;
    r._x = a._x + b._x;
    r._y = a._y + b._y;
    r._z = a._z + b._z;
    r._t = a._t + b._t;
    return r;
}

engine::Vector4F operator- (const engine::Vector4F& a, const engine::Vector4F& b) noexcept {
    engine::Vector4F r;
    r._x = a._x - b._x;
    r._y = a._y - b._y;
    r._z = a._z - b._z;
    r._t = a._t - b._t;
    return r;
}

engine::Vector4F operator*(const engine::Vector4F& a, float b) noexcept {
    engine::Vector4F r;
    r._x = a._x * b;
    r._y = a._y * b;
    r._z = a._z * b;
    r._t = a._t * b;
    return r;
}

engine::Vector4F operator*(const engine::Vector4F& a, int b) noexcept {
    return operator*(a, (float)b);
}

engine::Vector4F operator/(const engine::Vector4F& a, float b) noexcept(false) {
    if( b == 0.0f )
        throw engine::EngineVector4DivByZero();

    engine::Vector4F r;
    r._x = a._x / b;
    r._y = a._y / b;
    r._z = a._z / b;
    r._t = a._t / b;
    return r;
}

engine::Vector4F operator/(const engine::Vector4F& a, int b) noexcept(false) {
    return operator/(a, (float)b);
}

engine::Vector4F operator^(const engine::Vector4F& a, float b) noexcept {
    engine::Vector4F r;
    r._x = powf(a._x, b);
    r._y = powf(a._y, b);
    r._z = powf(a._z, b);
    r._t = powf(a._t, b);
    return r;
}

engine::Vector4F operator^(const engine::Vector4F& a, int b) noexcept {
    return operator^(a, (float)b);
}

engine::Vector4F& engine::Vector4F::operator=(const Vector4F& obj) noexcept {
    if( this == &obj )
        return *this;

    this->_x = obj._x;
    this->_y = obj._y;
    this->_z = obj._z;
    this->_t = obj._t;
    return *this;
}

engine::Vector4F& engine::Vector4F::operator+=(const Vector4F& obj) noexcept {
    this->_x += obj._x;
    this->_y += obj._y;
    this->_z += obj._z;
    this->_t += obj._t;
    return *this;
}

engine::Vector4F& engine::Vector4F::operator-=(const Vector4F& obj) noexcept {
    this->_x -= obj._x;
    this->_y -= obj._y;
    this->_z -= obj._z;
    this->_t -= obj._t;
    return *this;
}

engine::Vector4F& engine::Vector4F::operator*=(float op) noexcept {
    this->_x *= op;
    this->_y *= op;
    this->_z *= op;
    this->_t *= op;
    return *this;
}

engine::Vector4F& engine::Vector4F::operator*=(int op) noexcept {
    return this->operator*=((float)op);
}

engine::Vector4F& engine::Vector4F::operator/=(float op) noexcept(false) {
    if( op == 0.0f )
        throw EngineVector4DivByZero();

    this->_x /= op;
    this->_y /= op;
    this->_z /= op;
    this->_t /= op;
    return *this;
}

engine::Vector4F& engine::Vector4F::operator/=(int op) noexcept(false) {
    return this->operator/=((float)op);
}

engine::Vector4F& engine::Vector4F::operator^=(float op) noexcept {
    this->_x = powf(this->_x, op);
    this->_y = powf(this->_y, op);
    this->_z = powf(this->_z, op);
    this->_t = powf(this->_z, op);
    return *this;
}

engine::Vector4F& engine::Vector4F::operator^=(int op) noexcept {
    return this->operator^=((float) op);
}

bool operator==(const engine::Vector4F& a, const engine::Vector4F& b) noexcept {
    return a._x == b._x && a._y == b._y && a._z == b._z && a._t == b._t;
}

bool operator!=(const engine::Vector4F& a, const engine::Vector4F& b) noexcept {
    return a._x != b._z || a._y != b._y || a._z != b._z || a._t != b._t;
}

engine::Vector4F::operator Vector4D() const {
    return Vector4D(
        (double) this->_x,
        (double) this->_y,
        (double) this->_z,
        (double) this->_t
    );
}

engine::Vector4F::Vector4F(const Vector4D &obj) noexcept {
    this->_x = (float)obj.getX();
    this->_y = (float)obj.getY();
    this->_z = (float)obj.getZ();
    this->_t = (float)obj.getT();
}

engine::Vector4F &engine::Vector4F::operator=(const Vector4D & obj) noexcept {
    this->_x = (float)obj.getX();
    this->_y = (float)obj.getY();
    this->_z = (float)obj.getZ();
    this->_t = (float)obj.getT();

    return *this;
}

engine::Vector4D operator+ (const engine::Vector4D& a ,const engine::Vector4D& b) noexcept {
    engine::Vector4D r;
    r._x = a._x + b._x;
    r._y = a._y + b._y;
    r._z = a._z + b._z;
    r._t = a._t + b._t;
    return r;
}

engine::Vector4D operator- (const engine::Vector4D& a, const engine::Vector4D& b) noexcept {
    engine::Vector4D r;
    r._x = a._x - b._x;
    r._y = a._y - b._y;
    r._z = a._z - b._z;
    r._t = a._t - b._t;
    return r;
}

engine::Vector4D operator*(const engine::Vector4D& a, double b) noexcept {
    engine::Vector4D r;
    r._x = a._x * b;
    r._y = a._y * b;
    r._z = a._z * b;
    r._t = a._t * b;
    return r;
}

engine::Vector4D operator*(const engine::Vector4D& a, int b) noexcept {
    return operator*(a, (double)b);
}

engine::Vector4D operator/(const engine::Vector4D& a, double b) noexcept(false) {
    if( b == 0.0f )
        throw engine::EngineVector4DivByZero();

    engine::Vector4D r;
    r._x = a._x / b;
    r._y = a._y / b;
    r._z = a._z / b;
    r._t = a._t / b;
    return r;
}

engine::Vector4D operator/(const engine::Vector4D& a, int b) noexcept(false) {
    return operator/(a, (double)b);
}

engine::Vector4D operator^(const engine::Vector4D& a, double b) noexcept {
    engine::Vector4D r;
    r._x = pow(a._x, b);
    r._y = pow(a._y, b);
    r._z = pow(a._z, b);
    r._t = pow(a._t, b);
    return r;
}

engine::Vector4D operator^(const engine::Vector4D& a, int b) noexcept {
    return operator^(a, (double)b);
}

engine::Vector4D& engine::Vector4D::operator=(const engine::Vector4D& obj) noexcept {
    if( this == &obj )
        return *this;

    this->_x = obj._x;
    this->_y = obj._y;
    this->_z = obj._z;
    this->_t = obj._t;
    return *this;
}

engine::Vector4D& engine::Vector4D::operator+=(const engine::Vector4D& obj) noexcept {
    this->_x += obj._x;
    this->_y += obj._y;
    this->_z += obj._z;
    this->_t += obj._t;
    return *this;
}

engine::Vector4D& engine::Vector4D::operator-=(const engine::Vector4D& obj) noexcept {
    this->_x -= obj._x;
    this->_y -= obj._y;
    this->_z -= obj._z;
    this->_t -= obj._t;
    return *this;
}

engine::Vector4D& engine::Vector4D::operator*=(double op) noexcept {
    this->_x *= op;
    this->_y *= op;
    this->_z *= op;
    this->_t *= op;
    return *this;
}

engine::Vector4D& engine::Vector4D::operator*=(int op) noexcept {
    return this->operator*=((double)op);
}

engine::Vector4D& engine::Vector4D::operator/=(double op) noexcept(false) {
    if( op == 0.0f )
        throw EngineVector4DivByZero();

    this->_x /= op;
    this->_y /= op;
    this->_z /= op;
    this->_t /= op;
    return *this;
}

engine::Vector4D& engine::Vector4D::operator/=(int op) noexcept(false) {
    return this->operator/=((double)op);
}

engine::Vector4D& engine::Vector4D::operator^=(double op) noexcept {
    this->_x = pow(this->_x, op);
    this->_y = pow(this->_y, op);
    this->_z = pow(this->_z, op);
    this->_t = pow(this->_z, op);
    return *this;
}

engine::Vector4D& engine::Vector4D::operator^=(int op) noexcept {
    return this->operator^=((double) op);
}

bool operator==(const engine::Vector4D& a, const engine::Vector4D& b) noexcept {
    return a._x == b._x && a._y == b._y && a._z == b._z && a._t == b._t;
}

bool operator!=(const engine::Vector4D& a, const engine::Vector4D& b) noexcept {
    return a._x != b._z || a._y != b._y || a._z != b._z || a._t != b._t;
}

[[maybe_unused]] engine::Vector4D::Vector4D(const Vector4F & obj) noexcept {
    this->_x = (double)obj.getX();
    this->_y = (double)obj.getY();
    this->_z = (double)obj.getZ();
    this->_t = (double)obj.getT();
}

engine::Vector4D::operator Vector4F() const {
    return Vector4F(*this);
}

engine::Vector4D &engine::Vector4D::operator=(const Vector4F & obj) noexcept {
    this->_x = (double)obj.getX();
    this->_y = (double)obj.getY();
    this->_z = (double)obj.getZ();
    this->_t = (double)obj.getT();

    return *this;
}
