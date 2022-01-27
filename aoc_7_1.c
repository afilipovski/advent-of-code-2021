#include <stdio.h>
#define NUM_MAX 2048
#define abs(x) ((x) > 0 ? (x) : -(x))
int main() {
    int numbers[NUM_MAX] = {0};
    int temp_num, counter = 0;
    while(scanf("%d%*c",&temp_num)) {
        numbers[temp_num]++;
        printf("\nread %d",temp_num);
        counter++;
    }
    counter/=2;
    int median;
    for (median=0; median<NUM_MAX && counter > 0; median++) {
        counter -= numbers[median];
    }
    --median;
    printf("Median: %d",median);
    int fuel_expended = 0;
    for (int i=0; i<NUM_MAX; i++) {
        printf("\nFuel expenditure for %d: %d*%d = %d",i,numbers[i],i-median,numbers[i]*(i-median));
        fuel_expended += numbers[i]*abs(i-median);
    }
    printf("\nFuel expended: %d",fuel_expended);
    return 0;
}
