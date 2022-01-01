//
// Created by loghin on 18.12.2021.
//

#include <Logger.hpp>
#include <Engine.hpp>
#include <Settings.hpp>
#include <Window.hpp>

using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)

extern auto __setSettingsInstance ( __C_ENG_TYPE ( Settings ) * ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)
extern auto __setLoggerInstance ( __C_ENG_TYPE ( Logger ) * ) noexcept -> void; // NOLINT(bugprone-reserved-identifier)

int main (
        int argumentCount,
        char ** arguments
) {

    /**
     * Leave this here due to order of static allocations
     */
    auto _ = "leave this line here"_s;

    __C_ENG_TYPE ( Settings ) settings;
    __setSettingsInstance ( & settings );

    __C_ENG_TYPE ( Logger ) logger;
    __setLoggerInstance ( & logger );

    if ( static_cast < bool > ( __C_ENG_TYPE ( Settings ) :: instance().get( __C_ENG_TYPE ( Settings ) :: keyLogToConsole ) ) ) { // NOLINT(clion-misra-cpp2008-5-0-13)
        __C_ENG_TYPE ( Logger ) :: instance ().mirrorToConsole() = true;
    }

    (void) __C_ENG_TYPE ( Logger ) :: instance().system ( "Engine Main Test Application Start" );

    __C_ENG_TYPE ( Window ) window;
    window.resize(1366, 768);
    (void) window.init();

    (void) __C_ENG_TYPE ( Engine ) :: instance().setWindow ( & window );
    (void) __C_ENG_TYPE ( Engine ) :: instance().start ();

    (void) __C_ENG_TYPE ( Logger ) :: instance().system ( "Engine Main Test Application End" );

    return 0;
}