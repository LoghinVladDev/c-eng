#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
//
// Created by vladl on 05/07/2020.
//


#pragma once

#ifndef ENG1_VECTOR_H
#define ENG1_VECTOR_H

#include <string>
#include <cmath>
#include <exception>

namespace engine { class VectorF; class VectorD; }

engine::VectorF (operator+)(const engine::VectorF &, const engine::VectorF &) noexcept;
engine::VectorF operator-(const engine::VectorF &, const engine::VectorF &) noexcept;
engine::VectorF operator*(const engine::VectorF &, float) noexcept;
engine::VectorF operator*(const engine::VectorF &, int) noexcept;
engine::VectorF operator/(const engine::VectorF &, float) noexcept(false);
engine::VectorF operator/(const engine::VectorF &, int) noexcept(false);
engine::VectorF operator^(const engine::VectorF &, float) noexcept;
engine::VectorF operator^(const engine::VectorF &, int) noexcept;

engine::VectorD operator+(const engine::VectorD &, const engine::VectorD &) noexcept;
engine::VectorD operator-(const engine::VectorD &, const engine::VectorD &) noexcept;
engine::VectorD operator*(const engine::VectorD &, double) noexcept;
engine::VectorD operator*(const engine::VectorD &, int) noexcept;
engine::VectorD operator/(const engine::VectorD &, double) noexcept(false);
engine::VectorD operator/(const engine::VectorD &, int) noexcept(false);
engine::VectorD operator^(const engine::VectorD &, double) noexcept;
engine::VectorD operator^(const engine::VectorD &, int) noexcept;

bool operator==(const engine::VectorD &, const engine::VectorD &) noexcept;
bool operator!=(const engine::VectorD &, const engine::VectorD &) noexcept;

bool operator==(const engine::VectorF &, const engine::VectorF &) noexcept;
bool operator!=(const engine::VectorF &, const engine::VectorF &) noexcept;

namespace engine {

