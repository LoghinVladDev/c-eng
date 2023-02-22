//
// Created by loghin on 5/17/22.
//

#include "SceneComponentLoader.hpp"
#include <scene/ECM/Component.hpp>

#define C_ENG_MAP_START CLASS ( SceneComponentLoader, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

using namespace cds;
using namespace engine;

Self :: Destructor () noexcept {
    this->Self :: clear();
}

auto Self :: update ( cds :: DoubleLinkedList < Type ( Component ) * > & components ) noexcept -> Self & {

    while ( ! components.empty() ) {

        for ( auto & loader : this->_loaders ) {

            if ( loader->type() == components.front()->type() ) {

                loader->load ( components.front() );
                break;
            }
        }

        components.popFront();
    }

    return * this;
}

auto Self :: done () noexcept -> bool {
    return this->_loaders.all (
            [] ( UniquePointer < Type ( SceneSpecializedComponentLoader ) > & loader ) {
                return loader->done();
            }
    );
}

auto Self :: clear () noexcept -> Self & {

    return * this;
}
