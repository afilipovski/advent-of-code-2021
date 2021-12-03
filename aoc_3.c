#include<stdio.h>
#define INCIDENCE_LENGTH 12
int incidence[INCIDENCE_LENGTH] = {0};
int analyze_binary() {
    int n;
    while((n=getchar()) != '0' && n != '1') {
        if (n==EOF)
            return -1;
    }
    for (int i = 0; n == '0' || n == '1'; i++) {
        incidence[i] += n-'0';
        n = getchar();
    }
    return 0;
}
int main() {
    unsigned long long n;
    int counter=0;
    while(analyze_binary() == 0) {
        counter++;
    }
    unsigned int gamma = 0;
    unsigned int epsilon = 0;
    for (int i=0; i<INCIDENCE_LENGTH; i++) {
        gamma = 2*gamma + (incidence[i]>counter/2 ? 1 : 0);
        epsilon = 2*epsilon + (incidence[i]<counter/2 ? 1 : 0);
    }
    printf("%d",gamma*epsilon);
    return 0;
}
