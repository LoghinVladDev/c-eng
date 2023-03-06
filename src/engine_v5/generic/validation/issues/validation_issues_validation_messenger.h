//
// Created by loghin on 06/03/23.
//

#ifndef __C_ENG_VALIDATION_ISSUES_VALIDATION_MESSENGER_H__
#define __C_ENG_VALIDATION_ISSUES_VALIDATION_MESSENGER_H__


static S_ValidationIssue const validationIssueValidationMessengerParameterValues [] = {

};


static S_ValidationIssue const validationIssueValidationMessengerResourceManagement [] = {

};


static S_ValidationIssueCategory const validationIssueValidationMessengerCategories [] = {
        [VALIDATION_ISSUE_CATEGORY_PARAMETER_VALUES] = {
                .pIssues    = & validationIssueValidationMessengerParameterValues [0U],
                .issueCount = sizeof (validationIssueValidationMessengerParameterValues) / sizeof (validationIssueValidationMessengerParameterValues[0U])
        },
        [VALIDATION_ISSUE_CATEGORY_RESOURCE_MANAGEMENT] = {
                .pIssues    = & validationIssueValidationMessengerResourceManagement [0U],
                .issueCount = sizeof (validationIssueValidationMessengerResourceManagement) / sizeof (validationIssueValidationMessengerResourceManagement[0U])
        }
};

#endif //__C_ENG_VALIDATION_ISSUES_VALIDATION_MESSENGER_H__
