#include<stdio.h>
#include<ctype.h>
#define MAP_MAXSIZE 100000
int heightmap[MAP_MAXSIZE];
int marking[MAP_MAXSIZE] = {0};
int mapsize = 0, mapwidth = 0;
int num_marked;
void size_basin(int index) {
    if (!marking[index] && heightmap[index] != 9) {
        marking[index] = 1;
        num_marked++;
        if (index%mapwidth + 1 < mapwidth) size_basin(index+1);
        if (index%mapwidth - 1 >= 0) size_basin(index-1);
        if (index-mapwidth >= 0) size_basin(index-mapwidth);
        if (index+mapwidth < mapsize) size_basin(index+mapwidth);
    }
}
int main() {
    int entry;
    while((entry = getchar()) != '*') {
        if (isdigit(entry))
            heightmap[mapsize++] = entry - '0';
        if (!mapwidth && entry=='\n')
            mapwidth = mapsize;
    }
    int basins[256] = {0}; int basins_size = 0;
    for (int i=0; i<mapsize; i++) {
        num_marked = 0;
        size_basin(i);
        if (num_marked) basins[basins_size++] = num_marked;
    }
    int product = 1;
    for (int i=0; i<3; i++) {
        int max = -1; int max_index = -1;
        for (int j=0; j<basins_size; j++)
            if (basins[j] > max && basins[j] > -1) {
                max = basins[j];
                max_index = j;
            }
        product *= max;
        basins[max_index] = -1;
    }
    printf("%d",product);
    return 0;
}
