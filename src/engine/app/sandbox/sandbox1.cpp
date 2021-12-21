//
// Created by loghin on 04.03.2021.
//

/**
 * Test Source 1
 */

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <iostream>

using namespace std;

void ordon123(int n,int a[])
{
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(a[i]>a[j])
            {
                int aux=a[i];
                a[i]=a[j];
                a[j]=aux;
            }

}

int main () {
    int v[] = {3,1,2,1,3,1};

    ordon123(6, v);

    for ( int i = 0; i < 6; i++ ) {
        cout << v[i] << ' ';
    }
}