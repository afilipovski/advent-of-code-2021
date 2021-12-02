#include <stdio.h>
#include <string.h>
int main() {
    int n;
    char instruction[8];
    int depth=0, horizontal=0;
    while (scanf("%s%d",instruction,&n) == 2) {
        if (strcmp(instruction,"forward") == 0)
            horizontal += n;
        else if (strcmp(instruction,"up") == 0)
            depth -= n;
        else
            depth += n;
    }
    printf("%d",depth*horizontal);
    return 0;
}
