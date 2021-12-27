//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_COMPILER_HPP
#define __C_ENG_COMPILER_HPP

#define __C_ENG_NO_DISCARD __CDS_NoDiscard
#define __C_ENG_MAYBE_UNUSED __CDS_MaybeUnused

#define __C_ENG_STRINGIFY_PARSE_1(_token) # _token
#define __C_ENG_STRINGIFY(_token) __C_ENG_STRINGIFY_PARSE_1(_token)

#endif //__C_ENG_COMPILER_HPP
