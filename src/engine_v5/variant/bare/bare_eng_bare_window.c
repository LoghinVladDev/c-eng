/*
 * Created by loghin on 04/03/23.
 */

#include <engine.h>
#include <stdio.h>
#include <signal.h>

static SLEngine engine;

void sigCbk (int sigv) {
    slEngineRequestShutdown(engine);
}

int main (int argumentCount, char const * const * ppArguments) {

    (void) argumentCount;
    (void) ppArguments;

    signal (SIGTERM, & sigCbk);
    signal (SIGHUP, & sigCbk);

    SLResult result;

    SLEngineCreateInfo engineCreateInfo = {
            .structureType  = SL_STRUCTURE_TYPE_ENGINE_CREATE_INFO,
            .pNext          = NULL
    };

    result = slCreateEngine (& engine, & engineCreateInfo, NULL);
    if (result != SL_RESULT_OK) {
        fprintf (stderr, "Failed to create engine\n");
        return 1;
    }

    result = slEngineRun (engine);
    if (result != SL_RESULT_OK) {
        fprintf (stderr, "Engine Execution stopped with error\n");
        return 1;
    }

    slDestroyEngine (engine, NULL);

    return 0;
}
