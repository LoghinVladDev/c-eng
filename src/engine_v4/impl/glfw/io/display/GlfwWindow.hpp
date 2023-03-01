//
// Created by loghin on 27/02/23.
//

#ifndef __C_ENG_GLFWWINDOW_HPP__
#define __C_ENG_GLFWWINDOW_HPP__

#include <base/io/display/Window.hpp>
#include <GLFW/glfw3.h>


namespace engine::io {

    class GlfwWindow : public Window {
    private:
        friend class GlfwWindowManager;

        GLFWwindow * _pHandle {nullptr};

        explicit GlfwWindow (GLFWwindow * pWindow, Object const * pParent = nullptr) noexcept;

        auto requestCloseCancellation () noexcept -> void override;

    public:
        ~GlfwWindow () noexcept override;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "GlfwWindow";
        }

        __CDS_NoDiscard auto surface () const noexcept -> Surface const * override;
    };


    class GlfwWindowManager : public WindowManager {
    protected:
        class GlfwWindowBuilder : public WindowBuilder {
        protected:
            __CDS_NoDiscard auto _build () const noexcept (false) -> Window * override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
                return "GlfwWindowBuilder";
            }

            explicit GlfwWindowBuilder (Object const * pParent) noexcept;
            ~GlfwWindowBuilder () noexcept override = default;
        };

        auto _windowBuilder (Object const * pParent) const noexcept -> cds::UniquePointer <WindowBuilder> override;

    public:
        explicit GlfwWindowManager (Object const * pParent = nullptr) noexcept;
        ~GlfwWindowManager () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "GlfwWindowManager";
        }
    };

}


#endif //__C_ENG_GLFWWINDOW_HPP__
