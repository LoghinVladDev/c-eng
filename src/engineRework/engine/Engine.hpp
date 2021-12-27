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

    __C_ENG_PRE_DECLARE_CLASS ( Window );


#pragma push_macro ("__C_ENG_OBJECT_NAME")

#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Engine /* NOLINT(bugprone-reserved-identifier) */

    __C_ENG_CLASS : public cds :: Object {
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
        auto initializeSettings () noexcept -> __C_ENG_SELF &;
        auto startup () noexcept -> __C_ENG_SELF &;
        auto run () noexcept -> __C_ENG_SELF &;
        auto shutdown () noexcept -> __C_ENG_SELF &;

        __C_ENG_CONSTRUCTOR () noexcept;

        constexpr auto setState ( __C_ENG_TYPE ( EngineState ) state ) noexcept -> void {
            this->_state = state;
        }

    public:
        auto static instance () noexcept -> __C_ENG_SELF &;
        auto start () noexcept -> __C_ENG_SELF &;
        auto setWindow ( __C_ENG_TYPE ( Window ) * ) noexcept -> __C_ENG_SELF &;
        auto shutdownRequested () noexcept -> bool;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

#pragma pop_macro ("__C_ENG_OBJECT_NAME")


}

#endif //__C_ENG_ENGINE_HPP
