//
// Created by loghin on 25/02/23.
//

#ifndef __C_ENG_SURFACE_HPP__
#define __C_ENG_SURFACE_HPP__

#include <base/core/Object.hpp>

namespace engine::io {

    class Surface : public Object {
    public:

        explicit Surface (Object const * pParent = nullptr) noexcept;
        ~Surface () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "Surface";
        }
    };

}


#endif //__C_ENG_SURFACE_HPP__
