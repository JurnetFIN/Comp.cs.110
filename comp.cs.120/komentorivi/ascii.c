#include <stdio.h>

int main()
{
    int start;
    int end;
    int i;
    scanf("%d", &start);
    scanf("%d", &end);
    for(i=start; i<=end; ++i) {
        printf("%d", i);
        printf(": ");
        if((i > 32) && (i < 126))
            printf("%c", i);
        printf("\n");
    }

    return 0;
}
