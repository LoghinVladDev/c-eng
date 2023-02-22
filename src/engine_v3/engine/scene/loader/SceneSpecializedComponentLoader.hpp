//
// Created by loghin on 5/17/22.
//

#ifndef __C_ENG_SCENE_SPECIALIZED_COMPONENT_LOADER_HPP__
#define __C_ENG_SCENE_SPECIALIZED_COMPONENT_LOADER_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>


#define C_ENG_MAP_START CLASS ( SceneSpecializedComponentLoader, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Component );

    Class {
        ClassDefs

    public:
        virtual auto type () const noexcept -> Type ( ComponentTypeFlag ) = 0;
        virtual auto load ( Type ( Component ) * ) noexcept -> Self & = 0;
        virtual auto done () noexcept -> bool = 0;

        auto clear () noexcept -> Self & override = 0;

        Destructor () noexcept override = default;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_SCENE_SPECIALIZED_COMPONENT_LOADER_HPP__
