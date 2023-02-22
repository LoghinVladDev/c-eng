//
// Created by vladl on 13/07/2020.
//

#include "Vector2.h"

[[maybe_unused]] [[nodiscard]] bool engine::Vector2F::isNull() const noexcept {
    return this->_x == 0.0f && this->_y == 0.0f;
}

[[maybe_unused]] [[nodiscard]] std::string engine::Vector2F::toString() const noexcept {
    return
        "Vector2F { x = " +
        std::to_string(this->_x) +
        ", y = " +
        std::to_string(this->_y) +
        " }";
}

[[maybe_unused]] engine::Vector2F::operator std::string() const {
    return this->toString();
}

[[maybe_unused]] engine::Vector2F::operator Vector2D() const {
    return Vector2D((double)this->_x, (double)this->_y);
}

engine::Vector2F (operator+)(const engine::Vector2F& a, float b) noexcept {
    engine::Vector2F r;

    r._x = a._x + b;
    r._y = a._y + b;
    return r;
}

engine::Vector2F (operator-)(const engine::Vector2F& a, float b) noexcept {
    engine::Vector2F r;

    r._x = a._x - b;
    r._y = a._y - b;
    return r;
}

engine::Vector2F (operator+)(const engine::Vector2F& a, const engine::Vector2F& b) noexcept {
    engine::Vector2F r;

    r._x = a._x + b._x;
    r._y = a._y + b._y;
    return r;
}

engine::Vector2F (operator-)(const engine::Vector2F& a, const engine::Vector2F& b) noexcept {
    engine::Vector2F r;

    r._x = a._x - b._x;
    r._y = a._y - b._y;
    return r;
}

engine::Vector2F (operator*)(const engine::Vector2F& a, float b) noexcept {
    engine::Vector2F r;

    r._x = a._x * b;
    r._y = a._y * b;
    return r;
}

engine::Vector2F (operator*)(const engine::Vector2F& a, int b) noexcept {
    return operator*(a, (float) b);
}

engine::Vector2F (operator/)(const engine::Vector2F& a, float b) noexcept (false) {
    if(b == 0.0f)
        throw engine::EngineVector2DivByZero();

    engine::Vector2F r;

    r._x = a._x / b;
    r._y = a._y / b;
    return r;
}

engine::Vector2F (operator/)(const engine::Vector2F& a, int b) noexcept (false) {
    return operator/(a, (float) b);
}

engine::Vector2F (operator^)(const engine::Vector2F& a, float b) noexcept {
    engine::Vector2F r;

    r._x = powf(a._x, b);
    r._y = powf(a._y, b);
    return r;
}

engine::Vector2F (operator^)(const engine::Vector2F& a, int b) noexcept {
    return operator^ (a, (float)b);
}

engine::Vector2F engine::Vector2F::operator-() const noexcept {
    return Vector2F(-(this->_x), -(this->_y));
}

engine::Vector2F& engine::Vector2F::operator=(const engine::Vector2F& obj) noexcept {
    if(this == &obj)
        return *this;

    this->_x = obj._x;
    this->_y = obj._y;
    return *this;
}

engine::Vector2F& engine::Vector2F::operator=(const engine::Vector2D& obj) noexcept {
    this->_x = (float) obj.getX();
    this->_y = (float) obj.getY();
    return *this;
}

engine::Vector2F& engine::Vector2F::operator+=(const engine::Vector2F& obj) noexcept {
    this->_x += obj._x;
    this->_y += obj._y;
    return *this;
}
engine::Vector2F& engine::Vector2F::operator-=(const engine::Vector2F& obj) noexcept {
    this->_x -= obj._x;
    this->_y -= obj._y;
    return *this;
}

engine::Vector2F& engine::Vector2F::operator*=(float obj) noexcept {
    this->_x *= obj;
    this->_y *= obj;
    return *this;
}

engine::Vector2F& engine::Vector2F::operator*=(int obj) noexcept {
    return this->operator*=((float)obj);
}

engine::Vector2F& engine::Vector2F::operator/=(float obj) noexcept (false) {
    if(obj == 0.0f)
        throw engine::EngineVector2DivByZero();

    this->_x /= obj;
    this->_y /= obj;
    return *this;
}

