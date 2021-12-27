//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_NAMING_HPP
#define __C_ENG_NAMING_HPP


#ifndef __C_ENG_DEFAULT_NAMING_PREFIX
#define __C_ENG_DEFAULT_NAMING_PREFIX
#endif


#define __C_ENG_PREFIX_APPLICATION_PARSE2(_prefix, _type) _prefix ## _type
#define __C_ENG_PREFIX_APPLICATION_PARSE1(_prefix, _type) __C_ENG_PREFIX_APPLICATION_PARSE2(_prefix, _type)


#define __C_ENG_TYPE(_type) __C_ENG_PREFIX_APPLICATION_PARSE1(__C_ENG_DEFAULT_NAMING_PREFIX, _type)


#define __C_ENG_CLASS(_name)        class __C_ENG_TYPE(_name)
#define __C_ENG_STRUCT(_name)       struct __C_ENG_TYPE(_name)
#define __C_ENG_ENUM(_name, _type)  enum __C_ENG_TYPE(_name) : _type
#define __C_ENG_ALIAS(_name, _type) using __C_ENG_TYPE(_name) = _type


#define __C_ENG_ENUM_FIELD(_enum, _name, _value)   _enum ## _name = _value


#define __C_ENG_CONSTRUCTOR(_name) __C_ENG_TYPE(_name)
#define __C_ENG_DESTRUCTOR(_name) ~__C_ENG_TYPE(_name)


#endif //__C_ENG_NAMING_HPP
