//
// Created by Vlad on 03/07/2020.
//

#pragma once

#ifndef ENG1_ENGINE_H
#define ENG1_ENGINE_H

class GameObject;

#include "preCompiledHeaders.h"
#include "./window/Window.h"
#include "./util/dataStructures/Array.h"
#include "./util/obj/GameObject.h"
#include <random>

class Engine {
private:
    Window mainWindow {
        Size(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT),
        Point(DEFAULT_WINDOW_STARTING_POSITION_X, DEFAULT_WINDOW_STARTING_POSITION_Y),
        DEFAULT_WINDOW_TITLE
    };

    std::list<GameObject*> _allGameObjects {std::list<GameObject*>()};

    static Engine* _instance;

    Engine() noexcept;

    static void update() noexcept;
    static void render() noexcept;
    static void renderOnce() noexcept;
public:
    ~Engine() noexcept;

    [[maybe_unused]] void start(int = 0, char** = nullptr) noexcept;
    [[maybe_unused]] Window& getMainWindow() noexcept;

    [[maybe_unused]] [[nodiscard]] std::list<GameObject*>& getAllGameObjects() noexcept;
    [[maybe_unused]] void addGameObject(GameObject*) noexcept;

    [[maybe_unused]] void addKeyListener(KeyListener* listener) noexcept {
        this->mainWindow.addKeyListener(listener);
    }

    [[maybe_unused]] [[nodiscard]] static Engine* getInstance() noexcept;

    class [[maybe_unused]] EngineBuilder{
    private:
        Size mainWindowResolution { DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT };
        Point mainWindowLocation { DEFAULT_WINDOW_STARTING_POSITION_X, DEFAULT_WINDOW_STARTING_POSITION_Y };
        const char* mainWindowTitle { DEFAULT_WINDOW_TITLE };

    public:
        [[maybe_unused]] EngineBuilder& withMainWindowResolution( const Size& resolution ) noexcept {
            this->mainWindowResolution = resolution;
            return *this;
        }

        [[maybe_unused]] EngineBuilder& withMainWindowResolution( int width, int height ) noexcept {
            this->mainWindowResolution = Size(width, height);
            return *this;
        }

        [[maybe_unused]] EngineBuilder& withMainWindowLocation( const Point& location ) noexcept {
            this->mainWindowLocation = location;
            return *this;
        }

        [[maybe_unused]] EngineBuilder& withMainWindowLocation( int x, int y ) noexcept {
            this->mainWindowLocation = Point(x, y);
            return *this;
        }
        [[maybe_unused]] EngineBuilder& withMainWindowTitle ( const char* title ) noexcept {
            this->mainWindowTitle = title;
            return *this;
        }

        [[maybe_unused]] Engine* build() noexcept;
    };

};


#endif //ENG1_ENGINE_H
