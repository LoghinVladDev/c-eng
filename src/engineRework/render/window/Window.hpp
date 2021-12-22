//
// Created by loghin on 19.12.2021.
//

#ifndef C_ENG_WINDOW_HPP
#define C_ENG_WINDOW_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <Core.hpp>

#include <CDS/Queue>

namespace engine {

    class C_ENG_CLASS ( Engine );
    class C_ENG_CLASS ( Monitor );

    class C_ENG_CLASS ( Event );
    class C_ENG_CLASS ( WindowEvent );
    class C_ENG_CLASS ( MouseEvent );
    class C_ENG_CLASS ( KeyEvent );

    class C_ENG_CLASS ( Window ) : public cds :: Object {
    public:
        using Handle = GLFWwindow *;

        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: StringLiteral, defaultWindowTitle, "VEngineTest" ); // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT (
                WindowFlags,
                defaultFlags,
                    WindowFlag :: WindowFlagResizable           |
                    WindowFlag :: WindowFlagGrabFocusOnOpen     |
                    WindowFlag :: WindowFlagGrabFocusOnRaise
        )

    private:
        cds :: String _title { defaultWindowTitle };

        cds :: Queue < C_ENG_TYPE ( WindowEvent ) * >   _customWindowEvents;
        cds :: Queue < C_ENG_TYPE ( MouseEvent ) * >    _customMouseEvents;
        cds :: Queue < C_ENG_TYPE ( KeyEvent ) * >      _customKeyEvents;
        cds :: Queue < C_ENG_TYPE ( Event ) * >         _customEvents;

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( WindowFlags, flags, defaultFlags )

        C_ENG_CLASS_IMMUTABLE_FIELD ( Position, position, 0U, 0U )
        C_ENG_CLASS_IMMUTABLE_FIELD ( RectangleSize, size, 0U, 0U )
        C_ENG_CLASS_IMMUTABLE_FIELD ( Position, mousePosition, 0U, 0U )

        C_ENG_CLASS_IMMUTABLE_FIELD ( RectangleSize, minimumSize, cds :: limits :: U32_MIN, cds :: limits :: U32_MIN )
        C_ENG_CLASS_IMMUTABLE_FIELD ( RectangleSize, maximumSize, cds :: limits :: U32_MAX, cds :: limits :: U32_MAX )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, refreshRate, 60u )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Engine ) *, engine, nullptr )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Monitor ) const *, monitor, nullptr )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( WindowType, type, WindowType :: WindowTypeWindowed );

        friend auto __updateWindowSize ( C_ENG_TYPE ( Window ) *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)
        friend auto __updateCursorPos ( C_ENG_TYPE ( Window ) *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( Handle, handle, nullptr )

        auto applyFlagHints () const noexcept -> void;
        auto updateWindowLimits () noexcept -> void;

    public:
        auto init () noexcept (false) -> C_ENG_TYPE ( Window ) &;
        auto clear () noexcept -> C_ENG_TYPE ( Window ) &;

        auto setEngine ( C_ENG_TYPE ( Engine ) * ) noexcept -> C_ENG_TYPE ( Window ) &;

        explicit C_ENG_CONSTRUCTOR ( Window ) ( WindowFlags flags = defaultFlags ) noexcept :
                _flags ( flags ) {

        }

        C_ENG_DESTRUCTOR ( Window ) () noexcept {
            (void) this->clear();
        }

        auto makeWindowed () noexcept -> C_ENG_TYPE ( Window ) &;
        auto makeFullscreen ( C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> C_ENG_TYPE ( Window ) &;
        auto makeWindowedFullscreen ( C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> C_ENG_TYPE ( Window ) &;

        C_ENG_NO_DISCARD inline auto shouldClose () const noexcept -> bool {
            return glfwWindowShouldClose ( this->handle() );
        }

        C_ENG_MAYBE_UNUSED auto setWindowType ( WindowType, C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> C_ENG_TYPE ( Window ) &;

        auto move ( Position const & ) noexcept -> C_ENG_TYPE ( Window ) &;
        auto resize ( RectangleSize const & ) noexcept -> C_ENG_TYPE ( Window ) &;

        auto setMinimumSize ( RectangleSize const & ) noexcept -> C_ENG_TYPE ( Window ) &;
        auto setMaximumSize ( RectangleSize const & ) noexcept -> C_ENG_TYPE ( Window ) &;

        auto maximize () noexcept -> C_ENG_TYPE ( Window ) &;
        auto minimize () noexcept -> C_ENG_TYPE ( Window ) &;
        auto hide () noexcept -> C_ENG_TYPE ( Window ) &;
        auto show () noexcept -> C_ENG_TYPE ( Window ) &;
        auto grabInputFocus () noexcept -> C_ENG_TYPE ( Window ) &;
        auto requestAttention () noexcept -> C_ENG_TYPE ( Window ) &;

        auto pollEvents () noexcept -> C_ENG_TYPE ( Window ) &;

        auto handleEvent ( C_ENG_TYPE ( WindowEvent ) * ) noexcept -> C_ENG_TYPE ( Window ) &;
        auto handleEvent ( C_ENG_TYPE ( MouseEvent ) * ) noexcept -> C_ENG_TYPE ( Window ) &;
        auto handleEvent ( C_ENG_TYPE ( KeyEvent ) * ) noexcept -> C_ENG_TYPE ( Window ) &;
        auto handleEvent ( C_ENG_TYPE ( Event ) * ) noexcept -> C_ENG_TYPE ( Window ) &;

        inline auto move ( cds :: uint32 x, cds :: uint32 y ) noexcept -> C_ENG_TYPE ( Window ) & {
            return this->move ( { x, y } );
        }

        inline auto resize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> C_ENG_TYPE ( Window ) & {
            return this->resize ( { width, height } );
        }

        inline auto setMinimumSize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> C_ENG_TYPE ( Window ) & {
            return this->setMinimumSize ( { width, height } );
        }

        inline auto setMaximumSize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> C_ENG_TYPE ( Window ) & {
            return this->setMaximumSize ( { width, height } );
        }

        C_ENG_MAYBE_UNUSED auto setTitle ( cds :: String const & ) noexcept -> C_ENG_TYPE ( Window ) &;

        auto grabMouseCursor () noexcept -> C_ENG_TYPE ( Window ) &;
        auto releaseMouseCursor () noexcept -> C_ENG_TYPE ( Window ) &;

        auto monitorDisconnectedEvent () noexcept -> C_ENG_TYPE ( Window ) &;
    };

}

#endif //C_ENG_WINDOW_HPP
