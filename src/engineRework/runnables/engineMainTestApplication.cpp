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
    /**
     * Leave this here due to order of static allocations
     */
    auto _ = "leave this line here"_s;

    if ( static_cast < bool > ( C_ENG_CLASS ( Settings ) :: instance().get( C_ENG_CLASS ( Settings ) :: keyLogToConsole ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)
        C_ENG_CLASS ( Logger ) :: instance ().mirrorToConsole() = true;
    }

    (void) C_ENG_CLASS ( Logger ) :: instance().system ( "Engine Main Test Application Start" );

    C_ENG_CLASS ( Window ) window;
    (void) window.init();

    (void) C_ENG_CLASS ( Engine ) :: instance().setWindow ( & window );
    (void) C_ENG_CLASS ( Engine ) :: instance().start ();

    (void) C_ENG_CLASS ( Logger ) :: instance().system ( "Engine Main Test Application End" );

    return 0;
}