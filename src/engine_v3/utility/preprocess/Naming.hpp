//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_NAMING_HPP__
#define __C_ENG_NAMING_HPP__ /* NOLINT(bugprone-reserved-identifier) */


#ifndef __C_ENG_DEFAULT_NAMING_PREFIX
#define __C_ENG_DEFAULT_NAMING_PREFIX /* NOLINT(bugprone-reserved-identifier) */
#endif


#define __C_ENG_PREFIX_APPLICATION_PARSE2(_prefix, _type) _prefix ## _type /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_PREFIX_APPLICATION_PARSE1(_prefix, _type) __C_ENG_PREFIX_APPLICATION_PARSE2(_prefix, _type) /* NOLINT(bugprone-reserved-identifier) */


#define __C_ENG_TYPE(_type) __C_ENG_PREFIX_APPLICATION_PARSE1(__C_ENG_DEFAULT_NAMING_PREFIX, _type) /* NOLINT(bugprone-reserved-identifier) */


#define __C_ENG_ALIAS(_name, _type) using __C_ENG_TYPE(_name) = _type /* NOLINT(bugprone-reserved-identifier) */


#define __C_ENG_PRE_DECLARE_CLASS(_name)    class __C_ENG_TYPE(_name) /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_PRE_DECLARE_STRUCT(_name)   struct __C_ENG_TYPE(_name) /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_FRIEND_CLASS(_name)     friend class __C_ENG_TYPE(_name) /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_FRIEND_STRUCT(_name)    friend struct __C_ENG_TYPE(_name) /* NOLINT(bugprone-reserved-identifier) */


#endif //__C_ENG_NAMING_HPP__
