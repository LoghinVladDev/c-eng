//
// Created by loghin on 24/02/23.
//

#include "Display.hpp"

#include <CDS/String>
#include <CDS/Optional>

using namespace cds;

namespace engine::io {

    Display :: Display (Object const * pParent) noexcept : Object (pParent) {}


    auto Display :: name () const noexcept -> Optional <String> {
        return {};
    }


    auto Display :: physicalSizeMm () const noexcept -> Optional <Size2D> {
        return {};
    }


    auto Display :: scale () const noexcept -> engine::Size2DF {
        return {1.0f, 1.0f};
    }


    DisplayManager :: DisplayManager (Object const * pParent) noexcept : Object (pParent) {}

}
