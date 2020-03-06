#include <stack>

class Coord;
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	// Return true if there is a path from (sr,sc) to (er,ec)
	// through the maze; return false otherwise
	std::stack<Coord> s;
	Coord start(sr, sc);
	s.push(start);
	maze[sr][sc] = 's';
	while (!s.empty()) {
		Coord u = s.top();
		s.pop();
		int ro = u.r();
		int co = u.c();
		if (ro == er && co == ec)
			return true;
		if (maze[ro + 1][co] == '.') {
			s.push(Coord(ro + 1, co));
			maze[ro + 1][co] = 't';
		}
		if (maze[ro][co - 1] == '.') {
			s.push(Coord(ro, co - 1));
			maze[ro][co - 1] = 't';
		}
		if (maze[ro - 1][co] == '.') {
			s.push(Coord(ro - 1, co));
			maze[ro - 1][co] = 't';
		}
		if (maze[ro][co + 1] == '.') {
			s.push(Coord(ro, co + 1));
			maze[ro][co + 1] = 't';
		}
	}
	return false;
}