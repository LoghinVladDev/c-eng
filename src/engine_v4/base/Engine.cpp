/*
 * Created by loghin on 27/12/22.
 */

#include "Engine.hpp"

namespace engine {
    using namespace cds;
    using namespace engine::storage;

    Engine :: Engine (engine::Object const * pParent) noexcept : Object (pParent) {}


    auto Engine::setBaseStorage (UniquePointer <Storage> pStorage) noexcept -> Engine & {
        this->_pBaseStorage = std::move (pStorage);
        return * this;
    }


    auto Engine::setUserData (void * pUserData) noexcept -> Engine & {
        this->_pUserData = pUserData;
        return * this;
    }


    auto Engine::run (int argumentCount, char const * const * ppArguments) noexcept -> int {

        (void) argumentCount;
        (void) ppArguments;


        __C_ENG_OBJ_LOG(Info, "Engine Startup");

        __C_ENG_OBJ_LOG(Debug, "Calling Pre-Init Hook");
        this->_customPreInitHook (this);
        __C_ENG_OBJ_LOG(Debug, "Calling Engine Initialization");
        this->handleInit();
        __C_ENG_OBJ_LOG(Debug, "Calling Post-Init Hook");
        this->_customPostInitHook (this);

        __C_ENG_OBJ_LOG(Info, "Engine Startup Complete");

        __C_ENG_OBJ_LOG(Info, "Starting Engine Main Loop");
        while (! this->shutdownRequested()) {
            this->_customPreUpdateHook (this);
            this->handleUpdate();
            this->_customPostUpdateHook (this);
        }

        __C_ENG_OBJ_LOG(Info, "Engine Shutting Down");

        __C_ENG_OBJ_LOG(Debug, "Calling Pre-Shutdown Hook");
        this->_customPreShutdownHook (this);
        __C_ENG_OBJ_LOG(Debug, "Calling Engine Shutdown");
        this->handleShutdown();
        __C_ENG_OBJ_LOG(Debug, "Calling Post-Shutdown Hook");
        this->_customPostShutdownHook (this);

        __C_ENG_OBJ_LOG(Info, "Engine Shutdown Complete");

        return 0;
    }


    auto Engine :: handleInit () noexcept -> void {

    }


    auto Engine :: handleUpdate () noexcept -> void {

    }


    auto Engine :: handleShutdown () noexcept -> void {

    }


    auto Engine :: userData () const noexcept -> void * {
        return this->_pUserData;
    }


    auto Engine :: setPreInitHook (CustomHook hook) noexcept -> Engine & {
        this->_customPreInitHook = std::move(hook);
        return * this;
    }


    auto Engine :: setPreUpdateHook (CustomHook hook) noexcept -> Engine & {
        this->_customPreUpdateHook = std::move(hook);
        return * this;
    }


    auto Engine :: setPreShutdownHook (CustomHook hook) noexcept -> Engine & {
        this->_customPreShutdownHook = std::move(hook);
        return * this;
    }


    auto Engine :: setPostInitHook (CustomHook hook) noexcept -> Engine & {
        this->_customPostInitHook = std::move(hook);
        return * this;
    }


    auto Engine :: setPostUpdateHook (CustomHook hook) noexcept -> Engine & {
        this->_customPostUpdateHook = std::move(hook);
        return * this;
    }


    auto Engine :: setPostShutdownHook (CustomHook hook) noexcept -> Engine & {
        this->_customPostShutdownHook = std::move(hook);
        return * this;
    }


    auto Engine :: requestShutdown () noexcept -> void {
        __C_ENG_OBJ_LOG(Info, "Engine Shutdown Requested");
        this->_shutdownRequested = true;
    }


    auto Engine :: shutdownRequested () const noexcept -> bool {
        return this->_shutdownRequested;
    }
}
