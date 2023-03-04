/*
 * Created by loghin on 04/03/23.
 */

#ifndef __C_ENG_ENGINE_H__
#define __C_ENG_ENGINE_H__

#include <eng_types.h>

#ifndef ENG_CNF_STARTING_INSTANCE_CAPACITY
#define ENG_CNF_STARTING_INSTANCE_CAPACITY 8U
#endif

#ifdef __cplusplus
extern "C" {
#endif

__ENG_DEFINE_HANDLE(ENG_TYPE(Engine));


typedef void ( * ENG_TYPE(EngineMainHook) ) (
    ENG_TYPE(Engine) engine
);


typedef struct {
    ENG_TYPE(EngineMainHook)    pfnPreInit;
    ENG_TYPE(EngineMainHook)    pfnPostInit;
    ENG_TYPE(EngineMainHook)    pfnPreUpdate;
    ENG_TYPE(EngineMainHook)    pfnPostUpdate;
    ENG_TYPE(EngineMainHook)    pfnPreShutdown;
    ENG_TYPE(EngineMainHook)    pfnPostShutdown;
} ENG_TYPE(EngineMainCallbacks);


typedef struct {
    ENG_TYPE(StructureType)         structureType;
    void                    const * pNext;
    ENG_TYPE(EngineMainCallbacks)   mainCallbacks;
} ENG_TYPE(EngineCreateInfo);


extern ENG_TYPE(Result) ENG_SYM(CreateEngine) (
        ENG_TYPE(Engine)                      * pEngine,
        ENG_TYPE(EngineCreateInfo)      const * pCreateInfo,
        ENG_TYPE(AllocationCallbacks)   const * pAllocationCallbacks
);


extern void ENG_SYM(DestroyEngine) (
        ENG_TYPE(Engine)                        engine,
        ENG_TYPE(AllocationCallbacks)   const * pAllocationCallbacks
);


extern ENG_TYPE(Result) ENG_SYM(EngineRun) (
        ENG_TYPE(Engine)    engine
);


extern void ENG_SYM(EngineRequestShutdown) (
        ENG_TYPE(Engine)    engine
);


#ifdef __cplusplus
}
#endif


#endif /* __C_ENG_ENGINE_H__ */
