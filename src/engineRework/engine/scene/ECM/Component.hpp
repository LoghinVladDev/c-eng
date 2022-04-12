//
// Created by loghin on 4/6/22.
//

#ifndef C_ENG_COMPONENT_HPP
#define C_ENG_COMPONENT_HPP

#include <Preprocess.hpp>
#include <CDS/Object>
#include <Core.hpp>


#define C_ENG_MAP_START CLASS ( Component, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {
    Class {
        ClassDefs

    public:
        NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto type () const noexcept -> Type ( ComponentTypeFlag ) = 0;
        auto loadFrom ( cds :: JSON const & ) noexcept -> Self &;
        auto dumpTo ( cds :: JSON & json ) noexcept -> Self &;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //C_ENG_COMPONENT_HPP
