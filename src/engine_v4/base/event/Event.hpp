//
// Created by loghin on 01/03/23.
//

#ifndef __C_ENG_EVENT_HPP__
#define __C_ENG_EVENT_HPP__

#include <base/core/Object.hpp>

namespace engine::event {

    class Event : public Object {
    protected:
        explicit Event (Object * pEmitter) noexcept;

    public:

        ~Event () noexcept override = default;

        __CDS_NoDiscard constexpr auto emitter () const noexcept -> Object const * {
            return this->parent();
        }
    };

}


#endif //__C_ENG_EVENT_HPP__
