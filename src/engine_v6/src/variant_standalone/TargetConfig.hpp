#pragma once

namespace engine::config {

    template <> struct Parameter <ParameterType::LoggingEnabled> {
        constexpr static bool const value = true;
    };

}
