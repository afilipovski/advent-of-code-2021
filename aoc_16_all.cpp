#include <iostream>
#include <vector>

std::vector<bool> v;
struct packet {
	unsigned version;
	unsigned type_id;
	unsigned index_end;
	//za literali
	unsigned long long literal = 0;
	//za operatori
	unsigned ltype;
	unsigned length;
	std::vector<packet> spackets;
};

unsigned long long btoi(short a, short b) {
	unsigned long long res = 0;
	while(a<=b)
		res = 2*res + v[a++];
	return res;
}

packet parse_packet(unsigned index) {
	packet p;
	p.version = btoi(index,index+2);
	if ((p.type_id = btoi(index+3,index+5)) == 4) {
		unsigned data_block = index+6;
		while(data_block+4 < v.size()) {
			p.literal = 16*p.literal + btoi(data_block+1,data_block+4);
			if (v[data_block] == 0) break;
			data_block += 5;
		}
		p.index_end = data_block+4;
	}
	else {
		p.ltype = v[index+6];
		if (p.ltype) {
			p.length = btoi(index+7,index+17);
			unsigned data_block = index+18;
			for (unsigned i=0; i<p.length; i++) {
				packet temp = parse_packet(data_block);
				p.spackets.push_back(temp);
				data_block = temp.index_end+1;
			}
			p.index_end = data_block-1;
		}
		else {
			p.length = btoi(index+7,index+21);
			unsigned data_block = index+22;
			while(data_block < index+22+p.length) {
				packet temp = parse_packet(data_block);
				p.spackets.push_back(temp);
				data_block = temp.index_end+1;
			}
			p.index_end = data_block-1;
		}
	}
	return p;
}

int packet_ver_sum(const packet &p) {
	int sum = p.version;
	for (const packet &p2 : p.spackets)
		sum += packet_ver_sum(p2);
	return sum;
}

unsigned long long evaluate(const packet &p) {
	unsigned long long result;
	switch(p.type_id) {
		case 0:
			result = 0;
			for (const packet &p2 : p.spackets)
				result += evaluate(p2);
		break;
		case 1:
			result = 1;
			for (const packet &p2 : p.spackets)
				result *= evaluate(p2);
		break;
		case 2:
			result = evaluate(p.spackets[0]);
			for (unsigned i=0; i<p.spackets.size(); i++)
				if (evaluate(p.spackets[i+1]) < result) result = evaluate(p.spackets[i+1]);
		break;
		case 3:
			result = evaluate(p.spackets[0]);
			for (unsigned i=0; i<p.spackets.size(); i++)
				if (evaluate(p.spackets[i+1]) > result) result = evaluate(p.spackets[i+1]);
		break;
		case 4:
			result = p.literal;
		break;
		case 5:
			result = (evaluate(p.spackets[0]) > evaluate(p.spackets[1]));
		break;
		case 6:
			result = (evaluate(p.spackets[0]) < evaluate(p.spackets[1]));
		break;
		case 7:
			result = (evaluate(p.spackets[0]) == evaluate(p.spackets[1]));
		break;
	}
	return result;
}
int main() {
	char c;
	while(isalnum(c = std::cin.get())) {
		int n;
		if (isdigit(c))
			n = c-'0';
		else if (isalpha(c))
			n = c-'A'+10;
		v.push_back(n/8);
		v.push_back(n/4%2);
		v.push_back(n/2%2);
		v.push_back(n%2);
	}

	packet p = parse_packet(0);

	std::cout<<"P1: "<<packet_ver_sum(p)<<std::endl;
	std::cout<<"P2: "<<evaluate(p)<<std::endl;
}
