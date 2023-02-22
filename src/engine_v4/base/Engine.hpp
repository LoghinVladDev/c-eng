/*
 * Created by loghin on 27/12/22.
 */

#ifndef __C_ENG_ENGINE_HPP__
#define __C_ENG_ENGINE_HPP__

#include <CDS/Object>
#include <CDS/memory/UniquePointer>

#include "storage/Storage.hpp"

namespace engine {

    class Engine : public cds::Object {

    private:
        cds::UniquePointer <storage::Storage> _pBaseStorage {nullptr};

    public:
        auto setBaseStorage (
                cds::UniquePointer <storage::Storage> pStorage
        ) noexcept -> Engine &;

    public:
        auto run (
                int                  argumentCount,
                char const * const * ppArguments
        ) noexcept -> int;
    };

}


#endif /* __C_ENG_ENGINE_HPP__ */
