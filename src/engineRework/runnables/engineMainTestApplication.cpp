//
// Created by loghin on 18.12.2021.
//

#include <Logger.hpp>
#include <Engine.hpp>
#include <Settings.hpp>
#include <Window.hpp>

using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)

int main (
        int argumentCount,
        char ** arguments
) {


    if ( static_cast < bool > ( __C_ENG_TYPE ( Settings ) :: instance().get( __C_ENG_TYPE ( Settings ) :: keyLogToConsole ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)
        __C_ENG_TYPE ( Logger ) :: instance ().mirrorToConsole() = true;
    }

    (void) __C_ENG_TYPE ( Logger ) :: instance().system ( "Engine Main Test Application Start" );

    __C_ENG_TYPE ( Window ) window;
    (void) window.resize(1366U, 768U);
    (void) window.init();

    (void) __C_ENG_TYPE ( Engine ) :: instance().setWindow ( & window );
    (void) __C_ENG_TYPE ( Engine ) :: instance().start ();

    (void) __C_ENG_TYPE ( Logger ) :: instance().system ( "Engine Main Test Application End" );

    return 0;
}