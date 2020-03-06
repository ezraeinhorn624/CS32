#include <string>
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

int factorial(int n) {
	int ans = n;
	for (int i = n - 1; i > 0; i--) {
		ans *= i;
	}
	return ans;
}
int countIncludes(const std::string a1[], int n1, const std::string a2[], int n2);
void separate(std::string a[], int n, std::string separator, int& firstNotLess, int& firstGreater);
void exchange(std::string& x, std::string& y);
void order(std::string a[], int n);

int main() {
	string a[7] = { "stan","kyle","cartman","kenny","kyle","cartman","butters" };
	string a1[3] = { "stan","kenny","cartman" };
	string a2[3] = { "stan","cartman","butters" };
	string a0[3] = { "kenny","stan","cartman" };
	string a3[3] = { "kyle","cartman","butters" };
	//cerr << factorial(7 + 1) / (factorial(3) * factorial(7 + 1 - 3)) << endl;
	assert(countIncludes(a, 7, a1, 3) == 1);
	//cerr << endl;
	//cerr << factorial(7 + 1) / (factorial(3) * factorial(7 + 1 - 3)) << endl;
	assert(countIncludes(a, 7, a2, 3) == 2);
	//cerr << endl;
	//cerr << factorial(7 + 1) / (factorial(3) * factorial(7 + 1 - 3)) << endl;
	assert(countIncludes(a, 7, a0, 3) == 0);
	//cerr << endl;
	//cerr << factorial(7 + 1) / (factorial(3) * factorial(7 + 1 - 3)) << endl;
	assert(countIncludes(a, 7, a3, 3) == 3);
	assert(countIncludes(a, 7, a1, 0) == 1);
	string b[12] = { "1","2","3","2","3","1","2","2","3","4","2","3" };
	string b1[6] = { "3","1","2","2","3","4" };
	string b17[3] = { "1","2","3" };
	string b0[2] = { "0","1" };
	string b5[1] = { "2" };
	//cerr << endl;
	//cerr << factorial(12 + 1) / (factorial(6) * factorial(12 + 1 - 6)) << endl;
	assert(countIncludes(b, 12, b1, 6) == 2);
	//cerr << endl;
	//cerr << factorial(12 + 1) / (factorial(3) * factorial(12 + 1 - 3)) << endl;
	assert(countIncludes(b, 12, b17, 3) == 17);
	//cerr << endl;
	//cerr << factorial(12 + 1) / (factorial(2) * factorial(12 + 1 - 2)) << endl;
	assert(!countIncludes(b, 12, b0, 2));
	//cerr << endl;
	//cerr << factorial(12 + 1) / (factorial(1) * factorial(12 + 1 - 1)) << endl;
	assert(countIncludes(b, 12, b5, 1) == 5);
	//cerr << endl;
	string c[6] = { "2","4","1","5","0","3" };
	order(c, 6);
	for (int i = 0; i < 6; i++)
		assert(c[i] == to_string(i));
	string e[6] = { "2","4","7","5","6","3" };
	order(e, 6);
	for (int i = 0; i < 6; i++)
		assert(e[i] == to_string(i + 2));
	string d[12] = { "c","f","B","Z","r","R","e","A",".","1","j","K" };
	order(d, 12);
	assert(d[0] == "."); assert(d[1] == "1");
	assert(d[2] == "A"); assert(d[3] == "B");
	assert(d[4] == "K"); assert(d[5] == "R");
	assert(d[6] == "Z"); assert(d[7] == "c");
	assert(d[8] == "e"); assert(d[9] == "f");
	assert(d[10] == "j"); assert(d[11] == "r");

	return 0;
}
int countIncludes(const std::string a1[], int n1, const std::string a2[], int n2)
{
	if (a2->empty()) return 1;
	int count = 0;
	if (n2 > n1) return 0;
	if (n2 <= 0 || n1 <= 0)
		return 1;
	if (a1[n1 - 1] == a2[n2 - 1]) {
		count += countIncludes(a1, n1 - 1, a2, n2 - 1);
		if (n1 != 1)
			count += countIncludes(a1, n1 - 1, a2, n2);
	}
	else {
		count += countIncludes(a1, n1 - 1, a2, n2);
	}
	return count;
}

void exchange(std::string & x, std::string & y)
{
	std::string t = x;
	x = y;
	y = t;
}

void separate(std::string a[], int n, std::string separator, int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;
	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

void order(std::string a[], int n)
{
	if (n <= 1) return;
	int firstNotLess = 0, firstGreater = 0;
	separate(a, n, a[n - 1], firstNotLess, firstGreater);
	if (a[n - 1] != a[firstNotLess])
		order(a, n); // separate(a, n, a[n - 1], firstNotLess, firstGreater);
	//if (a[firstNotLess] > a[firstGreater])
		//exchange(a[firstNotLess], a[firstGreater]);
	order(a, n - 1);
}
/*// Return the number of ways that all n2 elements of a2 appear
	  // in the n1 element array a1 in the same order (though not
	  // necessarily consecutively).  The empty sequence appears in a
	  // sequence of length n1 in 1 way, even if n1 is 0.
	  // For example, if a1 is the 7 element array
	  //    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
	  // then for this value of a2            the function must return
	  //    "stan" "kenny" "cartman"                      1
	  //    "stan" "cartman" "butters"                    2
	  //    "kenny" "stan" "cartman"                      0
	  //    "kyle" "cartman" "butters"                    3
int countIncludes(const std::string a1[], int n1, const std::string a2[], int n2)
{
	if (a2->empty()) return 1;
	int count = 0;
	if (n2 > n1) return 0;
	if (n2 <= 0 || n1 <= 0)
		return 1;
	//cerr << "*";
	if (a1[n1 - 1] == a2[n2 - 1]) {
		count += countIncludes(a1, n1 - 1, a2, n2 - 1);
		if (n1 != 1)
			count += countIncludes(a1, n1 - 1, a2, n2);
	}
	else {
		count += countIncludes(a1, n1 - 1, a2, n2);
	}
	return count;
}

// Exchange two strings
void exchange(std::string & x, std::string & y)
{
	std::string t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(std::string a[], int n, std::string separator, int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < separator
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > separator

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
// string d[12] = { "c","f","B","Z","r","R","e","A",".","1","j","K" };

void order(std::string a[], int n)
{
	if (n <= 1) return;
	int firstNotLess = 0, firstGreater = 0;
	separate(a, n, a[n - 1], firstNotLess, firstGreater);
	if (a[n - 1] != a[firstNotLess])
		order(a, n); // separate(a, n, a[n - 1], firstNotLess, firstGreater);
	//if (a[firstNotLess] > a[firstGreater])
		//exchange(a[firstNotLess], a[firstGreater]);
	order(a, n - 1);
}*/