engine::Vector2F& engine::Vector2F::operator/=(int obj) noexcept (false) {
    return this->operator/=((float)obj);
}

engine::Vector2F& engine::Vector2F::operator^=(float obj) noexcept {
    this->_x = powf(this->_x, obj);
    this->_y = powf(this->_y, obj);
    return *this;
}

engine::Vector2F& engine::Vector2F::operator^=(int obj) noexcept {
    return this->operator^=((float) obj);
}

[[maybe_unused]] [[nodiscard]] float engine::Vector2F::length() const noexcept {
    return sqrtf( powf(this->_x, 2.0f) + powf(this->_y, 2.0f) );
}

[[maybe_unused]] [[nodiscard]] engine::Vector2F engine::Vector2F::normalize() const noexcept {
    return (*this) / this->length();
}

float engine::Vector2F::dotProduct(const engine::Vector2F & a, const engine::Vector2F & b, float angle) noexcept {
    return a.length() * b.length() * std::cos(angle);
}

bool engine::Vector2F::perpendicular(const engine::Vector2F &, const engine::Vector2F &) noexcept {
    return false;
}

bool engine::Vector2F::orthogonal(const engine::Vector2F &, const engine::Vector2F &) noexcept {
    return false;
}

bool engine::Vector2F::parallel(const engine::Vector2F &, const engine::Vector2F &) noexcept {
    return false;
}

float engine::Vector2F::getAngle(const engine::Vector2F & a, const engine::Vector2F & b) noexcept {
    return std::acos(( a * b ) / ( a.length() * b.length() ));
}

double engine::Vector2D::getAngle(const Vector2D & a, const Vector2D & b) noexcept {
    return std::acos(( a * b ) / ( a.length() * b.length() ));
}

[[maybe_unused]] [[nodiscard]] double engine::Vector2D::length() const noexcept {
    return sqrt( pow(this->_x, 2.0) + pow(this->_y, 2.0) );
}

[[maybe_unused]] [[nodiscard]] engine::Vector2D engine::Vector2D::normalize() const noexcept {
    return (*this) / this->length();
}

bool (operator==)(const engine::Vector2F& a,const engine::Vector2F& b) noexcept {
    return a._x == b._x && a._y == b._y;
}

bool (operator!=)(const engine::Vector2F& a,const engine::Vector2F& b) noexcept {
    return a._x != b._x || a._y != b._y;
}

[[maybe_unused]] [[nodiscard]] bool engine::Vector2D::isNull() const noexcept {
    return this->_x == 0.0f && this->_y == 0.0f;
}

[[maybe_unused]] [[nodiscard]] std::string engine::Vector2D::toString() const noexcept {
    return
            "Vector2D { x = " +
            std::to_string(this->_x) +
            ", y = " +
            std::to_string(this->_y) +
            " }";
}

[[maybe_unused]] engine::Vector2D::operator std::string() const {
    return this->toString();
}

[[maybe_unused]] engine::Vector2D::operator Vector2F() const {
    return Vector2F((float)this->_x, (float)this->_y);
}

engine::Vector2D (operator+)(const engine::Vector2D& a, double b) noexcept {
    engine::Vector2D r;

    r._x = a._x + b;
    r._y = a._y + b;
    return r;
}

engine::Vector2D (operator-)(const engine::Vector2D& a, double b) noexcept {
    engine::Vector2D r;

    r._x = a._x - b;
    r._y = a._y - b;
    return r;
}

engine::Vector2D (operator+)(const engine::Vector2D& a, const engine::Vector2D& b) noexcept {
    engine::Vector2D r;

    r._x = a._x + b._x;
    r._y = a._y + b._y;
    return r;
}

engine::Vector2D (operator-)(const engine::Vector2D& a, const engine::Vector2D& b) noexcept {
    engine::Vector2D r;

    r._x = a._x - b._x;
    r._y = a._y - b._y;
    return r;
}

