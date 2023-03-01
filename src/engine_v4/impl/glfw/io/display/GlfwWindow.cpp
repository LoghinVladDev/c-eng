//
// Created by loghin on 27/02/23.
//

#include "GlfwWindow.hpp"
#include "GlfwDisplay.hpp"

namespace engine::io {

    using namespace cds;

    namespace {
        auto glfwWindowCloseCallback (GLFWwindow * pHandle) noexcept -> void {
            auto * pWindow = static_cast <Window *> (glfwGetWindowUserPointer (pHandle));
            pWindow->close();
        }
    }

    GlfwWindow :: GlfwWindow (GLFWwindow * pHandle, Object const * pParent) noexcept :
            Window (pParent),
            _pHandle (pHandle) {

    }


    auto GlfwWindow :: requestCloseCancellation () noexcept -> void {
        glfwSetWindowShouldClose (this->_pHandle, GLFW_FALSE);
    }


    auto GlfwWindow :: surface () const noexcept -> Surface const * {
        return nullptr;
    }


    GlfwWindow :: ~GlfwWindow () noexcept {
        glfwDestroyWindow (this->_pHandle);
    }


    GlfwWindowManager :: GlfwWindowManager (Object const * pParent) noexcept : WindowManager (pParent) {}


    auto GlfwWindowManager :: GlfwWindowBuilder :: _build () const noexcept (false) -> Window * {

        auto const * pDisplay = dynamic_cast <GlfwDisplay const *> (this->display());
        if (this->display() != nullptr && pDisplay == nullptr) {
            __C_ENG_OBJ_LOG(Warning, "Creating Fullscreen/Borderless Window with incompatible display : "
                                     "GlfwWindow requires GlfwDisplay as base. Window will be windowed");
        }

        auto * pHandle = glfwCreateWindow (
                this->geometry().size.width,
                this->geometry().size.height,
                this->title(),
                pDisplay == nullptr ? nullptr : pDisplay->handle(),
                nullptr
        );

        if (pHandle == nullptr) {
            __C_ENG_OBJ_LOG(Error, "GlfwWindow creation failed");
            throw cds::RuntimeException ("GlfwWindow creation failed");
        }

        glfwSetWindowCloseCallback (pHandle, & glfwWindowCloseCallback);

        auto * pWindow = new GlfwWindow (pHandle, this->manager());
        glfwSetWindowUserPointer (pHandle, static_cast <void *> (pWindow));

        return pWindow;
    }


    GlfwWindowManager :: GlfwWindowBuilder :: GlfwWindowBuilder (Object const * pParent) noexcept :
            WindowBuilder (pParent) {

    }


    auto GlfwWindowManager :: _windowBuilder (Object const * pParent) const noexcept -> cds::UniquePointer <WindowBuilder> {
        return new GlfwWindowBuilder (pParent);
    }

}
