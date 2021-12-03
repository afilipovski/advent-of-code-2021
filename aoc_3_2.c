#include<stdio.h>
#define LENGTH 1000
#define WIDTH 13
int nums[LENGTH][WIDTH];
void write_number(int line) {
    int n;
    while((n=getchar()) != '0' && n != '1') {
        if (n==EOF)
            return;
    }
    for(int i=0; n=='0' || n=='1'; i++) {
        nums[line][i] = n-'0';
        n=getchar();
    }
}
int judge(int digit,int co2) {
    int sum=0, count=0;
    //find majority digit at [digit] (from all eligible numbers)
    for (int i=0; i<LENGTH; i++) {
        if (nums[i][WIDTH-1] != -1) {
            sum += nums[i][digit];
            count++;
        }
    }
    int seeked = (!co2 && sum>=count-sum) || (co2 && sum<count-sum);
    //all who don't comply have their check bit set to -1
    for (int i=0; i<LENGTH; i++) {
        if (nums[i][WIDTH-1] != -1 && nums[i][digit] != seeked) {
            nums[i][WIDTH - 1] = -1;
            count--;
        }
    }
    return count;
}
int build_number() {
    int n = 0;
    for (int i=0; i<LENGTH; i++) {
        if (nums[i][WIDTH-1] != -1) {
            for (int j = 0; j < WIDTH - 1; j++)
                n = 2 * n + nums[i][j];
            break;
        }
    }
    return n;
}
int main() {
    for (int i=0; i<LENGTH; i++) {
        write_number(i);
    }
//    for (int i=0; i<WIDTH-1; i++) {
//        printf("%d: %d\n",i+1, judge(i,0));
//    }
    for (int i=0; i<WIDTH-1; i++) {
        if (judge(i,0) == 1) {
            break;
        }
    }
    int oxygen= build_number();
    for (int i=0; i<LENGTH; i++) {
        nums[i][WIDTH-1] = 0;
    }
    for (int i=0; i<WIDTH-1; i++) {
        if (judge(i,1) == 1) {
            break;
        }
    }
    int co2 = build_number();
    printf("%d * %d = %d",oxygen,co2, oxygen*co2);
    return 0;
}
