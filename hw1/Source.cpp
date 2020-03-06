#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
	cout.setf(std::ios_base::boolalpha);
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
	cout << "All tests passed for sequence.cpp :)" << endl;
	ScoreList l;
	assert(l.add(2) == true);
	assert(l.add(99) == true);
	assert(l.add(101) == false);
	assert(l.minimum() == 2);
	assert(l.maximum() == 99);
	cout << "All tests passed for ScoreList.cpp :)" << endl;
	//*
	Sequence a(1000);   // a can hold at most 1000 items
	Sequence b(5);      // b can hold at most 5 items
	Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
	ItemType v = 4;

	// No failures inserting 5 items into b
	assert(b.insert(0) != -1);
	assert(b.insert(1) != -1);
	assert(b.insert(2) != -1);
	assert(b.insert(3) != -1);
	assert(b.insert(4) != -1);
	assert(a.insert(100) != -1);

	//Failure if we try to insert a sixth item into b
	assert(b.insert(5) == -1);
	
	// When two Sequences' contents are swapped, their capacities are
	// swapped as well:
	a.swap(b);
	assert(a.insert(v) == -1 && b.insert(v) != -1);
	for (int i = 0; i < 5; i++)
		assert(a.find(i) != -1);
	assert(b.find(100) != -1);
	cout << "All tests passed for newSequence.cpp :)" << endl;
	//*/
	return 0;
}