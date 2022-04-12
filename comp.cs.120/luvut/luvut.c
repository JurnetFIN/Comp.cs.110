#include <stdio.h>

int main()
{
    int num = 100;
    int i = 1;
    for(i=1; i <= num; ++i) {
        if (i % 2 == 0) {
            continue;
        } else if (i % 3 == 0) {
            continue;
        } else if (i % 5 == 0) {
            continue;
        } else {
            if (i != 1)
                printf(" ");
            printf("%d", i);
        }
    }
    printf("\n");
    return 0;
}
