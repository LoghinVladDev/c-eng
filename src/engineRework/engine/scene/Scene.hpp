//
// Created by loghin on 4/6/22.
//

#ifndef __C_ENG_SCENE_HPP__
#define __C_ENG_SCENE_HPP__

#include <Preprocess.hpp>
#include <Core.hpp>
#include <CDS/Array>
#include <CDS/Pointer>
#include <CDS/experimental/JSON>

#define C_ENG_MAP_START     CLASS ( Scene, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Entity );
    __C_ENG_PRE_DECLARE_CLASS ( Shader );

    Class {
        ClassDefs

        Const ( TYPE ( cds :: String ),    sceneNameKey,       VALUE ( "sceneName" ) )
        Const ( TYPE ( cds :: String ),    rootEntitiesKey,    VALUE ( "rootEntities" ) )

    private:
        auto loadEntity ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> cds :: UniquePointer < Type ( Entity ) >;

        using DirectEntities    = cds :: Array < cds :: UniquePointer < Type ( Entity ) > >;
        using IndirectEntities  = cds :: DoubleLinkedList < cds :: ForeignPointer < Type ( Entity ) > >;
        using Shaders           = cds :: Array < cds :: UniquePointer < Type ( Shader ) > >;

        Field ( TYPE ( IndirectEntities ),      entities,       NO_INIT, GET_DEFAULT, SET_NONE )
        Field ( TYPE ( DirectEntities ),        rootEntities,   NO_INIT, GET_DEFAULT, SET_NONE )

        Field ( TYPE ( cds :: String ),         name,           NO_INIT, GET_DEFAULT, SET_DEFAULT )

        auto removeNonRoot ( cds :: ForeignPointer < Type ( Entity ) > const & ) noexcept -> Self &;

    public:
        Constructor () noexcept = default;
        Constructor ( Self const & ) noexcept = delete;
        Constructor ( Self && ) noexcept;

        auto operator = ( Self const & ) noexcept -> Self & = delete;
        auto operator = ( Self && ) noexcept -> Self &;

        Destructor () noexcept;

        auto loadFrom ( cds :: json :: standard :: JsonObject const & ) noexcept (false) -> Self &;
        auto dumpTo ( cds :: json :: standard :: JsonObject & ) noexcept -> Self &;
        auto clear () noexcept -> Self & override;

        auto remove ( cds :: ForeignPointer < Type ( Entity ) > const & ) noexcept -> Self &;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif // __C_ENG_SCENE_HPP__