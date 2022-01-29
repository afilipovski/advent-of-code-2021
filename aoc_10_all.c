#include<stdio.h>
#include "stack.h"
#define MAXSCORE 1000
unsigned long long autocomplete_score(stack* s) {
    unsigned long long score = 0;
    while(s) {
        score*=5;
        switch(peek(s)) {
        case '(':
            score+=1; break;
        case '[':
            score+=2; break;
        case '{':
            score+=3; break;
        case '<':
            score+=4; break;
        }
        s = pop(s);
    }
    return score;
}

unsigned long long ac_scores[MAXSCORE];
unsigned long long ac_scores_size=0;
void sort_ac(int index_first) {
    unsigned long long min_val = ac_scores[index_first];
    int min_index = index_first;
    for (int i=index_first+1; i<ac_scores_size; i++) {
        if (ac_scores[i] < min_val) {
            min_val = ac_scores[i];
            min_index = i;
        }
    }
    unsigned long long temp = ac_scores[index_first];
    ac_scores[index_first] = ac_scores[min_index];
    ac_scores[min_index] = temp;
    if (index_first+1 < ac_scores_size)
        sort_ac(index_first+1);
}


int main() {
    int c;
    stack* s = 0;
    int corrupt = 0;
    int score = 0;
    while(c = getchar()) {
        switch(c) {
        case '\n':
        case '*':
            if (!corrupt) {
                ac_scores[ac_scores_size++] = autocomplete_score(s);
            }
            corrupt = 0;
            s = 0;
            break;
        case '(':
        case '[':
        case '{':
        case '<':
            s = push(s,c);
            break;
        case ')':
            if (!corrupt && peek(s) != '(') {
                corrupt = 1;
                score += 3;
            }
            else s=pop(s);
            break;
        case ']':
            if (!corrupt && peek(s) != '[') {
                corrupt = 1;
                score += 57;
            }
            else s=pop(s);
            break;
        case '}':
            if (!corrupt && peek(s) != '{') {
                corrupt = 1;
                score += 1197;
            }
            else s=pop(s);
            break;
        case '>':
            if (!corrupt && peek(s) != '<') {
                corrupt = 1;
                score += 25137;
            }
            else s=pop(s);
            break;

        };
        if (c=='*') break;
    }

    sort_ac(0);

    printf("Solution for P1: %d\n",score);
    for(int i=0; i<ac_scores_size; i++) {
        printf("%llu\n",ac_scores[i]);
    }
    printf("Solution for P2: %llu",ac_scores[ac_scores_size/2]);
    return 0;
}
