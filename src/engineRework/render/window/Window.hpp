//
// Created by loghin on 19.12.2021.
//

#ifndef C_ENG_WINDOW_HPP
#define C_ENG_WINDOW_HPP

#include <Preprocess.hpp>
#include <CDS/Object>

#include <Core.hpp>

namespace engine {

    class C_ENG_CLASS ( Engine );
    class C_ENG_CLASS ( Monitor );

    class C_ENG_CLASS ( Window ) : public cds :: Object {
    public:
        using WindowHandle = GLFWwindow *;

        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: StringLiteral, defaultWindowTitle, "VEngineTest" ); // NOLINT(clion-misra-cpp2008-8-0-1)

    private:
        cds :: String _title { defaultWindowTitle };

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, x, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, y, 0u )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, width, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, height, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, refreshRate, 60u )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, mouseX, 0u )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( cds :: uint32, mouseY, 0u )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Engine ) *, engine, nullptr )
        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( C_ENG_TYPE ( Monitor ) const *, monitor, nullptr )

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( WindowType, type, WindowType :: WindowTypeWindowed );

        friend auto __updateWindowSize ( C_ENG_TYPE ( Window ) *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)
        friend auto __updateCursorPos ( C_ENG_TYPE ( Window ) *, cds :: uint32, cds :: uint32 ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( WindowHandle, handle, nullptr )

    public:
        auto init () noexcept (false) -> C_ENG_TYPE ( Window ) &;
        auto clear () noexcept -> C_ENG_TYPE ( Window ) &;

        auto setEngine ( C_ENG_TYPE ( Engine ) * ) noexcept -> C_ENG_TYPE ( Window ) &;

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

        inline auto move ( cds :: uint32 x, cds :: uint32 y ) noexcept -> C_ENG_TYPE ( Window ) & {
            return this->move ( { x, y } );
        }

        inline auto resize ( cds :: uint32 width, cds :: uint32 height ) noexcept -> C_ENG_TYPE ( Window ) & {
            return this->resize ( { width, height } );
        }

        C_ENG_MAYBE_UNUSED auto setTitle ( cds :: String const & ) noexcept -> C_ENG_TYPE ( Window ) &;

        auto grabMouseCursor () noexcept -> C_ENG_TYPE ( Window ) &;
        auto releaseMouseCursor () noexcept -> C_ENG_TYPE ( Window ) &;

        auto monitorDisconnectedEvent () noexcept -> C_ENG_TYPE ( Window ) &;
    };

}

#endif //C_ENG_WINDOW_HPP
