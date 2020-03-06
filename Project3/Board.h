#ifndef BOARD_D
#define BOARD_D
#include "Side.h"

class Board {
public:
	~Board();
	Board(int nHoles, int nInitialBeansPerHole);
		//Construct a Board with the indicated number of holes per side(not counting the pot) and initial number of beans per hole.If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
	Board(const Board& other);
	int holes() const { return m_nholes; }
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	//If the hole indicated by(s, hole) is empty or invalid or a pot, this function returns false without changing anything.Otherwise, it will return true after sowing the beans : the beans are removed from hole(s, hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
	bool moveToPot(Side s, int hole, Side potOwner);
	//If the indicated hole is invalid or a pot, return false without changing anything.Otherwise, move all the beans in hole(s, hole) into the pot belonging to potOwnerand return true.
	bool setBeans(Side s, int hole, int beans);
private:
	int m_nholes;
	Hole* north;
	Hole* south;
};

#endif