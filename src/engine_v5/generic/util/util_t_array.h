//
// Created by loghin on 05/03/23.
//

#include <string.h>

#ifndef ARRAY_TYPENAME
#error Must define the ARRAY_TYPENAME macro to represent the array content type
#endif


#ifndef __ENGINE_ARRAY_EXPANDERS__
#define __ENGINE_ARRAY_EXPANDERS__
#define T_ARRAY(_type)                      __T_Array_ ## _type
#define T_ARRAY_INIT(_type)                 __T_Array_ ## _type ## _init
#define T_ARRAY_ENLARGE_IF_REQUIRED(_type)  __T_Array_ ## _type ## _enlargeIfRequired
#define T_ARRAY_CLEAR(_type)                __T_Array_ ## _type ## _clear
#define T_ARRAY_SIZE(_type)                 __T_Array_ ## _type ## _size
#define T_ARRAY_GET(_type)                  __T_Array_ ## _type ## _get
#define T_ARRAY_PUSH(_type)                 __T_Array_ ## _type ## _push
#define T_ARRAY_EMPTY(_type)                __T_Array_ ## _type ## _empty
#define T_ARRAY_REMOVE(_type)               __T_Array_ ## _type ## _remove
#endif


#define __LATE_PARSE(_call, ...) _call(__VA_ARGS__)


#define __DEFINE_ARRAY_TYPE(_type)  \
typedef struct {                    \
    _type     * pData;              \
    uint32_t    size;               \
    uint32_t    capacity;           \
} T_ARRAY(_type);


#define __DEFINE_ARRAY_INIT(_type)                                  \
static inline T_Result T_ARRAY_INIT(_type) (                        \
        T_ARRAY(_type)                * pArray,                     \
        uint32_t                        startingCapacity,           \
        T_AllocationCallbacks   const * pAllocationCallbacks        \
) {                                                                 \
                                                                    \
    pArray->pData       = NULL;                                     \
    pArray->size        = 0U;                                       \
    pArray->capacity    = startingCapacity;                         \
    if (startingCapacity != 0U) {                                   \
        pArray->pData = pAllocationCallbacks->pfnAllocation (       \
            pAllocationCallbacks->pUserData,                        \
            sizeof (_type) * startingCapacity,                      \
            _Alignof (_type),                                       \
            SYSTEM_ALLOCATION_SCOPE_ENGINE                          \
        );                                                          \
                                                                    \
        if (pArray->pData == NULL) {                                \
            return RESULT_ERROR_OUT_OF_MEMORY;                      \
        }                                                           \
    }                                                               \
                                                                    \
    return RESULT_OK;                                               \
}


#define __DEFINE_ARRAY_ENLARGE_IF_REQUIRED(_type)                   \
static inline T_Result T_ARRAY_ENLARGE_IF_REQUIRED(_type) (         \
        T_ARRAY(_type)                * pArray,                     \
        uint32_t                        requiredSize,               \
        T_AllocationCallbacks   const * pAllocationCallbacks        \
) {                                                                 \
                                                                    \
    if (pArray->size + requiredSize <= pArray->capacity) {          \
        return RESULT_OK;                                           \
    }                                                               \
                                                                    \
    uint32_t newCapacity =                                          \
            pArray->capacity * 2U > pArray->size + requiredSize ?   \
            pArray->capacity * 2U :                                 \
            pArray->size + requiredSize;                            \
                                                                    \
    _type * pNewData = pAllocationCallbacks->pfnReallocation (      \
            pAllocationCallbacks->pUserData,                        \
            pArray->pData,                                          \
            sizeof (_type) * newCapacity,                           \
            _Alignof (_type),                                       \
            SYSTEM_ALLOCATION_SCOPE_ENGINE                          \
    );                                                              \
                                                                    \
    if (pNewData == NULL) {                                         \
        return RESULT_ERROR_OUT_OF_MEMORY;                          \
    }                                                               \
                                                                    \
    pArray->capacity    = newCapacity;                              \
    pArray->pData       = pNewData;                                 \
    return RESULT_OK;                                               \
}


