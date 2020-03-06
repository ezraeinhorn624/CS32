#include <cstdlib>

#include <iostream>

#include <list>

#include <string>

#include <cassert>

#include <fstream>

#include <functional>

#include <sstream>

#include <vector>

#include <string.h>



using namespace std;



//Function Declarations

void createDiff(istream& fold, istream& fnew, ostream& fdiff);



bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);



void runtest(string oldtext, string newtext);



bool runtest(string oldName, string newName, string diffName, string newName2);



bool getInt(istream& inf, int& n);



bool getCommand(istream& inf, char& cmd, int& length, int& offset);



//Definition of hash table bucket

class hashBucket {

public:

	hashBucket();

	//~hashBucket();

	void addToBucket(std::string value);

	std::string get(int pos) const;

	bool remove(std::string value);

	int getSize() const;

	void setOffset(int offset);

	int getOffset(std::string value);

private:

	std::list<std::string> bucket;

	std::list<int> moffset;

	int msize;

};

//hash table bucket implementations

hashBucket::hashBucket()

	:msize(0) {

	bucket.clear();

	moffset.clear();

}

/*

 hashBucket::~hashBucket() {

 bucket.clear();

 moffset.clear();

 }

 */

void hashBucket::addToBucket(std::string value) {

	bucket.push_back(value);

	msize++;

}



std::string hashBucket::get(int pos) const {

	if (pos < 0 || pos >= bucket.size()) {

		std::cerr << "The item you are looking for doesn't exist!";

		return "";

	}

	list<string>::const_iterator it = bucket.begin();

	for (int i = 0; i != pos; i++) {

		it++;

	}

	return *it;

}



bool hashBucket::remove(std::string value) {

	list<int>::iterator ptrint = moffset.begin();

	for (std::list<std::string>::iterator ptr = bucket.begin(); ptr != bucket.end(); ++ptr) {

		if (*ptr == value) {

			msize--;

			bucket.erase(ptr);

			if (moffset.size() > bucket.size())

				moffset.erase(ptrint);

			return true;

		}

		if (moffset.size() == bucket.size()) {

			ptrint++;

		}

	}

	return false;

}



int hashBucket::getSize() const {

	return msize;

}



void hashBucket::setOffset(int offset) {

	moffset.push_back(offset);

}



int hashBucket::getOffset(string value) {

	list<std::string>::iterator ptr = bucket.begin();

	list<int>::iterator ptr2 = moffset.begin();

	for (; ptr != bucket.end(); ++ptr, ++ptr2) {

		if (*ptr == value)

			return *ptr2;

	}

	return -1;

}



//hash table definition

class hashTable {

public:

	hashTable(int capacity);    //assume input capacity is the size of the table

	~hashTable();

	int hashCode(std::string value);

	void addToMap(std::string value);

	bool removeFromMap(std::string value);

	int getSize() const;

	int getCapacity() const;

	bool find(std::string value, int offset);

	bool find(std::string value);

	void setOffset(int offset, string value);

	int getOffset(string value);

private:

	int msize;

	int mcapacity;

	std::vector<hashBucket*> mtable;

};



//hash table implementations

hashTable::hashTable(int capacity)

	:msize(0), mcapacity(capacity) {

	for (int i = 0; i < capacity; i++) {

		hashBucket* B = new hashBucket;

		mtable.push_back(B);

	}

}



hashTable::~hashTable() {

	for (int i = 0; i < mcapacity; i++) {

		hashBucket* ptr = mtable[i];

		delete ptr;

	}

}



int hashTable::hashCode(std::string value) {

	/*  //below is a hashing program i wrote

	 int prime = 67;

	 unsigned long hash = 0;

	 for (int i = 0; i < value.length(); i++) {

	 hash = (hash * prime) + value[i];

	 }

	 */

	std::hash<std::string> hasher;

	size_t hashed = hasher(value);

	if (mcapacity == 0) {

		return -1;

	}

	return (hashed % mcapacity);

}



