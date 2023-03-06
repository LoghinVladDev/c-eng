/*
 * Created by loghin on 04/03/23.
 */

#include <engine.h>
#include <cstdio>
#include <csignal>
#include <validation.h>
#include <variant/util/hl_logging/BasicLogger.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

struct UserData {

};

static SLEngine gEngine;

auto sigCbk (int sigv) -> void {
    slEngineRequestShutdown(gEngine);
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

static engine::io::Logger::Level const logLevelMap (SLValidationMessageSeverityFlagBits severity) {

    if (severity == SL_VALIDATION_MESSAGE_SEVERITY_ERROR_BIT)   return engine::io::Logger::Error;
    if (severity == SL_VALIDATION_MESSAGE_SEVERITY_WARNING_BIT) return engine::io::Logger::Warning;
    if (severity == SL_VALIDATION_MESSAGE_SEVERITY_INFO_BIT)    return engine::io::Logger::Info;
    if (severity == SL_VALIDATION_MESSAGE_SEVERITY_VERBOSE_BIT) return engine::io::Logger::Debug;
    return engine::io::Logger::Level::Info;
};

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

    auto sev2S = [](auto severity) {
        switch (severity) {
            case SL_VALIDATION_MESSAGE_SEVERITY_ERROR_BIT: return "ERR";
            case SL_VALIDATION_MESSAGE_SEVERITY_WARNING_BIT: return "WRN";
            case SL_VALIDATION_MESSAGE_SEVERITY_INFO_BIT: return "INF";
            case SL_VALIDATION_MESSAGE_SEVERITY_VERBOSE_BIT: return "VRB";
        }

        return "UNK";
    };

    auto typ2S = [](auto typeFlags) {

        cds::String s;
        if (typeFlags & SL_VALIDATION_MESSAGE_TYPE_GENERAL_BIT) s += ", general";
        if (typeFlags & SL_VALIDATION_MESSAGE_TYPE_VALIDATION_BIT) s += ", validation";
        if (typeFlags & SL_VALIDATION_MESSAGE_TYPE_PERFORMANCE_BIT) s += ", performance";

        return s.substr(2);
    };

    auto pLogger = static_cast < engine::io::Logger * > (pUserData);

    pLogger->log (
            logLevelMap(messageSeverity),
            cds::String::f (
                    "[%s - %s] %s: %d-%s\n",
                    sev2S (messageSeverity),
                    typ2S (messageTypeFlags).cStr(),
                    pCallbackData->pSourceApiInfo->pApiName,
                    pCallbackData->messageId,
                    pCallbackData->pMessage
            )
    );

    return false;
}

auto main (int argumentCount, char const * const * ppArguments) -> int {

    (void) argumentCount;
    (void) ppArguments;

    if (!std::filesystem::exists("log")) {
        std::filesystem::create_directory("log");
    }

    char timeBuffer [512U];
    strcpy (timeBuffer, "./log/");
    tm timeStruct;
    auto time = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());

#if defined(__CDS_Platform_Linux)
    localtime_r ( & time, & timeStruct );
#else
    localtime_s ( & timeStruct, & time );
#endif

    (void) std::strftime (
            timeBuffer + 6, 512U,
            "%d-%m-%Y-%H:%M:%S",
            & timeStruct
    );

    std::filesystem::create_directory(timeBuffer);

    std :: ofstream outGlobal (std::string(timeBuffer) + "/all.log");
    std :: ofstream outEngine (std::string(timeBuffer) + "/engine.log");
    std :: ofstream outGlfw (std::string(timeBuffer) + "/glfw.log");

    engine::io::BasicLogger engineLogger ("Engine Logger");
    engineLogger.addOutput (std::cout);
    engineLogger.addOutput (outGlobal);
    engineLogger.addOutput (outEngine);

    engine::io::BasicLogger glfwLogger ("GLFW Logger");
    glfwLogger.addOutput (std::cout);
    glfwLogger.addOutput (outGlobal);
    glfwLogger.addOutput (outGlfw);

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
            .pUserData              = & engineLogger
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

    result = slCreateEngine (& engineCreateInfo, nullptr, & gEngine);
    if (result != SL_RESULT_OK) {
        fprintf (stderr, "Failed to create engine\n");
        return 1;
    }

    result = slCreateValidationMessenger (gEngine, & validationMessengerCreateInfo, nullptr, & validationMessenger);
    if (result != SL_RESULT_OK) {
        fprintf (stderr, "Failed to create validation messenger\n");
        slDestroyEngine (gEngine, nullptr);
        return 1;
    }

    result = slEngineRun (gEngine);
    if (result != SL_RESULT_OK) {
        fprintf (stderr, "Engine Execution stopped with error\n");
        return 1;
    }

//    slDestroyValidationMessenger (engine, validationMessenger, nullptr);
    slDestroyEngine (gEngine, nullptr);

    return 0;
}
