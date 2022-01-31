#include "aoc_common.h"
#include<stdio.h>
#include <ctype.h>
int read_word(char* str) {
    int c;
    while(isspace(c=getchar())); //remove leading blanks
    int i;
    for (i=0; isalpha(c); i++) {
        str[i]=c;
        c = getchar();
    }
    ungetc(c,stdin);
    str[i]=0;
    return i;
}
