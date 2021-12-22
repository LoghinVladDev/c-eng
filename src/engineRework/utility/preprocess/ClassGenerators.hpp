//
// Created by loghin on 21.12.2021.
//

#ifndef C_ENG_CLASSGENERATORS_HPP
#define C_ENG_CLASSGENERATORS_HPP


#define C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD(_type, _name, _defaultValue)      \
    private:                                                                    \
        _type _ ## _name { _defaultValue };                                     \
                                                                                \
    public:                                                                     \
        C_ENG_NO_DISCARD constexpr auto _name () const noexcept -> _type {      \
            return this-> _ ## _name;                                           \
        }                                                                       \
    private:

#define C_ENG_CLASS_IMMUTABLE_FIELD(_type, _name, ...)                                  \
    private:                                                                            \
        _type _ ## _name { __VA_ARGS__ };                                               \
                                                                                        \
    public:                                                                             \
        C_ENG_NO_DISCARD constexpr auto _name () const noexcept -> _type const & {      \
            return this-> _ ## _name;                                                   \
        }                                                                               \
    private:

#define C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD(_type, _name, _defaultValue)        \
    private:                                                                    \
        _type _ ## _name { _defaultValue };                                     \
                                                                                \
    public:                                                                     \
        C_ENG_NO_DISCARD constexpr auto _name () const noexcept -> _type {      \
            return this-> _ ## _name;                                           \
        }                                                                       \
                                                                                \
        C_ENG_NO_DISCARD constexpr auto _name () noexcept -> _type & {          \
            return this-> _ ## _name;                                           \
        }                                                                       \
    private:

#define C_ENG_CLASS_MUTABLE_FIELD(_type, _name, ...)                                    \
    private:                                                                            \
        _type _ ## _name { __VA_ARGS__ };                                               \
                                                                                        \
    public:                                                                             \
        C_ENG_NO_DISCARD constexpr auto _name () const noexcept -> _type const & {      \
            return this-> _ ## _name;                                                   \
        }                                                                               \
                                                                                        \
        C_ENG_NO_DISCARD constexpr auto _name () noexcept -> _type & {                  \
            return this-> _ ## _name;                                                   \
        }                                                                               \
    private:

#define C_ENG_CLASS_PRIMITIVE_CONSTANT(_type, _name, _value) \
    public:                                                  \
        constexpr static _type _name = _value; // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //C_ENG_CLASSGENERATORS_HPP
