#include <stdio.h>
#define NUM_MAX 2048
#define abs(x) ((x) > 0 ? (x) : -(x))
int fea_point(int* arr, int point) {
    int fuel = 0;
    for (int i=0; i<NUM_MAX; i++) {
        fuel += arr[i] * (abs(i-point) * (abs(i-point) + 1))/2;
    }
    return fuel;
}
int main() {
    int numbers[NUM_MAX] = {0};
    int temp_num, counter = 0;
    while(scanf("%d%*c",&temp_num)) {
        numbers[temp_num]++;
        //printf("\nread %d",temp_num);
        counter++;
    }
    int min_fuel = fea_point(numbers,0);
    for (int i=1; i<NUM_MAX; i++) {
        int fuel = fea_point(numbers,i);
        if (fuel < min_fuel) min_fuel = fuel;
    }
    printf("%d",min_fuel);
    return 0;
}
