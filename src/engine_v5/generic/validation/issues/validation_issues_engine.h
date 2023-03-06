//
// Created by loghin on 06/03/23.
//

#ifndef __C_ENG_VALIDATION_ISSUES_ENGINE_H__
#define __C_ENG_VALIDATION_ISSUES_ENGINE_H__


static char * validationIssueEngineMessengerMemoryLeakCompose (
        S_ValidationIssuePtr    pIssue,
        char                  * pMessageBuffer,
        uint32_t                messageBufferLength,
        void            const * pSignaller,
        void            const * pCauseData
) {

    (void) pIssue;

    snprintf (
            pMessageBuffer,
            messageBufferLength,
            "ValidationMessenger '%p' of Engine '%p' has not been destroyed. Call '"
            __ENG_FSIGN_destroyValidationMessenger
            "' prior to calling '"
            __ENG_FSIGN_destroyEngine
            "' for each object created from the parent",
            pSignaller,
            pCauseData
    );
}


static S_ValidationIssue const validationIssueEngineParameterValues [] = {

};


static S_ValidationIssue const validationIssueEngineResourceManagement [] = {
        [VALIDATION_ISSUE_ID_VALIDATION_MESSENGER_NOT_DESTROYED] = {
                .typeFlags  = VALIDATION_MESSAGE_TYPE_VALIDATION_BIT,
                .severity   = VALIDATION_MESSAGE_SEVERITY_WARNING_BIT,
                .composer   = & validationIssueEngineMessengerMemoryLeakCompose
        }
};


static S_ValidationIssueCategory const validationIssueEngineCategories [] = {
        [VALIDATION_ISSUE_CATEGORY_PARAMETER_VALUES] = {
                .pIssues    = & validationIssueEngineParameterValues [0U],
                .issueCount = sizeof (validationIssueEngineParameterValues) / sizeof (validationIssueEngineParameterValues[0U])
        },
        [VALIDATION_ISSUE_CATEGORY_RESOURCE_MANAGEMENT] = {
                .pIssues    = & validationIssueEngineResourceManagement [0U],
                .issueCount = sizeof (validationIssueEngineResourceManagement) / sizeof (validationIssueEngineResourceManagement[0U])
        }
};

#endif //__C_ENG_VALIDATION_ISSUES_ENGINE_H__
