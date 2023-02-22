//
// Created by loghin on 30.12.2021.
//

#ifndef __C_ENG_FUNC_HPP__
#define __C_ENG_FUNC_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/Traits>

namespace engine {

    template < typename T, cds :: EnableIf < cds :: Type < T > :: isNumeric > = 0 >
    __C_ENG_NO_DISCARD constexpr auto compare (
            T left,
            T right
    ) noexcept -> __C_ENG_TYPE ( CompareResult ) {

        if ( left < right ) {
            return __C_ENG_TYPE ( CompareResult ) :: CompareResultLess;
        } else if ( left > right ) {
            return __C_ENG_TYPE ( CompareResult ) :: CompareResultGreater;
        } else {
            return __C_ENG_TYPE ( CompareResult ) :: CompareResultEquals;
        }

    }

}

#endif //__C_ENG_FUNC_HPP__
