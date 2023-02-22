//
// Created by vladl on 05/07/2020.
//

#include "Vector.h"

[[maybe_unused]] engine::VectorF engine::VectorF::nullVector = VectorF(0.0f, 0.0f, 0.0f);
[[maybe_unused]] engine::VectorD engine::VectorD::nullVector = VectorD(0.0,  0.0,  0.0);
//[[maybe_unused]] inline engine::VectorF::VectorF() noexcept = default;

//[[maybe_unused]] inline VectorF::VectorF(const VectorF & vector) noexcept = default;

[[maybe_unused]] [[nodiscard]] inline bool engine::VectorF::isNull() const noexcept {
    return this->_x == 0 && this->_y == 0 && this->_z == 0;
}

[[maybe_unused]] [[nodiscard]] inline std::string engine::VectorF::toString() const noexcept {
    return
        std::string("VectorF { x = ") +
        std::to_string(this->_x) +
        ", y = " +
        std::to_string(this->_y) +
        ", z = " +
        std::to_string(this->_z) +
        " }";
}

[[maybe_unused]] engine::VectorF::operator std::string() const {
    return this->toString();
}

[[maybe_unused]] inline engine::VectorD::VectorD() noexcept = default;

[[maybe_unused]] inline engine::VectorD::VectorD(double x, double y, double z) noexcept :
        _x(x), _y(y), _z(z) {

}

[[maybe_unused]] inline engine::VectorD::VectorD(const VectorD & vector) noexcept = default;

[[maybe_unused]] [[nodiscard]] inline bool engine::VectorD::isNull() const noexcept {
    return this->_x == 0 && this->_y == 0 && this->_z == 0;
}

[[maybe_unused]] inline engine::VectorD& engine::VectorD::setX(double x) noexcept {
    this->_x = x;
    return *this;
}

[[maybe_unused]] inline engine::VectorD &engine::VectorD::setY(double y) noexcept{
    this->_y = y;
    return *this;
}

[[maybe_unused]] inline engine::VectorD &engine::VectorD::setZ(double z) noexcept {
    this->_z = z;
    return *this;
}

[[maybe_unused]] [[nodiscard]] inline double engine::VectorD::getX() const noexcept {
    return this->_x;
}

[[maybe_unused]] [[nodiscard]] inline double engine::VectorD::getY() const noexcept {
    return this->_y;
}

[[maybe_unused]] [[nodiscard]] inline double engine::VectorD::getZ() const noexcept {
    return this->_z;
}

[[maybe_unused]] [[nodiscard]] inline std::string engine::VectorD::toString() const noexcept {
    return
            std::string("VectorD { x = ") +
            std::to_string(this->_x) +
            ", y = " +
            std::to_string(this->_y) +
            ", z = " +
            std::to_string(this->_z) +
            " }";
}

[[maybe_unused]] engine::VectorD::operator std::string() const {
    return this->toString();
}

engine::VectorF operator+ (const engine::VectorF& a, const float b) noexcept {
    engine::VectorF r;
    r._x = a._x + b;
    r._y = a._y + b;
    r._z = a._z + b;
    return r;
}

engine::VectorF operator- (const engine::VectorF& a, const float b) noexcept {
    engine::VectorF r;
    r._x = a._x - b;
    r._y = a._y - b;
    r._z = a._z - b;
    return r;
}

engine::VectorF operator+ (const engine::VectorF& a ,const engine::VectorF& b) noexcept {
    engine::VectorF r;
    r._x = a._x + b._x;
    r._y = a._y + b._y;
    r._z = a._z + b._z;
    return r;
}

engine::VectorF operator- (const engine::VectorF& a, const engine::VectorF& b) noexcept {
    engine::VectorF r;
    r._x = a._x - b._x;
    r._y = a._y - b._y;
    r._z = a._z - b._z;
    return r;
}

engine::VectorF engine::VectorF::operator-() const noexcept {
    return VectorF(-(this->_x), -(this->_y), -(this->_z));
}

engine::VectorF operator*(const engine::VectorF& a, float b) noexcept {
    engine::VectorF r;
    r._x = a._x * b;
    r._y = a._y * b;
    r._z = a._z * b;
    return r;
}

engine::VectorF operator*(const engine::VectorF& a, int b) noexcept {
    return operator*(a, (float)b);
}

engine::VectorF operator/(const engine::VectorF& a, float b) noexcept(false) {
    if( b == 0.0f )
        throw engine::EngineVectorDivByZero();

    engine::VectorF r;
    r._x = a._x / b;
    r._y = a._y / b;
    r._z = a._z / b;
    return r;
}

