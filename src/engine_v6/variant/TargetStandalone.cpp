#include "TargetStandaloneConfig.hpp"
#include "Engine.hpp"

namespace {
    using engine::Engine;
}

auto main (int argc, char const * const * ppARgv) noexcept -> int {

    Engine engine;
    engine::Logger l (std::cout);
    engine.setLogger(& l);

    engine.logger() << "test" << '\n';
    engine.logger() << "test";

    return 0;
}
