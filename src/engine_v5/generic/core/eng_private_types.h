/*
 * Created by loghin on 04/03/23.
 */

#ifndef __C_ENG_ENG_PRIVATE_TYPES_H__
#define __C_ENG_ENG_PRIVATE_TYPES_H__


#define RESULT_OK                                           ENG_ENUM_FIELD(RESULT_OK)
#define RESULT_ERROR_UNKNOWN                                ENG_ENUM_FIELD(RESULT_ERROR_UNKNOWN)
#define RESULT_ERROR_OUT_OF_MEMORY                          ENG_ENUM_FIELD(RESULT_ERROR_OUT_OF_MEMORY)

#define STRUCTURE_TYPE_ENGINE_CREATE_INFO                   ENG_ENUM_FIELD(STRUCTURE_TYPE_ENGINE_CREATE_INFO)
#define STRUCTURE_TYPE_VALIDATION_MESSAGE_CALLBACK_DATA     ENG_ENUM_FIELD(STRUCTURE_TYPE_VALIDATION_MESSAGE_CALLBACK_DATA)
#define STRUCTURE_TYPE_VALIDATION_MESSENGER_CREATE_INFO     ENG_ENUM_FIELD(STRUCTURE_TYPE_VALIDATION_MESSENGER_CREATE_INFO)

#define SYSTEM_ALLOCATION_SCOPE_ENGINE                      ENG_ENUM_FIELD(SYSTEM_ALLOCATION_SCOPE_ENGINE)

#ifdef __cplusplus
extern "C" {
#endif

typedef ENG_TYPE(Result)                T_Result;
typedef ENG_TYPE(StructureType)         T_StructureType;
typedef ENG_TYPE(SystemAllocationScope) T_SystemAllocationScope;
typedef ENG_TYPE(AllocationFunction)    T_AllocationFunction;
typedef ENG_TYPE(ReallocationFunction)  T_ReallocationFunction;
typedef ENG_TYPE(FreeFunction)          T_FreeFunction;
typedef ENG_TYPE(AllocationCallbacks)   T_AllocationCallbacks;
typedef ENG_TYPE(GenericInStructure)    T_GenericInStructure;
typedef ENG_TYPE(GenericOutStructure)   T_GenericOutStructure;
typedef ENG_TYPE(Flags)                 T_Flags;

#ifdef __cplusplus
}
#endif


#endif /* __C_ENG_ENG_PRIVATE_TYPES_H__ */