    class [[maybe_unused]] EngineVectorDivByZero : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Tried dividing by zero!";
        }
    };

    class VectorD;

    class [[maybe_unused]] VectorF {
    private:
        float _x{0.0f};
        float _y{0.0f};
        float _z{0.0f};

    public:
        [[maybe_unused]] [[maybe_unused]] static VectorF nullVector;

        [[maybe_unused]] VectorF() noexcept;

        [[maybe_unused]] VectorF(float x, float y, float z) noexcept:
                _x(x), _y(y), _z(z) {

        }

        [[maybe_unused]] VectorF(const VectorF &) noexcept = default;
        [[maybe_unused]] explicit VectorF(const VectorD &) noexcept;

        [[maybe_unused]] [[nodiscard]] bool isNull() const noexcept;

        [[maybe_unused]] VectorF &setX(float x) noexcept {
            this->_x = x;
            return *this;
        }

        [[maybe_unused]] VectorF &setY(float y) noexcept {
            this->_y = y;
            return *this;
        }

        [[maybe_unused]] VectorF &setZ(float z) noexcept {
            this->_z = z;
            return *this;
        }

        [[maybe_unused]] [[nodiscard]] float getX() const noexcept {
            return this->_x;
        }

        [[maybe_unused]] [[nodiscard]] float getY() const noexcept {
            return this->_y;
        }

        [[maybe_unused]] [[nodiscard]] float getZ() const noexcept {
            return this->_z;
        }

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
        [[maybe_unused]] explicit operator std::string() const;
        [[maybe_unused]] explicit operator VectorD() const;

        friend VectorF (::operator+)(const VectorF &, const VectorF &) noexcept;
        friend VectorF (::operator-)(const VectorF &, const VectorF &) noexcept;
        friend VectorF (::operator*)(const VectorF &, float) noexcept;
        friend VectorF (::operator*)(const VectorF &, int) noexcept;
        friend VectorF (::operator/)(const VectorF &, float) noexcept(false);
        friend VectorF (::operator/)(const VectorF &, int) noexcept(false);
        friend VectorF (::operator^)(const VectorF &, float) noexcept;
        friend VectorF (::operator^)(const VectorF &, int) noexcept;

        VectorF &operator=(const VectorF &) noexcept;
        VectorF &operator=(const VectorD &) noexcept;
        VectorF &operator+=(const VectorF &) noexcept;
        VectorF &operator-=(const VectorF &) noexcept;
        VectorF &operator*=(float) noexcept;
        VectorF &operator*=(int) noexcept;
        VectorF &operator/=(float) noexcept(false);
        VectorF &operator/=(int) noexcept(false);
        VectorF &operator^=(float) noexcept;
        VectorF &operator^=(int) noexcept;

        friend bool (::operator==)(const VectorF &, const VectorF &) noexcept;
        friend bool (::operator!=)(const VectorF &, const VectorF &) noexcept;
    };

    class [[maybe_unused]] VectorD {
    private:
        double _x{0.0f};
        double _y{0.0f};
        double _z{0.0f};

    public:
        [[maybe_unused]] static VectorD nullVector;

        [[maybe_unused]] VectorD() noexcept;
        [[maybe_unused]] VectorD(double x, double y, double z) noexcept;
        [[maybe_unused]] VectorD(const VectorD &) noexcept;
        [[maybe_unused]] explicit VectorD(const VectorF &) noexcept;

        [[maybe_unused]] [[nodiscard]] bool isNull() const noexcept;

        [[maybe_unused]] VectorD &setX(double) noexcept;
        [[maybe_unused]] VectorD &setY(double) noexcept;
        [[maybe_unused]] VectorD &setZ(double) noexcept;

        [[maybe_unused]] [[nodiscard]] double getX() const noexcept;
        [[maybe_unused]] [[nodiscard]] double getY() const noexcept;
        [[maybe_unused]] [[nodiscard]] double getZ() const noexcept;

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept;
        [[maybe_unused]] explicit operator std::string() const;
        [[maybe_unused]] explicit operator VectorF() const;

        friend VectorD (::operator+)(const VectorD &, const VectorD &) noexcept;
        friend VectorD (::operator-)(const VectorD &, const VectorD &) noexcept;
        friend VectorD (::operator*)(const VectorD &, double) noexcept;
        friend VectorD (::operator*)(const VectorD &, int) noexcept;
        friend VectorD (::operator/)(const VectorD &, double) noexcept(false);
        friend VectorD (::operator/)(const VectorD &, int) noexcept(false);
        friend VectorD (::operator^)(const VectorD &, double) noexcept;
        friend VectorD (::operator^)(const VectorD &, int) noexcept;

        VectorD &operator=(const VectorD &) noexcept;
        VectorD &operator=(const VectorF &) noexcept;
        VectorD &operator+=(const VectorD &) noexcept;
        VectorD &operator-=(const VectorD &) noexcept;
        VectorD &operator*=(double) noexcept;
        VectorD &operator*=(int) noexcept;
        VectorD &operator/=(double) noexcept(false);
        VectorD &operator/=(int) noexcept(false);
        VectorD &operator^=(double) noexcept;
        VectorD &operator^=(int) noexcept;

        friend bool (::operator==)(const VectorD &, const VectorD &) noexcept;
        friend bool (::operator!=)(const VectorD &, const VectorD &) noexcept;
    };

    [[maybe_unused]] typedef VectorF Vector;
}
[[maybe_unused]] engine::VectorF engine::VectorF::nullVector = VectorF(0.0f, 0.0f, 0.0f);
[[maybe_unused]] engine::VectorD engine::VectorD::nullVector = VectorD(0.0,  0.0,  0.0);

#ifndef nullvec
#define nullvec engine::VectorF::nullVector
#endif

#pragma clang diagnostic pop
#endif //ENG1_VECTOR_H
