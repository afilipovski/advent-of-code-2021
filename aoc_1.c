#include<stdio.h>
#include<ctype.h>
int getnum() {
    int c;
    int result = 0;
    while(!isdigit(c=getchar())) {
        if (c == EOF)
            return -1;
    }
    do {
        result = 10*result + c - '0';
    } while (isdigit(c=getchar()));
    return result;
}
int main() {
    int n1,n2;
    int counter = 0;
    n1 = getnum();
    while (n1 != -1 && (n2 = getnum()) != -1) {
        if (n2>n1)
            counter++;
        n1=n2;
    }
    printf("%d",counter);
    return 0;
}