void hashTable::addToMap(std::string value) {

	(mtable[hashCode(value)])->addToBucket(value);

	msize++;

}



bool hashTable::removeFromMap(std::string value) {

	if ((mtable[hashCode(value)])->remove(value))

		return true;

	return false;

}



int hashTable::getSize() const {

	return msize;

}



int hashTable::getCapacity() const {

	return mcapacity;

}



bool hashTable::find(std::string value) {

	int hash = hashCode(value);

	if (hash == -1) {

		return false;

	}

	if (mtable[hash]->getSize() == 0) {

		return false;

	}

	else {

		for (int i = 0; i < mtable[hash]->getSize(); i++) {

			if (mtable[hash]->get(i) == value) {

				return true;

			}

		}

	}

	return false;

}



bool hashTable::find(std::string value, int offset) {

	int hash = hashCode(value);

	if (mtable[hash]->getSize() == 0) {

		return false;

	}

	else {

		for (int i = 0; i < mtable[hash]->getSize(); i++) {

			if (mtable[hash]->get(i) == value && mtable[hash]->getOffset(value) == offset) {

				return true;

			}

		}

	}

	return false;

}



void hashTable::setOffset(int offset, string value) {

	mtable[hashCode(value)]->setOffset(offset);

}



int hashTable::getOffset(string value) {

	return (mtable[hashCode(value)]->hashBucket::getOffset(value));

}



int main1() {

	//    hashBucket* B[2];

	//    B[0] = new hashBucket;

	//    B[1] = new hashBucket;

	//    hashTable m(100);

	//    cerr << "Contructors passed" << endl;

	//

	//    B[0]->addToBucket("Hello");    //testing the bucket class

	//    assert(B[0]->get(0) == "Hello" && B[0]->getSize() == 1);

	//    B[0]->addToBucket("Goodbye");

	//    assert(B[0]->get(0) == "Hello");

	//    assert(B[0]->get(1) == "Goodbye" && B[0]->getSize() == 2);

	//    assert(B[0]->remove("Hello"));

	//    assert(B[0]->get(0) == "Goodbye");

	//    assert(B[0]->getSize() == 1);

	//    assert(!B[0]->remove("Hello"));

	//    assert(B[0]->remove("Goodbye") && B[0]->getSize() == 0);

	//    cerr << "Bucket tests passed" << endl;

	//

	//    assert(m.getCapacity() == 100);

	//    assert(m.getSize() == 0);

	//    m.addToMap("Hello");

	//    assert(m.getSize() == 1);

	//    assert(m.find("Not Found", 0) == false);

	//    cerr << "HashTable tests passed" << endl;

	//

	//    string s = "Hello World!";

	//    int x = s.length()/2;

	//    hashTable d(x);

	//    cerr << "Variable length table constructed" << endl;



	runtest("There's a bathroom on the right.\n hello",

		"There's a bad moon on the rise.");

	runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV \n YEET",

		"XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");

	runtest("abcdefgh00000000hcdefghi",

		"abcdefghi");



	ifstream greenEggs1("/Users/megangronstad/Desktop/JProject4/JProject4/greeneggs1.txt");

	ifstream greenEggs2("/Users/megangronstad/Desktop/JProject4/JProject4/greeneggs2.txt");

	ofstream diffFile("/Users/megangronstad/Desktop/JProject4/JProject4/diff.txt");



	createDiff(greenEggs1, greenEggs2, diffFile);



	ifstream diffFile2("/Users/megangronstad/Desktop/JProject4/JProject4/diffFile2.txt");

	ifstream greenEggsOld("/Users/megangronstad/Desktop/JProject4/JProject4/greeneggs1.txt");

	ofstream result("/Users/megangronstad/Desktop/JProject4/JProject4/result.txt");





	applyDiff(greenEggsOld, diffFile2, result);



	cout << "All tests passed" << endl;



	return 0;

}



