//
// Created by loghin on 24/02/23.
//

#include "Display.hpp"

#include <CDS/String>
#include <CDS/Optional>

using namespace cds;

namespace engine::io {

    Display :: Display (Object const * pParent) noexcept : Object (pParent) {}


    auto Display :: name () const noexcept -> StringView {
        return "Undefined";
    }


    auto Display :: physicalSizeMm () const noexcept -> Size2D {
        return {0U, 0U};
    }


    auto Display :: scale () const noexcept -> engine::Size2DF {
        return {1.0F, 1.0F};
    }


    DisplayManager :: DisplayManager (Object const * pParent) noexcept : Object (pParent) {}

}
