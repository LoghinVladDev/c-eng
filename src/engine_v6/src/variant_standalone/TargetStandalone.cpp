#include "Engine.hpp"

namespace {
    using engine::Engine;
    using engine::Logger;
}

namespace engine::meta {
    extern bool get();
}

std::string here (std::string s, std::source_location const l=std::source_location::current()) {
    return s + std::to_string(l.line());
}

auto main (int argc, char const * const * ppARgv) noexcept -> int {

    Engine engine;
    Logger l (std::cout);
    engine.setLogger(& l);
    auto h = here("test");

    engine.logger() << "test" << '\n';
    engine.logger() << "test";
    engine.logger() << std::hex << "0x..." << 123;
    engine.logger() << Logger::Warning << here("test") << std::hex << "0x..." << 123 << " " << h;
    engine.logger() << std::oct << 123;
    engine.logger() << std::oct << 123;

    return 0;
}
