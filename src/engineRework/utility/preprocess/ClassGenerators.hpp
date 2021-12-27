//
// Created by loghin on 21.12.2021.
//

#ifndef __C_ENG_CLASSGENERATORS_HPP
#define __C_ENG_CLASSGENERATORS_HPP


#define __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD(_type, _name, _defaultValue)      \
    private:                                                                    \
        _type _ ## _name { _defaultValue };                                     \
                                                                                \
    public:                                                                     \
        __C_ENG_NO_DISCARD constexpr auto _name () const noexcept -> _type {    \
            return this-> _ ## _name;                                           \
        }                                                                       \
    private:

#define __C_ENG_CLASS_IMMUTABLE_FIELD(_type, _name, ...)                                  \
    private:                                                                            \
        _type _ ## _name { __VA_ARGS__ };                                               \
                                                                                        \
    public:                                                                             \
        __C_ENG_NO_DISCARD constexpr auto _name () const noexcept -> _type const & {    \
            return this-> _ ## _name;                                                   \
        }                                                                               \
    private:

#define __C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD(_type, _name, _defaultValue)          \
    __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD(_type, _name, _defaultValue)            \
                                                                                    \
    public:                                                                         \
        __C_ENG_NO_DISCARD constexpr auto _name () noexcept -> _type & {            \
            return this-> _ ## _name;                                               \
        }                                                                           \
                                                                                    \
    private:

#define __C_ENG_CLASS_MUTABLE_FIELD(_type, _name, ...)                                  \
    __C_ENG_CLASS_IMMUTABLE_FIELD(_type, _name, __VA_ARGS__)                            \
                                                                                        \
    public:                                                                             \
        __C_ENG_NO_DISCARD constexpr auto _name () noexcept -> _type & {                \
            return this-> _ ## _name;                                                   \
        }                                                                               \
                                                                                        \
    private:

#define __C_ENG_CLASS_PRIMITIVE_CONSTANT(_type, _name, _value) \
    public:                                                  \
        constexpr static _type _name = _value; // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //__C_ENG_CLASSGENERATORS_HPP
