//
// Created by loghin on 5/16/22.
//

#include "Mesh.hpp"
#include <Logger.hpp>
#include <meshLoader/meshLoader>

using namespace cds;
using namespace engine;

using namespace cds :: json :: standard;

#define C_ENG_MAP_START CLASS ( Mesh, ENGINE_PARENT ( Component ) )
#include <ObjectMapping.hpp>

auto Self :: loadFrom ( JsonObject const & object ) noexcept (false) -> Self & {

    try {

        auto const & pathString = object.getString ( Self :: pathKey );

        this->_path = pathString;
    } catch ( KeyException const & ) {
        log :: err () << "Key '" << Self :: pathKey << "' not present in mesh component";
        throw;
    } catch ( TypeException const & ) {
        log :: err () << "Key '" << Self :: pathKey << "' present, but format is not ok. Expected : String";
        throw;
    } catch ( Path :: InvalidPath const & ) {
        log :: err () << "Path given for mesh invalid";
        throw;
    }

    return * this;
}

auto Self :: dumpTo ( JsonObject & object ) noexcept -> Self & {

    (void) this->Parent :: dumpTo ( object );

    (void) object.put (
            Self :: pathKey,
            this->_path.toString()
    );

    return * this;
}

auto Self :: clear () noexcept -> Self & {

    MeshLoader_destroyMesh ( this->handle(), nullptr );
    this->_handle = nullptr;

    return * this;
}

auto Self :: copy () const noexcept -> Self * {
    return new Self ( * this );
}

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) + " "
            "{ path = "_s   + this->_path +
            ", handle = "   + engine :: toString ( this->handle() ) +
            " }";
}

Self :: Constructor ( Self && object ) noexcept :
        _path ( std :: move ( object._path ) ),
        _handle ( cds :: exchange ( object._handle, nullptr ) ) {

}

Self :: Destructor () noexcept {
    (void) this->Self :: clear();
}

auto Self :: operator = ( Self && object ) noexcept -> Self & {

    if ( this == & object ) {
        return * this;
    }

    this->_path     = std :: move ( object._path );
    this->_handle   = cds :: exchange ( object._handle, nullptr );

    return * this;
}