void runtest(string oldtext, string newtext) {

	istringstream oldFile(oldtext);

	istringstream newFile(newtext);

	ostringstream diffFile;

	createDiff(oldFile, newFile, diffFile);

	string result = diffFile.str();

	cout << "The diff file length is " << result.size()

		<< " and its text is " << endl;

	cout << result << endl;

	oldFile.clear();   // clear the end of file condition

	oldFile.seekg(0);  // reset back to beginning of the stream

	istringstream diffFile2(result);

	ostringstream newFile2;

	assert(applyDiff(oldFile, diffFile2, newFile2));

	assert(newtext == newFile2.str());

}



bool runtest(string oldName, string newName, string diffName, string newName2) {

	if (diffName == oldName || diffName == newName ||

		newName2 == oldName || newName2 == diffName ||

		newName2 == newName)

	{

		cerr << "Files used for output must have names distinct from other files" << endl;

		return false;

	}

	ifstream oldFile(oldName, ios::binary);

	if (!oldFile)

	{

		cerr << "Cannot open " << oldName << endl;

		return false;

	}

	ifstream newFile(newName, ios::binary);

	if (!newFile)

	{

		cerr << "Cannot open " << newName << endl;

		return false;

	}

	ofstream diffFile(diffName, ios::binary);

	if (!diffFile)

	{

		cerr << "Cannot create " << diffName << endl;

		return false;

	}

	createDiff(oldFile, newFile, diffFile);

	diffFile.close();



	oldFile.clear();   // clear the end of file condition

	oldFile.seekg(0);  // reset back to beginning of the file

	ifstream diffFile2(diffName, ios::binary);

	if (!diffFile2)

	{

		cerr << "Cannot read the " << diffName << " that was just created!" << endl;

		return false;

	}

	ofstream newFile2(newName2, ios::binary);

	if (!newFile2)

	{

		cerr << "Cannot create " << newName2 << endl;

		return false;

	}

	assert(applyDiff(oldFile, diffFile2, newFile2));

	newFile2.close();



	newFile.clear();

	newFile.seekg(0);

	ifstream newFile3(newName2, ios::binary);

	if (!newFile)

	{

		cerr << "Cannot open " << newName2 << endl;

		return false;

	}

	if (!equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),

		istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))

	{

		cerr << newName2 << " is not identical to " << newName

			<< "; test FAILED" << endl;

		return false;

	}

	return true;

}



//Function implementations

void createDiff(istream& fold, istream& fnew, ostream& fdiff) {

	const int chunkSize = 6;

	string temp;        //process the old doc

	string old = "";

	while (getline(fold, temp)) { //continues running until getline fails, stream reaches end

		old += temp;          //puts the whole file into one string

		old += '\n';

		if (temp == "") {

			old += '\n';

		}

	}



	hashTable tab(old.length() * 2);  //create a hashtable twice the size of the number of 8-bit strings



	for (int i = 0; i < old.length(); i++) {  //store 8-bit chunks into the table

		string chunk;

		if (old.length() - i > chunkSize) {

			chunk = old.substr(i, chunkSize);

		}

		else {

			chunk = old.substr(i, old.length() - i);

		}

		tab.addToMap(chunk);

		tab.setOffset(i, chunk);

	}



	int offset = 0;

	int length = chunkSize;

	string newString;       //process the new doc

	string tempNew;

	bool recog = false;

	while (getline(fnew, tempNew)) {

		newString += tempNew;
		if (temp == "") {

			newString += '\n';

		}

	}



	for (int i = 0; i < newString.length() - chunkSize;)

	{

		int offcheck = 0;

		length = (i < newString.length() - chunkSize) ? chunkSize - 1 : newString.length() - i - 1;

		if (tab.find(newString.substr(i, chunkSize))) {

			string g = newString.substr(i, chunkSize);

			offset = tab.getOffset(g);

			offcheck = offset;

		}

		while (i < newString.length() && tab.find(newString.substr(i, chunkSize), offcheck)) {

			i++; length++; offcheck++;

			recog = true;

		}

		if ((i <= (newString.length() - chunkSize)) && recog) {

			i += (chunkSize - 1);

		}

		if (recog) {

			//current offset and length should be printed as copy

			fdiff << 'C' << length << ',' << offset;

		}



		length = 0; //reset length

		string toAdd;  //create a string to add

		recog = false;  //only print if the loop runs at least once

		if (i < newString.length() - chunkSize) {

			while (i < newString.length() && !tab.find(newString.substr(i, chunkSize))) {

				toAdd += newString[i];

				length++; i++;

				recog = true;

			}

		}

		else {

			while (i < newString.length() && !tab.find(newString.substr(i, chunkSize))) {

				toAdd += newString[i];

				length++;

				i++;

				recog = true;

			}

		}

		if (recog) {

			//current length and string to be added

			fdiff << 'A' << length << ':' << toAdd;

		}

	}

}



