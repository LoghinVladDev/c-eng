//
// Created by loghin on 28.12.2021.
//


/**
 * Object Mapping Header
 * Usage:
 *      #define C_ENG_MAP_START         < Object Meta Info >
 *      #include <ObjectMapping.hpp>
 *
 *
 *      /// object declaration / functions, etc ...
 *
 *
 *      #define C_ENG_MAP_END
 *      #include <ObjectMapping.hpp>
 *
 *
 *      < Object Meta Info > =
 *          If Class -> CLASS ( < name >, < derivationFormula > )
 *              < name > = name of object
 *              < derivationFormula > =
 *                  If NO_PARENT, class will not be derived
 *                  If PARENT ( < className > ), class will be derived from class of given name
 *                  If ENGINE_PARENT ( < className > ), class will be derived from engine class of given name ( prefix applied )
 *
 *          If Struct -> STRUCT ( < name >, < derivationFormula > )
 *              Same as class ( above )
 *
 *          If Enum -> ENUM ( < name >, < derivationFormula > )
 *              < name > = desired object name
 *              < derivationFormula > =
 *                  If NO_TYPE, no inheritance applied to enum ( classic style )
 *                  If TYPE ( < type > ) or ENGINE_TYPE ( < type > ), enum will be derived from said type,
 *                      -> all variables of enum type occupy the size of the inherited type
 *
 *
 *      Once between a BEGIN - END structure, the following keywords can be used for generation
 *          - Class  ---  Used in CLASS formula
 *              - generates the declaration tag of the class, with inheritance members.
 *                  Example :
 *                      #define C_ENG_MAP_BEGIN     CLASS ( Test, PARENT ( SomeObject ) )
 *                      #include <ObjectMapping.hpp>
 *
 *                      Class {         /// 'Class' will generate __C_ENG_TYPE ( Test ) : public SomeObject
 *
 *                      };
 *
 *          - Struct  ---  Used in STRUCT formula
 *              - same as above
 *
 *          - Enum  ---  Used in ENUM formula
 *              - same as class/struct, without access modifier ( public )
 *
 *          - Constructor  ---  Used in CLASS / STRUCT formulas
 *              - will generate the constructor name for this class
 *                  Example :
 *                      #define C_ENG_MAP_BEGIN     CLASS ( Test, NO_PARENT )
 *                      #include <ObjectMapping.hpp>
 *
 *                      Class {
 *                      public:
 *
 *                          Constructor ( int value ) {  /// will be replaced with __C_ENG_TYPE ( Test )
 *                              /// construct object ...
 *                          }
 *                      };
 *
 *          - Destructor  ---  Used in CLASS / STRUCT formulas
 *              - same as Constructor, but generates destructor
 *
 *          - Parent  ---  Used in CLASS / STRUCT formulas
 *              - will generate the parent class name
 *                  Example :
 *                      #define C_ENG_MAP_BEGIN     CLASS ( Test, PARENT ( OtherClass ) )
 *                      #include <ObjectMapping.hpp>
 *
 *                      Class {
 *                      public:
 *
 *                          Constructor ( int value ) : Parent ( value ) { } /// calls base class constructor
 *
 *                          void fDoSomething () override {
 *                              Parent :: fDoSomething (); /// calls overriden base function
 *
 *                              /// do extra stuff
 *                          }
 *
 *                      };
 *
 *          - Self  ---  Used in CLASS / STRUCT formulas
 *              - will generate the current class name
 *                  Example :
 *                      #define C_ENG_MAP_BEGIN     CLASS ( Test, PARENT ( OtherClass ) )
 *                      #include <ObjectMapping.hpp>
 *
 *                      Class {
 *                      public:
 *
 *                          Constructor ( int value ) : Parent ( value ) { } /// calls base class constructor
 *
 *                          static void fDoAnotherThing () {}
 *
 *                          void fDoSomething () override {
 *                              Parent :: fDoSomething (); /// calls overriden base function
 *
 *                              Self :: fDoAnotherThing (); /// will generate __C_ENG_TYPE ( Test ) :: fDoAnotherThing ();
 *                          }
 *
 *                      };
 *
 *          - Field  --- Used in CLASS / ENUM formulas
 *              - if used in ENUM formula, generates an enum field prefixed by the enum name ( to avoid naming conflicts )
 *                  Example:
 *                      #define C_ENG_MAP_BEGIN     ENUM ( Test, TYPE ( cds :: uint8 ) )
 *                      #include <ObjectMapping.hpp>
 *
 *                      Enum {                              /// replaced by enum Test : cds :: uint8 {
 *                          Field ( Sample,     0 ),        /// replaced by TestSample = static_cast < cds :: uint8 > ( 0 ),
 *                          Field ( Another,    1 )         /// replaced by TestAnother = static_cast < cds :: uint8 > ( 1 )
 *                      };
 *
 *              - if used in CLASS formula, generates a class field with requested properties
 *                  Usage : Field ( < typeFormula >, < name >, < defaultValueFormula >, < getterFormula >, < setterFormula > )
 *                      - Type Formulas:
 *                          - PRIMITIVE_TYPE ( < type > )                           -> will be a standard, non object, less or equals in size to 64 bits ( bool, int, float, pointers, etc. ), usually copied
 *                          - TYPE ( < type > )                                     -> will be a complex type, larger than 64 bits, usually referenced
 *                          - ENGINE_PRIMITIVE_TYPE ( < type > )                    -> same as PRIMITIVE_TYPE, but type name has the engine prefix applied
 *                          - ENGINE_TYPE ( < type > )                              -> same as TYPE, but type name has the engine prefix applied
 *                          - PRIMITIVE_TYPE_ARRAY ( < type >, < size > )           -> will be a standard, non object, less or equals in size to 64 bits per element, array
 *                          - ENGINE_PRIMITIVE_TYPE_ARRAY ( < type >, < size > )    -> same as PRIMITIVE_TYPE_ARRAY, but type name has the engine prefix applied
 *                      - name -> desired name of the field, used in getter. The field will be created with an underscore prefixed ( testField will actually be _testField )
 *                      - Default Value Formulas:
 *                          - DEFAULT_VALUE ( < value > )                           -> will initialize the object with given value, and, if it is primitive type, will cast the value to the element type
 *                          - NO_INIT                                               -> as suggested, does not have an initializer
 *                      - Getter Formulas:
 *                          - GET_DEFAULT                                           -> will generate a standard getter, by copy for primitives or const reference for complex types, with the name of the field
 *                          - GET_NONE                                              -> will not generate a getter
 *                      - Setter Formulas:
 *                          - SET_DEFAULT                                           -> will generate a setter by mutable getter, a function named just like the field returning a reference to field value
 *                          - SET_NONE                                              -> will not generate a setter
 *                          - SET ( < setterName > )                                -> will generate a setter declaration, which has to be defined in a source file / inlined in the header, with given name. The setter will return reference to caller object
 *                          - SET_INLINE ( < setterName > )                         -> will generate an inline setter, which will have the given name, will set the value and return reference to caller object
 *
 *                  - For examples, refer to src/engineRework/render/window/Window.hpp
 *          - Const  ---  Used in CLASS formula
 *              - Will generate a class static constant ( or constant expression ) with given type, name and value
 *              - Usage : Const ( < typeFormula >, < name >, < valueFormula > )
 *                  - Type Formulas:
 *                      - Same as Field Type Formula
 *                  - Value Formulas:
 *                      - VALUE ( < value > ) -> will encapsulate the parameter / parameters to cast / create object
 *                  - For examples, refer to src/engineRework/utility/settings/Settings.hpp
 *
 *
 *      - These Meta Definitions will be expanded further
 */


