//
// Created by loghin on 5/1/22.
//

#include "ThreadIdentification.hpp"
#include <CDS/HashMap>
#include <CDS/Mutex>
#include <CDS/LockGuard>

using namespace engine;
using namespace cds;

static cds :: Mutex                                     lock;
static cds :: HashMap < Thread :: ID, StringLiteral >   assoc;

auto engine :: storeThreadIdentificationString ( Thread :: ID ID, StringLiteral string ) noexcept -> void {
    LockGuard guard ( lock );
    assoc.emplace ( ID, string );
}

auto engine :: getThreadIdentificationString ( Thread :: ID ID ) noexcept -> StringLiteral {
    auto identification = assoc.find ( ID );
    if ( identification.hasValue() ) {
        return identification->get();
    }

    return unassignedThreadIdentificationString;
}
