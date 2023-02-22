//
// Created by vladl on 5/25/2021.
//

#ifndef C_ENG_VEVENT_H
#define C_ENG_VEVENT_H

#include <VObject.hpp>

namespace engine {

    class VEvent : public VObject {
    public:
        enum Type : uint8 {
            VEVENT_UNKNOWN          = 0x00u,
            VEVENT_KEY              = 0x01u,
            VEVENT_MOUSE            = 0x02u,
            VEVENT_JOYSTICK         = 0x04u,

            VEVENT_WINDOW_RESIZE    = 0x08u
        };

        [[nodiscard]] constexpr static auto toString (Type type) noexcept -> StringLiteral {
            switch (type) {
                case VEVENT_UNKNOWN:        return "Unknown";
                case VEVENT_KEY:            return "Key Event";
                case VEVENT_MOUSE:          return "Mouse Event";
                case VEVENT_JOYSTICK:       return "Joystick Event";
                case VEVENT_WINDOW_RESIZE:  return "Window Resize Event";
            }
        }

        [[nodiscard]] auto toString() const noexcept -> String override { return String("VEvent { type = ") + toString(this->_type) + " }"; }
        [[nodiscard]] auto hash () const noexcept -> Index override { return dataTypes::hash(static_cast<uint8>(this->_type)); }
        [[nodiscard]] auto copy () const noexcept -> VEvent * override = 0;

        [[nodiscard]] auto operator == (VEvent const & o) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_type == o._type;
        }

        [[nodiscard]] auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > ( & o );
            if ( p == nullptr ) return false;

            return this->operator==(*p);
        }

        VEvent () noexcept = delete;

        ~VEvent () noexcept override = default;
    protected:
        Type _type;

        explicit VEvent (Type type) noexcept : VObject(), _type (type) {}
        VEvent (VEvent const & o) noexcept = default;
        VEvent (VEvent && o) noexcept : VObject(o), _type(std::exchange(o._type, Type::VEVENT_UNKNOWN)) { }
    };

}


#endif //C_ENG_VEVENT_H
