//
// Created by loghin on 28.12.2021.
//

#if defined(C_ENG_MAP_START) && !defined(C_ENG_MAP_END)


#define __C_ENG_OBJECT_MAP_CLASS_CLASS(_typename, _baseFormula)                     __C_ENG_TYPE ( _typename )
#define __C_ENG_OBJECT_MAP_DECLARATION_CLASS(_typename, _baseFormula)               class __C_ENG_OBJECT_MAP_CLASS_CLASS( _typename, _baseFormula ) __C_ENG_OBJECT_MAP_PARENT_DECLARATION_ ## _baseFormula
#define __C_ENG_OBJECT_MAP_CONSTRUCTOR_CLASS(_typename, _baseFormula)               __C_ENG_OBJECT_MAP_CLASS_CLASS( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_DESTRUCTOR_CLASS(_typename, _baseFormula)                ~ __C_ENG_OBJECT_MAP_CLASS_CLASS( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_SELF_CLASS(_typename, _baseFormula)                      __C_ENG_OBJECT_MAP_CLASS_CLASS( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_PARENT_CLASS(_typename, _baseFormula)                    __C_ENG_OBJECT_MAP_PARENT_CLASS_ ## _baseFormula

#define __C_ENG_OBJECT_MAP_CLASS_STRUCT(_typename, _baseFormula)                    __C_ENG_TYPE ( _typename )
#define __C_ENG_OBJECT_MAP_DECLARATION_STRUCT(_typename, _baseFormula)              struct __C_ENG_OBJECT_MAP_CLASS_STRUCT( _typename, _baseFormula ) __C_ENG_OBJECT_MAP_PARENT_DECLARATION_ ## _baseFormula
#define __C_ENG_OBJECT_MAP_CONSTRUCTOR_STRUCT(_typename, _baseFormula)              __C_ENG_OBJECT_MAP_CLASS_STRUCT( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_DESTRUCTOR_STRUCT(_typename, _baseFormula)               ~ __C_ENG_OBJECT_MAP_CLASS_STRUCT( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_SELF_STRUCT(_typename, _baseFormula)                     __C_ENG_OBJECT_MAP_CLASS_STRUCT( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_PARENT_STRUCT(_typename, _baseFormula)                   __C_ENG_OBJECT_MAP_PARENT_STRUCT_ ## _baseFormula

#define __C_ENG_OBJECT_MAP_CLASS_ENUM(_typename, _baseFormula)                      __C_ENG_TYPE ( _typename )
#define __C_ENG_OBJECT_MAP_BASE_NAME_ENUM(_typename, _baseFormula)                  _typename
#define __C_ENG_OBJECT_MAP_BASE_TYPE_ENUM(_typename, _baseFormula)                  __C_ENG_OBJECT_MAP_BASE_TYPE_ ## _baseFormula
#define __C_ENG_OBJECT_MAP_DECLARATION_ENUM(_typename, _baseFormula)                enum __C_ENG_OBJECT_MAP_CLASS_ENUM(_typename, _baseFormula) __C_ENG_OBJECT_MAP_BASE_TYPE_ ## _baseFormula
#define __C_ENG_OBJECT_MAP_FIELD_ENUM(_typename, _baseFormula)                      __C_ENG_OBJECT_MAP_FIELD_ENUM_GEN

#define __C_ENG_OBJECT_MAP_FIELD_CASTER_GENERATOR_ENUM(_typename, _baseFormula)     __C_ENG_OBJECT_MAP_CAST_ ## _baseFormula
#define __C_ENG_OBJECT_MAP_CAST_NO_TYPE
#define __C_ENG_OBJECT_MAP_CAST_EXTERNAL_TYPE(_type)                                static_cast < _type >
#define __C_ENG_OBJECT_MAP_CAST_ENGINE_TYPE(_type)                                  static_cast < __C_ENG_TYPE ( _type ) >

#define __C_ENG_OBJECT_MAP_FIELD_ENUM_GEN(_name, _value)                            __C_ENG_OBJECT_MAP_META_PARSE1( __C_ENG_OBJECT_MAP_META_PARSE1 ( __C_ENG_OBJECT_MAP_BASE_NAME_, C_ENG_MAP_START ), _name) = __C_ENG_OBJECT_MAP_FIELD_ENUM_CASTER (_value)
#define __C_ENG_OBJECT_MAP_FIELD_ENUM_CASTER(_value)                                __C_ENG_OBJECT_MAP_META_PARSE1( __C_ENG_OBJECT_MAP_FIELD_CASTER_GENERATOR_, C_ENG_MAP_START )(_value)


#define __C_ENG_OBJECT_MAP_PARENT_CLASS_EXTERNAL_PARENT(_className)                 _className
#define __C_ENG_OBJECT_MAP_PARENT_CLASS_ENGINE_PARENT(_className)                   __C_ENG_TYPE ( _className )
#define __C_ENG_OBJECT_MAP_PARENT_CLASS_NO_PARENT


#define __C_ENG_OBJECT_MAP_PARENT_DECLARATION_EXTERNAL_PARENT(_className)           : public __C_ENG_OBJECT_MAP_PARENT_CLASS_EXTERNAL_PARENT ( _className )
#define __C_ENG_OBJECT_MAP_PARENT_DECLARATION_ENGINE_PARENT(_className)             : public __C_ENG_OBJECT_MAP_PARENT_CLASS_ENGINE_PARENT ( _className )
#define __C_ENG_OBJECT_MAP_PARENT_DECLARATION_NO_PARENT


