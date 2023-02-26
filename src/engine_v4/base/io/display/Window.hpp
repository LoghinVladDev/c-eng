/*
 * Created by loghin on 24/02/23.
 */

#ifndef __C_ENG_WINDOW_HPP__
#define __C_ENG_WINDOW_HPP__

#include <base/core/Object.hpp>

#include "Display.hpp"
#include "Surface.hpp"

namespace engine::io {

    class Window : public Object {
    public:

        explicit Window (Object const * pParent = nullptr) noexcept;
        ~Window () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "Window";
        }

        virtual auto surface () noexcept -> Surface * = 0;
    };

}


#endif /* __C_ENG_WINDOW_HPP__ */
