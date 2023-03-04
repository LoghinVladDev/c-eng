//
// Created by loghin on 04/03/23.
//

#include "eng_alloc.h"
#include "eng_private_types.h"


static void * internalAlloc (
        void                          * pUserData,
        size_t                          size,
        size_t                          alignment,
        T_SystemAllocationScope         scope
) {

    (void) pUserData;
    (void) alignment;
    (void) scope;

    return malloc (size);
}


static void * internalRealloc (
        void                          * pUserData,
        void                          * pOriginal,
        size_t                          size,
        size_t                          alignment,
        T_SystemAllocationScope         scope
) {

    (void) pUserData;
    (void) alignment;
    (void) scope;

    return realloc (pOriginal, size);
}


static void internalFree (
        void * pUserData,
        void * pMemory
) {

    (void) pUserData;

    free (pMemory);
}


static T_AllocationCallbacks internalAllocationCallbacks = {
        .pUserData          = NULL,
        .pfnAllocation      = & internalAlloc,
        .pfnReallocation    = & internalRealloc,
        .pfnFree            = & internalFree
};


T_AllocationCallbacks const * __allocationCallbacks (
        T_AllocationCallbacks const * pAllocationCallbacks
) {

    if (pAllocationCallbacks != NULL) {
        return pAllocationCallbacks;
    }

    return & internalAllocationCallbacks;
}
