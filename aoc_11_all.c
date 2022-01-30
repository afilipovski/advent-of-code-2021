#include<stdio.h>
#define N_STEPS 100
struct energy_levels {
    int matrix[10][10];
    int flashed[10][10];
};
typedef struct energy_levels EL;
int valid_position(int i, int j) {
    return (i>=0 && i<10 && j>=0 && j<10);
}
void flash(EL *el, int i, int j) {
    if (!valid_position(i,j) || el->flashed[i][j] || el->matrix[i][j] < 10) return;
    el->flashed[i][j] = 1;
    for (int y = i-1; y<=i+1; y++) {
        for (int x = j-1; x<=j+1; x++) {
            if (y==i && x==j) continue;
            if (valid_position(y,x)) {
                (el->matrix)[y][x]++;
                flash(el,y,x);
            }
        }
    }
}
void svp2(const EL *el, int *p2, int step) {
    if (*p2 > -1) return;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++)
            if (el->flashed[i][j] == 0) return;
    }
    *p2 = step;
}
int main() {
    EL el;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++)
            el.matrix[i][j] = getchar() - '0';
        getchar();
    }
    int num_flash = 0;
    int p2 = -1;
    for (int step=0; p2 == -1; step++) {
        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++) {
                el.flashed[i][j] = 0;
                el.matrix[i][j]++;
            }
        }
        for (int i=0; i<10; i++)
            for (int j=0; j<10; j++) {
                flash(&el,i,j);
            }
        svp2(&el,&p2,step+1);
        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++)
                if (el.matrix[i][j] > 9) {
                    el.matrix[i][j]=0;
                    if (step<N_STEPS) num_flash++;
                }
        }
    }
    printf("Solution to Part 1: %d\n",num_flash);
    printf("Solution to Part 2: %d",p2);
    return 0;
}
