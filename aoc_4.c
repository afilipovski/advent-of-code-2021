#include<stdio.h>
#include<ctype.h>
#include "queue.h"

#define BINGOLENGTH 100

int bingo[5][5][BINGOLENGTH];
int main() {
    int n; char c;
    while (scanf("%d%c",&n,&c)==2) {
        add(n);
        if (c!=',')
            break;
    }
    for(int i=0; i<BINGOLENGTH; i++) {
        for (int j=0; j<5; j++) {
            for (int k=0; k<5; k++) {
                scanf("%d",&bingo[k][j][i]);
            }
        }
    }
    while(curr->next != NULL) {
        int number = pop();
        int i, winner = 0;
        for(i=0; i<BINGOLENGTH; i++) {
            for (int j=0; j<5; j++) {
                for (int k=0; k<5; k++) {
                    if(bingo[k][j][i] == number)
                        bingo[k][j][i] = -1;
                }
            }
            for (int j=0; !winner && j<5; j++) {
                int k;
                for (k=0; k<5; k++) {
                    if(bingo[k][j][i] != -1)
                        break;
                }
                if (k == 5)
                    winner = 1;
            }
            for (int k=0; !winner && k<5; k++) {
                int j;
                for (j=0; j<5; j++) {
                    if(bingo[k][j][i] != -1)
                        break;
                }
                if (j == 5)
                    winner = 1;
            }
            if (winner) break;
        }
        if (winner) {
            int sum = 0;
            for (int j=0; j<5; j++) {
                for (int k=0; k<5; k++) {
                    if (bingo[k][j][i] != -1)
                        sum += bingo[k][j][i];
                }
            }
            printf("%d",sum*number);
            break;
        }
    }
    return 0;
}
