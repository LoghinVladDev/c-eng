//
// Created by vladl on 09/07/2020.
//

#ifndef ENG1_WINDOW_H
#define ENG1_WINDOW_H

#include <enginePreproc.h>
#include <iterator>

#ifndef DEFAULT_WINDOW_WIDTH
#define DEFAULT_WINDOW_WIDTH 1366
#endif
#ifndef DEFAULT_WINDOW_HEIGHT
#define DEFAULT_WINDOW_HEIGHT 768
#endif

#ifndef DEFAULT_WINDOW_TITLE
#define DEFAULT_WINDOW_TITLE "engineTest"
#endif

#ifndef DEFAULT_WINDOW_STARTING_POSITION_X
#define DEFAULT_WINDOW_STARTING_POSITION_X 100
#endif

#ifndef DEFAULT_WINDOW_STARTING_POSITION_Y
#define DEFAULT_WINDOW_STARTING_POSITION_Y 100
#endif

namespace engine {

    class [[maybe_unused]] WindowCreateNullException : public std::exception{
        public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Window creation failure";
        }
    };

    class [[maybe_unused]] Window {
    private:
        friend class Engine;

        constexpr static float MIN_OPENGL_VERSION = _GL_MIN_VER;
        constexpr static float MAX_OPENGL_VERSION = _GL_MAX_VER;

        constexpr static uint8 CURSOR_MOUSE_SHOWN           = 0x01;
        constexpr static uint8 CURSOR_MOUSE_HIDDEN          = 0x02;
        constexpr static uint8 CURSOR_MOUSE_DISABLED        = 0x04;
        constexpr static uint8 CURSOR_RAW_INPUT             = 0x08;

        Point _position     { DEFAULT_WINDOW_STARTING_POSITION_X, DEFAULT_WINDOW_STARTING_POSITION_Y };
        Size _size          { DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT } ;

        int _viewportWidth   { 0 };
        int _viewportHeight  { 0 };

        const char* _title  { DEFAULT_WINDOW_TITLE };

        GLFWwindow* _window {nullptr} ;

        static std::map <GLFWwindow*, Window*> GLFWWindowToWindowMap;

//        int _displayMode    { DEFAULT_DISPLAY_MODE_FLAGS};

//        static bool _mouseMoving;

        void init(int, char**) noexcept;
        void _setCallbacks() noexcept;
        void _setMouseOptions() noexcept;

        std::list <KeyListener*> keyListeners { std::list<KeyListener*>() } ;
        std::list <MouseListener*> mouseListeners { std::list<MouseListener*>() };

        static void defaultResizeWindowCallback(GLFWwindow*, int, int) noexcept;

        static void defaultMouseMoveHandlerCallback(GLFWwindow*, double, double) noexcept;
        static void defaultMouseClickedHandlerCallback(GLFWwindow*, int, int, int) noexcept;
        static void defaultMouseScrollHandlerCallback(GLFWwindow*, double, double) noexcept;
        static void defaultHandlerKeyCallback(GLFWwindow*, int, int, int, int) noexcept;

        void (*_mouseMoveCallback)  (GLFWwindow*, double, double)     = defaultMouseMoveHandlerCallback;
        void (*_mouseClickCallback) (GLFWwindow*, int, int, int)      = defaultMouseClickedHandlerCallback;
        void (*_mouseScrollCallback)(GLFWwindow*, double, double)     = defaultMouseScrollHandlerCallback;
        void (*_keyHandlerCallback) (GLFWwindow*, int, int, int, int) = defaultHandlerKeyCallback;

        void (*_resizeWindowCallback) (GLFWwindow*, int, int) = defaultResizeWindowCallback;

        uint8 _mouseModifiers = CURSOR_MOUSE_SHOWN;
    public:

        /**
         * Creates window object and OpenGL window
         *
         * @remark Implement Fullscreen/Windowed. 4'th param for windowed (which monitor)
         *
         * @remark 5'th param of glfwCreateWindow is sharing resources with other GL windows. Research
         *
         * @param width of the window
         * @param height of the window
         * @param x position of the window, useless right now
         * @param y position of the window, useless right now
         * @param title of the window
         */
        [[maybe_unused]] explicit Window(
                int width           = DEFAULT_WINDOW_WIDTH,
                int height          = DEFAULT_WINDOW_HEIGHT,
                int x               = DEFAULT_WINDOW_STARTING_POSITION_X,
                int y               = DEFAULT_WINDOW_STARTING_POSITION_Y,
                const char* title   = DEFAULT_WINDOW_TITLE
        ) noexcept :
                _position(x, y),
                _size(width, height),
                _title(title) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MIN_OPENGL_VERSION);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAX_OPENGL_VERSION);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        /**
         * Creates window object and OpenGL window
         *
         * @remark Implement Fullscreen/Windowed. 4'th param for windowed (which monitor)
         *
         * @remark 5'th param of glfwCreateWindow is sharing resources with other GL windows. Research
         *
         * @param resolution of the window
         * @param location of the window, unimplemented
         * @param title of the window
         */
        [[maybe_unused]] explicit Window(
                const Size& resolution,
                const Point& location,
                const char* title= DEFAULT_WINDOW_TITLE
        ) noexcept :
                _position(location),
                _size(resolution),
                _title(title) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MIN_OPENGL_VERSION);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAX_OPENGL_VERSION);
        }

        [[maybe_unused]] ~Window() {
            glfwDestroyWindow( this->_window );

            for( KeyListener* listener : this->keyListeners ){
                delete listener;
            }
        }
