//
// Created by loghin on 4/30/22.
//

#ifndef __C_ENG_GAME_OBJECT_HPP__
#define __C_ENG_GAME_OBJECT_HPP__


#include <Preprocess.hpp>
#include <scene/ECM/Entity.hpp>

#define C_ENG_MAP_START CLASS ( GameObject, ENGINE_PARENT ( Entity ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Mesh );
    __C_ENG_PRE_DECLARE_CLASS ( MeshRenderer );

    Class {
        using MeshType          = Type ( Mesh ) *;
        using MeshRendererType  = Type ( MeshRenderer ) *;

        ClassDefsNoPrefix

        Field ( PRIMITIVE_TYPE ( MeshType ),          mesh,           DEFAULT_VALUE ( nullptr ), GET_DEFAULT, SET_NONE )
        Field ( PRIMITIVE_TYPE ( MeshRendererType ),  meshRenderer,   DEFAULT_VALUE ( nullptr ), GET_DEFAULT, SET_NONE )

    public:
        NoDiscard constexpr auto drawable () const noexcept -> bool {
            return this->mesh() != nullptr && this->meshRenderer() != nullptr;
        }

        NoDiscard auto toString () const noexcept -> cds :: String override;
        NoDiscard auto copy () const noexcept -> Self * override;

        auto add ( Type ( Component ) * ) noexcept -> Self & override;
        auto remove ( Type ( Component ) * ) noexcept -> Self & override;

        auto clear () noexcept -> Self & override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_GAME_OBJECT_HPP__
