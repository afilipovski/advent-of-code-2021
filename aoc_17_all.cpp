#include <iostream>
#include <cmath>

inline void format(const std::string &s) {
	for (unsigned i=0; i<s.size(); i++)
		std::cin.get();
}
int main() {
	int xmin,xmax,ymin,ymax;
	format("target area: x="); std::cin>>xmin; format(".."); std::cin>>xmax;
	format(", y=");	std::cin>>ymin;	format(".."); std::cin>>ymax;
	int p1 = 0, p2 = 0;
	for (int i = ceil((-1+sqrt(1+8*abs(xmin)))/2); i<=xmax; i++) {
		for (int j=-150; j<10000; j++) {
			int valid = 0;
			int x=0,y=0;
			int y_local_highest = 0;
			int x_shift=i, y_shift=j;
			for (int k = 0; k<1000; k++) {
				x+=(x_shift==0 ? 0 : x_shift--);
				y+=(y_shift--);
				if (y > y_local_highest) y_local_highest = y;
				if (x >= xmin && x <= xmax && y >= ymin && y <= ymax) {
					valid = 1;
					break;
				}
				if (x > xmax) break;
			}
			if (valid) {
				p2++;
				if (y_local_highest > p1) p1 = y_local_highest;
			}
		}
	}
	std::cout<<"P1: "<<p1<<std::endl;
	std::cout<<"P2: "<<p2;
}
