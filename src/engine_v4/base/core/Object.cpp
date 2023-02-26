//
// Created by loghin on 26/02/23.
//

#include "Object.hpp"

using namespace engine;
using namespace engine::io;
using namespace cds;


#if __C_ENG_LOGGING_ENABLED
namespace {
    class : public Logger {
        auto log (Level level, StringView message) const noexcept -> void override {
            (void) level;
            (void) message;
        }
    } noLog;
}

auto engine::Object :: logger () const noexcept -> Logger const * {
    return this->_pLogger;
}

auto engine::Object :: setLogger (Logger const * pLogger) noexcept -> void {
    this->_pLogger = pLogger;
}
#endif


engine::Object :: Object (engine::Object const * pParent) noexcept {

    this->_pParent = pParent;

#if __C_ENG_LOGGING_ENABLED

    if (this->parent() != nullptr) {
        this->_pLogger = this->parent()->logger();
    }

    if (this->logger() == nullptr) {
        this->_pLogger = & noLog;
    }

#endif
}


