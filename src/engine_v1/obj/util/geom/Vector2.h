//
// Created by vladl on 13/07/2020.
//

#ifndef ENG1_VECTOR2_H
#define ENG1_VECTOR2_H

#include <string>
#include <cmath>
#include <exception>

namespace engine { class Vector2F; class Vector2D; }

engine::Vector2F operator+ (const engine::Vector2F&, float) noexcept;
engine::Vector2F operator- (const engine::Vector2F&, float) noexcept;
engine::Vector2F operator+ (const engine::Vector2F&, const engine::Vector2F&) noexcept;
engine::Vector2F operator- (const engine::Vector2F&, const engine::Vector2F&) noexcept;
engine::Vector2F operator* (const engine::Vector2F&, float) noexcept;
engine::Vector2F operator* (const engine::Vector2F&, int) noexcept;
engine::Vector2F operator/ (const engine::Vector2F&, float) noexcept (false);
engine::Vector2F operator/ (const engine::Vector2F&, int) noexcept (false);
engine::Vector2F operator^ (const engine::Vector2F&, float) noexcept;
engine::Vector2F operator^ (const engine::Vector2F&, int) noexcept;

float operator* (const engine::Vector2F&, const engine::Vector2F&) noexcept;

engine::Vector2D operator+ (const engine::Vector2D&, double) noexcept;
engine::Vector2D operator- (const engine::Vector2D&, double) noexcept;
engine::Vector2D operator+ (const engine::Vector2D&, const engine::Vector2D&) noexcept;
engine::Vector2D operator- (const engine::Vector2D&, const engine::Vector2D&) noexcept;
engine::Vector2D operator* (const engine::Vector2D&, double) noexcept;
engine::Vector2D operator* (const engine::Vector2D&, int) noexcept;
engine::Vector2D operator/ (const engine::Vector2D&, double) noexcept (false);
engine::Vector2D operator/ (const engine::Vector2D&, int) noexcept (false);
engine::Vector2D operator^ (const engine::Vector2D&, double) noexcept;
engine::Vector2D operator^ (const engine::Vector2D&, int) noexcept;

double operator* (const engine::Vector2D&, const engine::Vector2D&) noexcept;

bool operator==(const engine::Vector2F&, const engine::Vector2F&) noexcept;
bool operator!=(const engine::Vector2F&, const engine::Vector2F&) noexcept;

bool operator==(const engine::Vector2D&, const engine::Vector2D&) noexcept;
bool operator!=(const engine::Vector2D&, const engine::Vector2D&) noexcept;

namespace engine {

