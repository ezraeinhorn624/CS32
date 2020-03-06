#include "ScoreList.h"
using namespace std;

ScoreList::ScoreList(){

}
bool ScoreList::add(unsigned long score) {
	if (score < 0 || score>100 || m_seq.size()>=DEFAULT_MAX_ITEMS)
		return false;
	m_seq.insert(score);
	return true;
}
bool ScoreList::remove(unsigned long score) {
	if (m_seq.find(score) == -1)
		return false;
	m_seq.erase(m_seq.find(score));
	return true;
}
int ScoreList::size() const {
	return m_seq.size();
}
unsigned long ScoreList::maximum() const {
	if (m_seq.empty() == true)
		return NO_SCORE;
	for (unsigned long i = 0; i < 100; i++) {
		if (m_seq.find(100 - i)!=-1) {
			return (100 - i);
		}
	}
	return NO_SCORE;
}
unsigned long ScoreList::minimum() const {
	if (m_seq.empty() == true)
		return NO_SCORE;
	for (unsigned long i = 0; i < 100; i++) {
		if (m_seq.find(i) != -1) {
			return (i);
		}
	}
	return NO_SCORE;
}