//
// Created by loghin on 08.04.2021.
//

#ifndef C_ENG_VCAMERA_H
#define C_ENG_VCAMERA_H

#include <VGameObject.hpp>

namespace engine {

    class VCamera : public VGameObject {
    private:
        //// private variables
        glm::vec3       _front          {0.0f};
        glm::vec3       _up             {0.0f};
        glm::vec3       _right          {0.0f};
        glm::vec3       _worldUp        {0.0f};
        glm::vec3       _worldFront     {0.0f};

        VTransform    * _pTransform     {new VTransform()};

        //// private functions

    public:
        //// public variables

        //// public functions

        VCamera() noexcept {
            this->add(this->_pTransform);
        }
    };

}

#endif //C_ENG_VCAMERA_H
