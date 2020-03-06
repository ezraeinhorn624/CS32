#include "Hash.h"
#include <fstream>
#include <sstream>
#include <cassert>
using namespace std;
#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

bool getInt(istream& inf, int& n)
{
	char ch;
	if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
		return false;
	inf.unget();
	inf >> n;
	return true;
}
bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
	if (!inf.get(cmd))
	{
		cmd = 'x';  // signals end of file
		return true;
	}
	char ch;
	//cout << "character is " << cmd << endl;
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
	cerr << "exited getCommand because no valid char" << endl;
	return false;
}
Hash<string> readStreamIntoTable(istream& stream, int chunk){
	string stringVersion;
	char c;
	while (stream.get(c)) {
		stringVersion += c;
	}
	
	cerr << "old is : " << stringVersion << endl;
	int size = stringVersion.size();// / chunk;
	Hash<string> table(size);
	for (int i = 0; i < stringVersion.size(); i++) {
		string temp = "";
		for (int j = i; j < i + chunk && j < stringVersion.size(); j++) { // i*chunk
			temp += stringVersion[j];
		}
		table.insert(temp, i);
	}
	//table.display();
	return table;
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff) {
	AlarmClock ac(14800);
	const int chunkSize = 6;		//size of chunk stored in hash table
	int chunk = chunkSize;
	char c;
	Hash<string> table = readStreamIntoTable(fold, chunk); //member function to give us our hash table

	string news, olds, getlineTemp;
	//while (getline(fnew, getlineTemp)) { news += getlineTemp; } //get a string version of new
	while (fnew.get(c)) { news += c; }
	
	cerr << "New is : " << news << '(' << news.size() << ')' << endl;
	int counter = 0;									//
	for (int i = 0; i < news.size();) {					//loop through the new string
		if (ac.timedOut()) {
			cerr << "Alarm Clock timed out in CreateDiff outside loop" << endl;
			//exit(1);
		}
		chunk = chunkSize;
		string temp = "";
		bool atEnd = false;
		for (int j = 0; j < chunk && ((j + i) < news.size()); j++) {  //what chunk are we examining from fnew
			temp += news[i+j];
			if (j + i == news.size() - 1) { 
				chunk = j + 1; 
				atEnd = true;
			}
		} 

		if (table.isIn(temp)) {						//if we are at a match...
			if (counter != 0) {
				fdiff << 'A' << counter << ':';
				for (int j = i - counter; j < i && j < news.size(); j++)
					fdiff << news[j];
				counter = 0;
			}				//if we have gone a little while since a match, ADD everything in between
			int L = chunk;
			i++;
			int originalMatchOffset = table.offset(temp);	//store the offset of our original match b/c
			while (table.isIn(temp) && !atEnd) {	
				if (ac.timedOut()) {
					cerr << "Alarm Clock timed out in Create Diff inside loop" << endl;
					//exit(1);
				}
				//now we are going to search for matches right after our match
				int matchOffset = table.offset(temp);
				temp = "";
				int j = i;
				int stopper = j + chunk;
				for (; j < stopper && j < news.size() && !atEnd; j++) {
					temp += news[j];
					if (j == news.size() - 1) atEnd = true;
				}
				if (table.isIn(temp) && (table.offset(temp, matchOffset) == matchOffset + 1)) {
					L++;
					i++;
				}
				else break;
			}
			i += chunk;
			i--;
			fdiff << 'C' << L << ',' << originalMatchOffset;	//add the complete match to the diff file
		}
		else {   // if no match, increase the counter
			counter++;
			i++;
		}
		if (i == news.size() - 1 && counter != 0) { //but if we are at the end (and we didn't JUST match)
			counter++;
			fdiff << 'A' << counter << ':';     //then add our stuff to the diff file
			for (int j = 0; j < counter; j++)
				fdiff << news[news.size() - counter + j];
			break;
		}
	}
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew) {
	AlarmClock ac(4800);
	char ch, c;
	string olds = "";
	string news = "";
	string getlineTemp;
	int counter = 0;
	//while (getline(fold, getlineTemp)) { olds += getlineTemp; }
	while (fold.get(c)) { olds += c; }
	int len;
	int off;
	while (getCommand(fdiff, ch, len, off)) {
		if (ac.timedOut()) {
			cerr << "Alarm Clock timed out in apply diff" << endl;
			//exit(1);
		}
		if (ch == 'x') {
			cerr << "Here is new(x): " << news << endl;
			return true;
		}
		switch (ch) {
		case 'A':
			for (int j = 0; j < len; j++) {
				char ca = fdiff.get();
				news += ca;
				fnew << ca;
			}
			break;
		case 'C':
			for (int j = off; j < off + len; j++) {
				news += olds[j];
				fnew << olds[j];
			}
			break;
		}
	}
	cerr << "Here is new(no x): " << news << endl;
	return false;
}

void runtest(string oldtext, string newtext)
{
	istringstream oldFile(oldtext, ios::binary);
	istringstream newFile(newtext, ios::binary);
	ostringstream diffFile;
	createDiff(oldFile, newFile, diffFile);
	string result = diffFile.str();
	cerr << "The old file length is " << oldtext.size() << endl;
 	cerr << "The diff file length is " << result.size()
		<< " and its text is " << endl;
	cerr << result << endl;

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the stream
	istringstream diffFile2(result, ios::binary);
	ostringstream newFile2;
	assert(applyDiff(oldFile, diffFile2, newFile2));
	assert(newtext == newFile2.str());
}
bool runtest(string oldName, string newName, string diffName, string newName2)
{
	if (diffName == oldName || diffName == newName || newName2 == oldName || newName2 == diffName || newName2 == newName)
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

int main1()
{
	/*string s("Four score and seven years ago, our forefathers stepped forth on this land and put forth some ladi da that created some cool country or something, I think. And ever since then, the aliens have tried to take us over, but they have failed.");
	istringstream S(s);
	Hash<string> table = readStreamIntoTable(S, 8);
	//table.display();
	assert(table.isIn("Four sco"));
	assert(table.isIn("re and s"));
	assert(!(table.isIn("Four sc") || table.isIn("our scor")));*/
	runtest("There's a bathroom on the right.",	"There's a bad moon on the rise.");
	runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",	"XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
	runtest("abcdefgh00000000bcdefghi", "abcdefghi");
	string first = "Hello we are now going to a newline:" + '\n';
	first += "This is our new line.";
	string second = "How we are not winning at all:" + '\n';
	second += "This is it. This is us.";
	runtest(first, second);
	assert(runtest("OldFile.txt", "NewFile.txt", "mydifffile.txt", "mynewfile2.txt"));
	cerr << endl << "==================" << endl << "Running four big tests now:" << endl << endl;
	assert(runtest("testenter1.txt", "testenter2.txt", "testenterDIFF.txt", "testenterAPPLIED.txt"));
	assert(runtest("greeneggs1.txt", "greeneggs2.txt", "greeneggsDIFF.txt", "greeneggsAPPLIED.txt"));
	assert(runtest("smallmart1.txt", "smallmart2.txt", "smallmartDIFF.txt", "smallmartAPPLIED.txt"));
	assert(runtest("warandpeace1.txt", "warandpeace2.txt", "warandpeaceDIFF.txt", "warandpeaceAPPLIED.txt"));
	//assert(runtest("strange1.txt", "strange2.txt", "strangeDIFF.txt", "strangeAPPLIED.txt"));

	
	cerr << "All tests passed" << endl;
}