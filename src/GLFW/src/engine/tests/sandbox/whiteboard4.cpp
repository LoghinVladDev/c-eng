#include <iostream>
#include <fstream>

#define MAX_NUMBER_OF_PEOPLE 1005

std::ifstream fin ( "epidemie.in" );
std::ofstream fout ( "epidemie.out" );

int adj[ MAX_NUMBER_OF_PEOPLE ][ MAX_NUMBER_OF_PEOPLE ];
int n, m;
int i, j;

int totalDays = 0;

int todayInfectedCount;
int todayNewInfectedCount;

int todayInfected [ MAX_NUMBER_OF_PEOPLE ];
int todayNewInfected [ MAX_NUMBER_OF_PEOPLE ];

bool infectionHistory [ MAX_NUMBER_OF_PEOPLE ]; // true = inf, false not
                                                // 1            0                ( sizeof (bool) = sizeof(char) )

bool notAllPeopleAreInfected ();
void infectToday ();
void moveCasesAtEndOfDay ();
void readData ();

int main() {
    readData ();

    while ( notAllPeopleAreInfected () ) {
        infectToday();

        moveCasesAtEndOfDay();
        totalDays ++;
    }

    fout << totalDays << '\n';
}

void moveCasesAtEndOfDay () {
    todayInfectedCount = todayNewInfectedCount;

    for ( i = 0; i < todayNewInfectedCount; i++ )
        todayInfected [ i ] = todayNewInfected [ i ];
}

/**
 * todayInfected -> vecini in todayNewInfected
 */
void infectToday () {
    todayNewInfectedCount = 0;

    for ( int i = 0; i < todayInfectedCount; i++ ) {

        infectionHistory [ todayInfected [ i ] ] = true;

        for ( int person = 1; person <= n; person ++ ) {
            if ( adj [ todayInfected [ i ] ] [ person ] && ! infectionHistory [ person ] ) {
                todayNewInfected [ todayNewInfectedCount ++ ] = person;
            }
        }
    }
}

bool notAllPeopleAreInfected () {
    for ( int i = 1; i <= n; i++ )
        if ( ! infectionHistory[ i ] )
            return true;
    return false;
}

void readData () {
    fin >> n >> m;

    while ( m-- ) {
        fin >> i >> j;
        adj[i][j] = adj[j][i] = 1;
    }

    fin >> todayInfectedCount;
    for ( int i = 0; i < todayInfectedCount; i++ )
        fin >> todayInfected[ i ];
}