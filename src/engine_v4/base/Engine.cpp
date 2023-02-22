/*
 * Created by loghin on 27/12/22.
 */

#include "Engine.hpp"

namespace engine {
    using namespace cds;
    using namespace engine::storage;

    auto Engine::setBaseStorage (UniquePointer <Storage> pStorage) noexcept -> Engine & {
        this->_pBaseStorage = std::move (pStorage);
        return * this;
    }

    auto Engine::run (int argumentCount, char const * const * ppArguments) noexcept -> int {

        return 0;
    }
}
