#include "Sequence.h"
#include <iostream>
#include <list>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

void testSequenceH()
{
	Sequence<int> si;
	Sequence<string> ss;
	assert(ss.empty());
	assert(ss.size() == 0);
	assert(ss.insert("Hello") == 0);
	assert(si.insert(0, 20) == 0);
	assert(si.insert(10) == 0);
	assert(si.remove(10) == 1);
	assert(si.erase(0));
	assert(ss.remove("Goodbye") == 0);
	assert(ss.find("Hello") == 0);
	string s;
	assert(ss.get(0, s));
	assert(ss.set(0, "Hello"));
	Sequence<string> ss2(ss);
	ss2.swap(ss);
	ss2 = ss;
	assert(subsequence(ss, ss2) == 0);
	assert(subsequence(si, si) == -1);
	interleave(ss, ss2, ss);
	interleave(si, si, si);
}

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOdds(vector<int>& v)
{
	vector<int>::iterator ptr = v.begin();
	while (ptr != v.end()) {
		if (*ptr % 2 == 1)
			ptr = v.erase(ptr);
		else ptr++;
	}
}
void testOdds()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	vector<int> x(a, a + 8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	sort(x.begin(), x.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(x[k] == expect[k]);
}

vector<int> destroyedOnes;
class Movie
{
public:
	Movie(int r) : m_rating(r) {}
	~Movie() { destroyedOnes.push_back(m_rating); }
	int rating() const { return m_rating; }
private:
	int m_rating;
};

// Remove the movies in li with a rating below 55 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.
void removeBad(list<Movie*>& li)
{
	int m_size = li.size();
	list<Movie*> li2;
	while (li.size() != 0) {
		Movie* ptr = li.front();
		li.pop_front();
		if (ptr->rating() < 55) {
			delete ptr;
		}
		else {
			li2.push_back(ptr);
		}
	}
	li.swap(li2);
}
void testBad()
{
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	list<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes.size() == 4);
	vector<int> v;
	for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
	{
		Movie* mp = *p;
		v.push_back(mp->rating());
	}
	// Aside:  In C++11, the above loop could be
	//     for (auto p = x.begin(); p != x.end(); p++)
	//     {
	//         Movie* mp = *p;
	//         v.push_back(mp->rating());
	//     }
	// or    
	//     for (auto p = x.begin(); p != x.end(); p++)
	//     {
	//         auto mp = *p;
	//         v.push_back(mp->rating());
	//     }
	// or    
	//     for (Movie* mp : x)
	//         v.push_back(mp->rating());
	// or    
	//     for (auto mp : x)
	//         v.push_back(mp->rating());
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes.begin(), destroyedOnes.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes[k] == expectGone[k]);
	for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
		delete* p;  // Deallocate remaining movies.
}

int main()
{
	//testSequenceH();
	cout << "Sequence.h passed its tests." << endl;

	testOdds();
	cout << "Odds.cpp passed its tests" << endl;

	//testBad();
	cout << "Bad.cpp passed its tests" << endl;
	cout << "Tested list.cpp separately" << endl;
	cout << "Passed all tests" << endl;
	return 0;
}
