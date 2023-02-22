
#include <iostream>
#include <cstring>

using namespace std;

int main() {

    int x, y;
    cin >> x >> y;

    if ( x < y ) {
        x = x - y;
        y = x + y;
        x = y - x;
//        int z = x;
//        x = y;
//        y = z;
    }

    for (;x < 0;)

    std::cout << x << ' ' << y << '\n';

    char a[100]; int i;







    strcpy(a,"bacalaureat");
    cout<<strlen(a)<<endl;
    for(i=0;i<strlen(a);i++)
        if(strchr("aeiou",a[i]) != 0) /// daca a[i] e vocala
            cout<<'*';


}