#define __DEFINE_ARRAY_CLEAR(_type)                             \
static inline void T_ARRAY_CLEAR(_type) (                       \
        T_ARRAY(_type)                * pArray,                 \
        T_AllocationCallbacks   const * pAllocationCallbacks    \
) {                                                             \
                                                                \
    pAllocationCallbacks->pfnFree (                             \
            pAllocationCallbacks->pUserData,                    \
            pArray->pData                                       \
    );                                                          \
}


#define __DEFINE_ARRAY_SIZE(_type)              \
static inline uint32_t T_ARRAY_SIZE(_type) (    \
        T_ARRAY(_type) * pArray                 \
) {                                             \
                                                \
    return pArray->size;                        \
}


#define __DEFINE_ARRAY_GET(_type)           \
static inline _type * T_ARRAY_GET(_type) (  \
        T_ARRAY(_type)    * pArray,         \
        uint32_t            index           \
) {                                         \
                                            \
    return & pArray->pData [index];         \
}


#define __DEFINE_ARRAY_PUSH(_type)                                          \
static inline _type * T_ARRAY_PUSH(_type) (                                 \
        T_ARRAY(_type)                * pArray,                             \
        T_AllocationCallbacks   const * pAllocationCallbacks                \
) {                                                                         \
                                                                            \
    if (RESULT_ERROR_OUT_OF_MEMORY == T_ARRAY_ENLARGE_IF_REQUIRED(_type) (  \
            pArray,                                                         \
            1U,                                                             \
            pAllocationCallbacks                                            \
    )) {                                                                    \
        return NULL;                                                        \
    }                                                                       \
                                                                            \
    return & pArray->pData [pArray->size ++];                               \
}



#define __DEFINE_ARRAY_EMPTY(_type)             \
static inline bool T_ARRAY_EMPTY(_type) (       \
        T_ARRAY(_type)    * pArray              \
) {                                             \
                                                \
    return T_ARRAY_SIZE(_type) (pArray) == 0U;  \
}


#define __DEFINE_ARRAY_REMOVE(_type)        \
static inline void T_ARRAY_REMOVE(_type) (  \
        T_ARRAY(_type) * pArray,            \
        uint32_t index                      \
) {                                         \
                                            \
    (void) memmove (                        \
            pArray->pData [index],          \
            pArray->pData [index + 1U],     \
            pArray->size - index - 1U       \
    );                                      \
}


__LATE_PARSE(__DEFINE_ARRAY_TYPE, ARRAY_TYPENAME)
__LATE_PARSE(__DEFINE_ARRAY_INIT, ARRAY_TYPENAME)
__LATE_PARSE(__DEFINE_ARRAY_ENLARGE_IF_REQUIRED, ARRAY_TYPENAME)
__LATE_PARSE(__DEFINE_ARRAY_CLEAR, ARRAY_TYPENAME)
__LATE_PARSE(__DEFINE_ARRAY_SIZE, ARRAY_TYPENAME)
__LATE_PARSE(__DEFINE_ARRAY_GET, ARRAY_TYPENAME)
__LATE_PARSE(__DEFINE_ARRAY_PUSH, ARRAY_TYPENAME)
__LATE_PARSE(__DEFINE_ARRAY_EMPTY, ARRAY_TYPENAME)
__LATE_PARSE(__DEFINE_ARRAY_REMOVE, ARRAY_TYPENAME)


#undef __LATE_PARSE
#undef __DEFINE_ARRAY_TYPE
#undef __DEFINE_ARRAY_CLEAR
#undef __DEFINE_ARRAY_ENLARGE_IF_REQUIRED
#undef __DEFINE_ARRAY_INIT
#undef __DEFINE_ARRAY_SIZE
#undef __DEFINE_ARRAY_GET
#undef __DEFINE_ARRAY_PUSH
#undef __DEFINE_ARRAY_EMPTY
#undef __DEFINE_ARRAY_REMOVE
#undef ARRAY_TYPENAME

