//
// Created by loghin on 5/17/22.
//

#ifndef __C_ENG_SCENE_COMPONENT_LOADER_HPP__
#define __C_ENG_SCENE_COMPONENT_LOADER_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <scene/loader/SceneSpecializedComponentLoader.hpp>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/Array>


#define C_ENG_MAP_START CLASS ( SceneComponentLoader, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Component );

    Class {
        ClassDefs

        using Loaders = cds :: Array < cds :: UniquePointer < Type ( SceneSpecializedComponentLoader ) > >;

        Field ( TYPE ( Loaders ), loaders, NO_INIT, GET_NONE, SET_NONE )

    public:
        auto update ( cds :: DoubleLinkedList < Type ( Component ) * > & ) noexcept -> Self &;
        auto done () noexcept -> bool;

        auto clear () noexcept -> Self & override;

        Destructor () noexcept override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_SCENE_COMPONENT_LOADER_HPP__
