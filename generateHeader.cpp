// compile with g++ generateHeader.cpp
// then run ./a.out > constHammingNeighborhoods.h && rm a.out

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <utility>

using namespace std;

const char digits[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
const map<char,unsigned> rdigits = {{'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'a',10},{'b',11},{'c',12},{'d',13},{'e',14},{'f',15}};

vector<char> bitopneighborhood(char cnum, unsigned numFlippableBits, unsigned numBitsToFlip) {
	unsigned num = rdigits.at(cnum);
	if(numBitsToFlip>numFlippableBits) {
		cerr << "One cannot request to flip more bits (" << numBitsToFlip << ") than is available (" << numFlippableBits << ")" << endl;
		exit(EXIT_FAILURE);
	}
	switch(numFlippableBits) {
		case 1: {
			switch(numBitsToFlip) {
				case 1: return { digits[num^1] };
				default: { cerr << "Unsupported combination of numbers of bits to flip and flippable bits: " << numBitsToFlip << ", " << numFlippableBits << endl; exit(EXIT_FAILURE); }
			}
		}
		case 2: {
			switch(numBitsToFlip) {
				case 1: return { digits[num^1], digits[num^2] };
				case 2: return { digits[num^3] };
				default: { cerr << "Unsupported combination of numbers of bits to flip and flippable bits: " << numBitsToFlip << ", " << numFlippableBits << endl; exit(EXIT_FAILURE); }
			}
		}
		case 3: {
			switch(numBitsToFlip) {
				case 1: return { digits[num^1], digits[num^2], digits[num^4] };
				case 2: return { digits[num^3], digits[num^5], digits[num^6] };
				case 3: return { digits[num^7] };
				default: { cerr << "Unsupported combination of numbers of bits to flip and flippable bits: " << numBitsToFlip << ", " << numFlippableBits << endl; exit(EXIT_FAILURE); }
			}
		}
		case 4: {
			switch(numBitsToFlip) {
				case 1: return { digits[num^1], digits[num^2], digits[num^4], digits[num^8] };
				case 2: return { digits[num^3], digits[num^5], digits[num^6], digits[num^9], digits[num^10], digits[num^12] };
				case 3: return { digits[num^14], digits[num^13], digits[num^11], digits[num^7] };
				case 4: return { digits[num^15] };
				default: { cerr << "Unsupported combination of numbers of bits to flip and flippable bits: " << numBitsToFlip << ", " << numFlippableBits << endl; exit(EXIT_FAILURE); }
			}
		}
		default: { cerr << "Unsupported combination of numbers of bits to flip and flippable bits: " << numBitsToFlip << ", " << numFlippableBits << endl; exit(EXIT_FAILURE); }
	}
}

void printLookupMap(unsigned numFlippableBits, unsigned numBitsToFlip) {
	cout << "#define NEIGHBORHOODS" << numBitsToFlip << "OF" << numFlippableBits << " {\\" << endl;
	unsigned max = 1<<numFlippableBits;
	for(unsigned j=0; j<max; j++) {
		char c = digits[j];
		cout << "{'" << c << "',{";
		vector<char> hood = bitopneighborhood(c, numFlippableBits, numBitsToFlip);
		for(unsigned i=0; i<hood.size(); i++)
			cout << "'" << hood[i] << "'" << (i==hood.size()-1 ? "" : ",");
		cout << "}}" << (j==max-1 ? "}" : ",\\") << endl;
	}
}

void printAllLookupMaps() {
	for(unsigned fb=1; fb<5; fb++)
		for(unsigned btf=1; btf<fb+1; btf++) {
			printLookupMap(fb, btf);
			cout << endl;
		}
}

void printFullNeighborhoodsStructure() {
	cout << "// use it as vector<vector<map<char,vector<char>>>>" << endl
	     << "// first field is the number of flippable bits" << endl
	     << "// second is the number of bits that are to be flipped" << endl
	     << "// third is the character the neighborhood of which is sought" << endl
	     << endl
	     << "#pragma once" << endl
	     << endl;
	printAllLookupMaps();
	cout << "#define ALLNEIGBORS {\\" << endl;
	for(unsigned fb=1; fb<5; fb++) {
		cout << "{";
		for(unsigned btf=1; btf<fb+1; btf++)
			cout << "NEIGHBORHOODS" << btf << "OF" << fb << (btf==fb? (fb==4?"}}":"},\\") : ", ");
		cout << endl;
	}
}

int main() {
	printFullNeighborhoodsStructure();
	return 0;
}
