//
// Created by loghin on 05/03/23.
//

#ifndef __C_ENG_ENGINE_PRIVATE_H__
#define __C_ENG_ENGINE_PRIVATE_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef ENG_TYPE(Engine)                T_Engine;
typedef ENG_TYPE(EngineMainCallbacks)   T_EngineMainCallbacks;
typedef ENG_TYPE(EngineCreateInfo)      T_EngineCreateInfo;


#define createEngine            ENG_SYM(CreateEngine)
#define destroyEngine           ENG_SYM(DestroyEngine)
#define engineRun               ENG_SYM(EngineRun)
#define engineRequestShutdown   ENG_SYM(EngineRequestShutdown)



__ENG_HANDLE(ENG_TYPE(Engine)) {
    T_EngineMainCallbacks               mainCallbacks;
    bool                                shutdownRequested;
    void                              * pUserData;
    T_ValidationMessenger               localValidationMessenger;
};

typedef __ENG_HANDLE(ENG_TYPE(Engine))  S_PrivateEngine;


#ifdef __cplusplus
}
#endif

#endif //__C_ENG_ENGINE_PRIVATE_H__
