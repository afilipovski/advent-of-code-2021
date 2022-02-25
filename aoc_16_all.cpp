#include <iostream>
#include <vector>
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

unsigned long long btoi(std::vector<bool> &v, int a, int b) {
	unsigned long long res = 0;
	while(a<=b)
		res = 2*res + v[a++];
	return res;
}

packet parse_packet(std::vector<bool> &v, unsigned index) {
	//std::cout<<"\nSE POVIKUVA PARSE PACKET SO INDEX "<<index<<std::endl;
	packet p;
	if (index+5 >= v.size()) {
		p.version = -1;
		return p;
	}
	p.version = btoi(v,index,index+2);
	p.type_id = btoi(v,index+3,index+5);
	if (p.type_id == 4) {
		unsigned data_block = index+6;
		while(data_block+4 < v.size()) {
			p.literal = 16*p.literal + btoi(v,data_block+1,data_block+4);
			if (v[data_block] == 0) break;
			data_block += 5;
		}
		p.index_end = data_block+4;
	}
	else {
		p.ltype = v[index+6];
		if (p.ltype) {
			p.length = btoi(v,index+7,index+17);
			unsigned data_block = index+18;
			for (unsigned i=0; i<p.length && data_block<v.size(); i++) {
				packet temp = parse_packet(v,data_block);
				//std::cout<<"\ntemp end e "<<temp.index_end<<std::endl;
				if (temp.index_end < v.size()) p.spackets.push_back(temp);
				data_block = temp.index_end+1;
			}
			p.index_end = data_block-1;
		}
		else {
			p.length = btoi(v,index+7,index+21);
			unsigned data_block = index+22;
			while(data_block < index+18+p.length && data_block<v.size()) {
				packet temp = parse_packet(v,data_block);
				if (temp.index_end < v.size()) p.spackets.push_back(temp);
				data_block = temp.index_end+1;
			}
			p.index_end = data_block-1;
		}
	}
	return p;
}

void push_number(std::vector<bool> &v, int n) {
	v.push_back(n/8);
	v.push_back(n/4%2);
	v.push_back(n/2%2);
	v.push_back(n%2);
}

inline std::ostream& print_packet(std::ostream& o, packet &p) {
	o <<"DO "<<p.index_end<< " VERZIJA " << p.version << " TYPEID " <<p.type_id;
	if (p.type_id == 4) o << " LITERAL "<<p.literal<<std::endl;
	else {
		o << " LTYPE "<<p.ltype<<" LENGTH "<<p.length;
		o << std::endl;
		for (packet &p2 : p.spackets)
			print_packet(o,p2);
	}
	return o;
}
int packet_ver_sum(packet &p) {
	int sum = p.version;
	for (packet &p2 : p.spackets)
		sum += packet_ver_sum(p2);
	return sum;
}

unsigned long long evaluate(packet &p) {
	unsigned long long result;
	switch(p.type_id) {
		case 0:
			result = 0;
			for (packet &p2 : p.spackets)
				result += evaluate(p2);
		break;
		case 1:
			result = 1;
			for (packet &p2 : p.spackets)
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
	std::vector<bool> v;
	char c;
	while((c = std::cin.get()) != '*') {
		int numeric_representation;
		if (isdigit(c))
			numeric_representation = c-'0';
		else if (isalpha(c))
			numeric_representation = c-'A'+10;
		else
			numeric_representation = 0;
		push_number(v,numeric_representation);
	}
	for (bool digit : v)
		std::cout<<digit;
	std::cout<<std::endl;
	packet p = parse_packet(v,0);
	print_packet(std::cout,p);
//	while(p = parse_packet(v,endsofar), p.version != -1) {
//		print_packet(std::cout,p);
//		endsofar = p.index_end+1;
//		suma += packet_ver_sum(p);
//	}
	std::cout<<"\nP1: "<<packet_ver_sum(p)<<std::endl;
	std::cout<<"P2: "<<evaluate(p)<<std::endl;
//	int pos;
//	std::cin>>pos;
//	packet p = parse_packet(v,pos);
//	print_packet(std::cout,p);
}
