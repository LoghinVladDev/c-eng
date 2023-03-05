//
// Created by loghin on 05/03/23.
//

#include "validation.h"
#include <eng_types.h>
#include <eng_private_types.h>
#include <validation_private.h>
#include <engine_private.h>
#include <eng_alloc.h>
#include <string.h>


typedef struct {
    T_Engine                engine;
    T_ValidationMessenger * pMessengerHandles;
    uint32_t                messengerCount;
    uint32_t                messengerCapacity;
} S_ValidationEngineAssociation;


typedef struct {
    S_ValidationEngineAssociation * pAssociations;
    uint32_t                        associationCount;
    uint32_t                        associationCapacity;
} S_ValidationControl;


static S_ValidationControl validationControl = {
        .pAssociations          = NULL,
        .associationCount       = 0U,
        .associationCapacity    = 0U
};


static uint32_t const defaultMessengerCapacity = 4U;


static inline S_ValidationEngineAssociation * identifyAssociation (T_Engine engine) {

    for (uint32_t i = 0; i < validationControl.associationCount; ++ i) {
        if (validationControl.pAssociations [i].engine == engine) {
            return & validationControl.pAssociations [i];
        }
    }

    return NULL;
}


static inline S_ValidationEngineAssociation * createAssociation (
        T_Engine                        engine,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    T_ValidationMessenger * pNewMessengerHandles = pAllocationCallbacks->pfnAllocation (
            pAllocationCallbacks->pUserData,
            sizeof (T_ValidationMessenger) * defaultMessengerCapacity,
            _Alignof (T_ValidationMessenger),
            SYSTEM_ALLOCATION_SCOPE_ENGINE
    );

    if (pNewMessengerHandles == NULL) {
        return NULL;
    }

    if (validationControl.associationCount >= validationControl.associationCapacity) {

        uint32_t newCapacity =
                validationControl.associationCapacity == 0U ?
                defaultMessengerCapacity :
                validationControl.associationCapacity * 2U;

        S_ValidationEngineAssociation * pNewAssociations = pAllocationCallbacks->pfnReallocation (
                pAllocationCallbacks->pUserData,
                validationControl.pAssociations,
                sizeof (S_ValidationEngineAssociation) * newCapacity,
                _Alignof(S_ValidationEngineAssociation),
                SYSTEM_ALLOCATION_SCOPE_ENGINE
        );

        if (pNewAssociations == NULL) {
            pAllocationCallbacks->pfnFree (
                    pAllocationCallbacks->pUserData,
                    pNewMessengerHandles
            );

            return NULL;
        }

        validationControl.associationCapacity   = newCapacity;
        validationControl.pAssociations         = pNewAssociations;
        for (uint32_t i = validationControl.associationCount; i < validationControl.associationCapacity; ++ i) {
            validationControl.pAssociations [i].engine = NULL;
        }
    }

    S_ValidationEngineAssociation * pAssociation = & validationControl.pAssociations [validationControl.associationCount ++];
    pAssociation->engine            = engine;
    pAssociation->messengerCapacity = defaultMessengerCapacity;
    pAssociation->messengerCount    = 0U;
    pAssociation->pMessengerHandles = pNewMessengerHandles;
    return pAssociation;
}


static inline void destroyAssociation (
        S_ValidationEngineAssociation     * pAssociation,
        T_AllocationCallbacks       const * pAllocationCallbacks
) {

    pAllocationCallbacks->pfnFree (
            pAllocationCallbacks->pUserData,
            pAssociation->pMessengerHandles
    );

    for (uint32_t i = 0U; i < validationControl.associationCount; ++ i) {
        if (& validationControl.pAssociations [i] == pAssociation) {
            (void) memmove ( /* NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) */
                    & validationControl.pAssociations [i],
                    & validationControl.pAssociations [i + 1U],
                    validationControl.associationCount -- - i - 1U
            );

            break;
        }
    }

    if (validationControl.associationCount == 0U) {
        pAllocationCallbacks->pfnFree (
                pAllocationCallbacks->pUserData,
                validationControl.pAssociations
        );
    }
}


static inline void engineTrackMessenger (
        T_Engine                        engine,
        T_ValidationMessenger           messenger,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    T_ARRAY(T_ValidationMessenger) * pMessengerArray =
            & engine->pTrackedResources->validationMessengers;

    T_ValidationMessenger * pNewMessenger = T_ARRAY_PUSH (T_ValidationMessenger) (
            pMessengerArray,
            pAllocationCallbacks
    );

    if (pNewMessenger != NULL) {
        * pNewMessenger = messenger;
    }
}


