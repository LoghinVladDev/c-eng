//
// Created by Vlad-Andrei Loghin on 15.06.23.
//

#include "Unix.hpp"

using namespace engine;
using namespace cds;

namespace {
Api::Info const defaultApiInfo = {
    .name         = "Unix System API",
    .description  = "System Interaction with Unix Based OS",
    .purpose      = "mandatory=[system], optional=[]",
    .vendor       = "TBA",
    .vendorId     = Api::unknownVendorId,
    .sourceType   = Api::SourceType::OpenSource,
    .version      = {
        .variant      = variant::original,
        .major        = version::unspecified,
        .minor        = version::unspecified,
        .patch        = version::unspecified
    }
};
} // namespace

auto Unix::apiInfo() const noexcept -> Info const& {
  return defaultApiInfo;
}

auto Unix::getComponentList() noexcept -> Array <ApiComponent*> {
  return {systemComponent};
}

Unix::Unix(Engine* pParent) noexcept(false) :
    Api(pParent) {}
