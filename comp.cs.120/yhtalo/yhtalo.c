#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    float a = atof(argv[1]);
    float b = atof(argv[2]);
    float c = atof(argv[3]);

    float ratkaisut = b*b - 4*a*c;

    if(ratkaisut < 0) {
        printf("Ei ratkaisua\n");
        return 0;
    }

    if(ratkaisut == 0) {
        float x = (-1*b)/(2*a);
        printf("%.3f\n", x);
        return 0;
    }

    float x1 = ((-1*b)+sqrt(ratkaisut))/(2*a);
    float x2 = ((-1*b)-sqrt(ratkaisut))/(2*a);
    printf("%.3f %.3f\n", x2, x1);

    return 0;
}
