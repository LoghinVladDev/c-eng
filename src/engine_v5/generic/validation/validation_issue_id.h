//
// Created by loghin on 05/03/23.
//

#ifndef __C_ENG_VALIDATION_ISSUE_ID_H__
#define __C_ENG_VALIDATION_ISSUE_ID_H__

#define VALIDATION_ISSUE_ID_VALIDATION_MESSENGER_NOT_DESTROYED ((T_ValidationIssueId) 0U)


#define VALIDATION_ISSUE_ID_INVALID_GROUP       (0xFF000000U)
#define VALIDATION_ISSUE_ID_INVALID_CATEGORY    (0x00FF0000U)
#define VALIDATION_ISSUE_ID_INVALID_ID          (0x0000FFFFU)


#define VALIDATION_ISSUE_FULL_ID(_g, _c, _i) (  \
        ((_g) & 0xFF000000U) |                  \
        ((_c) & 0x00FF0000U) |                  \
        ((_i) & 0x0000FFFFU)                    \
)

#endif //__C_ENG_VALIDATION_ISSUE_ID_H__
