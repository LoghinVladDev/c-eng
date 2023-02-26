//
// Created by loghin on 26/02/23.
//

#include "Glfw.hpp"
#include <GLFW/glfw3.h>

namespace engine {

    using namespace io;
    using namespace cds;

    Glfw :: Glfw (Object const * pParent) noexcept (false) : Object (pParent) {

        __C_ENG_OBJ_LOG(Info, "Initializing GLFW");

        if (glfwInit() == GLFW_FALSE) {
            __C_ENG_OBJ_LOG(Error, "GLFW Could not be initialized");
            throw RuntimeException ("GLFW Initialization Failure");
        }
    }


#if __C_ENG_LOGGING_ENABLED
    Glfw :: Glfw (Logger const * pLogger, Object const * pParent) noexcept (false) : Glfw (pParent) {
        this->setLogger(pLogger);
    }
#endif


    Glfw :: ~Glfw () noexcept {

        glfwTerminate();
    }

}
