#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "aoc_common.h"

#define NODES_MAX 20
#define HISTORY_MAX 20

typedef struct Row Row;
typedef struct Path Path;
struct Row { //node
    char primary[6];
	char secondaries[NODES_MAX][6];
    int secondaries_size;
};
struct Path { //history of visited nodes
	char traversed[HISTORY_MAX][6];
	int num_traversed;
};

int times_traversed(const Path* path, const char* p) {
	int count = 0;
	for (int i=0; i<path->num_traversed; i++)
		if (strcmp(p,path->traversed[i]) == 0)
			count++;
	return count;
}

static int num_fullpaths = 0;
void traverse(Path path, const char* p, const Row *table, int primaries_size, int sc_bonus) {
	strcpy(path.traversed[path.num_traversed++],p); //add item to history

	if (strcmp("end",p) == 0) { //end of path, increment counter
		num_fullpaths++;
		return;
	}
	int i;
	for (i=0; i<primaries_size; i++)
		if (strcmp(p,table[i].primary) == 0)
			break;
	if (i == primaries_size)
		return;
	for (int j=0; j<table[i].secondaries_size; j++) {
		if (islower(table[i].secondaries[j][0])) {
			if (strcmp("start",table[i].secondaries[j]) == 0) continue;
			if (!times_traversed(&path,table[i].secondaries[j]))
				traverse(path,table[i].secondaries[j],table,primaries_size,sc_bonus);
			else if (sc_bonus)
				traverse(path,table[i].secondaries[j],table,primaries_size,0);
			else continue;
		}
		else
			traverse(path,table[i].secondaries[j],table,primaries_size,sc_bonus);
	}
}

void add_secondary(const char* p1, const char* p2, Row *table, int *primaries_size) {
    int i;
    for (i=0; i<*primaries_size; i++)
        if (strcmp(p1,table[i].primary) == 0) break;
    if (i == *primaries_size) { //if we haven't found p1 in the existing table, we make a new entry
        strcpy(table[i].primary,p1);
        table[i].secondaries_size = 0;
		(*primaries_size)++;
    }
    int j;
    for (j=0; j<table[i].secondaries_size; j++)
        if (strcmp(p2,table[i].secondaries[j]) == 0) break;
    if (j == table[i].secondaries_size) { //if we haven't found p2 in the row, we make a new entry
        strcpy(table[i].secondaries[j],p2);
        table[i].secondaries_size++;
    }
}

int main() {
    Row table[NODES_MAX];
    int primaries_size = 0;

    char p1[6];
    char p2[6];

    while(read_word(p1)) {
        getchar();
        read_word(p2);
        add_secondary(p1,p2,table,&primaries_size);
        add_secondary(p2,p1,table,&primaries_size);
    }

    Path path;
    path.num_traversed=0;

    traverse(path,"start",table,primaries_size,0);
	printf("P1: %d\n",num_fullpaths);

	path.num_traversed = 0;
	num_fullpaths = 0;

	traverse(path,"start",table,primaries_size,1);
	printf("P2: %d",num_fullpaths);

    return 0;
}
