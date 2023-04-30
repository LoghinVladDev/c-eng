#pragma once

namespace engine::config {

    enum class ParameterType {
        LoggingEnabled
    };

    template <ParameterType configValue>
    struct Parameter {
        constexpr static bool const value = false;
    };

    template <ParameterType configValue>
    constexpr static bool const value = Parameter <configValue> :: value;

}

#include "TargetConfig.hpp"
