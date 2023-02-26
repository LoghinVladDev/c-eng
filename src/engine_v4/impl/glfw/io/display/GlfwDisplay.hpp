//
// Created by loghin on 26/02/23.
//

#ifndef __C_ENG_GLFWDISPLAY_HPP__
#define __C_ENG_GLFWDISPLAY_HPP__

#include <base/io/display/Display.hpp>

namespace engine::io {

    class GlfwDisplay : public Display {
    public:

        explicit GlfwDisplay (Object const * pParent = nullptr) noexcept;
        ~GlfwDisplay () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "GlfwDisplay";
        }
    };


    class GlfwDisplayManager : public DisplayManager {
    public:

        explicit GlfwDisplayManager (Object const * pParent = nullptr) noexcept;
        ~GlfwDisplayManager () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "GlfwDisplayManager";
        }
    };

}

#endif //__C_ENG_GLFWDISPLAY_HPP__
