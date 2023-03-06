//
// Created by loghin on 05/03/23.
//

#ifndef __C_ENG_VALIDATION_ISSUES_H__
#define __C_ENG_VALIDATION_ISSUES_H__


typedef struct S_ValidationIssue_tag const * S_ValidationIssuePtr;

typedef char * (* PFN_ComposeValidationIssueMessage) (
        S_ValidationIssuePtr    pIssue,
        char                  * pMessageBuffer,
        uint32_t                messageBufferLength,
        void            const * pSignaller,
        void            const * pCauseData
);


typedef struct S_ValidationIssue_tag {
    T_ValidationMessageTypeFlags        typeFlags;
    T_ValidationMessageSeverityFlagBits severity;
    PFN_ComposeValidationIssueMessage   composer;
} S_ValidationIssue;

typedef struct {
    S_ValidationIssue           const * pIssues;
    uint32_t                            issueCount;
} S_ValidationIssueCategory;

typedef struct {
    S_ValidationIssueCategory   const * pCategories;
    uint32_t                            categoryCount;
} S_ValidationIssueGroup;

typedef struct {
    S_ValidationIssueGroup      const * pGroups;
    uint32_t                            groupCount;
} T_ValidationIssueSet;

#include <validation_issue_id.h>
#include "validation_issues_engine.h"
#include "validation_issues_validation_messenger.h"

static S_ValidationIssueGroup const validationIssueGroups [] = {
        [VALIDATION_ISSUE_GROUP_ENGINE] = {
                .pCategories    = & validationIssueEngineCategories [0U],
                .categoryCount  = sizeof (validationIssueEngineCategories) / sizeof (validationIssueEngineCategories[0U])
        },
        [VALIDATION_ISSUE_GROUP_VALIDATION_MESSENGER] = {
                .pCategories    = & validationIssueValidationMessengerCategories [0U],
                .categoryCount  = sizeof (validationIssueValidationMessengerCategories) / sizeof (validationIssueValidationMessengerCategories[0U])
        }
};


static T_ValidationIssueSet const validationIssueSet = {
        .pGroups    = & validationIssueGroups [0U],
        .groupCount = sizeof (validationIssueGroups) / sizeof (validationIssueGroups [0U])
};

#endif //__C_ENG_VALIDATION_ISSUES_H__
