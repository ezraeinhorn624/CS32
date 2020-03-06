#include <string>
#include "globals.h"
using namespace std;

#ifndef HISTORY
#define HISTORY

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private:
	char m_grid[MAXROWS][MAXCOLS];
	int m_rows;
	int m_cols;
};


#endif