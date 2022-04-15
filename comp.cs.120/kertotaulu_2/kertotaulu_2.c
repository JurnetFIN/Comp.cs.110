#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;
    printf("    ");

    for(i=atoi(argv[1]); i<=atoi(argv[2]); ++i) {
        if(i<10)
            printf("   ");
        else if(i<100)
            printf("  ");
        else
            printf(" ");

        printf("%d", i);
    }
    printf("\n");

    for(j=atoi(argv[3]); j<=atoi(argv[4]); ++j) {
        if(j<10)
            printf("   ");
        else if(j<100)
            printf("  ");
        else
            printf(" ");

        printf("%d", j);

        for(i=atoi(argv[1]); i<=atoi(argv[2]); ++i) {

            if(i*j<10)
                printf("   ");
            else if(i*j<100)
                printf("  ");
            else
                printf(" ");

            printf("%d", i*j);
        }
        printf("\n");
    }
    return 0;
}
