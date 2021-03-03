#include <iostream>
#include <fstream>

//std::ofstream fout ("summax.out");

int n, m;
int mat[10][10];

int dl[] = { -2, -1,  1,  2,  2,  1, -1, -2 };
int dc[] = {  1,  2,  2,  1, -1, -2, -2, -1 };

int salturi = 0;

void afis() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cout << mat[i][j] << ' ';
        }
        std::cout << '\n';
    }
    exit(0);
}

void bkt( int i, int j ) {
    salturi++;
    mat[i][j] = salturi;

    if( salturi == n * m ) {
        afis ();
    } else {
        for ( int k = 0; k < 8; k++ ) {
            int ln = i + dl[k];
            int cn = j + dc[k];

            if ( ln >= 1 && ln <= n && cn >=1 && cn <= m )
                if ( mat[ln][cn] == 0 )
                    bkt( ln, cn );
        }
    }

    mat[i][j] = 0;
    salturi--;
}

int main() {
    int pi, pj;

    std::cin >> n >> m >> pi >> pj;

    bkt( pi, pj );

    return 0;
}