#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    float a, b, c, x, x1, x2, ratkaisut;

    a = atof(argv[1]);
    b = atof(argv[2]);
    c = atof(argv[3]);

    ratkaisut = b*b - 4*a*c;

    if(ratkaisut < 0) {
        printf("Ei ratkaisua\n");
        return 0;
    }

    if(ratkaisut == 0) {
        x = (-1*b)/(2*a);
        printf("%.3f\n", x);
        return 0;
    }

    x1 = ((-1*b)+sqrt(ratkaisut))/(2*a);
    x2 = ((-1*b)-sqrt(ratkaisut))/(2*a);
    printf("%.3f %.3f\n", x2, x1);

    return 0;
}
