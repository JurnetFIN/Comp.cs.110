#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 3) {
        int start = atoi(argv[1]);
        int end = atoi(argv[2]);
        int i;
        for(i=start; i<=end; i++) {
            printf("%d", i);
            printf(": ");
            if((i > 32) && (i <= 126))
                printf("%c", i);
            printf("\n");
        }
    }
    return 0;
}
