//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_COMPILER_HPP__
#define __C_ENG_COMPILER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_NO_DISCARD __CDS_NoDiscard /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_MAYBE_UNUSED __CDS_MaybeUnused /* NOLINT(bugprone-reserved-identifier) */

#define __C_ENG_STRINGIFY_PARSE_1(_token) # _token /* NOLINT(bugprone-reserved-identifier) */
#define __C_ENG_STRINGIFY(_token) __C_ENG_STRINGIFY_PARSE_1(_token) /* NOLINT(bugprone-reserved-identifier) */

#endif //__C_ENG_COMPILER_HPP__
