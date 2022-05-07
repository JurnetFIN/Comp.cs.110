#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int potenssi = strlen(argv[1]);
    int luku = 0;

    if(argv[1][0] == '1') {
        luku = -(pow(2, potenssi-1));
    }

    for(int i = 1; i<strlen(argv[1]); i++) {

        if(argv[1][i] == '1') {
            luku += pow(2, potenssi-i-1);
        }
    }

    if(luku != 0) {
        printf("%d\n", luku);
    }

    return 0;
}
