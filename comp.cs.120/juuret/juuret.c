#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int i;
    int precision;
    precision = atoi(argv[1]);
    for(i = 2; i<argc; i++) {
        double juuri = atof(argv[i]);
        juuri = sqrtf(juuri);
        printf("sqrt(%*.*f) = %*.*f\n", 1, precision, atof(argv[i]), 1, precision, juuri);
    }
    return 0;
}
