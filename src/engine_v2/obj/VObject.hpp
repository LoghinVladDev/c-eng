//
// Created by loghin on 23.05.2021.
//

#ifndef C_ENG_VOBJECT_HPP
#define C_ENG_VOBJECT_HPP

#include <engineVulkanPreproc.hpp>
#include <CDS/Object>

namespace engine {

class VObject : public cds :: Object {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables

        //// public functions

        __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

        ~VObject() noexcept override = default;
    };

}

#endif //C_ENG_VOBJECT_HPP
