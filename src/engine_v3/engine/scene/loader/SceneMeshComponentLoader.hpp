//
// Created by loghin on 5/17/22.
//

#ifndef __C_ENG_SCENE_MESH_COMPONENT_LOADER_HPP__
#define __C_ENG_SCENE_MESH_COMPONENT_LOADER_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>


#define C_ENG_MAP_START CLASS ( SceneMeshComponentLoader, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Mesh );

    Class {
        ClassDefs

    public:
        auto load ( Type ( Mesh ) * ) noexcept -> Self &;
        auto done () noexcept -> bool;

        auto clear () noexcept -> Self & override;

        Destructor () noexcept override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_SCENE_MESH_COMPONENT_LOADER_HPP__
