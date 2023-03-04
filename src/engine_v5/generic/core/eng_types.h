/*
 * Created by loghin on 04/03/23.
 */

#ifndef __C_ENG_ENG_TYPES_H__
#define __C_ENG_ENG_TYPES_H__

#include "eng_prepro.h"
#include "stdint.h"
#include "stdlib.h"

#ifndef ENG_TYPE_TOKEN_PREFIX
#define ENG_TYPE_TOKEN_PREFIX SL
#endif

#ifndef ENG_SYM_TOKEN_PREFIX
#define ENG_SYM_TOKEN_PREFIX sl
#endif


#ifndef ENG_ENUM_FIELD_TOKEN_PREFIX
#define ENG_ENUM_FIELD_TOKEN_PREFIX             __ENG_CONCAT(ENG_TYPE_TOKEN_PREFIX, _)
#endif


#define ENG_TYPE(_type)                         __ENG_CONCAT(ENG_TYPE_TOKEN_PREFIX, _type)
#define ENG_SYM(_sym)                           __ENG_CONCAT(ENG_SYM_TOKEN_PREFIX, _sym)

#define ENG_ENUM_FIELD(_field)                  __ENG_CONCAT(ENG_ENUM_FIELD_TOKEN_PREFIX, _field)
#define ENG_ENUM_VALUED_FIELD(_field, _value)   __ENG_CONCAT(ENG_ENUM_FIELD_TOKEN_PREFIX, _field) = _value



#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ENG_ENUM_VALUED_FIELD(RESULT_OK, 0),
    ENG_ENUM_VALUED_FIELD(RESULT_ERROR_UNKNOWN, -1),
    ENG_ENUM_VALUED_FIELD(RESULT_ERROR_OUT_OF_MEMORY, -2)
} ENG_TYPE(Result);


typedef enum {
    ENG_ENUM_VALUED_FIELD(STRUCTURE_TYPE_ENGINE_CREATE_INFO, 1)
} ENG_TYPE(StructureType);


typedef enum {
    ENG_ENUM_FIELD(SYSTEM_ALLOCATION_SCOPE_ENGINE)
} ENG_TYPE(SystemAllocationScope);


typedef void * ( * ENG_TYPE(AllocationFunction) ) (
        void                          * pUserData,
        size_t                          size,
        size_t                          alignment,
        ENG_TYPE(SystemAllocationScope) scope
);


typedef void * ( * ENG_TYPE(ReallocationFunction) ) (
        void                          * pUserData,
        void                          * pOriginal,
        size_t                          size,
        size_t                          alignment,
        ENG_TYPE(SystemAllocationScope) scope
);


typedef void ( * ENG_TYPE(FreeFunction) ) (
        void                          * pUserData,
        void                          * pMemory
);


typedef struct {
    void                          * pUserData;
    ENG_TYPE(AllocationFunction)    pfnAllocation;
    ENG_TYPE(ReallocationFunction)  pfnReallocation;
    ENG_TYPE(FreeFunction)          pfnFree;
} ENG_TYPE(AllocationCallbacks);


typedef struct ENG_TYPE(GenericInStructure_Tag) {
    ENG_TYPE(StructureType)                             structureType;
    struct ENG_TYPE(GenericInStructure_Tag)     const * pNext;
} ENG_TYPE(GenericInStructure);


typedef struct ENG_TYPE(GenericOutStructure_Tag) {
    ENG_TYPE(StructureType)                             structureType;
    struct ENG_TYPE(GenericOutStructure_Tag)          * pNext;
} ENG_TYPE(GenericOutStructure);



#ifdef __cplusplus
}
#endif


#endif /* __C_ENG_ENG_TYPES_H__ */
