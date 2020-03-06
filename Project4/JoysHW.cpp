#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Person {

public:
	Person() {}
	Person(string name) { string m_name = name; } // default constructor
	string getName() const { return m_name; }
	Person* getBestFriend() const { return bestFriend; }
	int getPopularity() const { return popularity; }
	void setBestFriend(Person* in) { bestFriend = in; }
	void setPopularity() { popularity++; }
	void lowerPopularity() { popularity--; }

private:
	string m_name;
	Person* bestFriend = nullptr;
	int popularity = 0;

};


int main() {
	vector<Person*> people;
	char choice = 'y';
	while (choice == 'y') {
		string name;
		cout << "Name: ";
		getline(cin, name);
		people.push_back(new Person(name));
		cout << "Continue <y/n>? ";
		cin >> choice;
	}
	for (int i = 0; i < people.size(); i++) {
		string bestFriend;
		cout << "Best friend of " << people[i]->getName() << ": ";
		getline(cin, bestFriend);
		Person* bfriend = nullptr;
		for (int j = 0; j < people.size(); j++) {
			if (people[j]->getName() == bestFriend) {
				bfriend = people[j];
			}
		}
		if (bfriend == nullptr) cout << "unable to assign best friend" << endl;
		people[i]->setBestFriend(bfriend);
		if (bfriend != nullptr) bfriend->setPopularity();
	}
	return 0;
}

