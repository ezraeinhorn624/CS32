#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
	cerr.setf(std::ios_base::boolalpha);
	Sequence s;
	assert(s.empty() == true);
	assert(s.size() == 0);
	assert(s.insert(2, 4) == -1);
	assert(s.empty() == true);
	assert(s.insert(0, 1) == 0);
	s.insert(1, 2);
	s.insert(2, 3);
	assert(s.insert(3) == 2);
	assert(s.empty() == false);
	assert(s.size() == 4); //STILL NEED TEST CASES FOR THE REST OF THE FUNCTIONS.
	Sequence s1;
	assert(s1.empty());
	assert(s1.find(42) == -1);
	assert(s1.insert(42) == 0);
	assert(s1.size() == 1 && s1.find(42) == 0);
	assert(s1.insert(1) != -1 && s1.insert(2) != -1 && s1.insert(10) != -1);
	s1.swap(s);
	assert(s1.find(42) == -1);
	assert(s.find(10) == 3);
	cerr << "All tests passed for sequence.cpp :)" << endl;

	return 0;
}