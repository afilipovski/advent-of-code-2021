#include<stdio.h>
#include<string.h>
int main() {
    int horizontal=0, depth=0, aim=0;
    char instruction[8];
    int n;
    while(scanf("%s%d",instruction,&n) == 2) {
        if (strcmp(instruction,"forward")==0) {
            horizontal += n;
            depth += n*aim;
        }
        else if (strcmp(instruction,"up")==0)
            aim -= n;
        else
            aim += n;

    }
    printf("%d",horizontal*depth);
    return 0;
}
