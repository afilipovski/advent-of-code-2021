#include <stdio.h>
#include <string.h>
#define MAX_PERMS 5040

int leton (const char* input, int* perm) {
    int schema[7] = {0};
    for (int i=0; i<strlen(input); i++)
        schema[perm[input[i]-'a']] = 1;

    int nums[10][7] = {
    {1,1,1,0,1,1,1},  //0
    {0,0,1,0,0,1,0},  //1
    {1,0,1,1,1,0,1},  //2
    {1,0,1,1,0,1,1},  //3
    {0,1,1,1,0,1,0},  //4
    {1,1,0,1,0,1,1},  //5
    {1,1,0,1,1,1,1},  //6
    {1,0,1,0,0,1,0},  //7
    {1,1,1,1,1,1,1},  //8
    {1,1,1,1,0,1,1}}; //9
    for (int i=0; i<10; i++) {
        int equal = 1;
        for (int j=0; j<7 && equal; j++)
            if (nums[i][j] != schema[j])
                equal = 0;
        if (equal) {
            return i;
        }
    }
    return -1;
}

int vec_perms[MAX_PERMS][7];
int vec_i = 0;
void perms_init(int* arr, int begin, int N) {
    for(int i=0; i<7; i++) {
        int valid = 1;
        for (int j=0; j<begin && valid; j++)
            if(arr[j] == i) valid=0;
        if (valid) {
            arr[begin] = i;
            if (begin+1 < N)
                perms_init(arr,begin+1,N);
            else { //sme nasle edna permutacija, da se zacuva vo perms
                for (int j=0; j<7; j++)
                    vec_perms[vec_i][j] = arr[j];
                vec_i++;
            }
        }
    }
}

char observed_inputs[10][7];
int chkperm(int* perm) {
    for (int i=0; i<10; i++)
        if (leton(observed_inputs[i],perm) == -1) return 0;
    return 1;
}

int main() {
    int emptyarr[7] = {0};
    perms_init(emptyarr,0,7);

    int final_res = 0;

    while(1) {
        int i;
        for (i=0; i<10; i++) {
            scanf("%s",observed_inputs[i]);
            if (observed_inputs[i][0] == '*') break;
        }
        if (observed_inputs[i][0] == '*') break;

        int perm_needed;
        for (perm_needed=0; perm_needed<MAX_PERMS; perm_needed++)
            if (chkperm(vec_perms[perm_needed])) break;

        scanf("%*s");

        int number = 0;
        char digit_encoded[7];
        for (i=0; i<4; i++) {
            scanf("%s",digit_encoded);
            number = 10*number + leton(digit_encoded,vec_perms[perm_needed]);
        }
        final_res += number;
    }

    printf("%d",final_res);
    return 0;
}
