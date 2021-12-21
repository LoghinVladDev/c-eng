//
// Created by loghin on 18.12.2021.
//

#ifndef C_ENG_NAMING_HPP
#define C_ENG_NAMING_HPP


#ifndef C_ENG_DEFAULT_NAMING_PREFIX
#define C_ENG_DEFAULT_NAMING_PREFIX
#endif


#define __C_ENG_TYPE_PARSE2(_prefix, _type) _prefix ## _type
#define __C_ENG_TYPE_PARSE1(_prefix, _type) __C_ENG_TYPE_PARSE2(_prefix, _type)


#define C_ENG_TYPE(_type) __C_ENG_TYPE_PARSE1(C_ENG_DEFAULT_NAMING_PREFIX, _type)


#define C_ENG_CLASS(_name) C_ENG_TYPE(_name)


#define C_ENG_CONSTRUCTOR(_name) C_ENG_CLASS(_name)
#define C_ENG_DESTRUCTOR(_name) ~C_ENG_CLASS(_name)


#define C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD(_type, _name, _defaultValue)      \
    private:                                                                    \
        _type _ ## _name { _defaultValue };                                     \
                                                                                \
    public:                                                                     \
        C_ENG_NO_DISCARD constexpr auto _name () const noexcept -> _type {      \
            return this-> _ ## _name;                                           \
        }                                                                       \
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

#define C_ENG_CLASS_PRIMITIVE_CONSTANT(_type, _name, _value) \
    public:                                                  \
        constexpr static _type _name = _value; // NOLINT(clion-misra-cpp2008-8-0-1)


#endif //C_ENG_NAMING_HPP