engine::VectorF operator/(const engine::VectorF& a, int b) noexcept(false) {
    return operator/(a, (float)b);
}

engine::VectorF operator^(const engine::VectorF& a, float b) noexcept {
    engine::VectorF r;
    r._x = powf(a._x, b);
    r._y = powf(a._y, b);
    r._z = powf(a._z, b);
    return r;
}

engine::VectorF operator^(const engine::VectorF& a, int b) noexcept {
    return operator^(a, (float)b);
}

engine::VectorF& engine::VectorF::operator=(const VectorF& obj) noexcept {
    if( this == &obj )
        return *this;

    this->_x = obj._x;
    this->_y = obj._y;
    this->_z = obj._z;
    return *this;
}

engine::VectorF& engine::VectorF::operator+=(const VectorF& obj) noexcept {
    this->_x += obj._x;
    this->_y += obj._y;
    this->_z += obj._z;
    return *this;
}

engine::VectorF& engine::VectorF::operator-=(const VectorF& obj) noexcept {
    this->_x -= obj._x;
    this->_y -= obj._y;
    this->_z -= obj._z;
    return *this;
}

engine::VectorF& engine::VectorF::operator*=(float op) noexcept {
    this->_x *= op;
    this->_y *= op;
    this->_z *= op;
    return *this;
}

engine::VectorF& engine::VectorF::operator*=(int op) noexcept {
    return this->operator*=((float)op);
}

engine::VectorF& engine::VectorF::operator/=(float op) noexcept(false) {
    if( op == 0.0f )
        throw EngineVectorDivByZero();

    this->_x /= op;
    this->_y /= op;
    this->_z /= op;
    return *this;
}

engine::VectorF& engine::VectorF::operator/=(int op) noexcept(false) {
    return this->operator/=((float)op);
}

engine::VectorF& engine::VectorF::operator^=(float op) noexcept {
    this->_x = powf(this->_x, op);
    this->_y = powf(this->_y, op);
    this->_z = powf(this->_z, op);
    return *this;
}

engine::VectorF& engine::VectorF::operator^=(int op) noexcept {
    return this->operator^=((float) op);
}

bool operator==(const engine::VectorF& a, const engine::VectorF& b) noexcept {
    return a._x == b._x && a._y == b._y && a._z == b._z;
}

bool operator!=(const engine::VectorF& a, const engine::VectorF& b) noexcept {
    return a._x != b._z || a._y != b._y || a._z != b._z;
}

engine::VectorF::operator VectorD() const {
    return VectorD(
        (double) this->_x,
        (double) this->_y,
        (double) this->_z
    );
}

engine::VectorF::VectorF(const VectorD &obj) noexcept {
    this->_x = (float)obj.getX();
    this->_y = (float)obj.getY();
    this->_z = (float)obj.getZ();
}

[[maybe_unused]] [[nodiscard]] float engine::VectorF::length() const noexcept {
    return sqrtf( powf(this->_x, 2.0f) + powf(this->_y, 2.0f) + powf(this->_z, 2.0f) );
}

engine::VectorF &engine::VectorF::operator=(const VectorD & obj) noexcept {
    this->_x = (float)obj.getX();
    this->_y = (float)obj.getY();
    this->_z = (float)obj.getZ();

    return *this;
}

[[maybe_unused]] [[nodiscard]] engine::VectorF engine::VectorF::normalize() const noexcept {
    return (*this) / this->length();
}

float engine::VectorF::getAngle(const engine::VectorF & a, const engine::VectorF & b) noexcept {
    return std::acos((a * b) / (a.length() * b.length()));
}

double engine::VectorD::getAngle(const VectorD & a, const VectorD & b) noexcept {
    return std::acos((a * b) / (a.length() * b.length()));
}

engine::VectorF operator^ (const engine::VectorF& a, const engine::VectorF& b) noexcept {
    return engine::VectorF(
            a._y * b._z - a._z * b._y,
            a._z * b._x - a._x * b._z,
            a._x * b._y - a._y * b._x
    );
}

engine::VectorD operator^ (const engine::VectorD& a, const engine::VectorD& b) noexcept {
    return engine::VectorD(
            a._y * b._z - a._z * b._y,
            a._z * b._x - a._x * b._z,
            a._x * b._y - a._y * b._x
    );
}

engine::VectorD operator+ (const engine::VectorD& a ,const engine::VectorD& b) noexcept {
    engine::VectorD r;
    r._x = a._x + b._x;
    r._y = a._y + b._y;
    r._z = a._z + b._z;
    return r;
}

