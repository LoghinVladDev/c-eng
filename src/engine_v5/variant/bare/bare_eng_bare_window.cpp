/*
 * Created by loghin on 04/03/23.
 */

#include <engine.h>
#include <cstdio>
#include <csignal>
#include <validation.h>

struct UserData {

};

static SLEngine engine;

auto sigCbk (int sigv) -> void {
    slEngineRequestShutdown(engine);
}

auto preInit (void * pUserData, SLEngine lEngine) noexcept -> void {
    auto * pData = (UserData *) pUserData;
}

auto preUpdate (void * pUserData, SLEngine lEngine) noexcept -> void {
    auto * pData = (UserData *) pUserData;
}

auto postShutdown (void * pUserData, SLEngine lEngine) noexcept -> void {
    auto * pData = (UserData *) pUserData;
}

auto validationMessage (
        void                                      * pUserData,
        SLValidationMessageSeverityFlagBits         messageSeverity,
        SLValidationMessageTypeFlags                messageTypeFlags,
        SLValidationMessageCallbackData     const * pCallbackData
) noexcept -> bool {

    (void) pUserData;
    (void) messageSeverity;
    (void) messageTypeFlags;
    (void) pCallbackData;

    fprintf(stdout, "test\n");

    return false;
}

auto main (int argumentCount, char const * const * ppArguments) -> int {

    (void) argumentCount;
    (void) ppArguments;

    signal (SIGTERM, & sigCbk);
    signal (SIGHUP, & sigCbk);

    SLResult result;
    SLValidationMessenger validationMessenger;

    UserData userData = {

    };

    SLValidationMessengerCreateInfo validationMessengerCreateInfo = {
            .structureType          = SLStructureType :: SL_STRUCTURE_TYPE_VALIDATION_MESSENGER_CREATE_INFO,
            .pNext                  = nullptr,
            .flags                  = SLValidationMessengerCreateFlagBits :: SL_VALIDATION_MESSENGER_CREATE_ENABLE_RENDERER_MESSENGER_BIT,
            .messageSeverityFlags   =
                    SLValidationMessageSeverityFlagBits :: SL_VALIDATION_MESSAGE_SEVERITY_VERBOSE_BIT   |
                    SLValidationMessageSeverityFlagBits :: SL_VALIDATION_MESSAGE_SEVERITY_INFO_BIT      |
                    SLValidationMessageSeverityFlagBits :: SL_VALIDATION_MESSAGE_SEVERITY_WARNING_BIT   |
                    SLValidationMessageSeverityFlagBits :: SL_VALIDATION_MESSAGE_SEVERITY_ERROR_BIT,
            .messageTypeFlags       =
                    SLValidationMessageTypeFlagBits :: SL_VALIDATION_MESSAGE_TYPE_GENERAL_BIT           |
                    SLValidationMessageTypeFlagBits :: SL_VALIDATION_MESSAGE_TYPE_VALIDATION_BIT        |
                    SLValidationMessageTypeFlagBits :: SL_VALIDATION_MESSAGE_TYPE_PERFORMANCE_BIT,
            .messengerCallback      = & validationMessage,
            .pUserData              = nullptr
    };

    SLEngineCreateInfo engineCreateInfo = {
            .structureType      = SLStructureType :: SL_STRUCTURE_TYPE_ENGINE_CREATE_INFO,
            .pNext              = & validationMessengerCreateInfo,
            .flags              = 0U,
            .mainCallbacks      = {
                    .pfnPreInit         = & preInit,
                    .pfnPostInit        = nullptr,
                    .pfnPreUpdate       = & preUpdate,
                    .pfnPostUpdate      = nullptr,
                    .pfnPreShutdown     = nullptr,
                    .pfnPostShutdown    = & postShutdown
            },
            .validationEnabled  = true,
            .pUserData          = & userData
    };

    result = slCreateEngine (& engineCreateInfo, nullptr, & engine);
    if (result != SL_RESULT_OK) {
        fprintf (stderr, "Failed to create engine\n");
        return 1;
    }

    result = slCreateValidationMessenger (engine, & validationMessengerCreateInfo, nullptr, & validationMessenger);
    if (result != SL_RESULT_OK) {
        fprintf (stderr, "Failed to create validation messenger\n");
        slDestroyEngine (engine, nullptr);
        return 1;
    }

    result = slEngineRun (engine);
    if (result != SL_RESULT_OK) {
        fprintf (stderr, "Engine Execution stopped with error\n");
        return 1;
    }

//    slDestroyValidationMessenger (engine, validationMessenger, nullptr);
    slDestroyEngine (engine, nullptr);

    return 0;
}
