#include <iostream>
#include <fstream>

#include <list>

using namespace std;

list < int > adj [100];
int n;

struct obj {
    int i;
    double j;
};

int main() {
    /// 1 : 2, 3
    /// 2 : 1,
    /// 3 : N

    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(1);

    for ( auto it = adj[1].begin(); it != adj[1].end(); it++ ) {
        std::cout << *it << '\n';
    }

//    for ( const auto & vecin : adj[3] )
//        std::cout << vecin << '\n';
}
