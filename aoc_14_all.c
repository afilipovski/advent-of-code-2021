#include<stdio.h>
#include<ctype.h>
#include<malloc.h>
#define MAX_INSTRUCTIONS 200

typedef struct Instruction Instruction;
struct Instruction {
	char first;
	char last;
	char insert;
};
void copy_matrix(unsigned long long m1[26][26], const unsigned long long m2[26][26]) {
	for (int i=0; i<26; i++) {
		for (int j=0; j<26; j++)
			m1[i][j] = m2[i][j];
	}
}
void wipe_matrix(unsigned long long m[26][26]) {
	for (int i=0; i<26; i++) {
		for (int j=0; j<26; j++)
			m[i][j] = 0;
	}
}
void printresults(const unsigned long long *count) {
	unsigned long long max,min;
	int i;
	for (i=0; i<26; i++) {
		if (count[i] != 0) {
			min=max=count[i];
			break;
		}
	}
	while(i<26) {
		if (count[i] > max) max = count[i];
		if (count[i] < min && count[i] != 0) min = count[i];
		i++;
	}
	printf("%llu",max-min);
}
int main () {
	unsigned long long matrix_original[26][26] = {0};
	unsigned long long matrix_step[26][26] = {0};
	unsigned long long count[26] = {0};

	int first = getchar() - 'A';
	count[first]++;
	int second;
	while((second = getchar() - 'A') != '\n'-'A') {
		count[second]++;
		++matrix_original[first][second];
		first = second;
	}

	getchar();

	Instruction arr_inst[MAX_INSTRUCTIONS];
	int arr_inst_size = 0;
	while(scanf("%c",&arr_inst[arr_inst_size].first), isalpha(arr_inst[arr_inst_size].first)) {
		scanf("%c%*c%*c%*c%*c%c%*c",&arr_inst[arr_inst_size].last,&arr_inst[arr_inst_size].insert);
		arr_inst_size++;
	}

	for (int i=0; i<40; i++) {
		if (i==10) {
			printf("P1: "); printresults(count);
		}
		for (int j=0; j<arr_inst_size; j++) {
			unsigned long long relevant_pairs = matrix_original[arr_inst[j].first-'A'][arr_inst[j].last-'A'];
			matrix_step[arr_inst[j].first-'A'][arr_inst[j].insert-'A'] += relevant_pairs;
			matrix_step[arr_inst[j].insert-'A'][arr_inst[j].last-'A'] += relevant_pairs;
			count[arr_inst[j].insert-'A'] += relevant_pairs;
		}
		copy_matrix(matrix_original,matrix_step);
		wipe_matrix(matrix_step);
	}
	printf("\nP2: "); printresults(count);

    return 0;
}
