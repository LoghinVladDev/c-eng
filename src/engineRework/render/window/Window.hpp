//
// Created by loghin on 19.12.2021.
//

#ifndef __C_ENG_WINDOW_HPP
#define __C_ENG_WINDOW_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <Core.hpp>

#include <SimpleEventQueue.hpp>


#define C_ENG_MAP_START     CLASS ( Window, EXTERNAL_PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    __C_ENG_PRE_DECLARE_CLASS ( Engine );
    __C_ENG_PRE_DECLARE_CLASS ( Monitor );

    __C_ENG_PRE_DECLARE_CLASS ( Event );
    __C_ENG_PRE_DECLARE_CLASS ( WindowEvent );
    __C_ENG_PRE_DECLARE_CLASS ( MouseEvent );
    __C_ENG_PRE_DECLARE_CLASS ( KeyEvent );

    Class {
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

        friend auto __updateWindowSize ( Self *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)
        friend auto __updateCursorPos ( Self *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)

        auto applyFlagHints () const noexcept -> void;
        auto updateWindowLimits () noexcept -> void;

    public:
        auto init () noexcept (false) -> Self &;
        auto clear () noexcept -> Self &;

        auto setEngine ( __C_ENG_TYPE ( Engine ) * ) noexcept -> Self &;

        explicit Constructor (
                __C_ENG_TYPE ( WindowFlags ) flags = defaultFlags
        ) noexcept :
                _flags ( flags ) {

        }

        Destructor () noexcept {
            (void) this->clear();
        }

        auto makeWindowed () noexcept -> Self &;
        auto makeFullscreen ( __C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> Self &;
        auto makeWindowedFullscreen ( __C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> Self &;

        __C_ENG_NO_DISCARD inline auto shouldClose () const noexcept -> bool {
            return glfwWindowShouldClose ( this->handle() );
        }

        __C_ENG_MAYBE_UNUSED auto setWindowType ( __C_ENG_TYPE ( WindowType ), __C_ENG_TYPE ( Monitor ) const * = nullptr ) noexcept -> Self &;

        auto move ( __C_ENG_TYPE ( Position ) const & ) noexcept -> Self &;
        auto resize ( __C_ENG_TYPE ( Size ) const & ) noexcept -> Self &;

        auto setMinimumSize ( __C_ENG_TYPE ( Size ) const & ) noexcept -> Self &;
        auto setMaximumSize ( __C_ENG_TYPE ( Size ) const & ) noexcept -> Self &;

        auto maximize () noexcept -> Self &;
        auto minimize () noexcept -> Self &;
        auto hide () noexcept -> Self &;
        auto show () noexcept -> Self &;
        __C_ENG_MAYBE_UNUSED auto grabInputFocus () noexcept -> Self &;
        __C_ENG_MAYBE_UNUSED auto requestAttention () noexcept -> Self &;

        auto pollEvents () noexcept -> Self &;

        __C_ENG_MAYBE_UNUSED auto handleEvent ( __C_ENG_TYPE ( WindowEvent ) const & ) noexcept -> Self &;
        __C_ENG_MAYBE_UNUSED auto handleEvent ( __C_ENG_TYPE ( MouseEvent ) const & ) noexcept -> Self &;
        __C_ENG_MAYBE_UNUSED auto handleEvent ( __C_ENG_TYPE ( KeyEvent ) const & ) noexcept -> Self &;
        __C_ENG_MAYBE_UNUSED auto handleEvent ( __C_ENG_TYPE ( Event ) const & ) noexcept -> Self &;

        inline auto move ( cds :: uint32 x, cds :: uint32 y ) noexcept -> Self & {
            return this->move ( { x, y } );
        }

        inline auto resize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> Self & {
            return this->resize ( { width, height } );
        }

        __C_ENG_MAYBE_UNUSED inline auto setMinimumSize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> Self & {
            return this->setMinimumSize ( { width, height } );
        }

        __C_ENG_MAYBE_UNUSED inline auto setMaximumSize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> Self & {
            return this->setMaximumSize ( { width, height } );
        }

        __C_ENG_MAYBE_UNUSED auto setTitle ( cds :: String const & ) noexcept -> Self &;

        auto grabMouseCursor () noexcept -> Self &;
        auto releaseMouseCursor () noexcept -> Self &;

        auto monitorDisconnectedEvent () noexcept -> Self &;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
        __C_ENG_NO_DISCARD auto equals ( cds :: Object const & ) const noexcept -> bool override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_WINDOW_HPP
