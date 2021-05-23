//
// Created by loghin on 23.05.2021.
//

#ifndef C_ENG_VRENDEROBJECT_HPP
#define C_ENG_VRENDEROBJECT_HPP

#include <VObject.hpp>
#include <vulkanExplicitTypes.h>

namespace engine {

    class VRenderObject : public VObject {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables

        //// public functions

        [[nodiscard]] auto toString () const noexcept -> String override;

        virtual auto clear () noexcept -> void = 0;

        ~VRenderObject() noexcept override = default;
    };

}

#endif //C_ENG_VRENDEROBJECT_HPP
