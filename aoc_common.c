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
int raw_number(int* num) {
	int c = getchar();
	if (!isdigit(c)) return 0;
	*num = 0;
	do {
		*num = 10 * (*num) + c - '0';
	} while(isdigit(c = getchar()));
	ungetc(c,stdin);
	return 1;
}