#if defined(C_ENG_MAP_START) && !defined(C_ENG_MAP_END)


#define __C_ENG_OBJECT_MAP_CLASS_CLASS(_typename, _baseFormula)                     __C_ENG_TYPE ( _typename )
#define __C_ENG_OBJECT_MAP_DECLARATION_CLASS(_typename, _baseFormula)               class __C_ENG_OBJECT_MAP_CLASS_CLASS( _typename, _baseFormula ) __C_ENG_OBJECT_MAP_PARENT_DECLARATION_ ## _baseFormula
#define __C_ENG_OBJECT_MAP_CONSTRUCTOR_CLASS(_typename, _baseFormula)               __C_ENG_OBJECT_MAP_CLASS_CLASS( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_DESTRUCTOR_CLASS(_typename, _baseFormula)                ~ __C_ENG_OBJECT_MAP_CLASS_CLASS( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_SELF_CLASS(_typename, _baseFormula)                      __C_ENG_OBJECT_MAP_CLASS_CLASS( _typename, _baseFormula )
#define __C_ENG_OBJECT_MAP_PARENT_CLASS(_typename, _baseFormula)                    __C_ENG_OBJECT_MAP_PARENT_CLASS_ ## _baseFormula
#define __C_ENG_OBJECT_MAP_FIELD_CLASS(_typename, _baseFormula)                     __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN
#define __C_ENG_OBJECT_MAP_CONST_CLASS(_typename, _baseFormula)                     __C_ENG_OBJECT_MAP_CONST_GEN