#define __C_ENG_OBJECT_MAP_BASE_TYPE_EXTERNAL_TYPE(_type)                           : _type
#define __C_ENG_OBJECT_MAP_BASE_TYPE_ENGINE_TYPE(_type)                             : __C_ENG_TYPE ( _type )
#define __C_ENG_OBJECT_MAP_BASE_TYPE_NO_TYPE


#define __C_ENG_OBJECT_MAP_META_PARSE2(_prefix, _mapDef)                            _prefix ## _mapDef
#define __C_ENG_OBJECT_MAP_META_PARSE1(_prefix, _mapDef)                            __C_ENG_OBJECT_MAP_META_PARSE2(_prefix, _mapDef)


#define Class                                                                       __C_ENG_OBJECT_MAP_META_PARSE1(__C_ENG_OBJECT_MAP_DECLARATION_,     C_ENG_MAP_START)
#define Struct                                                                      __C_ENG_OBJECT_MAP_META_PARSE1(__C_ENG_OBJECT_MAP_DECLARATION_,     C_ENG_MAP_START)
#define Enum                                                                        __C_ENG_OBJECT_MAP_META_PARSE1(__C_ENG_OBJECT_MAP_DECLARATION_,     C_ENG_MAP_START)
#define Constructor                                                                 __C_ENG_OBJECT_MAP_META_PARSE1(__C_ENG_OBJECT_MAP_CONSTRUCTOR_,     C_ENG_MAP_START)
#define Destructor                                                                  __C_ENG_OBJECT_MAP_META_PARSE1(__C_ENG_OBJECT_MAP_DESTRUCTOR_,      C_ENG_MAP_START)
#define Self                                                                        __C_ENG_OBJECT_MAP_META_PARSE1(__C_ENG_OBJECT_MAP_SELF_,            C_ENG_MAP_START)
#define Parent                                                                      __C_ENG_OBJECT_MAP_META_PARSE1(__C_ENG_OBJECT_MAP_PARENT_,          C_ENG_MAP_START)
#define Field                                                                       __C_ENG_OBJECT_MAP_META_PARSE1(__C_ENG_OBJECT_MAP_FIELD_,           C_ENG_MAP_START)


#elif defined(C_ENG_MAP_END) && defined(C_ENG_MAP_START)


#undef __C_ENG_OBJECT_MAP_CLASS_CLASS
#undef __C_ENG_OBJECT_MAP_DECLARATION_CLASS
#undef __C_ENG_OBJECT_MAP_CONSTRUCTOR_CLASS
#undef __C_ENG_OBJECT_MAP_DESTRUCTOR_CLASS
#undef __C_ENG_OBJECT_MAP_SELF_CLASS
#undef __C_ENG_OBJECT_MAP_PARENT_CLASS

#undef __C_ENG_OBJECT_MAP_CLASS_STRUCT
#undef __C_ENG_OBJECT_MAP_DECLARATION_STRUCT
#undef __C_ENG_OBJECT_MAP_CONSTRUCTOR_STRUCT
#undef __C_ENG_OBJECT_MAP_DESTRUCTOR_STRUCT
#undef __C_ENG_OBJECT_MAP_SELF_STRUCT
#undef __C_ENG_OBJECT_MAP_PARENT_STRUCT

#undef __C_ENG_OBJECT_MAP_CLASS_ENUM
#undef __C_ENG_OBJECT_MAP_BASE_NAME_ENUM
#undef __C_ENG_OBJECT_MAP_BASE_TYPE_ENUM
#undef __C_ENG_OBJECT_MAP_DECLARATION_ENUM
#undef __C_ENG_OBJECT_MAP_FIELD_ENUM

#undef __C_ENG_OBJECT_MAP_FIELD_CASTER_GENERATOR_ENUM
#undef __C_ENG_OBJECT_MAP_CAST_NO_TYPE
#undef __C_ENG_OBJECT_MAP_CAST_EXTERNAL_TYPE
#undef __C_ENG_OBJECT_MAP_CAST_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_FIELD_ENUM_GEN
#undef __C_ENG_OBJECT_MAP_FIELD_ENUM_CASTER


#undef __C_ENG_OBJECT_MAP_PARENT_CLASS_EXTERNAL_PARENT
#undef __C_ENG_OBJECT_MAP_PARENT_CLASS_ENGINE_PARENT
#undef __C_ENG_OBJECT_MAP_PARENT_CLASS_NO_PARENT

#undef __C_ENG_OBJECT_MAP_PARENT_DECLARATION_EXTERNAL_PARENT
#undef __C_ENG_OBJECT_MAP_PARENT_DECLARATION_ENGINE_PARENT
#undef __C_ENG_OBJECT_MAP_PARENT_DECLARATION_NO_PARENT

#undef __C_ENG_OBJECT_MAP_BASE_TYPE_EXTERNAL_TYPE
#undef __C_ENG_OBJECT_MAP_BASE_TYPE_ENGINE_TYPE
#undef __C_ENG_OBJECT_MAP_BASE_TYPE_NO_TYPE


#undef __C_ENG_OBJECT_MAP_META_PARSE2
#undef __C_ENG_OBJECT_MAP_META_PARSE1


#undef Class
#undef Struct
#undef Enum
#undef Constructor
#undef Destructor
#undef Parent
#undef Self
#undef Field


#undef C_ENG_MAP_END
#undef C_ENG_MAP_START

#else

#error Wrong Usage of ObjectMapping. Use 'C_ENG_MAP_START' or 'C_ENG_MAP_END'.

#endif
