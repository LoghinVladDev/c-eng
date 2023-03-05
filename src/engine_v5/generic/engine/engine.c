/*
 * Created by loghin on 04/03/23.
 */

#include <engine.h>

#include <eng_private_types.h>

#include <validation.h>
#include <validation_private.h>
#include <validation_messenger_private.h>

#include <eng_alloc.h>
#include <eng_types.h>
#include <engine_private.h>
#include <stdbool.h>


static inline T_Engine newEngine (
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    T_Engine newEngine = pAllocationCallbacks->pfnAllocation (
            pAllocationCallbacks->pUserData,
            sizeof (S_PrivateEngine),
            _Alignof (S_PrivateEngine),
            SYSTEM_ALLOCATION_SCOPE_ENGINE
    );

    if (newEngine == NULL) {
        return NULL;
    }

    * newEngine = (S_PrivateEngine) {
            .shutdownRequested  = false,
            .mainCallbacks      = {
                    .pfnPreInit         = NULL,
                    .pfnPostInit        = NULL,
                    .pfnPreUpdate       = NULL,
                    .pfnPostUpdate      = NULL,
                    .pfnPreShutdown     = NULL,
                    .pfnPostShutdown    = NULL
            },

            .localValidationMessenger   = NULL
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


static inline void validate_createEngine (
        T_ValidationMessenger           messenger,
        T_EngineCreateInfo      const * pCreateInfo,
        T_AllocationCallbacks   const * pAllocationCallbacks,
        T_Engine                      * pEngine
) {

}


static inline void validate_destroyEngine (
        T_Engine                        engine,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

}


T_Result createEngine (
        T_EngineCreateInfo      const * pCreateInfo,
        T_AllocationCallbacks   const * pAllocationCallbacks,
        T_Engine                      * pEngine
) {

    T_AllocationCallbacks const * pAlloc = __allocationCallbacks(pAllocationCallbacks);
    T_Engine engine = newEngine (pAlloc);

    if (engine == NULL) {
        return RESULT_ERROR_OUT_OF_MEMORY;
    }

    T_GenericInStructure const * pNext = pCreateInfo->pNext;
    while (pNext != NULL) {

        switch (pNext->structureType) {
            case STRUCTURE_TYPE_VALIDATION_MESSENGER_CREATE_INFO: {

                if (! pCreateInfo->validationEnabled) {
                    break;
                }

                engine->localValidationMessenger = __validation_createMessenger (
                        (T_ValidationMessengerCreateInfo const *) pNext,
                        pAlloc
                );

                if (engine->localValidationMessenger == NULL) {
                    freeEngine (engine, pAlloc);
                    return RESULT_ERROR_OUT_OF_MEMORY;
                }

                validate_createEngine (
                        engine->localValidationMessenger,
                        pCreateInfo, pAllocationCallbacks, pEngine
                );

                break;
            }

            default: {
                break;
            }
        }

        pNext = pNext->pNext;
    }

    engine->mainCallbacks   = pCreateInfo->mainCallbacks;
    engine->pUserData       = pCreateInfo->pUserData;

    * pEngine = engine;
    return RESULT_OK;
}


void destroyEngine (
        T_Engine                        engine,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    T_AllocationCallbacks const * pAlloc = __allocationCallbacks(pAllocationCallbacks);

    if (engine->localValidationMessenger) {
        validate_destroyEngine (engine, pAlloc);
        __validation_destroyMessenger (engine->localValidationMessenger, pAlloc);
    }

    freeEngine (engine, pAlloc);
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
        engine->mainCallbacks.pfnPreInit (engine->pUserData, engine);
    }

    init (engine);

    if (engine->mainCallbacks.pfnPostInit != NULL) {
        engine->mainCallbacks.pfnPostInit (engine->pUserData, engine);
    }

    while (! engine->shutdownRequested) {

        if (engine->mainCallbacks.pfnPreUpdate != NULL) {
            engine->mainCallbacks.pfnPreUpdate (engine->pUserData, engine);
        }

        update (engine);

        if (engine->mainCallbacks.pfnPostUpdate != NULL) {
            engine->mainCallbacks.pfnPostUpdate (engine->pUserData, engine);
        }
    }

    if (engine->mainCallbacks.pfnPreShutdown != NULL) {
        engine->mainCallbacks.pfnPreShutdown (engine->pUserData, engine);
    }

    shutdown (engine);

    if (engine->mainCallbacks.pfnPostShutdown != NULL) {
        engine->mainCallbacks.pfnPostShutdown (engine->pUserData, engine);
    }

    return RESULT_OK;
}


void engineRequestShutdown (
        T_Engine engine
) {

    engine->shutdownRequested = true;
}
