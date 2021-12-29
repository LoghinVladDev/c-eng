//
// Created by loghin on 19.12.2021.
//

#ifndef __C_ENG_WINDOW_HPP
#define __C_ENG_WINDOW_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <Core.hpp>

#include <SimpleEventQueue.hpp>


#define C_ENG_MAP_START     CLASS ( Window, PARENT ( cds :: Object ) )
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

        Const ( PRIMITIVE_TYPE ( cds :: StringLiteral ),    defaultWindowTitle, VALUE ( "VEngineTest" ) )
        Const ( ENGINE_PRIMITIVE_TYPE ( WindowFlags ),      defaultFlags,       VALUE ( WindowFlagResizable | WindowFlagGrabFocusOnOpen | WindowFlagGrabFocusOnRaise ) ) // NOLINT(clion-misra-cpp2008-4-5-2)

    private:
        Field ( TYPE ( cds :: String ),                                                     title,              DEFAULT_VALUE ( defaultWindowTitle ),                                   GET_DEFAULT,    SET_NONE )

        Field ( TYPE ( utility :: SimpleEventQueue < __C_ENG_TYPE ( WindowEvent ) * > ),    customWindowEvents, NO_INIT,                                                                GET_NONE,       SET_NONE )
        Field ( TYPE ( utility :: SimpleEventQueue < __C_ENG_TYPE ( MouseEvent ) * > ),     customMouseEvents,  NO_INIT,                                                                GET_NONE,       SET_NONE )
        Field ( TYPE ( utility :: SimpleEventQueue < __C_ENG_TYPE ( KeyEvent ) * > ),       customKeyEvents,    NO_INIT,                                                                GET_NONE,       SET_NONE )
        Field ( TYPE ( utility :: SimpleEventQueue < __C_ENG_TYPE ( Event ) * > ),          customEvents,       NO_INIT,                                                                GET_NONE,       SET_NONE )

        Field ( PRIMITIVE_TYPE ( Handle ),                                                  handle,             DEFAULT_VALUE ( nullptr ),                                              GET_DEFAULT,    SET_NONE )
        Field ( ENGINE_PRIMITIVE_TYPE ( WindowFlags ),                                      flags,              DEFAULT_VALUE ( defaultFlags ),                                         GET_DEFAULT,    SET_NONE )

        Field ( ENGINE_TYPE ( Position ),                                                   position,           DEFAULT_VALUE ( 0u, 0u ),                                               GET_DEFAULT,    SET_NONE )
        Field ( ENGINE_TYPE ( Size ),                                                       size,               DEFAULT_VALUE ( 0u, 0u ),                                               GET_DEFAULT,    SET_NONE )
        Field ( ENGINE_TYPE ( Position ),                                                   mousePosition,      DEFAULT_VALUE ( 0u, 0u ),                                               GET_DEFAULT,    SET_NONE )

        Field ( ENGINE_TYPE ( Size ),                                                       minimumSize,        DEFAULT_VALUE ( cds :: limits :: U32_MIN, cds :: limits :: U32_MIN ),   GET_DEFAULT,    SET ( setMinimumSize ) )
        Field ( ENGINE_TYPE ( Size ),                                                       maximumSize,        DEFAULT_VALUE ( cds :: limits :: U32_MAX, cds :: limits :: U32_MAX ),   GET_DEFAULT,    SET ( setMaximumSize ) )

        Field ( PRIMITIVE_TYPE ( cds :: uint32 ),                                           refreshRate,        DEFAULT_VALUE ( 60u ),                                                  GET_DEFAULT,    SET_NONE )

        Field ( ENGINE_PRIMITIVE_TYPE ( Engine * ),                                         engine,             DEFAULT_VALUE ( nullptr ),                                              GET_DEFAULT,    SET ( setEngine ) )
        Field ( ENGINE_PRIMITIVE_TYPE ( Monitor const * ),                                  monitor,            DEFAULT_VALUE ( nullptr ),                                              GET_DEFAULT,    SET_NONE )

        Field ( ENGINE_PRIMITIVE_TYPE ( WindowType ),                                       type,               DEFAULT_VALUE ( WindowTypeWindowed ),                                   GET_DEFAULT,    SET_NONE )

        friend auto __updateWindowSize ( Self *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)
        friend auto __updateCursorPos ( Self *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)

        auto applyFlagHints () const noexcept -> void;
        auto updateWindowLimits () noexcept -> void;

    public:
        auto init () noexcept (false) -> Self &;
        auto clear () noexcept -> Self &;

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
