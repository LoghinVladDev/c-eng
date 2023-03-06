//
// Created by loghin on 26/02/23.
//

#include "Logger.hpp"

using namespace engine::io;
using namespace cds;

auto Logger :: log (
        Level           level,
        StringView      message,
        StringView      fileName,
        StringView      functionName,
        long long int   lineNumber
) const noexcept -> void {

    (void) fileName;
    (void) functionName;
    (void) lineNumber;

    this->log (
            level,
            message
    );
}


auto Logger :: log (
        Level                   level,
        StringView              message,
        StringView              fileName,
        StringView              functionName,
        long long int           lineNumber,
        engine::Object  const * pObject
) const noexcept -> void {

    (void) fileName;
    (void) functionName;
    (void) lineNumber;
    (void) pObject;

    this->log (
            level,
            message
    );
}
