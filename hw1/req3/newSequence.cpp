#include "newSequence.h"
using namespace std;

Sequence::Sequence(const int size) {
	if (size < 0) exit(1);
	max_size = size;
	m_size = 0;
	m_array = new ItemType[max_size];
}
Sequence::~Sequence() {
	delete[] m_array;
}
Sequence::Sequence(const Sequence& other) {
	m_size = other.m_size;
	max_size = other.max_size;

	m_array = new ItemType[max_size];
	for (int i = 0; i < m_size; i++) {
		m_array[i] = other.m_array[i];
	}
}

Sequence& Sequence::operator = (const Sequence& other) {
	if (this != &other){
		delete[] m_array;
		m_size = other.m_size;
		max_size = other.max_size;
		m_array = new ItemType[max_size];
		for (int i = 0; i < m_size; i++) {
			m_array[i] = other.m_array[i];
		}
	}
	return *this;
}

bool Sequence::empty() const {  // Return true if the sequence is empty, otherwise false.
	if (m_size <= 0)
		return true;
	return false;
}
int Sequence::size() const { //return number of items in sequence
	return m_size;
}
int Sequence::insert(int pos, const ItemType& value) {
	if (pos < 0 || pos > m_size)
		return -1;
	for (int i = m_size; i > pos; i--) {
		m_array[i] = m_array[i - 1];
	}
	m_array[pos] = value;
	m_size++;
	return 0;
}
int Sequence::insert(const ItemType& value) {
	if (m_size >= max_size) return -1;
	int p = m_size;
	for (int i = m_size; i > 0; i--) {
		if (m_array[i] >= value)
			p = i;
	}
	for (int i = m_size; i > p; i--)
		m_array[i] = m_array[i - 1];
	*(m_array+p) = value;
	m_size++;
	return p;
}
bool Sequence::erase(int pos) {
	if (pos < 0 || pos >= m_size) return false;
	for (int i = pos; i < m_size; i++)
		m_array[i] = m_array[i + 1];
	m_size--;
	return true;
}
int Sequence::remove(const ItemType& value) {
	int r = 0;
	for (int i = 0;i < m_size;i++) {
		if (m_array[i] == value) {
			for (int n = i; n < m_size; n++)
				m_array[n] = m_array[n + 1];
			m_size--;
			r++;
		}
	}
	return r;
}
bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= max_size)
		return false;
	value = m_array[pos];
	return true;
}
bool Sequence::set(int pos, const ItemType& value) {
	if (pos < 0 || pos >= m_size)
		return false;
	m_array[pos] = value;
	return true;
}


int Sequence::find(const ItemType& value) const {
	int p = -1;
	for (int i = 0;i < m_size;i++) {
		if (m_array[i] == value) {
			p = i;
			break;
		}
	}
	return p;
}
void Sequence::swap(Sequence& other) {
	ItemType* m = other.m_array;
	other.m_array = m_array;
	m_array = m;
	int s = other.m_size;
	other.m_size = m_size;
	m_size = s;
	s = other.max_size;
	other.max_size = max_size;
	max_size = s;//*/
	//Sequence m(other);
	//other = Sequence(*this);
	//*this = Sequence(m);
	//delete m;
	//Sequence m_other(other);
	//other = *this;
	//*this = m_other;
}