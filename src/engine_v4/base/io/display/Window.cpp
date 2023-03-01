//
// Created by loghin on 24/02/23.
//

#include "Window.hpp"

#include <base/io/event/window/WindowCloseEvent.hpp>

namespace engine::io {

    using namespace cds;


    Window :: Window (Object const * pParent) noexcept : Object (pParent) {}


    Window :: ~Window () noexcept {

        if (this->_pManager != nullptr) {
            this->_pManager->removeWindow (this);
        }
    }


    auto Window :: close () noexcept -> void {

        WindowCloseEvent event (this);
        this->closeEvent (& event);

        if (event.isCloseCancelled()) {
            this->requestCloseCancellation();
        } else {
            if ( this->_pManager != nullptr ) {
                this->_pManager->removeWindow( this );
            }
        }
    }


    WindowManager :: WindowBuilder :: WindowBuilder (Object const * pParent) noexcept : Object (pParent) {}


    auto WindowManager ::WindowBuilder :: build () const noexcept (false) -> Window * {
        auto * pWindow = this->_build();
        this->_pManager->addWindow (pWindow);
        return pWindow;
    }


    WindowManager :: WindowManager (Object const * pParent) noexcept : Object (pParent) {}


    WindowManager :: ~WindowManager () noexcept = default;


    auto WindowManager :: addWindow (Window * pWindow) noexcept -> void {
        this->_windows.emplaceBack (pWindow);
        pWindow->_pManager = this;
    }


    auto WindowManager :: windowBuilder () noexcept -> UniquePointer <WindowBuilder> {
        auto pBuilder = this->_windowBuilder (this);
        pBuilder->_pManager = this;
        return pBuilder;
    }


    auto WindowManager :: removeWindow (Window * pWindow) noexcept -> void {

        for (auto iterator = this->_windows.begin(); iterator != this->_windows.end(); ++ iterator) {
            if (iterator->get() == pWindow) {
                iterator->release();
                this->_windows.remove (iterator);
                break;
            }
        }

        if (this->_windows.empty()) {
            this->_onAllClosedCallback();
        }
    }


    auto WindowManager :: setOnAllWindowsClosedCallback (cds::Function <void(void)> callback) noexcept -> void {
        this->_onAllClosedCallback = std::move (callback);
    }


    auto Window :: closeEvent (WindowCloseEvent * pEvent) noexcept -> void {

    }

}
