#include<stdio.h>
#include<ctype.h>
#define GRIDLENGTH 1000
#define min(a,b) (a<b ? a : b)
#define max(a,b) (a>b ? a : b)
int grid[GRIDLENGTH][GRIDLENGTH];
int getnumber(int* n) {
    int temp = 0;
    int input;
    while (!isdigit(input = getchar())) {
        if (input == '\n')
            return 0;
    }
    while (isdigit(input)) {
        temp = 10 * temp + input - '0';
        input = getchar();
    }
    *n = temp;
    return 1;
}
int analyze_line(int diagonal) {
    int x1,y1,x2,y2;
    if (!(getnumber(&x1) && getnumber(&y1) && getnumber(&x2) && getnumber(&y2)))
        return 0;
    if (x1 == x2) {
        for (int i = min(y1,y2); i <= max(y1,y2) ; i++)
            grid[i][x1]++;
    }
    else {
        int m = (y2-y1)/(x2-x1);
        if (m != 0 && !diagonal)
            return 1;
        int b = y1 - m*x1;
        for (int i = min(x1,x2); i<=max(x1,x2); i++) {
            grid[m*i + b][i]++;
        }
    }
    return 1;
}
int main() {
    while(analyze_line(0));
    int places = 0;
    for(int i=0; i<GRIDLENGTH; i++) {
        for(int j=0; j<GRIDLENGTH; j++) {
            if (grid[i][j] >= 2)
                places++;
        }
    }
    printf("%d",places);
}
