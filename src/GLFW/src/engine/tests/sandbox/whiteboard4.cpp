#include <iostream>
//#include <fstream>
//using namespace std;
//ifstream fin ("cerc.in");
//ofstream fout ("cerc.out");

#define fin std::cin
#define fout std::cout

int n, solutie[100], vf[100], summax, vect[100], solfinal[100];

int suma () {
    int sum = 0;
    for (int i = 1;i < n;i++)
        sum += solutie[i]*solutie[i+1];
    sum += solutie[n]*solutie[1];
    return sum;
}

void afis () {
    int sumaCurenta = suma();
    if (sumaCurenta > summax) {
        summax = sumaCurenta;
        for (int i = 1;i <= n;i++)
            solfinal[i] = solutie[i];
    }
}

//G n noduri -> k muchii. G n + 1 noduri adaugam n muchii
//G n + 1 ...

// G (1) => 0 muchii
// G (2) => 1 muchie
// G (3) => 3 muchii ( 1 + 2 )
// G (4) => 3 + 3 ( 3 + 2 + 1 )

// G(n) => max 1 + 2 + 3 + ... + n muchii = n(n-1) / 2

void bkt (int pos) {
    if (pos == n+1)
        afis();
    else {
        for (int i = 1;i <= n;i++)
            if (vf[i] == 0) {
                vf[i] = 1;
                solutie[pos] = vect[i];
                bkt(pos + 1);
                vf[i] = 0;
            }
    }
}


int main()
{
    fin >> n;
    for (int i = 1;i <= n;i++)
        fin >> vect[i];
    for (int i = 1;i < n;i++)
        for (int j = i+1;j <= n;j++)
            if (vect[i] > vect[j])
                std::swap(vect[i],vect[j]);

    solutie[1] = vect[1];
    vf[1] = 1;
    bkt(2);
    for (int i = 1;i <= n;i++)
        fout<<solfinal[i]<<' ';
    return 0;
}
