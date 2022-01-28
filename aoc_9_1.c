#include<stdio.h>
#include<ctype.h>
#define MAP_MAXSIZE 100000
int main() {
    int heightmap[MAP_MAXSIZE];
    int entry, mapsize = 0, mapwidth = 0;
    while((entry = getchar()) != '*') {
        if (isdigit(entry))
            heightmap[mapsize++] = entry - '0';
        if (!mapwidth && entry=='\n')
            mapwidth = mapsize;
    }
    int res = 0;
    for (int i=0; i<mapsize; i++) {
        int lowpoint = 1;
        if (i%mapwidth-1 >= 0 && heightmap[i-1] <= heightmap[i]) lowpoint = 0;
        if (i%mapwidth+1 < mapwidth && heightmap[i+1] <= heightmap[i]) lowpoint = 0;
        if (i-mapwidth >= 0 && heightmap[i-mapwidth] <= heightmap[i]) lowpoint = 0;
        if (i+mapwidth < mapsize && heightmap[i+mapwidth] <= heightmap[i]) lowpoint = 0;
        if (lowpoint) res += heightmap[i]+1;
    }
    printf("\nSirina %d, mapsize %d\n",mapwidth,mapsize);
    printf("%d",res);
}
