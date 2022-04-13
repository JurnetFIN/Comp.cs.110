#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 2) {
        int start = atoi(argv[0]);
        int end = atoi(argv[1]);
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
    }
    return 0;
}
