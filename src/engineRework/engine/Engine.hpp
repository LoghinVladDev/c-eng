//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_ENGINE_HPP
#define __C_ENG_ENGINE_HPP

#include <Preprocess.hpp>
#include <CDS/Pointer>

#include <Core.hpp>

#include <EventHandler.hpp>


#define C_ENG_MAP_START     CLASS ( Engine, EXTERNAL_PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Window );
    __C_ENG_PRE_DECLARE_CLASS ( RenderEngine );

    Class {
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( EngineState ), state, __C_ENG_TYPE ( EngineState ) :: EngineStateInactive )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( Window ) *, window, nullptr )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( RenderEngine ) *, renderEngine, nullptr )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool, externalRenderEngine, true )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, frameDeltaTime, 0.0 )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool, logFPSToConsole, false )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, fpsUpdateFrameTime, 512ULL )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, showFpsEveryTick, 8192ULL )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, frameCount, 0ULL )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, fps, 0.0f )

        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( EventHandler ), eventHandler )

    private:
        auto initializeSettings () noexcept -> Self &;
        auto initializeRenderEngine () noexcept -> Self &;
        auto startup () noexcept -> Self &;
        auto run () noexcept -> Self &;
        auto shutdown () noexcept -> Self &;

        Constructor () noexcept;
        Destructor () noexcept override;

        constexpr auto setState ( __C_ENG_TYPE ( EngineState ) state ) noexcept -> void {
            this->_state = state;
        }

    public:
        auto static instance () noexcept -> Self &;
        auto start () noexcept -> Self &;
        auto setWindow ( __C_ENG_TYPE ( Window ) * ) noexcept -> Self &;
        auto setRenderEngine ( __C_ENG_TYPE ( RenderEngine ) * ) noexcept -> Self &;
        auto shutdownRequested () noexcept -> bool;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_ENGINE_HPP