    class [[maybe_unused]] EngineVector2DivByZero : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Tried dividing by zero!";
        }
    };

    class Vector2F {
    private:
        float _x {0.0f};
        float _y {0.0f};

    public:
        [[maybe_unused]] static Vector2F nullVector;

        [[maybe_unused]] Vector2F() noexcept = default;
        [[maybe_unused]] Vector2F(float x, float y) noexcept : _x(x), _y(y) { }

        [[maybe_unused]] [[nodiscard]] bool isNull() const noexcept;

        [[maybe_unused]] Vector2F &setX(float x) noexcept {
            this->_x = x;
            return *this;
        }

        [[maybe_unused]] Vector2F &setY(float y) noexcept {
            this->_y = y;
            return *this;
        }

        [[maybe_unused]] [[nodiscard]] float getX() const noexcept {
            return this->_x;
        }

        [[maybe_unused]] [[nodiscard]] float getY() const noexcept {
            return this->_y;
        }

        [[maybe_unused]] [[nodiscard]] float length() const noexcept;
        [[maybe_unused]] [[nodiscard]] Vector2F normalize() const noexcept;
        [[maybe_unused]] [[nodiscard]] static float dotProduct(const Vector2F&, const Vector2F&, float) noexcept;
        [[maybe_unused]] [[nodiscard]] static bool perpendicular(const Vector2F&, const Vector2F&) noexcept;
        [[maybe_unused]] [[nodiscard]] static bool orthogonal(const Vector2F&, const Vector2F&) noexcept;
        [[maybe_unused]] [[nodiscard]] static bool parallel(const Vector2F&, const Vector2F&) noexcept;
        [[maybe_unused]] [[nodiscard]] static float getAngle(const Vector2F&, const Vector2F&) noexcept;

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
        [[maybe_unused]] explicit operator std::string() const;
        [[maybe_unused]] explicit operator Vector2D() const;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedGlobalDeclarationInspection"

        friend Vector2F (::operator+)(const Vector2F&, float) noexcept;
        friend Vector2F (::operator-)(const Vector2F&, float) noexcept;
        friend Vector2F (::operator+)(const Vector2F&, const Vector2F&) noexcept;
        friend Vector2F (::operator-)(const Vector2F&, const Vector2F&) noexcept;
        friend Vector2F (::operator*)(const Vector2F&, float) noexcept;
        friend Vector2F (::operator*)(const Vector2F&, int) noexcept;
        friend Vector2F (::operator/)(const Vector2F&, float) noexcept (false);
        friend Vector2F (::operator/)(const Vector2F&, int) noexcept (false);
        friend Vector2F (::operator^)(const Vector2F&, float) noexcept;
        friend Vector2F (::operator^)(const Vector2F&, int) noexcept;

        friend float (::operator*)(const Vector2F&, const Vector2F&) noexcept;

#pragma clang diagnostic pop
#pragma clang diagnostic pop

        Vector2F operator-() const noexcept;
        Vector2F& operator=(const Vector2F&) noexcept;
        Vector2F& operator=(const Vector2D&) noexcept;
        Vector2F& operator+=(const Vector2F&) noexcept;
        Vector2F& operator-=(const Vector2F&) noexcept;
        Vector2F& operator*=(float) noexcept;
        Vector2F& operator*=(int) noexcept;
        Vector2F& operator/=(float) noexcept (false);
        Vector2F& operator/=(int) noexcept (false);
        Vector2F& operator^=(float) noexcept;
        Vector2F& operator^=(int) noexcept;

        friend bool (::operator==)(const Vector2F&, const Vector2F&) noexcept;
        friend bool (::operator!=)(const Vector2F&, const Vector2F&) noexcept;
    };

    class Vector2D {

    private:
        double _x {0.0f};
        double _y {0.0f};

    public:
        [[maybe_unused]] static Vector2D nullVector;

        [[maybe_unused]] Vector2D() noexcept = default;
        [[maybe_unused]] Vector2D(double x, double y) noexcept : _x(x), _y(y) { }

        [[maybe_unused]] [[nodiscard]] bool isNull() const noexcept;

        [[maybe_unused]] Vector2D &setX(double x) noexcept {
            this->_x = x;
            return *this;
        }

        [[maybe_unused]] Vector2D &setY(double y) noexcept {
            this->_y = y;
            return *this;
        }

        [[maybe_unused]] [[nodiscard]] double getX() const noexcept {
            return this->_x;
        }

        [[maybe_unused]] [[nodiscard]] double getY() const noexcept {
            return this->_y;
        }

        [[maybe_unused]] [[nodiscard]] double length() const noexcept;
        [[maybe_unused]] [[nodiscard]] Vector2D normalize() const noexcept;
        [[maybe_unused]] [[nodiscard]] static double dotProduct(const Vector2D&, const Vector2D&, double) noexcept;
        [[maybe_unused]] [[nodiscard]] static bool perpendicular(const Vector2D&, const Vector2D&) noexcept;
        [[maybe_unused]] [[nodiscard]] static bool orthogonal(const Vector2D&, const Vector2D&) noexcept;
        [[maybe_unused]] [[nodiscard]] static bool parallel(const Vector2D&, const Vector2D&) noexcept;
        [[maybe_unused]] [[nodiscard]] static double getAngle(const Vector2D&, const Vector2D&) noexcept;

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
        [[maybe_unused]] explicit operator std::string() const;
        [[maybe_unused]] explicit operator Vector2F() const;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedGlobalDeclarationInspection"

        friend Vector2D (::operator+)(const Vector2D&, double) noexcept;
        friend Vector2D (::operator-)(const Vector2D&, double) noexcept;
        friend Vector2D (::operator+)(const Vector2D&, const Vector2D&) noexcept;
        friend Vector2D (::operator-)(const Vector2D&, const Vector2D&) noexcept;
        friend Vector2D (::operator*)(const Vector2D&, double) noexcept;
        friend Vector2D (::operator*)(const Vector2D&, int) noexcept;
        friend Vector2D (::operator/)(const Vector2D&, double) noexcept (false);
        friend Vector2D (::operator/)(const Vector2D&, int) noexcept (false);
        friend Vector2D (::operator^)(const Vector2D&, double) noexcept;
        friend Vector2D (::operator^)(const Vector2D&, int) noexcept;

        friend double (::operator*)(const Vector2D&, const Vector2D&) noexcept;

#pragma clang diagnostic pop
#pragma clang diagnostic pop

        Vector2D operator-() const noexcept;
        Vector2D& operator=(const Vector2D&) noexcept;
        Vector2D& operator=(const Vector2F&) noexcept;
        Vector2D& operator+=(const Vector2D&) noexcept;
        Vector2D& operator-=(const Vector2D&) noexcept;
        Vector2D& operator*=(double) noexcept;
        Vector2D& operator*=(int) noexcept;
        Vector2D& operator/=(double) noexcept (false);
        Vector2D& operator/=(int) noexcept (false);
        Vector2D& operator^=(double) noexcept;
        Vector2D& operator^=(int) noexcept;

        friend bool (::operator==)(const Vector2D&, const Vector2D&) noexcept;
        friend bool (::operator!=)(const Vector2D&, const Vector2D&) noexcept;
    };

    typedef engine::Vector2F Vector2;
}


#endif //ENG1_VECTOR2_H
