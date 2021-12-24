//
// Created by loghin on 18.12.2021.
//

#ifndef C_ENG_ENGINE_HPP
#define C_ENG_ENGINE_HPP

#include <Preprocess.hpp>
#include <CDS/Pointer>

#include <Core.hpp>

#include <EventHandler.hpp>

namespace engine {

    class C_ENG_CLASS ( Window );

    class C_ENG_CLASS ( Engine ) : public cds :: Object {
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( EngineState, state, EngineState :: EngineStateInactive )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Window ) *, window, nullptr )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, frameDeltaTime, 0.0 )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool, logFPSToConsole, false )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, fpsUpdateFrameTime, 512ULL )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, showFpsEveryTick, 8192ULL )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint64, frameCount, 0ULL )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( double, fps, 0.0f )

        C_ENG_CLASS_IMMUTABLE_FIELD ( C_ENG_TYPE ( EventHandler ), eventHandler )

    private:
        auto initializeSettings () noexcept -> C_ENG_TYPE ( Engine & );
        auto startup () noexcept -> C_ENG_TYPE ( Engine ) &;
        auto run () noexcept -> C_ENG_TYPE ( Engine ) &;
        auto shutdown () noexcept -> C_ENG_TYPE ( Engine ) &;

        C_ENG_CONSTRUCTOR ( Engine ) () noexcept;

        constexpr auto setState ( EngineState state ) noexcept -> void {
            this->_state = state;
        }

    public:
        auto static instance () noexcept -> C_ENG_TYPE ( Engine ) &;
        auto start () noexcept -> C_ENG_TYPE ( Engine ) &;
        auto setWindow ( C_ENG_TYPE ( Window ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto shutdownRequested () noexcept -> bool;

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#endif //C_ENG_ENGINE_HPP
