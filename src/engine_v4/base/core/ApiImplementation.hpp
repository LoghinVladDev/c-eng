//
// Created by loghin on 26/02/23.
//

#ifndef __C_ENG_APIIMPLEMENTATION_HPP__
#define __C_ENG_APIIMPLEMENTATION_HPP__

#include <CDS/Object>
#include <base/core/Core.hpp>

namespace engine {

    class ApiImplementation {
    public:
        __CDS_NoDiscard virtual auto apiInfo () const noexcept -> ApiInfo const & = 0;
    };

}


#endif //__C_ENG_APIIMPLEMENTATION_HPP__
