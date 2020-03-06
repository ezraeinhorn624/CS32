#include "Sequence.h"
using namespace std;

Sequence::Sequence(){
	m_size = 0;
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
	int p = size();
	for (int i = size(); i > 0;i--) {
		if (m_array[i] >= value)
			p = i;
	}
	if (size() == DEFAULT_MAX_ITEMS)
		return -1;
	for (int i = size(); i > p; i--)
		m_array[i] = m_array[i - 1];
	m_array[p] = value;
	m_size++;
	return p;
}
bool Sequence::erase(int pos) {
	if (pos < 0 || pos >= (m_size))
		return false;
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
	if (pos < 0 || pos >= m_size)
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
void Sequence::swap(Sequence& other) { // (Implementation note : The swap function is easily implementable without creating any additional array or additional Sequence.)
	Sequence m_other = other;
	for (int i = 0; i < DEFAULT_MAX_ITEMS;i++)
		other.m_array[i] = m_array[i];
	for (int i = 0; i < DEFAULT_MAX_ITEMS;i++)
		m_array[i] = m_other.m_array[i];
	other.m_size = m_size;
	m_size = m_other.m_size;
}