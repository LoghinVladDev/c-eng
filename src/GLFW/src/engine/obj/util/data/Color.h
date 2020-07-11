//
// Created by vladl on 07/07/2020.
//

#ifndef ENG1_COLOR_H
#define ENG1_COLOR_H

#include <src/GLFW/src/engine/types.h>
#include <src/GLFW/src/engine/obj/util/geom/Vector4.h>
#include <src/GLFW/src/engine/obj/util/geom/Vector.h>

namespace engine {

    class Color {
    public:
        constexpr static uint8 RED_MIN = UINT8_MIN;
        constexpr static uint8 RED_MAX = UINT8_MAX;

        constexpr static uint8 GREEN_MIN = UINT8_MIN;
        constexpr static uint8 GREEN_MAX = UINT8_MAX;

        constexpr static uint8 BLUE_MIN = UINT8_MIN;
        constexpr static uint8 BLUE_MAX = UINT8_MAX;

        constexpr static uint8 ALPHA_MIN = UINT8_MIN;
        constexpr static uint8 ALPHA_MAX = UINT8_MAX;

    private:

        uint8 _red{RED_MIN};
        uint8 _blue{BLUE_MIN};
        uint8 _green{GREEN_MIN};
        uint8 _alpha{ALPHA_MAX};

        constexpr static uint8 _convertFloatToColor(float _convert) {
            if (_convert > 1.0f)
                _convert = 1.0f;
            else if (_convert < 0.0f)
                _convert = 0.0f;
            else
                _convert *= 255.0f;
            return (uint8) _convert;
        }

    public:
        Color() = default;

        [[maybe_unused]] [[maybe_unused]] Color(const Color &) = default;

        [[maybe_unused]] explicit Color(uint8, uint8 = GREEN_MIN, uint8 = BLUE_MIN, uint8 = ALPHA_MAX);

        [[maybe_unused]] explicit Color(const VectorF &);
        [[maybe_unused]] explicit Color(const VectorD &);
        [[maybe_unused]] explicit Color(const Vector4F &);
        [[maybe_unused]] explicit Color(const Vector4D &);

        [[maybe_unused]] [[nodiscard]] uint8 getRed() const noexcept { return this->_red; }
        [[maybe_unused]] [[nodiscard]] uint8 getGreen() const noexcept { return this->_green; }
        [[maybe_unused]] [[nodiscard]] uint8 getBlue() const noexcept { return this->_blue; }
        [[maybe_unused]] [[nodiscard]] uint8 getAlpha() const noexcept { return this->_alpha; }

        [[maybe_unused]] [[nodiscard]] VectorF getColorAsVector() const noexcept {
            return VectorF(
                    (float) this->_red / 255.0f,
                    (float) this->_green / 255.0f,
                    (float) this->_blue / 255.0f
            );
        }

        [[maybe_unused]] void setRed(uint8 red = RED_MIN) noexcept { this->_red = red; }
        [[maybe_unused]] void setGreen(uint8 green = GREEN_MIN) noexcept { this->_green = green; }
        [[maybe_unused]] void setBlue(uint8 blue = BLUE_MIN) noexcept { this->_blue = blue; }
        [[maybe_unused]] void setAlpha(uint8 alpha = ALPHA_MAX) noexcept { this->_alpha = alpha; }

        [[maybe_unused]] void set(uint8 red = RED_MIN, uint8 green = GREEN_MIN, uint8 blue = BLUE_MIN, uint8 alpha = ALPHA_MAX) noexcept {
            this->_red = red;
            this->_green = green;
            this->_blue = blue;
            this->_alpha = alpha;
        }

        [[maybe_unused]] void set(const VectorF &color) {
            this->_red = Color::_convertFloatToColor(color.getX());
            this->_green = Color::_convertFloatToColor(color.getY());
            this->_blue = Color::_convertFloatToColor(color.getZ());
        }

        [[maybe_unused]] void set(const VectorD &color) {
            this->_red = Color::_convertFloatToColor((float)color.getX());
            this->_green = Color::_convertFloatToColor((float)color.getY());
            this->_blue = Color::_convertFloatToColor((float)color.getZ());
        }

        [[maybe_unused]] void set(const Vector4F &color) {
            this->_red = Color::_convertFloatToColor(color.getX());
            this->_green = Color::_convertFloatToColor(color.getY());
            this->_blue = Color::_convertFloatToColor(color.getZ());
            this->_alpha = Color::_convertFloatToColor(color.getT());
        }

        [[maybe_unused]] void set(const Vector4D &color) {
            this->_red = Color::_convertFloatToColor((float)color.getX());
            this->_green = Color::_convertFloatToColor((float)color.getY());
            this->_blue = Color::_convertFloatToColor((float)color.getZ());
            this->_alpha = Color::_convertFloatToColor((float)color.getT());
        }

        [[maybe_unused]] void setAsDrawColor() const {
            VectorF _convert = this->getColorAsVector();

            glColor3f(_convert.getX(), _convert.getY(), _convert.getY());
        }

        [[maybe_unused]] [[nodiscard]] std::string toString() const noexcept {
            return "Color { red = " +
                   std::to_string(this->_red) +
                   ", blue = " +
                   std::to_string(this->_blue) +
                   ", green = " +
                   std::to_string(this->_green) +
                   ", alpha = " +
                   std::to_string(this->_alpha) +
                   "}";
        }
    };

}

#endif //ENG1_COLOR_H
