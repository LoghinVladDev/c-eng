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


#define __C_ENG_ALIAS(_name, _type) using __C_ENG_TYPE(_name) = _type


#define __C_ENG_ENUM                                        enum __C_ENG_TYPE(__C_ENG_OBJECT_NAME) : __C_ENG_OBJECT_TYPE
#define __C_ENG_ENUM_FIELD_PARSE2(_prefix, _name, _value)   _prefix ## _name = static_cast < __C_ENG_OBJECT_TYPE > ( _value )
#define __C_ENG_ENUM_FIELD_PARSE1(_prefix, _name, _value)   __C_ENG_ENUM_FIELD_PARSE2(_prefix, _name, _value)
#define __C_ENG_ENUM_FIELD(_name, _value)                   __C_ENG_ENUM_FIELD_PARSE1(__C_ENG_OBJECT_NAME, _name, _value)

#define __C_ENG_STRUCT  struct __C_ENG_TYPE(__C_ENG_OBJECT_NAME)
#define __C_ENG_CLASS   class __C_ENG_TYPE(__C_ENG_OBJECT_NAME)

#define __C_ENG_PRE_DECLARE_CLASS(_name)    class __C_ENG_TYPE(_name)
#define __C_ENG_PRE_DECLARE_STRUCT(_name)   struct __C_ENG_TYPE(_name)

#define __C_ENG_FRIEND_CLASS(_name)     friend class __C_ENG_TYPE(_name)
#define __C_ENG_FRIEND_STRUCT(_name)    friend struct __C_ENG_TYPE(_name)

#define __C_ENG_SELF        __C_ENG_TYPE(__C_ENG_OBJECT_NAME)

#define __C_ENG_CONSTRUCTOR __C_ENG_SELF
#define __C_ENG_DESTRUCTOR ~__C_ENG_SELF


#endif //__C_ENG_NAMING_HPP
