#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i, j, k, pituus;
    k = atoi(argv[2])*atoi(argv[4]);
    pituus = 1;
    while(k > 10) {
        pituus++;
        k = k/10;
    }

    for(i=0; i<=pituus; ++i) {
        printf(" ");
    }

    for(i=atoi(argv[1]); i<=atoi(argv[2]); ++i) {
        printf(" %*d", pituus, i);
    }
    printf("\n");

    for(j=atoi(argv[3]); j<=atoi(argv[4]); ++j) {
        printf(" %*d", pituus, j);
        for(i=atoi(argv[1]); i<=atoi(argv[2]); ++i) {
            printf(" %*d", pituus, i*j);
        }
        printf("\n");
    }
    return 0;
}
