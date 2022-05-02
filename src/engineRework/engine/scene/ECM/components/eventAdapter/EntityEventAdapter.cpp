//
// Created by loghin on 5/2/22.
//

#include "EntityEventAdapter.hpp"
#include <Logger.hpp>

using namespace engine;
using namespace cds;
using namespace cds :: json :: standard;

#define C_ENG_MAP_START CLASS ( EntityEventAdapter, ENGINE_PARENT ( Component ) )
#include <ObjectMapping.hpp>

auto Self :: loadFrom ( JsonObject const & json ) noexcept -> Self & {

    try {
        auto const & adapterJson = json.getJson ( Self :: controllerAdapterKey );

        try {
            this->setControllerComponent ( Type ( EntityEventAdapterControllerComponent ) :: instantiate ( adapterJson ).release() );
        } catch ( Exception const & ) {
            log :: warn () << "Failed to create EventAdapterComponent, it will not be added to the EventAdapter";
        }

    } catch ( KeyException const & ) {
    } catch ( TypeException const & exception ) {
        log :: warn ()
                << "Could not add event adapter '"
                << Self :: controllerAdapterKey
                << "', format invalid : "
                << exception.toString();
    }

    try {
        auto const & adapterJson = json.getJson ( Self :: keyAdapterKey );

        try {
            this->setKeyComponent ( Type ( EntityEventAdapterKeyComponent ) :: instantiate ( adapterJson ).release() );
        } catch ( Exception const & ) {
            log :: warn () << "Failed to create EventAdapterComponent, it will not be added to the EventAdapter";
        }

    } catch ( KeyException const & ) {
    } catch ( TypeException const & exception ) {
        log :: warn ()
                << "Could not add event adapter '"
                << Self :: keyAdapterKey
                << "', format invalid : "
                << exception.toString();
    }

    try {
        auto const & adapterJson = json.getJson ( Self :: mouseAdapterKey );

        try {
            this->setMouseComponent( Type ( EntityEventAdapterMouseComponent ) :: instantiate ( adapterJson ).release() );
        } catch ( Exception const & ) {
            log :: warn () << "Failed to create EventAdapterComponent, it will not be added to the EventAdapter";
        }

    } catch ( KeyException const & ) {
    } catch ( TypeException const & exception ) {
        log :: warn ()
                << "Could not add event adapter '"
                << Self :: mouseAdapterKey
                << "', format invalid : "
                << exception.toString();
    }

    return * this;
}

auto Self :: dumpTo ( JsonObject & json ) noexcept -> Self & {

    (void) this->Parent :: dumpTo ( json );

    if ( this->_controllerEventAdapter != nullptr ) {
        JsonObject controllerEventAdapterJson;

        this->_controllerEventAdapter->dumpTo ( controllerEventAdapterJson );
        (void) json.put ( Self :: controllerAdapterKey, controllerEventAdapterJson );
    }

    if ( this->_keyEventAdapter != nullptr ) {
        JsonObject keyEventAdapterJson;

        this->_keyEventAdapter->dumpTo ( keyEventAdapterJson );
        (void) json.put ( Self :: keyAdapterKey, keyEventAdapterJson );
    }

    if ( this->_mouseEventAdapter != nullptr ) {
        JsonObject mouseEventAdapterJson;

        this->_mouseEventAdapter->dumpTo ( mouseEventAdapterJson );
        (void) json.put ( Self :: mouseAdapterKey, mouseEventAdapterJson );
    }

    return * this;
}

auto Self :: clear () noexcept -> Self & {

    delete cds :: exchange ( this->_controllerEventAdapter, nullptr );
    delete cds :: exchange ( this->_mouseEventAdapter, nullptr );
    delete cds :: exchange ( this->_keyEventAdapter, nullptr );

    return * this;
}

Self :: Destructor () noexcept {

    (void) this->Self::clear();
}

Self :: Constructor ( Self const & obj ) noexcept :
        _mouseEventAdapter ( obj._mouseEventAdapter == nullptr ? nullptr : obj._mouseEventAdapter->copy() ),
        _keyEventAdapter ( obj._keyEventAdapter == nullptr ? nullptr : obj._keyEventAdapter->copy() ),
        _controllerEventAdapter ( obj._controllerEventAdapter == nullptr ? nullptr : obj._controllerEventAdapter->copy() ) {

    this->_mouseEventAdapter->adapter() = this;
    this->_keyEventAdapter->adapter() = this;
    this->_controllerEventAdapter->adapter() = this;
}

Self :: Constructor ( Self && obj ) noexcept :
        _mouseEventAdapter ( cds :: exchange ( obj._mouseEventAdapter, nullptr ) ),
        _keyEventAdapter ( cds :: exchange ( obj._keyEventAdapter, nullptr ) ),
        _controllerEventAdapter ( cds :: exchange ( obj._controllerEventAdapter, nullptr ) ) {

    this->_mouseEventAdapter->adapter() = this;
    this->_keyEventAdapter->adapter() = this;
    this->_controllerEventAdapter->adapter() = this;
}

auto Self :: operator = ( Self const & obj ) noexcept -> Self & {
    if ( this == & obj ) {
        return * this;
    }

    this->_mouseEventAdapter = obj._mouseEventAdapter == nullptr ? nullptr : obj._mouseEventAdapter->copy();
    this->_keyEventAdapter = obj._keyEventAdapter == nullptr ? nullptr : obj._keyEventAdapter->copy();
    this->_controllerEventAdapter = obj._controllerEventAdapter == nullptr ? nullptr : obj._controllerEventAdapter->copy();

    this->_mouseEventAdapter->adapter() = this;
    this->_keyEventAdapter->adapter() = this;
    this->_controllerEventAdapter->adapter() = this;

    return * this;
}

auto Self :: operator = ( Self && obj ) noexcept -> Self & {
    if ( this == & obj ) {
        return * this;
    }

    this->_mouseEventAdapter = cds ::exchange ( obj._mouseEventAdapter, nullptr );
    this->_keyEventAdapter = cds ::exchange ( obj._keyEventAdapter, nullptr );
    this->_controllerEventAdapter = cds ::exchange ( obj._controllerEventAdapter, nullptr );

    this->_mouseEventAdapter->adapter() = this;
    this->_keyEventAdapter->adapter() = this;
    this->_controllerEventAdapter->adapter() = this;

    return * this;
}

auto Self :: copy () const noexcept -> Self * {
    return new Self ( * this );
}

auto Self :: setControllerComponent ( ControllerEventAdapterComponentType pComponent ) noexcept -> Self & {

    if ( this->_controllerEventAdapter != nullptr ) {
        delete this->_controllerEventAdapter;
    }

    this->_controllerEventAdapter = pComponent;
    this->_controllerEventAdapter->adapter() = this;
    return * this;
}

auto Self :: setKeyComponent ( KeyEventAdapterComponentType pComponent ) noexcept -> Self & {

    if ( this->_keyEventAdapter != nullptr ) {
        delete this->_keyEventAdapter;
    }

    this->_keyEventAdapter = pComponent;
    this->_keyEventAdapter->adapter() = this;
    return * this;
}

auto Self :: setMouseComponent ( MouseEventAdapterComponentType pComponent ) noexcept -> Self & {

    if ( this->_mouseEventAdapter != nullptr ) {
        delete this->_mouseEventAdapter;
    }

    this->_mouseEventAdapter = pComponent;
    this->_mouseEventAdapter->adapter() = this;
    return * this;
}
