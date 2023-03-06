//
// Created by loghin on 05/03/23.
//

#ifndef __C_ENG_VALIDATION_PRIVATE_H__
#define __C_ENG_VALIDATION_PRIVATE_H__


#define VALIDATION_MESSENGER_MESSAGE_BUFFER_LENGTH                  512

#define VALIDATION_MESSENGER_CREATE_ENABLE_RENDERER_MESSENGER_BIT   ENG_ENUM_FIELD(VALIDATION_MESSENGER_CREATE_ENABLE_RENDERER_MESSENGER_BIT)

#define VALIDATION_MESSAGE_SEVERITY_VERBOSE_BIT                     ENG_ENUM_FIELD(VALIDATION_MESSAGE_SEVERITY_VERBOSE_BIT)
#define VALIDATION_MESSAGE_SEVERITY_INFO_BIT                        ENG_ENUM_FIELD(VALIDATION_MESSAGE_SEVERITY_INFO_BIT)
#define VALIDATION_MESSAGE_SEVERITY_WARNING_BIT                     ENG_ENUM_FIELD(VALIDATION_MESSAGE_SEVERITY_WARNING_BIT)
#define VALIDATION_MESSAGE_SEVERITY_ERROR_BIT                       ENG_ENUM_FIELD(VALIDATION_MESSAGE_SEVERITY_ERROR_BIT)

#define VALIDATION_MESSAGE_TYPE_GENERAL_BIT                         ENG_ENUM_FIELD(VALIDATION_MESSAGE_TYPE_GENERAL_BIT)
#define VALIDATION_MESSAGE_TYPE_VALIDATION_BIT                      ENG_ENUM_FIELD(VALIDATION_MESSAGE_TYPE_VALIDATION_BIT)
#define VALIDATION_MESSAGE_TYPE_PERFORMANCE_BIT                     ENG_ENUM_FIELD(VALIDATION_MESSAGE_TYPE_PERFORMANCE_BIT)


#define VALIDATION_ISSUE_CATEGORY_PARAMETER_VALUES                  ENG_ENUM_FIELD(VALIDATION_ISSUE_CATEGORY_PARAMETER_VALUES)
#define VALIDATION_ISSUE_CATEGORY_RESOURCE_MANAGEMENT               ENG_ENUM_FIELD(VALIDATION_ISSUE_CATEGORY_RESOURCE_MANAGEMENT)

#define VALIDATION_ISSUE_GROUP_ENGINE                               ENG_ENUM_FIELD(VALIDATION_ISSUE_GROUP_ENGINE)
#define VALIDATION_ISSUE_GROUP_VALIDATION_MESSENGER                 ENG_ENUM_FIELD(VALIDATION_ISSUE_GROUP_VALIDATION_MESSENGER)


#define createValidationMessenger ENG_SYM(CreateValidationMessenger)
#define destroyValidationMessenger ENG_SYM(DestroyValidationMessenger)
#define raiseValidationIssue ENG_SYM(RaiseValidationIssue)
#define raiseValidationIssueDirect ENG_SYM(RaiseValidationIssueDirect)

#define __ENG_FSIGN_createValidationMessenger   __ENG_STRINGIFY(createValidationMessenger)
#define __ENG_FSIGN_destroyValidationMessenger  __ENG_STRINGIFY(destroyValidationMessenger)
#define __ENG_FSIGN_raiseValidationIssue        __ENG_STRINGIFY(raiseValidationIssue)
#define __ENG_FSIGN_raiseValidationIssueDirect  __ENG_STRINGIFY(raiseValidationIssueDirect)


#ifdef __cplusplus
extern "C" {
#endif


typedef __ENG_HANDLE(ENG_TYPE(ValidationMessenger)) S_PrivateValidationMessenger;
typedef ENG_TYPE(ValidationMessenger)               T_ValidationMessenger;
typedef ENG_TYPE(ValidationMessengerCreateFlagBits) T_ValidationMessengerCreateFlagBits;
typedef ENG_TYPE(ValidationMessageSeverityFlagBits) T_ValidationMessageSeverityFlagBits;
typedef ENG_TYPE(ValidationMessageTypeFlagBits)     T_ValidationMessageTypeFlagBits;
typedef ENG_TYPE(ValidationMessageSeverityFlags)    T_ValidationMessageSeverityFlags;
typedef ENG_TYPE(ValidationMessageTypeFlags)        T_ValidationMessageTypeFlags;
typedef ENG_TYPE(ValidationMessengerCreateFlags)    T_ValidationMessengerCreateFlags;
typedef ENG_TYPE(ValidationMessageCallbackData)     T_ValidationMessageCallbackData;
typedef ENG_TYPE(ValidationMessengerCallback)       T_ValidationMessengerCallback;
typedef ENG_TYPE(ValidationMessengerCreateInfo)     T_ValidationMessengerCreateInfo;
typedef ENG_TYPE(ValidationIssueId)                 T_ValidationIssueId;
typedef ENG_TYPE(ValidationIssueId)                 T_ValidationIssueId;
typedef ENG_TYPE(ValidationIssueGroup)              T_ValidationIssueGroup;
typedef ENG_TYPE(ValidationIssueCategory)           T_ValidationIssueCategory;

#include "validation_messenger_private.h"

#ifdef __cplusplus
}
#endif

#endif //__C_ENG_VALIDATION_PRIVATE_H__
