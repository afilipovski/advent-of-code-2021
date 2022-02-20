#include<stdio.h>
#include<malloc.h>
#include"naive_pq.h"
#define DIMENSION 100

int risk[DIMENSION][DIMENSION];
int access[5*DIMENSION][5*DIMENSION];

typedef struct coordinates {
	int y;
	int x;
	int cost;
} coordinates;
coordinates* coords(int _y, int _x, int _cost) {
	coordinates *c = malloc(sizeof(coordinates));
	c->y = _y;
	c->x = _x;
	c->cost = _cost;
	return c;
}
coordinates cauto(coordinates* c) {
	coordinates cres;
	cres.y = c->y;
	cres.x = c->x;
	cres.cost = c->cost;
	free(c);
	return cres;
}

int valid_pos(int y, int x) {
	return (y>=0 && x>=0 && y<5*DIMENSION && x<5*DIMENSION);
}
int risk_compute(int y, int x) {
	return (risk[y%DIMENSION][x%DIMENSION] + y/DIMENSION + x/DIMENSION) % 10 
	     + (risk[y%DIMENSION][x%DIMENSION] + y/DIMENSION + x/DIMENSION) / 10;
}

int main() {
	for (int i=0; i<DIMENSION; i++) {
		for (int j=0; j<DIMENSION; j++)
			risk[i][j] = getchar() - '0';
		getchar();
	}
	
	pqueue* head = NULL;
	push(&head,0,coords(0,0,0));
	access[0][0] = 1;
	
	while(1) {
		coordinates c = cauto(pop(&head));
		if (c.y == DIMENSION-1 && c.x == DIMENSION-1) {
			printf("P1: %d",-c.cost);
			//break;
		}
		if (c.y == 5*DIMENSION-1 && c.x == 5*DIMENSION-1) {
			printf("\nP2: %d",-c.cost);
			break;
		}
		if (valid_pos(c.y,c.x+1) && !access[c.y][c.x+1]) {
			push(&head,c.cost-risk_compute(c.y,c.x+1),coords(c.y,c.x+1,c.cost-risk_compute(c.y,c.x+1)));
			access[c.y][c.x+1] = 1;
		}
		if (valid_pos(c.y+1,c.x) && !access[c.y+1][c.x]) {
			push(&head,c.cost-risk_compute(c.y+1,c.x),coords(c.y+1,c.x,c.cost-risk_compute(c.y+1,c.x)));
			access[c.y+1][c.x] = 1;
		}
		if (valid_pos(c.y,c.x-1) && !access[c.y][c.x-1]) {
			push(&head,c.cost-risk_compute(c.y,c.x-1),coords(c.y,c.x-1,c.cost-risk_compute(c.y,c.x-1)));
			access[c.y][c.x-1] = 1;
		}
		if (valid_pos(c.y-1,c.x) && !access[c.y-1][c.x]) {
			push(&head,c.cost-risk_compute(c.y-1,c.x),coords(c.y-1,c.x,c.cost-risk_compute(c.y-1,c.x)));
			access[c.y-1][c.x] = 1;
		}
	}
}
