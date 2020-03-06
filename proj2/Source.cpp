#include "Sequence.h"
#include <cassert>
#include <iostream>

int main() {
	Sequence s;
	cerr << "'aaa' inserted at position " << s.insert("aaa") << endl;
	cerr << s.size() << endl;
	cerr << "'bbb' inserted at position " << s.insert("bbb") << endl;
	cerr << s.size() << endl;
	cerr << "'ddd' inserted at position " << s.insert("ddd") << endl;
	cerr << s.size() << endl;
	cerr << "'bbb' inserted at position " << s.insert("bbb") << endl;
	cerr << s.size() << endl;
	cerr << "'000' inserted at position " << s.insert(0, "000") << endl;
	cerr << s.size() << endl;
	assert(s.erase(2));
	assert(s.insert("eee") == 4 && s.insert("ccc") == 3);
	ItemType x;
	for (int i = 0; i < s.size(); i++) {
		assert(s.get(i, x));
		cerr << "The item at position " << i << " is " << x << endl;
	}
		cerr << endl;
	assert(s.erase(0));
	assert(s.size() == 5);
	assert(s.insert("ccc") == 2);
	assert(s.remove("ccc") == 2);
	for (int i = 0; i < s.size(); i++) {
		assert(s.get(i, x));
		cerr << "The item at position " << i << " is " << x << endl;
	}
		cerr << endl;
	assert(s.insert("cc1")==2);
	assert(s.set(2, "ccc") == true);
	assert(s.find("bbb") == 1);
	assert(s.find("fff") == -1);
	assert(s.find("aaa") == 0);
	Sequence d;
	assert(d.insert(0, "000")==0);
	assert(d.insert(1, "111")==1);
	assert(d.size() == 2);
	d.swap(s);
	assert(s.size() == 2&&d.size()==5);
	for (int i = 0; i < s.size(); i++) {
		assert(s.get(i, x));
		cerr << "The item at position " << i << " is " << x << endl;
	}
	cerr << endl;
	for (int i = 0; i < d.size(); i++) {
		assert(d.get(i, x));
		cerr << "The item at position " << i << " is " << x << endl;
	}
	cerr << endl;
	Sequence c;
	c.swap(d);
	assert(d.size() == 0);
	assert(c.size() == 5);
	assert(c.set(0, "new0"));
	assert(!d.set(1, "new1"));
	
	return 0;
}