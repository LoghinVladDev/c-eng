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


#endif //C_ENG_NAMING_HPP
