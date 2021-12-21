//
// Created by loghin on 18.12.2021.
//

#ifndef C_ENG_ENGINE_HPP
#define C_ENG_ENGINE_HPP

#include <Preprocess.hpp>
#include <CDS/Pointer>

#include <Core.hpp>

namespace engine {

    class C_ENG_CLASS ( Window );

    class C_ENG_CLASS ( ResizeEvent );

    class C_ENG_CLASS ( KeyPressEvent );
    class C_ENG_CLASS ( KeyReleaseEvent );

    class C_ENG_CLASS ( MouseMoveEvent );
    class C_ENG_CLASS ( MouseEnterEvent );
    class C_ENG_CLASS ( MouseLeaveEvent );
    class C_ENG_CLASS ( MousePressEvent );
    class C_ENG_CLASS ( MouseReleaseEvent );
    class C_ENG_CLASS ( MouseScrollEvent );

    class C_ENG_CLASS ( Engine ) : public cds :: Object {
    public:

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( EngineState, state, EngineState :: EngineStateInactive )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Window ) *, window, nullptr )

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

        auto resizeEvent ( C_ENG_TYPE ( ResizeEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto keyPressEvent ( C_ENG_TYPE ( KeyPressEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto keyReleaseEvent ( C_ENG_TYPE ( KeyReleaseEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto mouseMoveEvent ( C_ENG_TYPE ( MouseMoveEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mousePressEvent ( C_ENG_TYPE ( MousePressEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseReleaseEvent ( C_ENG_TYPE ( MouseReleaseEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseEnterEvent ( C_ENG_TYPE ( MouseEnterEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseLeaveEvent ( C_ENG_TYPE ( MouseLeaveEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;
        auto mouseScrollEvent ( C_ENG_TYPE ( MouseScrollEvent ) * ) noexcept -> C_ENG_TYPE ( Engine ) &;

        auto shutdownRequested () noexcept -> bool;
    };

}

#endif //C_ENG_ENGINE_HPP
