#include<stdio.h>
#include"aoc_common.h"
#define POINTS_MAX 1000
#define INSTRUCTION_MAX 20

typedef struct Instruction Instruction;
typedef struct Point Point;
struct Instruction {
	int axis;
	int line;
};
struct Point {
	int x;
	int y;
};

Point points[POINTS_MAX];
Instruction instructions[INSTRUCTION_MAX];
int points_size = 0;
int instruction_size = 0;

int getpoint(Point *p) {
	if (!raw_number(&(p->x))) return 0;
	getchar(); //for the comma
	if (!raw_number(&(p->y))) return 0;
	getchar(); //for the newline
	return 1;
}
int getinstruction(Instruction *i) {
	if(getchar() != 'f') return 0;
	scanf("%*s%*s");
	getchar(); //for the space;
	int c = getchar();
	if (c == 'x') i->axis = 0;
	else if (c == 'y') i->axis = 1;
	else return 0;
	getchar(); //for the equals sign
	raw_number(&(i->line));
	getchar(); //for the newline
	return 1;
}
void erase_point(const Point *p) {
	for (int i=0; i<points_size; i++)
		if (p->x == points[i].x && p->y == points[i].y) {
			points[i].x = -1;
			points[i].y = -1;
		}
}
int find_point(int y, int x) {
	for (int i=0; i<points_size; i++)
		if (x == points[i].x && y == points[i].y) {
			return 1;
		}
	return 0;
}
void step(int instruction_index) {
	if (instructions[instruction_index].axis == 0) { //for x
		for (int i=0; i<points_size; i++)
			if (points[i].x > instructions[instruction_index].line) {
				Point local_new;
				local_new.x = 2*instructions[instruction_index].line - points[i].x;
				local_new.y = points[i].y;

				erase_point(&local_new);

				points[i] = local_new;
			}
	}
	if (instructions[instruction_index].axis == 1) { //for y
		for (int i=0; i<points_size; i++)
			if (points[i].y > instructions[instruction_index].line) {
				Point local_new;
				local_new.y = 2*instructions[instruction_index].line - points[i].y;
				local_new.x = points[i].x;

				erase_point(&local_new);

				points[i] = local_new;
			}
	}
}
int main() {
	while(getpoint(&points[points_size]))
		points_size++;
	while(getinstruction(&instructions[instruction_size]))
		instruction_size++;

	int y_size=15, x_size=15;
	if (instructions[0].axis == 0) x_size = instructions[0].line;
	if (instructions[0].axis == 1) y_size = instructions[0].line;

	step(0);
	int counter = 0;
	for (int i=0; i<points_size; i++) {
		if (points[i].x != -1)
			counter++;
	}
	printf("P1: %d",counter);

	for (int i=1; i<instruction_size; i++) {
		if (instructions[i].axis == 0) x_size = instructions[i].line;
		if (instructions[i].axis == 1) y_size = instructions[i].line;
		step(i);
	}
	printf("\nP2:\n",x_size,y_size);
	for (int i=0; i<y_size; i++) {
		for (int j=0; j<x_size; j++) {
			printf("%c",find_point(i,j) ? '#' : '.');
		}
		printf("\n");
	}
    return 0;
}
