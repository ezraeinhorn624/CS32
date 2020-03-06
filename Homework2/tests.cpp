#include <string>
#include <cassert>
#include <iostream>

//EVAL TESTS
int main1()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	//new tests
	assert(evaluate("T&F", pf, answer) == 0 && pf == "TF&" && !answer);
	assert(evaluate("T(^F)", pf, answer) == 1);
	assert(evaluate("((T^F)", pf, answer) == 1);
	assert(evaluate("(T&T)^F", pf, answer) == 0 && pf == "TT&F^" && answer);

	cout << "Passed all tests" << endl;
}

//MAZE TESTS
int main2() {
	char maze[10][10] = {
				{ 'X','X','X','X','X','X','X','X','X','X' },
				{ 'X','.','.','.','.','X','.','.','.','X' },
				{ 'X','.','X','X','.','X','X','X','.','X' },
				{ 'X','X','X','.','.','.','.','X','.','X' },
				{ 'X','.','X','X','X','.','X','X','X','X' },
				{ 'X','.','X','.','.','.','X','.','.','X' },
				{ 'X','.','.','.','X','.','X','.','.','X' },
				{ 'X','X','X','X','X','.','X','.','X','X' },
				{ 'X','.','.','.','.','.','.','.','.','X' },
				{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 3, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
	return 0;
}