#define __C_ENG_OBJECT_MAP_CLASS_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)              _typename
#define __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)         \
    class __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS_EXTRACT_NESTER_ ## _nesterFormula ::           \
    __C_ENG_OBJECT_MAP_CLASS_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)                   \
    __C_ENG_OBJECT_MAP_PARENT_DECLARATION_ ## _baseFormula

#define __C_ENG_OBJECT_MAP_CONSTRUCTOR_NESTED_CLASS(_typename, _nesterFormula, _baseFormula) \
    __C_ENG_OBJECT_MAP_CLASS_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)

#define __C_ENG_OBJECT_MAP_DESTRUCTOR_NESTED_CLASS(_typename, _nesterFormula, _baseFormula) \
    ~ __C_ENG_OBJECT_MAP_CLASS_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)

#define __C_ENG_OBJECT_MAP_SELF_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)   \
    __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS_EXTRACT_NESTER_ ## _nesterFormula ::    \
    __C_ENG_OBJECT_MAP_CLASS_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)

#define __C_ENG_OBJECT_MAP_PARENT_NESTED_CLASS(_typename, _nesterFormula, _baseFormula) __C_ENG_OBJECT_MAP_PARENT_CLASS_ ## _baseFormula
#define __C_ENG_OBJECT_MAP_FIELD_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)  __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN
#define __C_ENG_OBJECT_MAP_CONST_NESTED_CLASS(_typename, _nesterFormula, _baseFormula)  __C_ENG_OBJECT_MAP_CONST_GEN
#define __C_ENG_OBJECT_MAP_NESTER_NESTED_CLASS(_typename, _nesterFormula, _baseFormula) \
    __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS_EXTRACT_NESTER_ ## _nesterFormula


#define __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS_EXTRACT_NESTER_ENGINE_TYPE( _typename )      __C_ENG_TYPE ( _typename )
#define __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS_EXTRACT_NESTER_TYPE( _typename )             _typename


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN(_typeFormula, _name, _dValFormula, _getFormula, _setFormula) \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_ ## _typeFormula                           \
        __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_DECLARATION(_typeFormula, _name, _dValFormula)               \
                                                                                                        \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_ACCESS_MODIFIER_ ## _getFormula                           \
        __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER(_typeFormula, _name, _getFormula)                     \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_ ## _setFormula                           \
        __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER(_typeFormula, _name, _setFormula)                     \
    private:


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_DECLARATION(_typeFormula, _name, _defValFormula)         \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ ## _typeFormula                                \
    _ ## _name                                                                                      \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_ ## _typeFormula                     \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CASTED_ ## _defValFormula              \
    (_typeFormula, _defValFormula);


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CASTED_DEFAULT_VALUE(...)  __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CASTED
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CASTED_NO_INIT             __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_NO_INIT

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CASTED(_typeFormula, _defValFormula) \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ ## _typeFormula ( _typeFormula, _defValFormula )

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_NO_INIT(_typeFormula, _defValFormula)


