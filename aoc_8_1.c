#include <stdio.h>
#include <string.h>
int main() {
    char str[8] = "";
    int counter = 0;
    while(1) {
        for (int i=0; i<=10; i++) { //<= for |
            scanf("%s",str);
            if (str[0] == '*') break;
        }
        if (str[0] == '*') break;
        for (int i=0; i<4; i++) {
            scanf("%s",str);
            int length = strlen(str);
            if (length == 2 || length == 4 || length == 3 || length == 7)
                counter++;
        }
    }
    printf("%d",counter);
    return 0;
}
