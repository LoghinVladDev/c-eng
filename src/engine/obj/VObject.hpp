//
// Created by loghin on 23.05.2021.
//

#ifndef C_ENG_VOBJECT_HPP
#define C_ENG_VOBJECT_HPP

#include <engineVulkanPreproc.hpp>
#include <CDS/Object>

namespace engine {

    class VObject : public Object {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables

        //// public functions

        [[nodiscard]] auto toString () const noexcept -> String override;

        ~VObject() noexcept override = default;
    };

}

#endif //C_ENG_VOBJECT_HPP
