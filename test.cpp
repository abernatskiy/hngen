#include <iostream>

#include "hngen.h"

//const char digits[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
//const std::map<char,unsigned> rdigits = {{'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'a',10},{'b',11},{'c',12},{'d',13},{'e',14},{'f',15}};

using namespace std;

int main() {

	HammingNeighborhoodGenerator hng(6);

	vector<string> neighs = hng.getNeighbors("00", 2);

	for(const auto& ne : neighs)
		cout << ne << endl;

	return 0;
}
