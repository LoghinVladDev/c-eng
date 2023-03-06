//
// Created by loghin on 25/02/23.
//

#ifndef __C_ENG_COMPILER_HPP__
#define __C_ENG_COMPILER_HPP__

#if defined(__CDS_compiler_clang) || defined(__CDS_compiler_gcc)

#define __C_ENG_E_FUNCTION__  __func__
#define __C_ENG_E_LINE__      __LINE__
#define __C_ENG_E_FILE__      __FILE__

#elif defined(__CDS_compiler_MinGW)

#define __C_ENG_E_FUNCTION__  __PRETTY_FUNCTION__
#define __C_ENG_E_LINE__      __LINE__
#define __C_ENG_E_FILE__      __FILE__

#elif defined(__CDS_compiler_MSVC)

#define __C_ENG_E_FUNCTION__  __FUNCSIG__
#define __C_ENG_E_LINE__      __LINE__
#define __C_ENG_E_FILE__      __FILE__

#else

#define __C_ENG_E_FUNCTION__  "Function-ID Macro not Defined"
#define __C_ENG_E_LINE__      "Line-ID Macro not Defined"
#define __C_ENG_E_FILE__      0

#endif

#endif /* __C_ENG_COMPILER_HPP__ */
