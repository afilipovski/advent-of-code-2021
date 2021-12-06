#include<stdio.h>
#define DAYS 256
int main() {
    unsigned long long fish[9] = {0};
    int num_input;
    char char_input;
    while (scanf("%d%c",&num_input,&char_input) == 2) {
        fish[num_input]++;
    }
    for (int i=0; i<DAYS; i++) {
        unsigned long long tempzero = fish[0];
        for (int j=0; j<8; j++) {
            fish[j] = fish[j+1];
        }
        fish[8]=tempzero;
        fish[6] += tempzero;
    }
    unsigned long long sum=0;
    for (int i=0; i<9; i++) {
        sum += fish[i];
    }
    printf("%lli",sum);
    return 0;
}
