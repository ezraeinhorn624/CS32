#ifndef HASH_H
#define HASH_H
#include <cstdlib>
#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <vector>
#include <cstdlib>
//using namespace std;

struct HashNode {
	std::string value = "";
	int offset = 0;
	HashNode* next = nullptr;
};

template <typename t>
class Hash {
public:
	Hash(int size) :m_size(size), m_capacity(size*2) { 
		for (int i = 0; i < size*2; i++) {
			m_array.push_back(new HashNode);
		}
	}
	/*~Hash() {
		for (int i = 0; i < m_capacity; i++) {
			HashNode<t>* ptr = m_array[i];
			delete ptr;
		} 
	}*/
	void insert(t x) { 
		HashNode* ptr = m_array[hashF(x)];
		while (ptr->next != nullptr) ptr = ptr->next;
		ptr->value = x;
	}
	void insert(t x, int index) {
		HashNode* ptr = m_array[hashF(x)];
		while (ptr->value != "") {
			if (ptr->next == nullptr) {
				ptr->next = new HashNode;
			}
			ptr = ptr->next;
		}
		ptr->value = x;
		ptr->offset = index;
	}
	bool remove(t x) {
		HashNode* ptr = m_array[hashF(x)];
		if (ptr->value == "") return false;
		if (ptr->value == x) {
			m_array[hashF(x)] = ptr->next;
			delete ptr;
		}
		while (ptr->next->value != x) {
			if (ptr->next->next == nullptr) return false;
			ptr = ptr->next;
		}
		if (ptr->next->value == x) {
			HashNode* temp = ptr->next;
			ptr->next = temp->next;
			delete temp;
			return true;
		}
		return false;
	}
	bool isIn(t x) const {
		HashNode* ptr = m_array[hashF(x)];
		if (ptr->value == "") return false;
		while (ptr->value != x) {
			if (ptr->next == nullptr) return false;
			if (ptr->next->value == x)
				return true;
			ptr = ptr->next;
		}
		if (ptr->value == x)
			return true;
		return false;
	}
	int hashF(t x) const {
		unsigned long u = 0;
		for (int i = 0; i < x.length(); i++) {
			u *= 83;
			u += x[i];
		}
		u = u % m_capacity;
		return u;
	}
	void display() const{
		int counter = 0;
		for (int i = 0; i < m_capacity; i++) {
			if (m_array[i]->value != "") {
				std::cerr << counter << ' ';
				counter++;
				std::cerr << m_array[i]->value << std::endl;
			}
			HashNode* ptr = m_array[i];
			while (ptr->next != nullptr) {
				std::cerr << counter << ' ';
				counter++;
				ptr = ptr->next;
				std::cerr << ptr->value << std::endl;
			}
		}
	}
	int offset(t x) const {
		HashNode* ptr = m_array[hashF(x)];
		if (ptr->value == "") return -1;
		while (ptr->value != x) {
			if (ptr->next == nullptr) return -1;
			if (ptr->next->value == x)
				return ptr->next->offset;
			ptr = ptr->next;
		}
		if (ptr->value == x)
			return ptr->offset;
		return -1;
	}
	int offset(t x, int otherOffset) const {
		int returnValue = -1;
		HashNode* ptr = m_array[hashF(x)];
		if (ptr->value == "") return -1;
		while (ptr->value != x || returnValue != otherOffset + 1) {
			if (ptr->next == nullptr) break;
			if (ptr->next->value == x) {
				if (returnValue == -1) returnValue = ptr->next->offset;
				else if (ptr->next->offset == otherOffset + 1) {
					returnValue = ptr->next->offset;
					break;
				}
			}
			ptr = ptr->next;
		}
		if (ptr->value == x)
			returnValue = ptr->offset;
		return returnValue;
	}
private:
	int m_size;
	int m_capacity;
	std::vector<HashNode*> m_array;
};

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
	AlarmClock(int ms)
	{
		m_timedOut = false;
		m_isRunning = true;
		m_alarmClockFuture = std::async([=]() {
			for (int k = 0; k < ms && m_isRunning; k++)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (m_isRunning)
				m_timedOut = true;
			});
	}

	~AlarmClock()
	{
		m_isRunning = false;
		m_alarmClockFuture.get();
	}

	bool timedOut() const
	{
		return m_timedOut;
	}

	AlarmClock(const AlarmClock&) = delete;
	AlarmClock& operator=(const AlarmClock&) = delete;
private:
	std::atomic<bool> m_isRunning;
	std::atomic<bool> m_timedOut;
	std::future<void> m_alarmClockFuture;
};


#endif