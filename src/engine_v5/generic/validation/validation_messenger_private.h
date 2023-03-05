//
// Created by loghin on 05/03/23.
//

#ifndef __C_ENG_VALIDATION_MESSENGER_PRIVATE_H__
#define __C_ENG_VALIDATION_MESSENGER_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

__ENG_HANDLE(ENG_TYPE(ValidationMessenger)) {
    T_ValidationMessengerCreateFlags    createFlags;
    T_ValidationMessengerCallback       callback;
    T_ValidationMessageTypeFlags        typeFlags;
    T_ValidationMessageSeverityFlags    severityFlags;
    void                              * pUserData;
};

static inline T_ValidationMessenger __validation_createMessenger (
        T_ValidationMessengerCreateInfo const * pCreateInfo,
        T_AllocationCallbacks           const * pAllocationCallbacks
) {

    T_ValidationMessenger messenger = pAllocationCallbacks->pfnAllocation (
            pAllocationCallbacks->pUserData,
            sizeof (S_PrivateValidationMessenger),
            _Alignof (S_PrivateValidationMessenger),
            SYSTEM_ALLOCATION_SCOPE_ENGINE
    );

    if (messenger == NULL) {
        return NULL;
    }

    messenger->createFlags      = pCreateInfo->flags;
    messenger->callback         = pCreateInfo->messengerCallback;
    messenger->typeFlags        = pCreateInfo->messageTypeFlags;
    messenger->severityFlags    = pCreateInfo->messageSeverityFlags;
    messenger->pUserData        = pCreateInfo->pUserData;

    return messenger;
}


static inline void __validation_destroyMessenger (
        T_ValidationMessenger                   messenger,
        T_AllocationCallbacks           const * pAllocationCallbacks
) {

    pAllocationCallbacks->pfnFree (pAllocationCallbacks->pUserData, messenger);
}

#ifdef __cplusplus
}
#endif

#endif //__C_ENG_VALIDATION_MESSENGER_PRIVATE_H__
