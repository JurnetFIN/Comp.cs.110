#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int voittorivi[7];
    int lottorivi[7];
    int oikein[7];
    int i = argc;
    int j;

    printf("Voittorivi:");
    for(i = 0; i<7; i++) {
        voittorivi[i] = atoi(argv[i+1]);
        printf(" %d", atoi(argv[i+1]));
    }
    printf("\n");

    printf("Lottorivi:");
    for(i = 0; i<7; i++) {
        lottorivi[i] = atoi(argv[i+8]);
        printf(" %d", lottorivi[i]);
    }
    printf("\n");

    int k;
    k = 0;
    for(i = 0; i<7; i++) {
        for(j = 0; j<7; j++) {
            if(lottorivi[i] == voittorivi[j]) {
                oikein[k] = lottorivi[i];
                k++;
            }
        }
    }

    if (k != 0) {
        printf("%d oikein:", k);
        for(i = 0; i<k; i++) {
            printf(" %d", oikein[i]);
        }

        printf("\n");
    } else {
        printf("Ei yhtään oikein!\n");
    }
    return 0;
}
