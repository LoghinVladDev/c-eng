//
// Created by loghin on 05/03/23.
//

#ifndef __C_ENG_ENGINE_PRIVATE_H__
#define __C_ENG_ENGINE_PRIVATE_H__


#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_TYPENAME T_ValidationMessenger
#include <templates/util_t_array.h>

typedef ENG_TYPE(Engine)                T_Engine;
typedef ENG_TYPE(EngineMainCallbacks)   T_EngineMainCallbacks;
typedef ENG_TYPE(EngineCreateInfo)      T_EngineCreateInfo;


#define createEngine            ENG_SYM(CreateEngine)
#define destroyEngine           ENG_SYM(DestroyEngine)
#define engineRun               ENG_SYM(EngineRun)
#define engineRequestShutdown   ENG_SYM(EngineRequestShutdown)
#define engineGetApiInfo        ENG_SYM(EngineGetApiInfo)

#define __ENG_FSIGN_createEngine            __ENG_STRINGIFY(createEngine)
#define __ENG_FSIGN_destroyEngine           __ENG_STRINGIFY(destroyEngine)
#define __ENG_FSIGN_engineRun               __ENG_STRINGIFY(engineRun)
#define __ENG_FSIGN_engineRequestShutdown   __ENG_STRINGIFY(engineRequestShutdown)
#define __ENG_FSIGN_engineGetApiInfo        __ENG_STRINGIFY(EngineGetApiInfo)


typedef struct {
    T_ARRAY(T_ValidationMessenger)  validationMessengers;
} S_EngineTrackedResources;


__ENG_HANDLE(ENG_TYPE(Engine)) {
    T_EngineMainCallbacks               mainCallbacks;
    bool                                shutdownRequested;
    void                              * pUserData;
    T_ApiInfo                           apiInfo;
    T_ValidationMessenger               localValidationMessenger;
    S_EngineTrackedResources          * pTrackedResources;
};

typedef __ENG_HANDLE(ENG_TYPE(Engine))  S_PrivateEngine;


#ifdef __cplusplus
}
#endif

#endif //__C_ENG_ENGINE_PRIVATE_H__
