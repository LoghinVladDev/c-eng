#include <iostream>
#include <fstream>
#include <cstring>

std::ifstream fin ("list.in");
std::ofstream fout ("list.out");

#define NR_NODURI 100

struct Node {
    int value;
    Node * next;
};

struct Edge {
    int from;
    int to;
};

void pushFront ( int value, Node * & vf ) {
    Node * p = new Node { value, vf };
    vf = p;
}

void printList ( Node * vf ) {
    while (vf != nullptr) {
        std::cout << vf->value << ' ';
        vf = vf->next;
    }
    std::cout << '\n';
}

bool contains ( int value, Node * vf ) {
    while ( vf != nullptr ) {
        if ( value == vf->value )
            return true;
        vf = vf->next;
    }
    return false;
}

void deleteList ( Node * & vf ) {
    while ( vf != nullptr ) {
        Node * vCopy = vf;
        vf = vf->next;
        delete vCopy;
    }
}

Node * adjacencyLists[ NR_NODURI + 1 ];
Node * arrivals [ NR_NODURI + 1 ];
Edge   edges [ NR_NODURI * (NR_NODURI + 1) ];
int    edgeCount;

int    componentForNode [ NR_NODURI + 1 ];

int n, m;

void clearAdjacencyLists () {
    for ( int i = 1; i <= n; i++ )
        deleteList ( adjacencyLists[i] );
    for ( int i = 1; i <= n; i++ )
        deleteList ( arrivals[i] );
}

int friendCounter = 0;

void BFS ( int startNode ) {
    int coada[ NR_NODURI + 1 ];
    bool viz [ NR_NODURI + 1 ];
    memset ( coada, 0, sizeof ( coada ) );
    memset ( viz, 0, sizeof ( viz ) );

    int ic = 0, sc = 0;
    coada[ 0 ] = startNode;
    viz [ startNode ] = true;

    while ( ic <= sc ) {
        int currentNode = coada [ ic++ ];

        for ( int neighbour = 1; neighbour <= n; neighbour++ ) {
            if (
                    contains( neighbour, adjacencyLists[currentNode] ) &&
                    ! viz [ neighbour ]
                    ) {
                coada[ ++sc ] = neighbour;
                viz [ neighbour ] = true;
                pushFront ( neighbour, arrivals[ startNode ] );
            }
        }
    }
}

bool comparaMultimi ( Node * front1, Node * front2 ) {
    bool vf1 [ NR_NODURI + 1 ];
    bool vf2 [ NR_NODURI + 1 ];

    memset ( vf1, 0, sizeof( vf1 ) );
    memset ( vf2, 0, sizeof( vf2 ) );

    while ( front1 != nullptr ) {
        vf1 [ front1->value ] = true;
        front1 = front1->next;
    }
    while ( front2 != nullptr ) {
        vf2 [ front2->value ] = true;
        front2 = front2->next;
    }

    for ( int i = 1; i <= n ; i++ ) {
        if ( vf1[ i ] != vf2[ i ] )
            return false;
    }

    return true;
}

/// 2 : 2 3 5 4 1   vf1 : 1 1 1 1 1
/// 5 : 5 3         vf2 : 0 0 1 0 1

bool edgeCompare ( Edge e1, Edge e2 ) {
    if ( e1.from == e2.from )
        return e1.to < e2.to;
    return e1.from < e2.from;
}

#include <algorithm>
int main() {

    std::cin >> n >> m;

    while ( m-- ) {
        int i, j;
        std::cin >> i >> j;
        edges [ edgeCount ].from = i;
        edges [ edgeCount++ ].to = j;

        pushFront( j, adjacencyLists[i] );
    }

    for ( int i = 1; i <= n; i++ )
        BFS ( i );
//
//    for (int i = 1; i <= n ; ++i) {
//        std::cout << "Din nodul " << i << " vom putea ajunge in : ";
//        printList( arrivals[i] );
//    }
//
    for (int i = 1; i <= n ; ++i) {
//        std::cout << "Multimea " << i << " tare conexa : ";
        pushFront( i, arrivals[i] );
//        printList( arrivals[i] );
    }

//    std::cout << comparaMultimi ( arrivals[1], arrivals[3] ) << '\n';

    int nrMultimiDisjuncte = 0;
    Node * multimiDisjucte [ NR_NODURI + 1 ];
    for ( int i = 1; i <= n; i++ ) {
        Node * multimeCurenta = arrivals [ i ];

        bool gasit = false;
        for ( int j = 0; j < nrMultimiDisjuncte; j++ ) {
            if ( comparaMultimi( multimeCurenta, multimiDisjucte[j] ) ) {
                gasit = true;
                break;
            }
        }
        if ( ! gasit ) {
            multimiDisjucte [ nrMultimiDisjuncte++ ] = multimeCurenta;
        }
    }

    for ( int i = 1 ;i <= n; i++ ) {
        for( int j = 0; j < nrMultimiDisjuncte; j++ )
            if ( comparaMultimi  ( arrivals[i], multimiDisjucte[j] ) ) {
                componentForNode [ i ] = j;
            }
    }

//    for ( int i = 1; i<=n; i++ ) {
//        std::cout << i << ' ' << componentForNode [ i ] << '\n';
//    }

    Edge uselessEdges[ NR_NODURI * ( NR_NODURI + 1 ) ];
    int uselessEdgeCount = 0;
    for ( int i = 0; i < edgeCount; i++ ) {
        if ( componentForNode[ edges[i].from ] != componentForNode[ edges[i].to ] )
            uselessEdges [ uselessEdgeCount ++ ] = edges [ i ];
    }

    std::sort ( uselessEdges, uselessEdges + uselessEdgeCount, edgeCompare );

    std::cout << uselessEdgeCount << '\n';

    for ( int i = 0; i < uselessEdgeCount; i++ )
        std::cout << uselessEdges [ i ].from << ' ' << uselessEdges [ i ].to << '\n';

//    std::cout << nrMultimiDisjuncte << '\n';

    clearAdjacencyLists();
}
