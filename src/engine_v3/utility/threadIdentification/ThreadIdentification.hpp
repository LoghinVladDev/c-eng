//
// Created by loghin on 5/1/22.
//

#ifndef __C_ENG_THREAD_IDENTIFICATION_HPP__
#define __C_ENG_THREAD_IDENTIFICATION_HPP__

#include <CDS/Thread>

namespace engine {

    constexpr cds :: StringLiteral engineThreadIdentificationString         = "Engine Main Thread";
    constexpr cds :: StringLiteral sceneLoaderThreadIdentificationString    = "Scene Loader Thread";
    constexpr cds :: StringLiteral unassignedThreadIdentificationString     = "Unassigned/External Thread";

    extern auto storeThreadIdentificationString ( cds :: Thread :: ID, cds :: StringLiteral ) noexcept -> void;
    extern auto getThreadIdentificationString ( cds :: Thread :: ID ) noexcept -> cds :: StringLiteral;

}

#endif //__C_ENG_THREAD_IDENTIFICATION_HPP__
