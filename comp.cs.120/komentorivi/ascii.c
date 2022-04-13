#include <stdio.h>

int main()
{
    char chr;
    int start;
    int end;
    scanf("%d", &start);
    scanf("%d", &end);

    int i;
    for(i=start; i<end; ++i) {
        printf("%d", i);
        printf(": ");
        if((i > 32) && (i < 126))
            printf("%c", i);
        printf("\n");
    }

    return 0;
}
