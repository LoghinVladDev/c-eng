//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_ENGINE_HPP
#define __C_ENG_ENGINE_HPP

#include <Preprocess.hpp>
#include <CDS/Pointer>

#include <Core.hpp>

#include <EventHandler.hpp>

namespace engine {

    __C_ENG_CLASS ( Window );

    __C_ENG_CLASS ( Engine ) : public cds :: Object {
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( EngineState ), state, __C_ENG_TYPE ( EngineState ) :: EngineStateInactive )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( Window ) *, window, nullptr )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, frameDeltaTime, 0.0 )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool, logFPSToConsole, false )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, fpsUpdateFrameTime, 512ULL )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, showFpsEveryTick, 8192ULL )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, frameCount, 0ULL )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, fps, 0.0f )

        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( EventHandler ), eventHandler )

    private:
        auto initializeSettings () noexcept -> __C_ENG_TYPE ( Engine & );
        auto startup () noexcept -> __C_ENG_TYPE ( Engine ) &;
        auto run () noexcept -> __C_ENG_TYPE ( Engine ) &;
        auto shutdown () noexcept -> __C_ENG_TYPE ( Engine ) &;

        __C_ENG_CONSTRUCTOR ( Engine ) () noexcept;

        constexpr auto setState ( __C_ENG_TYPE ( EngineState ) state ) noexcept -> void {
            this->_state = state;
        }

    public:
        auto static instance () noexcept -> __C_ENG_TYPE ( Engine ) &;
        auto start () noexcept -> __C_ENG_TYPE ( Engine ) &;
        auto setWindow ( __C_ENG_TYPE ( Window ) * ) noexcept -> __C_ENG_TYPE ( Engine ) &;
        auto shutdownRequested () noexcept -> bool;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#endif //__C_ENG_ENGINE_HPP
