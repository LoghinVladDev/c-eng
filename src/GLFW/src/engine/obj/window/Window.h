//
// Created by vladl on 09/07/2020.
//

#ifndef ENG1_WINDOW_H
#define ENG1_WINDOW_H

#include <enginePreprocessHeaders.h>
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

namespace Engine {

    class [[maybe_unused]] WindowCreateNullException : public std::exception{
        public:
        [[nodiscard]] const char * what() const noexcept override {
            return "Window creation failure";
        }
    };

    class [[maybe_unused]] Window {
    private:
        constexpr static float MIN_OPENGL_VERSION = _GL_MIN_VER;
        constexpr static float MAX_OPENGL_VERSION = _GL_MAX_VER;

        Point _position     { DEFAULT_WINDOW_STARTING_POSITION_X, DEFAULT_WINDOW_STARTING_POSITION_Y };
        Size _size          { DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT } ;

        const char* _title  { DEFAULT_WINDOW_TITLE};

        GLFWwindow* _window;

        static std::map <GLFWwindow*, Window*> GLFWWindowToWindowMap;

//        int _displayMode    { DEFAULT_DISPLAY_MODE_FLAGS};

//        static bool _mouseMoving;

        void init(int, char**) noexcept;

        std::list <KeyListener*> keyListeners { std::list<KeyListener*>() } ;

        static void defaultHandlerKeyCallback(GLFWwindow*, int, int, int, int) noexcept;

        void (*_keyHandlerCallback) (GLFWwindow*, int, int, int, int) = defaultHandlerKeyCallback;

//        static std::list<KeyListener*> keyListeners;
//        static std::list<MouseListener*> mouseListeners;

//        static void defaultDisplayFunction()            noexcept;
//        static void defaultReshapeFunction(int, int)    noexcept;
//        static void defaultRedrawFunction()             noexcept;
//
//        static void defaultKeyboardHandlerFunction(uint8, [[maybe_unused]] int, int)    noexcept;
//        static void defaultSpecialKeyHandlerFunction(int, int, int)                     noexcept;
//
//        static void defaultKeyUpHandlerFunction(uint8, int, int)                        noexcept;
//        static void defaultSpecUpHandlerFunction(int, int, int)                         noexcept;
//
//        static void defaultMouseHandlerFunction(int, int, int, int)                     noexcept;
//        static void defaultMouseMoveFunction(int, int)                                  noexcept;

//        void (*_displayFunction) () = defaultDisplayFunction;
//        void (*_reshapeFunction) (int, int) = defaultReshapeFunction;
//        void (*_redrawFunction)  () = defaultRedrawFunction;
//
//        void (*_keyHandlerFunction)         (uint8, int, int)   = defaultKeyboardHandlerFunction;
//        void (*_specialKeyHandlerFunction)  (int, int, int)     = defaultSpecialKeyHandlerFunction;
//        void (*_keyUpHandlerFunction)       (uint8, int, int)   = defaultKeyUpHandlerFunction;
//        void (*_specKeyUpHandlerFunction)   (int, int, int)     = defaultSpecUpHandlerFunction;
//
//        void (*_mouseButtonFunction)        (int, int, int, int)= defaultMouseHandlerFunction;
//        void (*_mouseMoveFunction)          (int, int)          = defaultMouseMoveFunction;

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
        ) noexcept (false) :
                _position(x, y),
                _size(width, height),
                _title(title) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MIN_OPENGL_VERSION);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAX_OPENGL_VERSION);

            this->_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

            if(this->_window == nullptr)
                throw WindowCreateNullException();

            Window::GLFWWindowToWindowMap.insert(std::pair<GLFWwindow*, Window*> ( this->_window, this ) );
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
        ) noexcept (false) :
                _position(location),
                _size(resolution),
                _title(title) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MIN_OPENGL_VERSION);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAX_OPENGL_VERSION);

            this->_window = glfwCreateWindow(resolution.getWidth(), resolution.getHeight(), title, nullptr, nullptr);

            if(this->_window == nullptr)
                throw WindowCreateNullException();

            Window::GLFWWindowToWindowMap.insert(std::pair<GLFWwindow*, Window*> ( this->_window, this ) );
        }

        [[maybe_unused]] ~Window() {
            glfwDestroyWindow( this->_window );
        }
//        [[maybe_unused]] bool isMouseMoving() {
//            bool cpy = this->_mouseMoving;
//            this->_mouseMoving = false;
//            return cpy;
//        }

        [[maybe_unused]] static Window* getWindowByGLFWWindow(GLFWwindow* window) noexcept {
            return Window::GLFWWindowToWindowMap[window];
        }

        [[maybe_unused]] bool willClose() noexcept {
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

        [[maybe_unused]] void addKeyListener(KeyListener* listener) noexcept {
            Window::keyListeners.push_back(listener);
        }
//
//        [[maybe_unused]] void addMouseListener(MouseListener* listener) noexcept {
//            listener->setParent(this);
//            Window::mouseListeners.push_back(listener);
//        }

//        [[maybe_unused]] static std::list <KeyListener*> & getActiveKeyListeners () noexcept;

//        [[maybe_unused]] static void disableKeyRepeats() noexcept;
//        [[maybe_unused]] static void enableKeyRepeats()  noexcept;

        [[maybe_unused]] void run(int = 1, char** = nullptr) noexcept;
    };

}


#endif //ENG1_WINDOW_H
