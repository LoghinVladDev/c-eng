/*
 * Created by loghin on 04/03/23.
 */

#include <engine.h>
#include <eng_alloc.h>
#include <eng_private_types.h>
#include <stdbool.h>


typedef ENG_TYPE(Engine)                T_Engine;
typedef ENG_TYPE(EngineMainCallbacks)   T_EngineMainCallbacks;
typedef ENG_TYPE(EngineCreateInfo)      T_EngineCreateInfo;


#define createEngine            ENG_SYM(CreateEngine)
#define destroyEngine           ENG_SYM(DestroyEngine)
#define engineRun               ENG_SYM(EngineRun)
#define engineRequestShutdown   ENG_SYM(EngineRequestShutdown)


__ENG_HANDLE(ENG_TYPE(Engine)) {
    T_EngineMainCallbacks   mainCallbacks;
    bool                    shutdownRequested;
};


typedef __ENG_HANDLE(ENG_TYPE(Engine))  T_PrivateEngine;


static inline T_Engine newEngine (
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    T_Engine newEngine = pAllocationCallbacks->pfnAllocation (
            pAllocationCallbacks->pUserData,
            sizeof (T_PrivateEngine),
            _Alignof (T_PrivateEngine),
            SYSTEM_ALLOCATION_SCOPE_ENGINE
    );

    if (newEngine == NULL) {
        return NULL;
    }

    * newEngine = (T_PrivateEngine) {
            .shutdownRequested = false,
            .mainCallbacks = {
                    .pfnPreInit         = NULL,
                    .pfnPostInit        = NULL,
                    .pfnPreUpdate       = NULL,
                    .pfnPostUpdate      = NULL,
                    .pfnPreShutdown     = NULL,
                    .pfnPostShutdown    = NULL
            }
    };

    return newEngine;
}


static inline void freeEngine (
        T_Engine                        engine,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    pAllocationCallbacks->pfnFree (
            pAllocationCallbacks->pUserData,
            engine
    );
}


T_Result createEngine (
        T_Engine                      * pEngine,
        T_EngineCreateInfo      const * pCreateInfo,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    T_Engine engine = newEngine (__allocationCallbacks (pAllocationCallbacks));

    if (engine == NULL) {
        return RESULT_ERROR_OUT_OF_MEMORY;
    }

    engine->mainCallbacks = pCreateInfo->mainCallbacks;

    * pEngine = engine;
    return RESULT_OK;
}


void destroyEngine (
        T_Engine                        engine,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    freeEngine (engine, __allocationCallbacks(pAllocationCallbacks));
}


static inline void init (
        T_Engine engine
) {

    (void) engine;
}


static inline void update (
        T_Engine engine
) {

    (void) engine;
}


static inline void shutdown (
        T_Engine engine
) {

    (void) engine;
}


T_Result engineRun (
        T_Engine engine
) {

    if (engine->mainCallbacks.pfnPreInit != NULL) {
        engine->mainCallbacks.pfnPreInit (engine);
    }

    init (engine);

    if (engine->mainCallbacks.pfnPostInit != NULL) {
        engine->mainCallbacks.pfnPostInit (engine);
    }

    while (! engine->shutdownRequested) {

        if (engine->mainCallbacks.pfnPreUpdate != NULL) {
            engine->mainCallbacks.pfnPreUpdate (engine);
        }

        update (engine);

        if (engine->mainCallbacks.pfnPostUpdate != NULL) {
            engine->mainCallbacks.pfnPostUpdate (engine);
        }
    }

    if (engine->mainCallbacks.pfnPreShutdown != NULL) {
        engine->mainCallbacks.pfnPreShutdown (engine);
    }

    shutdown (engine);

    if (engine->mainCallbacks.pfnPostShutdown != NULL) {
        engine->mainCallbacks.pfnPostShutdown (engine);
    }

    return RESULT_OK;
}


void engineRequestShutdown (
        T_Engine engine
) {

    engine->shutdownRequested = true;
}
