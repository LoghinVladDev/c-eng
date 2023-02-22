//
// Created by loghin on 5/16/22.
//

#ifndef __C_ENG_MESH_HPP__
#define __C_ENG_MESH_HPP__

#include <Preprocess.hpp>
#include <scene/ECM/Component.hpp>
#include <meshLoader/publicTypes>

#define C_ENG_MAP_START CLASS ( Mesh, ENGINE_PARENT ( Component ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        ClassDefs

        Const ( TYPE ( cds :: String ),             pathKey,            VALUE ( "path" ) )
        Const ( TYPE ( cds :: String ),             relativeToSceneKey, VALUE ( "relativeToScene" ) )

        Field ( TYPE ( cds :: Path ),               path,               NO_INIT,                    GET_DEFAULT,    SET_NONE )
        Field ( PRIMITIVE_TYPE ( MeshLoader_Mesh ), handle,             DEFAULT_VALUE ( nullptr ),  GET_DEFAULT,    SET_NONE )

    public:
        NoDiscard constexpr auto type () const noexcept -> Type ( ComponentTypeFlag ) override {
            return ComponentTypeFlagMesh;
        }

        Constructor () noexcept = default;

        Constructor ( Self const & ) noexcept = default;
        Constructor ( Self && ) noexcept;

        auto operator = ( Self const & ) noexcept -> Self & = default;
        auto operator = ( Self && ) noexcept -> Self &;

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> Self & override;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self & override;
        auto clear () noexcept -> Self & override;

        NoDiscard auto copy () const noexcept -> Self * override;
        NoDiscard auto toString () const noexcept -> cds :: String override;

        Destructor () noexcept override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>

#endif // __C_ENG_MESH_HPP__
