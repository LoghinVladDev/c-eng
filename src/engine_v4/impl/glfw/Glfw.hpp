//
// Created by loghin on 26/02/23.
//

#ifndef __C_ENG_GLFW_HPP__
#define __C_ENG_GLFW_HPP__

#include <CDS/memory/UniquePointer>

#include <base/core/Object.hpp>
#include <base/core/ApiImplementation.hpp>
#include <base/io/display/Display.hpp>
#include <base/io/display/Window.hpp>


namespace engine {

    class Glfw : public Object, public ApiImplementation {
    private:
        cds::UniquePointer <io::DisplayManager> _pDisplayManager;
        cds::UniquePointer <io::WindowManager>  _pWindowManager;
        ApiInfo                                 _apiInfo {};

        auto initLib () noexcept(false) -> void;

    public:
        explicit Glfw (Object const * pParent = nullptr) noexcept (false);

#if __C_ENG_LOGGING_ENABLED
        explicit Glfw (io::Logger const * pLogger, Object const * pParent = nullptr) noexcept (false);
#endif

        ~Glfw () noexcept override;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "Glfw";
        }

        __CDS_NoDiscard auto apiInfo () const noexcept -> ApiInfo const & override;

        __CDS_NoDiscard auto displayManager () noexcept -> io::DisplayManager *;
        __CDS_NoDiscard auto displayManager () const noexcept -> io::DisplayManager const *;
        __CDS_NoDiscard auto windowManager () noexcept -> io::WindowManager *;
        __CDS_NoDiscard auto windowManager () const noexcept -> io::WindowManager const *;

        auto pollEvents () noexcept -> void;
    };

}


#endif //__C_ENG_GLFW_HPP__