engine::VectorD operator- (const engine::VectorD& a, const engine::VectorD& b) noexcept {
    engine::VectorD r;
    r._x = a._x - b._x;
    r._y = a._y - b._y;
    r._z = a._z - b._z;
    return r;
}

engine::VectorD operator*(const engine::VectorD& a, double b) noexcept {
    engine::VectorD r;
    r._x = a._x * b;
    r._y = a._y * b;
    r._z = a._z * b;
    return r;
}

engine::VectorD operator*(const engine::VectorD& a, int b) noexcept {
    return operator*(a, (double)b);
}

engine::VectorD operator/(const engine::VectorD& a, double b) noexcept(false) {
    if( b == 0.0f )
        throw engine::EngineVectorDivByZero();

    engine::VectorD r;
    r._x = a._x / b;
    r._y = a._y / b;
    r._z = a._z / b;
    return r;
}

engine::VectorD operator/(const engine::VectorD& a, int b) noexcept(false) {
    return operator/(a, (double)b);
}

engine::VectorD operator^(const engine::VectorD& a, double b) noexcept {
    engine::VectorD r;
    r._x = pow(a._x, b);
    r._y = pow(a._y, b);
    r._z = pow(a._z, b);
    return r;
}

engine::VectorD operator^(const engine::VectorD& a, int b) noexcept {
    return operator^(a, (double)b);
}

engine::VectorD& engine::VectorD::operator=(const engine::VectorD& obj) noexcept {
    if( this == &obj )
        return *this;

    this->_x = obj._x;
    this->_y = obj._y;
    this->_z = obj._z;
    return *this;
}

engine::VectorD& engine::VectorD::operator+=(const engine::VectorD& obj) noexcept {
    this->_x += obj._x;
    this->_y += obj._y;
    this->_z += obj._z;
    return *this;
}

engine::VectorD& engine::VectorD::operator-=(const engine::VectorD& obj) noexcept {
    this->_x -= obj._x;
    this->_y -= obj._y;
    this->_z -= obj._z;
    return *this;
}

engine::VectorD& engine::VectorD::operator*=(double op) noexcept {
    this->_x *= op;
    this->_y *= op;
    this->_z *= op;
    return *this;
}

engine::VectorD& engine::VectorD::operator*=(int op) noexcept {
    return this->operator*=((double)op);
}

engine::VectorD& engine::VectorD::operator/=(double op) noexcept(false) {
    if( op == 0.0f )
        throw EngineVectorDivByZero();

    this->_x /= op;
    this->_y /= op;
    this->_z /= op;
    return *this;
}

engine::VectorD& engine::VectorD::operator/=(int op) noexcept(false) {
    return this->operator/=((double)op);
}

engine::VectorD& engine::VectorD::operator^=(double op) noexcept {
    this->_x = pow(this->_x, op);
    this->_y = pow(this->_y, op);
    this->_z = pow(this->_z, op);
    return *this;
}

engine::VectorD& engine::VectorD::operator^=(int op) noexcept {
    return this->operator^=((double) op);
}

bool operator==(const engine::VectorD& a, const engine::VectorD& b) noexcept {
    return a._x == b._x && a._y == b._y && a._z == b._z;
}

bool operator!=(const engine::VectorD& a, const engine::VectorD& b) noexcept {
    return a._x != b._z || a._y != b._y || a._z != b._z;
}

[[maybe_unused]] engine::VectorD::VectorD(const VectorF & obj) noexcept {
    this->_x = (double)obj.getX();
    this->_y = (double)obj.getY();
    this->_z = (double)obj.getZ();
}

engine::VectorD::operator VectorF() const {
    return VectorF(*this);
}
 // v * w = len(v) * len(w) * cos(angl)
engine::VectorD &engine::VectorD::operator=(const VectorF & obj) noexcept {
    this->_x = (double)obj.getX();
    this->_y = (double)obj.getY();
    this->_z = (double)obj.getZ();

    return *this;
}

[[maybe_unused]] [[nodiscard]] double engine::VectorD::length() const noexcept {
    return sqrt( pow(this->_x, 2.0) + pow(this->_y, 2.0) + pow(this->_z, 2.0) );
}

[[maybe_unused]] [[nodiscard]] engine::VectorD engine::VectorD::normalize() const noexcept {
    return (*this) / this->length();
}

float operator* (const engine::VectorF& a, const engine::VectorF& b) noexcept {
    return a._x * b._x + a._y * b._y + a._z * b._z;
}

double operator* (const engine::VectorD& a, const engine::VectorD& b) noexcept {
    return a._x * b._x + a._y * b._y + a._z * b._z;
}