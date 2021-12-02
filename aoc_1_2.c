#include<stdio.h>
int main() {
    int num[3],n;
    int counter = 0;
    for (int i=0; i<3; i++) {
        scanf("%d",&n);
        num[i] = n;
    }
    while (scanf("%d",&n)) {
        if (n>num[0]) counter++;
        num[0]=num[1];
        num[1]=num[2];
        num[2]=n;
    }
    printf("%d",counter);
    return 0;
}
