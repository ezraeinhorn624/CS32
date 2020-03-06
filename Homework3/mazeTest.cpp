#include <iostream>
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
int main() {
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
	char maze1[10][10] = {
				{ 'X','X','X','X','X','X','X','X','X','X' },
				{ 'X','.','.','.','.','X','.','.','.','X' },
				{ 'X','.','X','X','.','X','X','X','.','X' },
				{ 'X','X','X','.','.','.','.','X','.','X' },
				{ 'X','.','X','X','X','.','X','X','X','X' },
				{ 'X','.','X','.','X','.','X','.','.','X' },
				{ 'X','.','.','.','X','.','X','.','.','X' },
				{ 'X','X','X','X','X','.','X','.','X','X' },
				{ 'X','.','.','.','.','.','.','.','.','X' },
				{ 'X','X','X','X','X','X','X','X','X','X' }
	};
	if (pathExists(maze, 3, 5, 8, 8))
		std::cout << "maze Solvable!" << std::endl;
	else
		std::cout << "maze: Out of luck!" << std::endl;
	if (pathExists(maze1, 4, 1, 8, 8))
		std::cout << "maze1 Solvable!" << std::endl;
	else
		std::cout << "maze1: Out of luck!" << std::endl;
	return 0;
}
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	// Return true if there is a path from (sr,sc) to (er,ec)
	// through the maze; return false otherwise
	if (sr == er && sc == ec)
		return true;
	maze[sr][sc] = 'v';
	if (maze[sr + 1][sc] == '.' && pathExists(maze, sr + 1, sc, er, ec))
		return true;
	if (maze[sr - 1][sc] == '.' && pathExists(maze, sr - 1, sc, er, ec))
		return true;
	if (maze[sr][sc + 1] == '.' && pathExists(maze, sr, sc + 1, er, ec))
		return true;
	if (maze[sr][sc - 1] == '.' && pathExists(maze, sr, sc - 1, er, ec))
		return true;
	return false;
}