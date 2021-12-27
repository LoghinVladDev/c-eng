//
// Created by loghin on 19.12.2021.
//

#ifndef __C_ENG_WINDOW_HPP
#define __C_ENG_WINDOW_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <Core.hpp>

#include <SimpleEventQueue.hpp>

namespace engine {

    __C_ENG_CLASS ( Engine );
    __C_ENG_CLASS ( Monitor );

    __C_ENG_CLASS ( Event );
    __C_ENG_CLASS ( WindowEvent );
    __C_ENG_CLASS ( MouseEvent );
    __C_ENG_CLASS ( KeyEvent );

    __C_ENG_CLASS ( Window ) : public cds :: Object {
    public:
        using Handle = GLFWwindow *;

        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: StringLiteral, defaultWindowTitle, "VEngineTest" ); // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT (                            // NOLINT(clion-misra-cpp2008-4-5-2)
                __C_ENG_TYPE ( WindowFlags ),
                defaultFlags,
                    __C_ENG_TYPE ( WindowFlag ) :: WindowFlagResizable           |
                    __C_ENG_TYPE ( WindowFlag ) :: WindowFlagGrabFocusOnOpen     |
                    __C_ENG_TYPE ( WindowFlag ) :: WindowFlagGrabFocusOnRaise
        )

    private:
        cds :: String _title { defaultWindowTitle };

        utility :: SimpleEventQueue < __C_ENG_TYPE ( WindowEvent ) * >   _customWindowEvents;
        utility :: SimpleEventQueue < __C_ENG_TYPE ( MouseEvent ) * >    _customMouseEvents;
        utility :: SimpleEventQueue < __C_ENG_TYPE ( KeyEvent ) * >      _customKeyEvents;
        utility :: SimpleEventQueue < __C_ENG_TYPE ( Event ) * >         _customEvents;

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( Handle, handle, nullptr )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( WindowFlags ), flags, defaultFlags )

        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Position ), position, 0U, 0U )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Size ), size, 0U, 0U )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Position ), mousePosition, 0U, 0U )

        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Size ), minimumSize, cds :: limits :: U32_MIN, cds :: limits :: U32_MIN )
        __C_ENG_CLASS_IMMUTABLE_FIELD ( __C_ENG_TYPE ( Size ), maximumSize, cds :: limits :: U32_MAX, cds :: limits :: U32_MAX )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, refreshRate, 60u )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( Engine ) *, engine, nullptr )
        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( Monitor ) const *, monitor, nullptr )

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( WindowType ), type, __C_ENG_TYPE ( WindowType ) :: WindowTypeWindowed );

        friend auto __updateWindowSize ( __C_ENG_TYPE ( Window ) *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)
        friend auto __updateCursorPos ( __C_ENG_TYPE ( Window ) *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)

        auto applyFlagHints () const noexcept -> void;
        auto updateWindowLimits () noexcept -> void;

    public:
        auto init () noexcept (false) -> __C_ENG_TYPE ( Window ) &;
        auto clear () noexcept -> __C_ENG_TYPE ( Window ) &;

        auto setEngine ( __C_ENG_TYPE ( Engine ) * ) noexcept -> __C_ENG_TYPE ( Window ) &;

        explicit __C_ENG_CONSTRUCTOR ( Window ) ( __C_ENG_TYPE ( WindowFlags ) flags = defaultFlags ) noexcept :
                _flags ( flags ) {

        }

        __C_ENG_DESTRUCTOR ( Window ) () noexcept {
            (void) this->clear();
        }

        auto makeWindowed () noexcept -> __C_ENG_TYPE ( Window ) &;
        auto makeFullscreen ( __C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> __C_ENG_TYPE ( Window ) &;
        auto makeWindowedFullscreen ( __C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> __C_ENG_TYPE ( Window ) &;

        __C_ENG_NO_DISCARD inline auto shouldClose () const noexcept -> bool {
            return glfwWindowShouldClose ( this->handle() );
        }

        __C_ENG_MAYBE_UNUSED auto setWindowType ( __C_ENG_TYPE ( WindowType ), __C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> __C_ENG_TYPE ( Window ) &;

        auto move ( __C_ENG_TYPE ( Position ) const & ) noexcept -> __C_ENG_TYPE ( Window ) &;
        auto resize ( __C_ENG_TYPE ( Size ) const & ) noexcept -> __C_ENG_TYPE ( Window ) &;

        auto setMinimumSize ( __C_ENG_TYPE ( Size ) const & ) noexcept -> __C_ENG_TYPE ( Window ) &;
        auto setMaximumSize ( __C_ENG_TYPE ( Size ) const & ) noexcept -> __C_ENG_TYPE ( Window ) &;

        auto maximize () noexcept -> __C_ENG_TYPE ( Window ) &;
        auto minimize () noexcept -> __C_ENG_TYPE ( Window ) &;
        auto hide () noexcept -> __C_ENG_TYPE ( Window ) &;
        auto show () noexcept -> __C_ENG_TYPE ( Window ) &;
        __C_ENG_MAYBE_UNUSED auto grabInputFocus () noexcept -> __C_ENG_TYPE ( Window ) &;
        __C_ENG_MAYBE_UNUSED auto requestAttention () noexcept -> __C_ENG_TYPE ( Window ) &;

        auto pollEvents () noexcept -> __C_ENG_TYPE ( Window ) &;

        __C_ENG_MAYBE_UNUSED auto handleEvent ( __C_ENG_TYPE ( WindowEvent ) const & ) noexcept -> __C_ENG_TYPE ( Window ) &;
        __C_ENG_MAYBE_UNUSED auto handleEvent ( __C_ENG_TYPE ( MouseEvent ) const & ) noexcept -> __C_ENG_TYPE ( Window ) &;
        __C_ENG_MAYBE_UNUSED auto handleEvent ( __C_ENG_TYPE ( KeyEvent ) const & ) noexcept -> __C_ENG_TYPE ( Window ) &;
        __C_ENG_MAYBE_UNUSED auto handleEvent ( __C_ENG_TYPE ( Event ) const & ) noexcept -> __C_ENG_TYPE ( Window ) &;

        inline auto move ( cds :: uint32 x, cds :: uint32 y ) noexcept -> __C_ENG_TYPE ( Window ) & {
            return this->move ( { x, y } );
        }

        inline auto resize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> __C_ENG_TYPE ( Window ) & {
            return this->resize ( { width, height } );
        }

        __C_ENG_MAYBE_UNUSED inline auto setMinimumSize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> __C_ENG_TYPE ( Window ) & {
            return this->setMinimumSize ( { width, height } );
        }

        __C_ENG_MAYBE_UNUSED inline auto setMaximumSize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> __C_ENG_TYPE ( Window ) & {
            return this->setMaximumSize ( { width, height } );
        }

        __C_ENG_MAYBE_UNUSED auto setTitle ( cds :: String const & ) noexcept -> __C_ENG_TYPE ( Window ) &;

        auto grabMouseCursor () noexcept -> __C_ENG_TYPE ( Window ) &;
        auto releaseMouseCursor () noexcept -> __C_ENG_TYPE ( Window ) &;

        auto monitorDisconnectedEvent () noexcept -> __C_ENG_TYPE ( Window ) &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#endif //__C_ENG_WINDOW_HPP
