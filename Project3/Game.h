#ifndef GAME_D
#define GAME_D
#include "Player.h"

class Game {
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const{
		return (m_board.beans(s, hole));
	}
private:
	Board m_board;
	Side whoseTurn;
	Player* south;
	Player* north;
};

#endif