bool applyDiff(istream& fold, istream& fdiff, ostream& fnew) {

	char ch;

	string temp;

	string oldString = "";

	string newString = "";

	while (getline(fold, temp)) {

		oldString += temp;

		oldString += '\n';

		if (temp == "") {

			oldString += '\n';

		}

	}

	int len;

	int offset;

	while (getCommand(fdiff, ch, len, offset)) {

		if (ch == 'x') {

			cerr << "Here is new(x): " << newString << endl;

			return true;

		}

		switch (ch) {

		case 'A':

			for (int i = 0; i < len; i++) {

				char ca = fdiff.get();

				newString += ca;

				fnew << ca;

			}

			break;

		case 'C':

			for (int i = offset; i < offset + len && i < oldString.size(); i++) {

				newString += oldString[i];

				fnew << oldString[i];

			}

			break;

		}

	}

	//    fnew << "Hi there";

	return false;

}



//Helper Functions

bool getInt(istream& inf, int& n) {

	char ch;

	if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))

		return false;

	inf.unget();

	inf >> n;

	return true;

}



bool getCommand(istream& inf, char& cmd, int& length, int& offset) {

	if (!inf.get(cmd))

	{

		cmd = 'x';  // signals end of file

		return true;

	}

	char ch;

	switch (cmd)

	{

	case 'A':

		return getInt(inf, length) && inf.get(ch) && ch == ':';

	case 'C':

		return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);

	case '\r':

	case '\n':

		return true;

	}

	return false;

}

int main()
{
	/*string s("Four score and seven years ago, our forefathers stepped forth on this land and put forth some ladi da that created some cool country or something, I think. And ever since then, the aliens have tried to take us over, but they have failed.");
	istringstream S(s);
	Hash<string> table = readStreamIntoTable(S, 8);
	//table.display();
	assert(table.isIn("Four sco"));
	assert(table.isIn("re and s"));
	assert(!(table.isIn("Four sc") || table.isIn("our scor")));*/
	runtest("There's a bathroom on the right.", "There's a bad moon on the rise.");
	runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV", "XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
	runtest("abcdefgh00000000bcdefghi", "abcdefghi");
	string first = "Hello we are now going to a newline:" + '\n';
	first += "This is our new line.";
	string second = "How we are not winning at all:" + '\n';
	second += "This is it. This is us.";
	runtest(first, second);
	assert(runtest("OldFile.txt", "NewFile.txt", "mydifffile.txt", "mynewfile2.txt"));
	cerr << endl << "==================" << endl << "Running five big tests now:" << endl << endl;
	assert(runtest("testenter1.txt", "testenter2.txt", "testenterDIFF.txt", "testenterAPPLIED.txt"));
	assert(runtest("greeneggs1.txt", "greeneggs2.txt", "greeneggsDIFF.txt", "greeneggsAPPLIED.txt"));
	assert(runtest("smallmart1.txt", "smallmart2.txt", "smallmartDIFF.txt", "smallmartAPPLIED.txt"));
	assert(runtest("warandpeace1.txt", "warandpeace2.txt", "warandpeaceDIFF.txt", "warandpeaceAPPLIED.txt"));
	assert(runtest("strange1.txt", "strange2.txt", "strangeDIFF.txt", "strangeAPPLIED.txt"));


	cerr << "All tests passed" << endl;
	return 0;
}