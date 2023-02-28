//
// Created by loghin on 26/02/23.
//

#include "Glfw.hpp"
#include <GLFW/glfw3.h>

#include <impl/glfw/io/display/GlfwDisplay.hpp>
#include <impl/glfw/io/display/GlfwWindow.hpp>

namespace engine {

    using namespace io;
    using namespace cds;
    using namespace cds::literals;

    namespace {

        ApiInfo glfwStandardApiInfo = {
                .pApiName       = "GLFW",
                .pApiPurpose    = "Platform Independent API for creating windows, context and surfaces, reading input, handling events, etc.",
                .pVendorInfo    = "The GLFW Organization, domain - glfw.org, Licence Holder of GLFW - zlib/libpng licence",
                .provenience    = ApiProvenience::OpenSource
        };


        constexpr auto glfwCodeToString (int code) noexcept -> char const * {

            switch ( code ) {
                case GLFW_NOT_INITIALIZED:      return "GLFW_NOT_INITIALIZED";
                case GLFW_NO_CURRENT_CONTEXT:   return "GLFW_NO_CURRENT_CONTEXT";
                case GLFW_INVALID_ENUM:         return "GLFW_INVALID_ENUM";
                case GLFW_INVALID_VALUE:        return "GLFW_INVALID_VALUE";
                case GLFW_OUT_OF_MEMORY:        return "GLFW_OUT_OF_MEMORY";
                case GLFW_API_UNAVAILABLE:      return "GLFW_API_UNAVAILABLE";
                case GLFW_VERSION_UNAVAILABLE:  return "GLFW_VERSION_UNAVAILABLE";
                case GLFW_PLATFORM_ERROR:       return "GLFW_PLATFORM_ERROR";
                case GLFW_FORMAT_UNAVAILABLE:   return "GLFW_FORMAT_UNAVAILABLE";
                default:                        return "";
            }
        }

        Glfw * pGlfwInstance = nullptr;

        auto glfwErrorCallback (int code, char const * pDescription) noexcept -> void {

            if (pGlfwInstance == nullptr) {
                return;
            }

            __C_ENG_LOG(
                    pGlfwInstance->logger(), Error,
                    "Glfw Error : "_s + glfwCodeToString(code) + " -> " + pDescription
            );
        }

        auto glfwDisplayChangeDetectedCallback (
                GLFWmonitor   * pDisplayHandle,
                cds::sint32     event
        ) noexcept -> void {

            if (pGlfwInstance == nullptr) {
                return;
            }

            auto * pDisplayManager = dynamic_cast <GlfwDisplayManager *> (pGlfwInstance->displayManager());
            if (pDisplayManager == nullptr) {
                return;
            }

            if (event == GLFW_CONNECTED) {
                pDisplayManager->addDisplay (pDisplayHandle);
            } else if (event == GLFW_DISCONNECTED) {
                pDisplayManager->removeDisplay (pDisplayHandle);
            }
        }
    }


    Glfw :: Glfw (Object const * pParent) noexcept (false) : Object (pParent) {
        this->initLib ();
    }


#if __C_ENG_LOGGING_ENABLED
    Glfw :: Glfw (Logger const * pLogger, Object const * pParent) noexcept (false) : Object (pLogger, pParent) {
        this->initLib ();
    }
#endif


    auto Glfw :: initLib () noexcept (false) -> void {

        __C_ENG_OBJ_LOG(Info, "Initializing GLFW");

        if (glfwInit() == GLFW_FALSE) {

            __C_ENG_OBJ_LOG(Error, "GLFW Could not be initialized");

            char const * pDescription;
            int code = glfwGetError (& pDescription);

            throw RuntimeException ("GLFW Initialization Failure : "_s + glfwCodeToString(code) + " -> " + pDescription);
        }

        pGlfwInstance = this;
        glfwSetErrorCallback (& glfwErrorCallback);
        glfwSetMonitorCallback (& glfwDisplayChangeDetectedCallback);

        sint32 vRuntimeMajor;
        sint32 vRuntimeMinor;
        sint32 vRuntimePatch;
        glfwGetVersion (& vRuntimeMajor, & vRuntimeMinor, & vRuntimePatch);

        this->_apiInfo = {
                .pApiName       = glfwStandardApiInfo.pApiName,
                .pApiPurpose    = glfwStandardApiInfo.pApiPurpose,
                .pVendorInfo    = glfwStandardApiInfo.pVendorInfo,
                .provenience    = glfwStandardApiInfo.provenience,
                .version        = {
                        .variant    = 0U,
                        .major      = static_cast <uint32> (vRuntimeMajor),
                        .minor      = static_cast <uint32> (vRuntimeMinor),
                        .patch      = static_cast <uint32> (vRuntimePatch)
                }
        };

        this->_pDisplayManager  = new GlfwDisplayManager (this);
        this->_pWindowManager   = new GlfwWindowManager (this);
    }


    Glfw :: ~Glfw () noexcept {

        __C_ENG_OBJ_LOG(Info, "Shutting down GLFW");
        glfwTerminate();
    }


    auto Glfw :: apiInfo () const noexcept -> ApiInfo const & {
        return this->_apiInfo;
    }


    auto Glfw :: displayManager () noexcept -> DisplayManager * {
        return this->_pDisplayManager;
    }


    auto Glfw :: displayManager () const noexcept -> DisplayManager const * {
        return this->_pDisplayManager;
    }


    auto Glfw :: windowManager () noexcept -> WindowManager * {
        return this->_pWindowManager;
    }


    auto Glfw :: windowManager () const noexcept -> WindowManager const * {
        return this->_pWindowManager;
    }


    auto Glfw :: pollEvents () noexcept -> void {
        glfwPollEvents();
    }

}