engine::Vector2D (operator*)(const engine::Vector2D& a, double b) noexcept {
    engine::Vector2D r;

    r._x = a._x * b;
    r._y = a._y * b;
    return r;
}

engine::Vector2D (operator*)(const engine::Vector2D& a, int b) noexcept {
    return operator*(a, (double) b);
}

engine::Vector2D (operator/)(const engine::Vector2D& a, double b) noexcept (false) {
    if(b == 0.0f)
        throw engine::EngineVector2DivByZero();

    engine::Vector2D r;

    r._x = a._x / b;
    r._y = a._y / b;
    return r;
}

engine::Vector2D (operator/)(const engine::Vector2D& a, int b) noexcept (false) {
    return operator/(a, (double) b);
}

engine::Vector2D (operator^)(const engine::Vector2D& a, double b) noexcept {
    engine::Vector2D r;

    r._x = pow(a._x, b);
    r._y = pow(a._y, b);
    return r;
}

engine::Vector2D (operator^)(const engine::Vector2D& a, int b) noexcept {
    return operator^ (a, (double)b);
}

engine::Vector2D engine::Vector2D::operator-() const noexcept {
    return Vector2D(-(this->_x), -(this->_y));
}

engine::Vector2D& engine::Vector2D::operator=(const engine::Vector2D& obj) noexcept {
    if(this == &obj)
        return *this;

    this->_x = obj._x;
    this->_y = obj._y;
    return *this;
}

engine::Vector2D& engine::Vector2D::operator=(const engine::Vector2F& obj) noexcept {
    this->_x = (double) obj.getX();
    this->_y = (double) obj.getY();
    return *this;
}

engine::Vector2D& engine::Vector2D::operator+=(const engine::Vector2D& obj) noexcept {
    this->_x += obj._x;
    this->_y += obj._y;
    return *this;
}
engine::Vector2D& engine::Vector2D::operator-=(const engine::Vector2D& obj) noexcept {
    this->_x -= obj._x;
    this->_y -= obj._y;
    return *this;
}

engine::Vector2D& engine::Vector2D::operator*=(double obj) noexcept {
    this->_x *= obj;
    this->_y *= obj;
    return *this;
}

engine::Vector2D& engine::Vector2D::operator*=(int obj) noexcept {
    return this->operator*=((double)obj);
}

engine::Vector2D& engine::Vector2D::operator/=(double obj) noexcept (false) {
    if(obj == 0.0f)
        throw engine::EngineVector2DivByZero();

    this->_x /= obj;
    this->_y /= obj;
    return *this;
}

engine::Vector2D& engine::Vector2D::operator/=(int obj) noexcept (false) {
    return this->operator/=((double)obj);
}

engine::Vector2D& engine::Vector2D::operator^=(double obj) noexcept {
    this->_x = pow(this->_x, obj);
    this->_y = pow(this->_y, obj);
    return *this;
}

engine::Vector2D& engine::Vector2D::operator^=(int obj) noexcept {
    return this->operator^=((double) obj);
}

double engine::Vector2D::dotProduct(const engine::Vector2D & a, const engine::Vector2D & b, double angle) noexcept {
    return a.length() * b.length() * std::cos(angle);
}

bool engine::Vector2D::perpendicular(const engine::Vector2D &, const engine::Vector2D &) noexcept {
    return false;
}

bool engine::Vector2D::orthogonal(const engine::Vector2D &, const engine::Vector2D &) noexcept {
    return false;
}

bool engine::Vector2D::parallel(const engine::Vector2D &, const engine::Vector2D &) noexcept {
    return false;
}

bool (operator==)(const engine::Vector2D& a,const engine::Vector2D& b) noexcept {
    return a._x == b._x && a._y == b._y;
}

bool (operator!=)(const engine::Vector2D& a,const engine::Vector2D& b) noexcept {
    return a._x != b._x || a._y != b._y;
}

float (operator*)(const engine::Vector2F& a, const engine::Vector2F& b) noexcept {
    return a._x * b._x + a._y * b._y;
}

double (operator*)(const engine::Vector2D& a, const engine::Vector2D& b) noexcept {
    return a._x * b._x + a._y * b._y;
}