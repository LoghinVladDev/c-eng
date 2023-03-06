/*
 * Created by loghin on 04/03/23.
 */

#include <engine.h>

#include <eng_private_types.h>

#include <validation.h>
#include <validation_private.h>
#include <validation_messenger_private.h>
#include <validation_issue_id.h>

#include <eng_alloc.h>
#include <eng_types.h>
#include <engine_private.h>
#include <stdbool.h>


static T_ApiInfo const globalApiInfo = {
        .pApiName       = "PH Engine Name",
        .pApiPurpose    = "PH Engine Purpose",
        .pVendorInfo    = "PH Vendor Info",
        .provenience    = SL_API_PROVENIENCE_PROPRIETARY,
        .version        = {
                .variant        = ENG_VERSION_VARIANT,
                .major          = ENG_VERSION_MAJOR,
                .minor          = ENG_VERSION_MINOR,
                .patch          = ENG_VERSION_PATCH
        }
};


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

            .localValidationMessenger   = NULL,
            .pTrackedResources          = NULL
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

    (void) pAllocationCallbacks;

    S_EngineTrackedResources        * pTrackedResources = engine->pTrackedResources;
    T_ARRAY(T_ValidationMessenger)  * pMessengerArray   = & pTrackedResources->validationMessengers;

    for (uint32_t i = 0U; i < T_ARRAY_SIZE(T_ValidationMessenger)(pMessengerArray); ++ i) {
        raiseValidationIssueDirect (
                engine,
                engine->localValidationMessenger,
                VALIDATION_ISSUE_GROUP_ENGINE,
                VALIDATION_ISSUE_CATEGORY_RESOURCE_MANAGEMENT,
                VALIDATION_ISSUE_ID_VALIDATION_MESSENGER_NOT_DESTROYED,
                engine,
                T_ARRAY_GET(T_ValidationMessenger)(pMessengerArray, i)
        );
    }
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

    engine->apiInfo = globalApiInfo;

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

                engine->pTrackedResources = pAlloc->pfnAllocation (
                        pAlloc->pUserData,
                        sizeof (S_EngineTrackedResources),
                        _Alignof (S_EngineTrackedResources),
                        SYSTEM_ALLOCATION_SCOPE_ENGINE
                );

                T_ARRAY_INIT(T_ValidationMessenger) (
                        & engine->pTrackedResources->validationMessengers,
                        0U,
                        pAlloc
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

    if (engine->localValidationMessenger != NULL) {

        validate_destroyEngine (engine, pAlloc);
        pAlloc->pfnFree (
                pAlloc->pUserData,
                engine->pTrackedResources
        );

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


T_ApiInfo const * engineGetApiInfo (
        T_Engine engine
) {

    if (engine == NULL) {
        return & globalApiInfo;
    }

    return & engine->apiInfo;
}
