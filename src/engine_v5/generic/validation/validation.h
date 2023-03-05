//
// Created by loghin on 05/03/23.
//

#ifndef __C_ENG_VALIDATION_H__
#define __C_ENG_VALIDATION_H__

#include <engine.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

__ENG_DEFINE_HANDLE(ENG_TYPE(ValidationMessenger));


typedef enum {
    ENG_ENUM_VALUED_FIELD(VALIDATION_MESSENGER_CREATE_ENABLE_RENDERER_MESSENGER_BIT,    0x00000001U)
} ENG_TYPE(ValidationMessengerCreateFlagBits);


typedef enum {
    ENG_ENUM_VALUED_FIELD(VALIDATION_MESSAGE_SEVERITY_VERBOSE_BIT,  0x00000001U),
    ENG_ENUM_VALUED_FIELD(VALIDATION_MESSAGE_SEVERITY_INFO_BIT,     0x00000002U),
    ENG_ENUM_VALUED_FIELD(VALIDATION_MESSAGE_SEVERITY_WARNING_BIT,  0x00000004U),
    ENG_ENUM_VALUED_FIELD(VALIDATION_MESSAGE_SEVERITY_ERROR_BIT,    0x00000008U),
} ENG_TYPE(ValidationMessageSeverityFlagBits);

typedef enum {
    ENG_ENUM_VALUED_FIELD(VALIDATION_MESSAGE_TYPE_GENERAL_BIT,      0x00000001U),
    ENG_ENUM_VALUED_FIELD(VALIDATION_MESSAGE_TYPE_VALIDATION_BIT,   0x00000002U),
    ENG_ENUM_VALUED_FIELD(VALIDATION_MESSAGE_TYPE_PERFORMANCE_BIT,  0x00000004U)
} ENG_TYPE(ValidationMessageTypeFlagBits);


typedef enum {
    ENG_ENUM_FIELD(VALIDATION_ISSUE_CATEGORY_PARAMETER_VALUES),
    ENG_ENUM_FIELD(VALIDATION_ISSUE_CATEGORY_RESOURCE_MANAGEMENT)
} ENG_TYPE(ValidationIssueCategory);


typedef enum {
    ENG_ENUM_FIELD(VALIDATION_ISSUE_GROUP_ENGINE),
    ENG_ENUM_FIELD(VALIDATION_ISSUE_GROUP_VALIDATION_MESSENGER)
} ENG_TYPE(ValidationIssueGroup);


typedef uint16_t ENG_TYPE(ValidationIssueId);


typedef ENG_TYPE(Flags) ENG_TYPE(ValidationMessageSeverityFlags);
typedef ENG_TYPE(Flags) ENG_TYPE(ValidationMessageTypeFlags);
typedef ENG_TYPE(Flags) ENG_TYPE(ValidationMessengerCreateFlags);


typedef struct {
    ENG_TYPE(StructureType)         structureType;
    void                    const * pNext;
    ENG_TYPE(ApiInfo)       const * pSourceApiInfo;
    uint32_t                        messageId;
    char                    const * pMessage;
} ENG_TYPE(ValidationMessageCallbackData);


typedef bool (* ENG_TYPE(ValidationMessengerCallback)) (
        void                                          * pUserData,
        ENG_TYPE(ValidationMessageSeverityFlagBits)     messageSeverity,
        ENG_TYPE(ValidationMessageTypeFlags)            messageTypeFlags,
        ENG_TYPE(ValidationMessageCallbackData) const * pCallbackData
);


typedef struct {
    ENG_TYPE(StructureType)                     structureType;
    void                                const * pNext;
    ENG_TYPE(ValidationMessengerCreateFlags)    flags;
    ENG_TYPE(ValidationMessageSeverityFlags)    messageSeverityFlags;
    ENG_TYPE(ValidationMessageTypeFlags)        messageTypeFlags;
    ENG_TYPE(ValidationMessengerCallback)       messengerCallback;
    void                                      * pUserData;
} ENG_TYPE(ValidationMessengerCreateInfo);


extern ENG_TYPE(Result) ENG_SYM(CreateValidationMessenger) (
        ENG_TYPE(Engine)                                engine,
        ENG_TYPE(ValidationMessengerCreateInfo) const * pCreateInfo,
        ENG_TYPE(AllocationCallbacks)           const * pAllocationCallbacks,
        ENG_TYPE(ValidationMessenger)                 * pMessenger
);


extern void ENG_SYM(DestroyValidationMessenger) (
        ENG_TYPE(Engine)                        engine,
        ENG_TYPE(ValidationMessenger)           validationMessenger,
        ENG_TYPE(AllocationCallbacks)   const * pAllocationCallbacks
);


extern void ENG_SYM(RaiseValidationIssue) (
        ENG_TYPE(Engine)                        engine,
        ENG_TYPE(ValidationIssueGroup)          group,
        ENG_TYPE(ValidationIssueCategory)       category,
        ENG_TYPE(ValidationIssueId)             identifier
);


extern void ENG_SYM(RaiseValidationIssueDirect) (
        ENG_TYPE(ValidationMessenger)           messenger,
        ENG_TYPE(ValidationIssueGroup)          group,
        ENG_TYPE(ValidationIssueCategory)       category,
        ENG_TYPE(ValidationIssueId)             identifier
);

#ifdef __cplusplus
}
#endif

#endif //__C_ENG_VALIDATION_H__
