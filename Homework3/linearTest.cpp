#include <string>
#include <cassert>
#include <iostream>

bool allTrue(const std::string a[], int n);
int countFalse(const std::string a[], int n);
int firstFalse(const std::string a[], int n);
int indexOfLeast(const std::string a[], int n);
bool includes(const std::string a1[], int n1, const std::string a2[], int n2);

bool somePredicate(std::string s) {
	return s.size() == 10;
}
int main() {
	const std::string s[4] = { "1234567898", "yeet", "12345678909", "hi" };
	const std::string c[5] = { "1234567890","1234567890","1234567890","a","1234567890" };
	const std::string d[1] = { "1234567890" };
	const std::string q[5] = { "1234567898", "yeet", "12345678909", "hi", "0987654321" };
	const std::string e[1] = { "" };
	const std::string n[3] = { "1234567890" , "1234567891" , "1234567892" };
	const std::string a[5] = { "5","3","1","8","546" };
	const std::string b[10] = { "5","4","3","2","1","6","7","a","c","z" };
	const std::string i1[6] = { "my","name","is","ezra","einhorn","(avery)" };
	const std::string i2[3] = { "my","is","(avery)" };
	const std::string i3[3] = { "my","(avery)","is" };
	assert(!somePredicate(s[1]));
	assert(somePredicate(s[0]));
	assert(!somePredicate(s[2]));
	assert(!somePredicate(s[3]));

	assert(!allTrue(s, 4));
	assert(allTrue(d, 1));
	assert(!allTrue(q, 5));
	assert(!allTrue(e, 1));
	assert(allTrue(n, 3));

	assert(countFalse(s, 4) == 3);
	assert(countFalse(d, 1) == 0);
	assert(countFalse(q, 5) == 3);
	assert(countFalse(e, 1) == 1);
	assert(countFalse(n, 3) == 0);

	assert(firstFalse(s, 4) == 1);
	assert(firstFalse(d, 1) == -1);
	assert(firstFalse(q, 5) == 1);
	assert(firstFalse(e, 1) == 0);
	assert(firstFalse(n, 3) == -1);
	assert(firstFalse(c, 5) == 3);

	assert(indexOfLeast(a, 5) == 2);
	assert(indexOfLeast(b, 1) == 0);
	assert(indexOfLeast(a, 0) == -1);
	assert(indexOfLeast(a, 2) == 1);
	assert(indexOfLeast(b, 10) == 4);
	assert(indexOfLeast(b, 4) == 3);

	assert(includes(i1, 6, i2, 3));
	assert(!includes(i1, 5, i2, 3));
	assert(!includes(i1, 6, i3, 3));
	assert(includes(i1, 5, i2, 2));
	assert(includes(q, 5, s, 4));
	assert(includes(n, 3, d, 1));
	assert(includes(i1, -1, i2, 0));
	assert(!includes(i1, 2, i2, 3));

	return 0;
}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const std::string a[], int n)
{
	if (n <= 0);
	else if (!somePredicate(a[n - 1]))
		return false;
	else if (!allTrue(a, n - 1))
		return false;
	return true;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const std::string a[], int n)
{
	int c = 0;
	if (n <= 0)
		return c;
	else if (!somePredicate(a[n - 1]))
		c++;
	c += countFalse(a, n - 1);
	return c;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const std::string a[], int n)
{
	int c = -1;
	if (n <= 0)
		return c;
	if (!somePredicate(a[n - 1]))
		c = n - 1;
	if (firstFalse(a, n - 1) != -1)
		c = firstFalse(a, n - 1);
	return c;
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const std::string a[], int n)
{
	if (n <= 0) {
		return -1;
	}
	if (n == 1) {
		return 0;
	}
	int min = 0;
	if (n == 2) {
		if (a[0] > a[1])
			return 1;
		else
			return 0;
	}
	if (a[indexOfLeast(a, n - 1)] <= a[n - 1])
		min = indexOfLeast(a, n - 1);
	else
		min = n - 1;
	return min;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if	 a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const std::string a1[], int n1, const std::string a2[], int n2)
{
	if (n2 <= 0) return true;
	if (n2 > n1) return false;
	if (a1[n1 - 1] == a2[n2 - 1])
		return includes(a1, n1 - 1, a2, n2 - 1);
	return includes(a1, n1 - 1, a2, n2);
}