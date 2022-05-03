#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool palindrome_recursive(char *s, size_t pituus) {
    if (pituus < 2) {
        return true;
    }

    if ( tolower(s[0]) != tolower(s[pituus-1]) ) {
        return false;
    }

    return palindrome_recursive(s+1, pituus-2);
}

int main(int argc, char *argv[])
{
    int i;
    for(i=1; i<argc; ++i) {
        char* word;
        word = argv[i];

        if(palindrome_recursive(word, strlen(word))) {
            printf("\"%s\": on palindromi\n", word);
        } else {
            printf("\"%s\": ei ole palindromi\n", word);
        }
    }
}