static inline void engineUntrackMessenger (
        T_Engine                        engine,
        T_ValidationMessenger           messenger,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    T_ARRAY(T_ValidationMessenger) * pMessengerArray =
            & engine->pTrackedResources->validationMessengers;

    for (uint32_t i = 0U; i < T_ARRAY_SIZE(T_ValidationMessenger) (pMessengerArray); ++ i) {
        if (* T_ARRAY_GET(T_ValidationMessenger) (pMessengerArray, i) == messenger) {
            T_ARRAY_REMOVE(T_ValidationMessenger) (pMessengerArray, i);
            break;
        }
    }

    if (T_ARRAY_EMPTY(T_ValidationMessenger) (pMessengerArray)) {
        T_ARRAY_CLEAR(T_ValidationMessenger) (pMessengerArray, pAllocationCallbacks);
    }
}


T_Result createValidationMessenger (
        T_Engine                                engine,
        T_ValidationMessengerCreateInfo const * pCreateInfo,
        T_AllocationCallbacks           const * pAllocationCallbacks,
        T_ValidationMessenger                 * pMessenger
) {

    T_AllocationCallbacks   const * pAlloc          = __allocationCallbacks (pAllocationCallbacks);
    S_ValidationEngineAssociation * pAssociation    = identifyAssociation (engine);
    if (pAssociation == NULL) {
        pAssociation = createAssociation (engine, pAlloc);
        if (pAssociation == NULL) {
            return RESULT_ERROR_OUT_OF_MEMORY;
        }
    }

    if (pAssociation->messengerCount >= pAssociation->messengerCapacity) {
        uint32_t newCapacity =
                pAssociation->messengerCapacity == 0U ?
                defaultMessengerCapacity :
                pAssociation->messengerCapacity * 2U;

        T_ValidationMessenger * pNewMessengerHandles = pAlloc->pfnReallocation (
                pAlloc->pUserData,
                pAssociation->pMessengerHandles,
                sizeof (T_ValidationMessenger) * newCapacity,
                _Alignof (T_ValidationMessenger),
                SYSTEM_ALLOCATION_SCOPE_ENGINE
        );

        if (pNewMessengerHandles == NULL) {
            return RESULT_ERROR_OUT_OF_MEMORY;
        }

        pAssociation->pMessengerHandles = pNewMessengerHandles;
        pAssociation->messengerCapacity = newCapacity;
    }

    pAssociation->pMessengerHandles [pAssociation->messengerCount] = __validation_createMessenger (
            pCreateInfo,
            pAlloc
    );

    if (pAssociation->pMessengerHandles [pAssociation->messengerCount] == NULL) {
        return RESULT_ERROR_OUT_OF_MEMORY;
    }

    * pMessenger = pAssociation->pMessengerHandles [pAssociation->messengerCount ++];

    if (engine->localValidationMessenger != NULL) {
        engineTrackMessenger (engine, * pMessenger, pAlloc);
    }

    return RESULT_OK;
}

void destroyValidationMessenger (
        T_Engine                        engine,
        T_ValidationMessenger           messenger,
        T_AllocationCallbacks   const * pAllocationCallbacks
) {

    T_AllocationCallbacks   const * pAlloc          = __allocationCallbacks (pAllocationCallbacks);
    S_ValidationEngineAssociation * pAssociation    = identifyAssociation (engine);

    if (engine->localValidationMessenger != NULL) {
        engineUntrackMessenger (engine, messenger, pAlloc);
    }

    if (pAssociation == NULL) {
        return;
    }

    for (uint32_t i = 0U; i < pAssociation->messengerCount; ++ i) {
        if (pAssociation->pMessengerHandles [i] == messenger) {

            __validation_destroyMessenger (pAssociation->pMessengerHandles [i], pAlloc);
            memmove ( /* NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) */
                    & pAssociation->pMessengerHandles [i],
                    & pAssociation->pMessengerHandles [i + 1],
                    pAssociation->messengerCount -- - i - 1
            );

            break;
        }
    }

    if (pAssociation->messengerCount == 0U) {
        destroyAssociation (pAssociation, pAlloc);
    }
}