#define  __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_PRIMITIVE_TYPE(_typename)  __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_PRIMITIVE_TYPE_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_PRIMITIVE_TYPE_CALL(_typeFormula, _defValFormula)    \
    { static_cast < __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_ ## _typeFormula >                           \
    ( __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_ ## _defValFormula ) }

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_PRIMITIVE_TYPE(_typename) __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_PRIMITIVE_TYPE_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_PRIMITIVE_TYPE_CALL(_typeFormula, _defValFormula)     \
    { static_cast < __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_ ## _typeFormula >                                   \
    ( __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_ ## _defValFormula ) }

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_TYPE(_typename) __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_TYPE_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_TYPE_CALL(_typeFormula, _defValFormula) \
    { __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_ ## _defValFormula }

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_TYPE(_typename) __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_TYPE_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_TYPE_CALL(_typeFormula, _defValFormula) \
    { __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_ ## _defValFormula }

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_DEFAULT_VALUE(...)  __VA_ARGS__

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_PRIMITIVE_TYPE(...)        __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_TYPE(...)                  __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_ENGINE_PRIMITIVE_TYPE(...) __C_ENG_TYPE ( __VA_ARGS__ )
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_ENGINE_TYPE(...)           __C_ENG_TYPE ( __VA_ARGS__ )


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER(_typeFormula, _name, _getFormula)                 \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_META_MODIFIERS_ ## _getFormula                \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_MODIFIERS_ ## _getFormula                     \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_NAME_ ## _getFormula ( _name )                \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_OBJECT_MODIFIERS_ ## _getFormula              \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_RETURN_TYPE_ ## _getFormula ( _typeFormula )  \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_DEFINITION_ ## _getFormula ( _name )


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_META_MODIFIERS_GET_DEFAULT_PROTECTED  __C_ENG_NO_DISCARD
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_META_MODIFIERS_GET_DEFAULT            __C_ENG_NO_DISCARD
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_META_MODIFIERS_GET_NONE

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_MODIFIERS_GET_DEFAULT_PROTECTED   constexpr auto
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_MODIFIERS_GET_DEFAULT             constexpr auto
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_MODIFIERS_GET_NONE

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_NAME_GET_DEFAULT_PROTECTED(_name) _name ()
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_NAME_GET_DEFAULT(_name)           _name ()
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_NAME_GET_NONE(_name)

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_OBJECT_MODIFIERS_GET_DEFAULT_PROTECTED    const noexcept
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_OBJECT_MODIFIERS_GET_DEFAULT              const noexcept
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_OBJECT_MODIFIERS_GET_NONE

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_RETURN_TYPE_GET_DEFAULT_PROTECTED(_typeFormula)   \
    ->                                                                                                      \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ ## _typeFormula                                        \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_ ## _typeFormula

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_RETURN_TYPE_GET_DEFAULT(_typeFormula) \
    ->                                                                                          \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ ## _typeFormula                            \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_ ## _typeFormula

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_RETURN_TYPE_GET_NONE(_typeFormula)

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_DEFINITION_GET_DEFAULT_PROTECTED( _name ) \
    { return this-> _ ## _name; }

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_DEFINITION_GET_DEFAULT( _name ) \
    { return this-> _ ## _name; }

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_DEFINITION_GET_NONE( _name )

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_PRIMITIVE_TYPE(...)                             __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_TYPE(...)                                       __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ENGINE_PRIMITIVE_TYPE(...)                      __C_ENG_TYPE(__VA_ARGS__)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ENGINE_TYPE(...)                                __C_ENG_TYPE(__VA_ARGS__)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_PRIMITIVE_TYPE_ARRAY(_typename, _size)          _typename
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ENGINE_PRIMITIVE_TYPE_ARRAY(_typename, _size)   __C_ENG_TYPE(_typename)

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_PRIMITIVE_TYPE(...)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_TYPE(...)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_ENGINE_PRIMITIVE_TYPE(...)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_ENGINE_TYPE(...)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_PRIMITIVE_TYPE_ARRAY(_typename, _size)           [_size]
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_ENGINE_PRIMITIVE_TYPE_ARRAY(_typename, _size)    [_size]

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_PRIMITIVE_TYPE(...)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_TYPE(...)                     const &
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_ENGINE_PRIMITIVE_TYPE(...)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_ENGINE_TYPE(...)              const &


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER(_typeFormula, _name, _setFormula)                 \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_ ## _setFormula                \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_ ## _setFormula                     \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_ ## _setFormula (_name, _setFormula)     \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_ ## _setFormula(_typeFormula)      \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_ ## _setFormula              \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_ ## _setFormula ( _typeFormula )  \
    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_ ## _setFormula ( _name )

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET_NONE
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET_DEFAULT
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET_DEFAULT_PROTECTED
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET(_setterName)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET_INLINE(_setterName)

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET_NONE
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET_DEFAULT                 constexpr auto
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET_DEFAULT_PROTECTED       constexpr auto
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET(_setterName)            auto
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET_INLINE(_setterName)     inline auto

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_NONE                     __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_NONE_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT                  __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT_PROTECTED        __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT_PROTECTED_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET(_setterName)             __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_INLINE(_setterName)      __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_INLINE_CALL

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_NONE                   __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_EMPTY_PARAMETERS
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT                __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT_PARAM
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT_PROTECTED      __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT_PROTECTED_PARAM
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET(_setterName)           __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_PARAM
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_INLINE(_setterName)    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_NAMED_PARAM

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET_NONE
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET_DEFAULT              noexcept
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET_DEFAULT_PROTECTED    noexcept
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET(_setterName)         noexcept
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET_INLINE(_setterName)  noexcept

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_NONE                      __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_NONE_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT                   __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED         __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET(_setterName)              __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_CALL
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_INLINE(_setterName)       __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_INLINE_CALL

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_NONE_CALL(_typeFormula)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_CALL(_typeFormula)            -> __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_ ## _typeFormula &
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_CALL(_typeFormula)  -> __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_ ## _typeFormula &
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_CALL(_typeFormula)                    -> Self &
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_INLINE_CALL(_typeFormula)             -> Self &

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET_NONE                   __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_NONE
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET_DEFAULT                __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_DEFAULT
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET_DEFAULT_PROTECTED      __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_DEFAULT
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET(_setterName)           __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_NOT_IN_HEADER
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET_INLINE(_setterName)    __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_IN_HEADER


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_PRIMITIVE_TYPE(...)        __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_TYPE(...)                  __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_ENGINE_PRIMITIVE_TYPE(...) __C_ENG_TYPE ( __VA_ARGS__ )
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_ENGINE_TYPE(...)           __C_ENG_TYPE ( __VA_ARGS__ )

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_PRIMITIVE_TYPE(...)        __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_TYPE(...)                  __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_ENGINE_PRIMITIVE_TYPE(...) __C_ENG_TYPE ( __VA_ARGS__ )
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_ENGINE_TYPE(...)           __C_ENG_TYPE ( __VA_ARGS__ )


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_NONE_CALL(_name, _setFormula)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT_CALL(_name, _setFormula)             _name
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT_PROTECTED_CALL(_name, _setFormula)   _name
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_CALL(_name, _setFormula)                     __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_FORMULA_CALL_ ## _setFormula
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_INLINE_CALL(_name, _setFormula)              __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_FORMULA_CALL_ ## _setFormula

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_FORMULA_CALL_SET(_setterName)            _setterName
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_FORMULA_CALL_SET_INLINE(_setterName)     _setterName


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_EMPTY_PARAMETERS(_typeFormula)

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_PARAM(_typeFormula)        \
    (   __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_ ## _typeFormula               \
        __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_ ## _typeFormula )

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_NAMED_PARAM(_typeFormula)  \
    (   __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_ ## _typeFormula               \
        __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_ ## _typeFormula value )

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT_PARAM(_typeFormula) ()
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT_PROTECTED_PARAM(_typeFormula) ()


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_PRIMITIVE_TYPE(...)            __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_TYPE(...)                      __VA_ARGS__
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_ENGINE_PRIMITIVE_TYPE(...)     __C_ENG_TYPE(__VA_ARGS__)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_ENGINE_TYPE(...)               __C_ENG_TYPE(__VA_ARGS__)

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_PRIMITIVE_TYPE(...)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_TYPE(...)               const &
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_ENGINE_PRIMITIVE_TYPE(...)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_ENGINE_TYPE(...)        const &

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_NONE(_fieldName)
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_NOT_IN_HEADER(_fieldName)  ;
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_IN_HEADER(_fieldName) {    \
        this-> _ ## _fieldName = value;                                                 \
        return * this;                                                                  \
    }

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_DEFAULT(_fieldName) {  \
        return this-> _ ## _fieldName;                                              \
    }

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
#define __C_ENG_OBJECT_MAP_CAST_TYPE(_type)                                         static_cast < _type >
#define __C_ENG_OBJECT_MAP_CAST_ENGINE_TYPE(_type)                                  static_cast < __C_ENG_TYPE ( _type ) >

#define __C_ENG_OBJECT_MAP_FIELD_ENUM_GEN(_name, _value)                            __C_ENG_OBJECT_MAP_META_CALL( __C_ENG_OBJECT_MAP_META_CALL ( __C_ENG_OBJECT_MAP_BASE_NAME_, C_ENG_MAP_START ), _name) = __C_ENG_OBJECT_MAP_FIELD_ENUM_CASTER (_value)
#define __C_ENG_OBJECT_MAP_FIELD_ENUM_CASTER(_value)                                __C_ENG_OBJECT_MAP_META_CALL( __C_ENG_OBJECT_MAP_FIELD_CASTER_GENERATOR_, C_ENG_MAP_START )(_value)



#define __C_ENG_OBJECT_MAP_PARENT_CLASS_PARENT(_className)                          _className
#define __C_ENG_OBJECT_MAP_PARENT_CLASS_ENGINE_PARENT(_className)                   __C_ENG_TYPE ( _className )
#define __C_ENG_OBJECT_MAP_PARENT_CLASS_NO_PARENT


#define __C_ENG_OBJECT_MAP_PARENT_DECLARATION_PARENT(_className)                    : public __C_ENG_OBJECT_MAP_PARENT_CLASS_PARENT ( _className )
#define __C_ENG_OBJECT_MAP_PARENT_DECLARATION_ENGINE_PARENT(_className)             : public __C_ENG_OBJECT_MAP_PARENT_CLASS_ENGINE_PARENT ( _className )
#define __C_ENG_OBJECT_MAP_PARENT_DECLARATION_NO_PARENT


#define __C_ENG_OBJECT_MAP_BASE_TYPE_TYPE(_type)                                    : _type
#define __C_ENG_OBJECT_MAP_BASE_TYPE_ENGINE_TYPE(_type)                             : __C_ENG_TYPE ( _type )
#define __C_ENG_OBJECT_MAP_BASE_TYPE_NO_TYPE


#define __C_ENG_OBJECT_MAP_META_JOIN_AND_CALL(_prefix, _mapDef)                     _prefix ## _mapDef
#define __C_ENG_OBJECT_MAP_META_CALL(_prefix, _mapDef)                              __C_ENG_OBJECT_MAP_META_JOIN_AND_CALL(_prefix, _mapDef)


#define __C_ENG_OBJECT_MAP_CONST_GEN(_typeFormula, _name, _valueFormula)                        \
    public:                                                                                     \
        __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_ ## _typeFormula                                \
        __C_ENG_OBJECT_MAP_CONST_TYPE_ ## _typeFormula                                          \
        _name                                                                                   \
        __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ ## _typeFormula (_typeFormula, _valueFormula );

#define __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_PRIMITIVE_TYPE(...)         constexpr static
#define __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_TYPE(...)                   const inline static
#define __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_ENGINE_PRIMITIVE_TYPE(...)  constexpr static
#define __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_ENGINE_TYPE(...)            const inline static

#define __C_ENG_OBJECT_MAP_CONST_TYPE_PRIMITIVE_TYPE(...)         __VA_ARGS__
#define __C_ENG_OBJECT_MAP_CONST_TYPE_TYPE(...)                   __VA_ARGS__
#define __C_ENG_OBJECT_MAP_CONST_TYPE_ENGINE_PRIMITIVE_TYPE(...)  __C_ENG_TYPE ( __VA_ARGS__ )
#define __C_ENG_OBJECT_MAP_CONST_TYPE_ENGINE_TYPE(...)            __C_ENG_TYPE ( __VA_ARGS__ )

#define __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_PRIMITIVE_TYPE(...)           __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_PRIMITIVE_TYPE_CALL
#define __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_TYPE(...)                     __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_TYPE_CALL
#define __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_PRIMITIVE_TYPE(...)    __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_PRIMITIVE_TYPE_CALL
#define __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_TYPE(...)              __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_TYPE_CALL

#define __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_PRIMITIVE_TYPE_CALL(_typeFormula, _valueFormula)            \
    = static_cast < __C_ENG_OBJECT_MAP_CONST_TYPE_ ## _typeFormula > (                                  \
        __C_ENG_OBJECT_MAP_CONST_VALUE_ ## _valueFormula )

#define __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_PRIMITIVE_TYPE_CALL(_typeFormula, _valueFormula)             \
    = static_cast < __C_ENG_OBJECT_MAP_CONST_TYPE_ ## _typeFormula > (                                          \
        __C_ENG_OBJECT_MAP_CONST_VALUE_ ## _valueFormula )

#define __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_TYPE_CALL(_typeFormula, _valueFormula) \
    = __C_ENG_OBJECT_MAP_CONST_VALUE_ ## _valueFormula

#define __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_TYPE_CALL(_typeFormula, _valueFormula) \
    = __C_ENG_OBJECT_MAP_CONST_VALUE_ ## _valueFormula

#define __C_ENG_OBJECT_MAP_CONST_VALUE_VALUE(...)    __VA_ARGS__


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_TYPE(...)                          private:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_ENGINE_TYPE(...)                   private:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_PRIMITIVE_TYPE(...)                private:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_ENGINE_PRIMITIVE_TYPE(...)         private:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_PRIMITIVE_TYPE_ARRAY(...)          private:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_ENGINE_PRIMITIVE_TYPE_ARRAY(...)   private:


#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_ACCESS_MODIFIER_GET_NONE
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_ACCESS_MODIFIER_GET_DEFAULT                           public:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_ACCESS_MODIFIER_GET_DEFAULT_PROTECTED                 protected:

#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET_NONE
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET_DEFAULT               public:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET_DEFAULT_PROTECTED     protected:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET_INLINE(...)           public:
#define __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET(...)                  public:


#define Class                                                                       __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_DECLARATION_,     C_ENG_MAP_START)
#define Struct                                                                      __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_DECLARATION_,     C_ENG_MAP_START)
#define Enum                                                                        __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_DECLARATION_,     C_ENG_MAP_START)
#define Constructor                                                                 __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_CONSTRUCTOR_,     C_ENG_MAP_START)
#define Destructor                                                                  __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_DESTRUCTOR_,      C_ENG_MAP_START)
#define Self                                                                        __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_SELF_,            C_ENG_MAP_START)
#define Parent                                                                      __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_PARENT_,          C_ENG_MAP_START)
#define Field                                                                       __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_FIELD_,           C_ENG_MAP_START)
#define Const                                                                       __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_CONST_,           C_ENG_MAP_START)
#define Nester                                                                      __C_ENG_OBJECT_MAP_META_CALL(__C_ENG_OBJECT_MAP_NESTER_,          C_ENG_MAP_START)
#define Type                                                                        __C_ENG_TYPE
#define NoDiscard                                                                   __C_ENG_NO_DISCARD
#define MaybeUnused                                                                 __C_ENG_MAYBE_UNUSED


#elif defined(C_ENG_MAP_END) && defined(C_ENG_MAP_START)


#undef __C_ENG_OBJECT_MAP_CLASS_CLASS
#undef __C_ENG_OBJECT_MAP_DECLARATION_CLASS
#undef __C_ENG_OBJECT_MAP_CONSTRUCTOR_CLASS
#undef __C_ENG_OBJECT_MAP_DESTRUCTOR_CLASS
#undef __C_ENG_OBJECT_MAP_SELF_CLASS
#undef __C_ENG_OBJECT_MAP_PARENT_CLASS
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_DECLARATION

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_DECLARATION
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CASTED_DEFAULT_VALUE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CASTED_NO_INIT

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CASTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_NO_INIT

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_PRIMITIVE_TYPE_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_PRIMITIVE_TYPE_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_ENGINE_TYPE_CALL

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_DEFAULT_VALUE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_ENGINE_TYPE


#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_META_MODIFIERS_GET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_META_MODIFIERS_GET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_META_MODIFIERS_GET_NONE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_MODIFIERS_GET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_MODIFIERS_GET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_MODIFIERS_GET_NONE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_NAME_GET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_NAME_GET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_NAME_GET_NONE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_OBJECT_MODIFIERS_GET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_OBJECT_MODIFIERS_GET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_OBJECT_MODIFIERS_GET_NONE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_RETURN_TYPE_GET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_RETURN_TYPE_GET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_RETURN_TYPE_GET_NONE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_DEFINITION_GET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_DEFINITION_GET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_EXTRACT_DEFINITION_GET_NONE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_ENGINE_TYPE


#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_META_MODIFIERS_SET_INLINE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_MODIFIERS_SET_INLINE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_INLINE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_INLINE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_OBJECT_MODIFIERS_SET_INLINE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_INLINE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_DEFINITION_SET_INLINE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_NONE_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_DEFAULT_PROTECTED_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_INLINE_CALL

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_FORMULA_CALL_SET
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_NAME_SET_FORMULA_CALL_SET_INLINE


#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_EMPTY_PARAMETERS
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_PARAM
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_NAMED_PARAM
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT_PARAM
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAMETERS_SET_DEFAULT_PROTECTED_PARAM


#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_NOT_IN_HEADER
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_IN_HEADER
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_DEFINITION_DEFAULT

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_NONE_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_CALL
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_INLINE_CALL


#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_ENGINE_TYPE


#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_REQUIRED_TYPE_CALL

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_DEFAULT_VALUE_CAST_TYPE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_TYPE

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_MODIFIERS_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_EXTRACT_TYPE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_RETURN_TYPE_SET_DEFAULT_PROTECTED_EXTRACT_TYPE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_TYPE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_EXTRACT_PARAM_MODIFIERS_TYPE


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
#undef __C_ENG_OBJECT_MAP_CAST_TYPE
#undef __C_ENG_OBJECT_MAP_CAST_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_FIELD_ENUM_GEN
#undef __C_ENG_OBJECT_MAP_FIELD_ENUM_CASTER


#undef __C_ENG_OBJECT_MAP_PARENT_CLASS_PARENT
#undef __C_ENG_OBJECT_MAP_PARENT_CLASS_ENGINE_PARENT
#undef __C_ENG_OBJECT_MAP_PARENT_CLASS_NO_PARENT

#undef __C_ENG_OBJECT_MAP_PARENT_DECLARATION_PARENT
#undef __C_ENG_OBJECT_MAP_PARENT_DECLARATION_ENGINE_PARENT
#undef __C_ENG_OBJECT_MAP_PARENT_DECLARATION_NO_PARENT

#undef __C_ENG_OBJECT_MAP_BASE_TYPE_TYPE
#undef __C_ENG_OBJECT_MAP_BASE_TYPE_ENGINE_TYPE
#undef __C_ENG_OBJECT_MAP_BASE_TYPE_NO_TYPE


#undef __C_ENG_OBJECT_MAP_META_JOIN_AND_CALL
#undef __C_ENG_OBJECT_MAP_META_CALL


#undef __C_ENG_OBJECT_MAP_CONST_CLASS

#undef __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_TYPE_MODIFIERS_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_CONST_TYPE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_TYPE_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_TYPE_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_TYPE_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_TYPE

#undef __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_PRIMITIVE_TYPE_CALL
#undef __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_PRIMITIVE_TYPE_CALL
#undef __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_TYPE_CALL
#undef __C_ENG_OBJECT_MAP_CONST_VALUE_CAST_ENGINE_TYPE_CALL

#undef __C_ENG_OBJECT_MAP_CONST_VALUE_VALUE


#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_PRIMITIVE_TYPE_ARRAY
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ENGINE_PRIMITIVE_TYPE_ARRAY

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_ENGINE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_PRIMITIVE_TYPE_ARRAY
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_EXTRACT_TYPE_ARRAY_SIZE_ENGINE_PRIMITIVE_TYPE_ARRAY


#undef __C_ENG_OBJECT_MAP_CLASS_NESTED_CLASS
#undef __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS
#undef __C_ENG_OBJECT_MAP_CONSTRUCTOR_NESTED_CLASS
#undef __C_ENG_OBJECT_MAP_DESTRUCTOR_NESTED_CLASS
#undef __C_ENG_OBJECT_MAP_SELF_NESTED_CLASS
#undef __C_ENG_OBJECT_MAP_PARENT_NESTED_CLASS
#undef __C_ENG_OBJECT_MAP_FIELD_NESTED_CLASS
#undef __C_ENG_OBJECT_MAP_CONST_NESTED_CLASS
#undef __C_ENG_OBJECT_MAP_NESTER_NESTED_CLASS

#undef __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS_EXTRACT_NESTER_ENGINE_TYPE
#undef __C_ENG_OBJECT_MAP_DECLARATION_NESTED_CLASS_EXTRACT_NESTER_TYPE


#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_ENGINE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_ENGINE_PRIMITIVE_TYPE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_PRIMITIVE_TYPE_ARRAY
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_FIELD_ACCESS_MODIFIER_ENGINE_PRIMITIVE_TYPE_ARRAY

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_ACCESS_MODIFIER_GET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_ACCESS_MODIFIER_GET_DEFAULT
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_GETTER_ACCESS_MODIFIER_GET_DEFAULT_PROTECTED

#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET_NONE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET_DEFAULT_PROTECTED
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET_INLINE
#undef __C_ENG_OBJECT_MAP_FIELD_CLASS_GEN_SETTER_ACCESS_MODIFIER_SET


#undef Class
#undef Struct
#undef Enum
#undef Constructor
#undef Destructor
#undef Parent
#undef Self
#undef Field
#undef Const
#undef Nester
#undef Type
#undef NoDiscard
#undef MaybeUnused


#undef C_ENG_MAP_END
#undef C_ENG_MAP_START

#else

#error Wrong Usage of ObjectMapping. Use 'C_ENG_MAP_START' or 'C_ENG_MAP_END'.

#endif
