#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i;
    int a;
    char isnt;
    char prefix;
    prefix = 'F';
    for(i = atoi(argv[1]); i<=atoi(argv[2]); i++) {
        isnt = 'T';
        for(a = 3; a<argc; a++) {
            if((i % atoi(argv[a])) == 0)
               isnt = 'F';
        }
        if(isnt == 'T') {
            if(prefix == 'T')
                printf(" ");
            prefix = 'T';
            printf("%d", i);
        }

    }
    printf("\n");
    return 0;
}
