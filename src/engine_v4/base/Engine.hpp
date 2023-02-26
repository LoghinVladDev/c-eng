/*
 * Created by loghin on 27/12/22.
 */

#ifndef __C_ENG_ENGINE_HPP__
#define __C_ENG_ENGINE_HPP__

#include <CDS/Function>
#include <CDS/memory/UniquePointer>

#include <base/core/Object.hpp>
#include <base/storage/Storage.hpp>

namespace engine {

    class Engine : public Object {

    public:
        using CustomHook = cds::Function <auto (Engine *) -> void>;

    private:
        cds::UniquePointer <storage::Storage>       _pBaseStorage       {nullptr};
        void                                      * _pUserData          {nullptr};

        CustomHook                                  _customPreInitHook      {[](auto){}};
        CustomHook                                  _customPostInitHook     {[](auto){}};
        CustomHook                                  _customPreUpdateHook    {[](auto){}};
        CustomHook                                  _customPostUpdateHook   {[](auto){}};
        CustomHook                                  _customPreShutdownHook  {[](auto){}};
        CustomHook                                  _customPostShutdownHook {[](auto){}};

        bool                                        _shutdownRequested      {false};

        auto handleInit () noexcept -> void;
        auto handleUpdate () noexcept -> void;
        auto handleShutdown () noexcept -> void;

        __CDS_NoDiscard auto shutdownRequested () const noexcept -> bool;

    public:
        explicit Engine (Object const * pParent = nullptr) noexcept;

        ~Engine () noexcept override = default;
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto className () const noexcept -> cds::StringView override {
            return "Engine";
        }

        auto setBaseStorage (
                cds::UniquePointer <storage::Storage> pStorage
        ) noexcept -> Engine &;

        auto setUserData (void * pUserData) noexcept -> Engine &;
        __CDS_NoDiscard auto userData () const noexcept -> void *;
        auto setPreInitHook (CustomHook hook) noexcept -> Engine &;
        auto setPreUpdateHook (CustomHook hook) noexcept -> Engine &;
        auto setPreShutdownHook (CustomHook hook) noexcept -> Engine &;
        auto setPostInitHook (CustomHook hook) noexcept -> Engine &;
        auto setPostUpdateHook (CustomHook hook) noexcept -> Engine &;
        auto setPostShutdownHook (CustomHook hook) noexcept -> Engine &;

        auto requestShutdown () noexcept -> void;

        auto run (
                int                  argumentCount,
                char const * const * ppArguments
        ) noexcept -> int;
    };

}


#endif /* __C_ENG_ENGINE_HPP__ */
