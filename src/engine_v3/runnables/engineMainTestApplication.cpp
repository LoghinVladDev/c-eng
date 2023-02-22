//
// Created by loghin on 18.12.2021.
//

#include <Logger.hpp>
#include <Engine.hpp>
#include <Settings.hpp>
#include <Window.hpp>

using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)

#define C_ENG_MAP_START SOURCE
#include <ObjectMapping.hpp>

int main (
        int argumentCount,
        char ** arguments
) {

    if ( static_cast < bool > ( Type ( Settings ) :: instance().get( Type ( Settings ) :: keyLogToConsole ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)
        Type ( Logger ) :: instance ().mirrorToConsole() = true;
    }

    (void) Type ( Logger ) :: instance().system ( "Engine Main Test Application Start" );

    Type ( Window ) window;
    (void) window.resize(1366U, 768U);
    (void) window.init();

    (void) Type ( Engine ) :: instance().setWindow ( & window );
    (void) Type ( Engine ) :: instance().loadNextSceneFrom ( "./../data/scenes/testingScene.json" );
    (void) Type ( Engine ) :: instance().start ();

    (void) Type ( Logger ) :: instance().system ( "Engine Main Test Application End" );

    return 0;
}