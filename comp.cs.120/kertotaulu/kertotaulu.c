#include <stdio.h>

int main()
{
    int x = 1;
    int y = 1;
    printf("   x   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
    for(x=1; x<=15; ++x) {

        if(x<10)
            printf("   ");
        else if(x<100)
            printf("  ");
        else
            printf(" ");

        printf("%d", x);

        for(y=1; y<=15; ++y) {

            if(x*y<10)
                printf("   ");
            else if(x*y<100)
                printf("  ");
            else
                printf(" ");

            printf("%d", x*y);
        }
        printf("\n");
    }
    return 0;
}
