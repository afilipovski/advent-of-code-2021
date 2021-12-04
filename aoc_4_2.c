#include<stdio.h>
#include<ctype.h>
#include "queue.h"

#define BINGOLENGTH 100

int bingo[5][5][BINGOLENGTH];
int arr_winner[BINGOLENGTH];
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
    int num_of_winners=0;
    while(curr->next != NULL) {
        int number = pop();
        int i=0;
        for(i=0; i<BINGOLENGTH; i++) {
            if (arr_winner[i]) continue;
            for (int j=0; j<5; j++) {
                for (int k=0; k<5; k++) {
                    if(bingo[k][j][i] == number)
                        bingo[k][j][i] = -1;
                }
            }
            for (int j=0; !arr_winner[i] && j<5; j++) {
                int k;
                for (k=0; k<5; k++) {
                    if(bingo[k][j][i] != -1)
                        break;
                }
                if (k == 5) {
                    arr_winner[i] = 1;
                    num_of_winners++;
                }
            }
            for (int k=0; !arr_winner[i] && k<5; k++) {
                int j;
                for (j=0; j<5; j++) {
                    if(bingo[k][j][i] != -1)
                        break;
                }
                if (j == 5) {
                    arr_winner[i] = 1;
                    num_of_winners++;
                }
            }
            if (num_of_winners == BINGOLENGTH) {
                int sum = 0;
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < 5; k++)
                        if (bingo[k][j][i] != -1)
                            sum+=bingo[k][j][i];
                }
                printf("%d * %d = %d",number,sum,number*sum);
            }
        }
    }
    return 0;
}