//        [[maybe_unused]] bool isMouseMoving() {
//            bool cpy = this->_mouseMoving;
//            this->_mouseMoving = false;
//            return cpy;
//        }

        [[maybe_unused]] void disableMouseCursor() noexcept {
            if(this->_window != nullptr)
                glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            this->_mouseModifiers = CURSOR_MOUSE_DISABLED;
        }

        [[maybe_unused]] void hideMouseCursor() noexcept {
            if(this->_window != nullptr)
                glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            this->_mouseModifiers = CURSOR_MOUSE_HIDDEN;
        }

        [[maybe_unused]] void enableMouseCursor() noexcept {
            if(this->_window != nullptr)
                glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            this->_mouseModifiers = CURSOR_MOUSE_SHOWN;
        }

        [[maybe_unused]] void enableRawMouseInput() noexcept {
            if(this->_window != nullptr)
                if(glfwRawMouseMotionSupported())
                    glfwSetInputMode(this->_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
            this->_mouseModifiers |= CURSOR_RAW_INPUT;
        }

        [[maybe_unused]] void disableRawMouseInput() noexcept {
            if(this->_window != nullptr)
                if(glfwRawMouseMotionSupported())
                    glfwSetInputMode(this->_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
            if(this->_mouseModifiers & CURSOR_RAW_INPUT)
                this->_mouseModifiers ^= CURSOR_RAW_INPUT;
        }

        [[maybe_unused]] [[nodiscard]] static Window* getWindowByGLFWWindow(GLFWwindow* window) noexcept {
            return Window::GLFWWindowToWindowMap[window];
        }

        [[maybe_unused]] [[nodiscard]] bool willClose() noexcept {
            return glfwWindowShouldClose(this->_window);
        }

        [[maybe_unused]] void grabFocus() {
            glfwMakeContextCurrent(this->_window);
        }

        [[maybe_unused]] void setSize        (const Size& size)  noexcept {
            this->_size = size;
        }

        [[maybe_unused]] void setSize        (int width, int height)     noexcept{
            this->_size.setWidth(width);
            this->_size.setHeight(height);
        }

        [[maybe_unused]] void setPosition    (const Point& point) noexcept {
            this->_position = point;
        }

        [[maybe_unused]] void setPosition    (int x, int y)     noexcept {
            this->_position.setX(x);
            this->_position.setY(y);
        }

        [[maybe_unused]] void setTitle       (const char* title)  noexcept {
            this->_title = title;
        }

        [[maybe_unused]] void close() noexcept;

//        [[maybe_unused]] void setDisplayMode (int)          noexcept;

//        [[maybe_unused]] void setDisplayFunctionCallback     ( void (*) ()                = defaultDisplayFunction )              noexcept;
//        [[maybe_unused]] void setReshapeFunctionCallback     ( void (*) (int, int)        = defaultReshapeFunction )              noexcept;
//        [[maybe_unused]] void setRedrawFunctionCallback      ( void (*) ()                = defaultRedrawFunction  )              noexcept;
//
//        [[maybe_unused]] void setKeyHandlerCallback          ( void (*) (uint8, int, int) = defaultKeyboardHandlerFunction )      noexcept;
//        [[maybe_unused]] void setSpecialKeyHandlerCallback   ( void (*) (int, int, int)   = defaultSpecialKeyHandlerFunction )    noexcept;
//
//        [[maybe_unused]] void setKeyUpHandlerCallback        ( void (*) (uint8, int, int) = defaultKeyUpHandlerFunction )         noexcept;
//        [[maybe_unused]] void setSpecKeyUpHandlerCallback    ( void (*) (int, int, int)   = defaultSpecUpHandlerFunction )        noexcept;
//
//        [[maybe_unused]] void setMouseButtonCallback         ( void (*) (int,int,int,int) = defaultMouseHandlerFunction )         noexcept;
//        [[maybe_unused]] void setMouseMoveCallback           ( void (*) (int, int)        = defaultMouseMoveFunction )            noexcept;

        [[maybe_unused]] void setMouseMoveHandlerCallback ( void (* callback) (GLFWwindow*, double, double) = defaultMouseMoveHandlerCallback ) noexcept {
            this->_mouseMoveCallback = callback;
        }

        [[maybe_unused]] void setMouseClickHandlerCallback ( void (* callback) (GLFWwindow*, int, int, int) = defaultMouseClickedHandlerCallback ) noexcept {
            this->_mouseClickCallback = callback;
        }

        [[maybe_unused]] void setMouseScrollHandlerCallback ( void (* callback) (GLFWwindow*, double, double) = defaultMouseScrollHandlerCallback ) noexcept {
            this->_mouseScrollCallback = callback;
        }

        [[maybe_unused]] void setKeyHandlerCallback (void (* callback ) (GLFWwindow*, int, int, int, int) = defaultHandlerKeyCallback ) noexcept {
            this->_keyHandlerCallback = callback;
        }

        [[maybe_unused]] [[nodiscard]] Size&         getSize()        noexcept {
            return this->_size;
        }

        [[maybe_unused]] [[nodiscard]] Point&        getPosition()    noexcept {
            return this->_position;
        }

        [[maybe_unused]] [[nodiscard]] const char*   getTitle() const noexcept {
            return this->_title;
        }

        [[maybe_unused]] [[nodiscard]] GLFWwindow*   getGLFWWindow() const noexcept {
            return this->_window;
        }

    private:
        [[maybe_unused]] [[nodiscard]] int&          getViewportWidth() noexcept {
            return this->_viewportWidth;
        }

        [[maybe_unused]] [[nodiscard]] int&          getViewportHeight() noexcept {
            return this->_viewportHeight;
        }
    public:

        [[maybe_unused]] void addKeyListener(KeyListener* listener) noexcept {
            this->keyListeners.push_back(listener);
        }

        [[maybe_unused]] void addMouseListener(MouseListener* listener) noexcept {
            this->mouseListeners.push_back(listener);
        }
//
//        [[maybe_unused]] void addMouseListener(MouseListener* listener) noexcept {
//            listener->setParent(this);
//            Window::mouseListeners.push_back(listener);
//        }

//        [[maybe_unused]] static std::list <KeyListener*> & getActiveKeyListeners () noexcept;

//        [[maybe_unused]] static void disableKeyRepeats() noexcept;
//        [[maybe_unused]] static void enableKeyRepeats()  noexcept;

        [[maybe_unused]] void run(int = 1, char** = nullptr) noexcept (false);

//        virtual void update() noexcept ;
//        virtual void render() noexcept ;
    };

}


#endif //ENG1_WINDOW_H
