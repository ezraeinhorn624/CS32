#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
	ScoreList l;
	assert(l.add(2) == true);
	assert(l.add(99) == true);
	assert(l.add(101) == false);
	assert(l.minimum() == 2);
	assert(l.maximum() == 99);
	cerr << "All tests passed for ScoreList.cpp :)" << endl;
	return 0;
}