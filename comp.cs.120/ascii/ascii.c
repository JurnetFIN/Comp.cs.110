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
            printf("%d: %c\n", i, i);
        }
    }
    return 0;
}
