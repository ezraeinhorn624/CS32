#include "History.h"

#include <iostream>

using namespace std;

History::History(int nRows, int nCols):m_rows(nRows), m_cols(nCols) {
	// Position (row,col) of the arena coordinate system is represented in
	// the array element grid[row-1][col-1]
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < nRows; r++) {
		for (c = 0; c < nCols; c++) {
			m_grid[r][c] = '.';
			cerr << m_grid[r][c];
		}
		cerr << endl;
	}
}
bool History::record(int r, int c) {
	if (r > m_rows || c > m_cols)
		return false;	
	if (m_grid[r][c] == '.')
		m_grid[r][c] = 'A';
	else if (m_grid[r][c] == 'Z'){}
	else
		m_grid[r][c]++;
	return true;
}
void History::display() const {
	clearScreen();
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
			cout << m_grid[r][c];
		cout << endl;
	}
	cout << endl;
}