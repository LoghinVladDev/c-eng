//
// Created by Vlad on 03/07/2020.
//

#ifndef ENG1_ENGINE_H
#define ENG1_ENGINE_H

#include "./window/Window.h"

class Engine {
private:
    Window mainWindow;

    Engine() noexcept;

public:

    ~Engine() noexcept;

    [[maybe_unused]] void start(int = 0, char** = nullptr) noexcept;
    [[maybe_unused]] inline Window& getMainWindow() { return this->mainWindow; }

    [[maybe_unused]] inline void addKeyListener(KeyListener* listener) { this->mainWindow.addKeyListener(listener); }

    class [[maybe_unused]] EngineBuilder{
    private:
        Size mainWindowResolution { DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT };
        Point mainWindowLocation { DEFAULT_WINDOW_STARTING_POSITION_X, DEFAULT_WINDOW_STARTING_POSITION_Y };
        const char* mainWindowTitle { DEFAULT_WINDOW_TITLE };

    public:
        [[maybe_unused]] inline EngineBuilder& withMainWindowResolution( Size resolution ) noexcept {
            this->mainWindowResolution = resolution;
            return *this;
        }

        [[maybe_unused]] inline EngineBuilder& withMainWindowResolution( int width, int height ) noexcept {
            this->mainWindowResolution = Size(width, height);
            return *this;
        }

        [[maybe_unused]] inline EngineBuilder& withMainWindowLocation( Point location ) noexcept {
            this->mainWindowLocation = location;
            return *this;
        }

        [[maybe_unused]] inline EngineBuilder& withMainWindowLocation( int x, int y ) noexcept {
            this->mainWindowLocation = Point(x, y);
            return *this;
        }

        [[maybe_unused]] inline EngineBuilder& withMainWindowTitle ( const char* title ) noexcept {
            this->mainWindowTitle = title;
            return *this;
        }

        [[maybe_unused]] inline Engine build() noexcept {
            Engine result;

            result.mainWindow = Window();
            result.mainWindow.setSize(this->mainWindowResolution);
            result.mainWindow.setPosition(this->mainWindowLocation);
            result.mainWindow.setTitle(this->mainWindowTitle);

            return result;
        }
    };

};


#endif //ENG1_ENGINE_H
