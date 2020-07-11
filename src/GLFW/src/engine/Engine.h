//
// Created by Vlad on 03/07/2020.
//

#pragma once

#ifndef ENG1_ENGINE_H
#define ENG1_ENGINE_H

class GameObject;

//#include "preCompiledHeaders.h"
//#include "./window/Window.h"
//#include "./util/dataStructures/Array.h"
//#include "./util/obj/GameObject.h"
//#include "util/obj/standardObj/Camera.h"
//#include <random>

#include <enginePreproc.h>
#include <obj/window/Window.h>
#include <obj/util/struct/inputAxisFunc.h>

class Camera;
class Window;
namespace engine {

    class Engine {
    private:
        Window *mainWindow {nullptr} ;

//        std::list<GameObject *> _allGameObjects{std::list<GameObject *>()};
//
//        Camera *_activeCamera;

        static Engine *_instance;

        Engine() noexcept;

        struct INPUT_AXIS* _ptrToInputAxisStr {nullptr} ;

//        void _sortObjectsByDrawPriority() noexcept;

        void update() noexcept;
        void render() noexcept;

//        static void renderOnce() noexcept;

    public:
        ~Engine() noexcept;

        [[maybe_unused]] void start(int = 0, char ** = nullptr) noexcept;

        [[maybe_unused]] Window *getMainWindow() noexcept {
            return this->mainWindow;
        }

//        [[maybe_unused]] [[nodiscard]] std::list<GameObject *> &getAllGameObjects() noexcept;

//        [[maybe_unused]] void addGameObject(GameObject *) noexcept;

//        [[maybe_unused]] void setActiveCamera(Camera *camera) noexcept {
//            if (this->_activeCamera != nullptr)
//                this->_allGameObjects.push_back((GameObject *) camera);

//            this->_activeCamera = camera;
//            this->_allGameObjects.remove((GameObject *) camera);
//        }
        [[maybe_unused]] [[nodiscard]] struct INPUT_AXIS* getInputAxisStructure() noexcept {
            return this->_ptrToInputAxisStr;
        }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
        [[maybe_unused]] void addKeyListener(KeyListener *listener, Window* window = nullptr) noexcept {
            if(window == nullptr)
                this->mainWindow->addKeyListener(listener);
            else {
                //TODO : add listener for certain window
                this->mainWindow->addKeyListener(listener);
            }
        }

        [[maybe_unused]] void addMouseListener(MouseListener *listener, Window* window = nullptr) noexcept {
            if(window == nullptr)
                this->mainWindow->addMouseListener(listener);
            else {
                //TODO : add listener for certain window
                this->mainWindow->addMouseListener(listener);
            }
        }
#pragma clang diagnostic pop

//        [[maybe_unused]] void addMouseListener(MouseListener *listener) noexcept {
//            this->mainWindow.addMouseListener(listener);
//        }

        [[maybe_unused]] [[nodiscard]] static Engine *getInstance() noexcept;

        class [[maybe_unused]] EngineBuilder {
        private:
            Size mainWindowResolution{DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
            Point mainWindowLocation{DEFAULT_WINDOW_STARTING_POSITION_X, DEFAULT_WINDOW_STARTING_POSITION_Y};
            const char *mainWindowTitle{DEFAULT_WINDOW_TITLE};

        public:
            [[maybe_unused]] EngineBuilder &withMainWindowResolution(const Size &resolution) noexcept {
                this->mainWindowResolution = resolution;
                return *this;
            }

            [[maybe_unused]] EngineBuilder &withMainWindowResolution(int width, int height) noexcept {
                this->mainWindowResolution = Size(width, height);
                return *this;
            }

            [[maybe_unused]] EngineBuilder &withMainWindowLocation(const Point &location) noexcept {
                this->mainWindowLocation = location;
                return *this;
            }

            [[maybe_unused]] EngineBuilder &withMainWindowLocation(int x, int y) noexcept {
                this->mainWindowLocation = Point(x, y);
                return *this;
            }

            [[maybe_unused]] EngineBuilder &withMainWindowTitle(const char *title) noexcept {
                this->mainWindowTitle = title;
                return *this;
            }

            [[maybe_unused]] Engine *build() noexcept;
        };

    };

}


#endif //ENG1_ENGINE_H
