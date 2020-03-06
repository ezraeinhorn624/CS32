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

#include "Game.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool move(const AlarmClock& ac, Board& b, Side s, int hole, int depth) {
	if (b.beansInPlay(s) == 0 || b.beansInPlay(opponent(s)) == 0) {
		for (int i = 1; i <= b.holes(); i++) {
			b.moveToPot(NORTH, i, NORTH);
			b.moveToPot(SOUTH, i, SOUTH);
		}
		return true;
	}
	Side ES;
	int EH;
	if (!b.sow(s, hole, ES, EH)) {	return false;	}
	if (ES == s) {
		if (EH == POT) {
			int hole, val = 0, numHoles = b.holes();
			if (depth == 0) depth = 1;
			findMove(ac, b, s, depth, hole, val, numHoles);
			move(ac, b, s, hole, depth);
		}
		else if (b.beans(s, EH) == 1 && b.beans(opponent(s), EH) > 0) {
			b.moveToPot(opponent(ES), EH, ES);
			b.moveToPot(ES, EH, ES);
		}
	}
	return true;
}
void findMove(const AlarmClock& ac, const Board& b, Side s, int recursionDepth, int& bestHole, int& value, int numHoles) {
	if (ac.timedOut()) {
		cerr << "timed out at top" << endl;
		return;
	}
	if (recursionDepth == 0 && !(b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0 || b.beans(SOUTH, POT) > b.totalBeans() / 2 || b.beans(NORTH, POT) > b.totalBeans() / 2)) {
		bestHole = -1;
		value = (b.beans(NORTH, POT) - b.beans(SOUTH, POT));
		return;
	}
	if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0) {
	//	cerr << "Beans in play is zero on some side" << endl;
		bestHole = -1;
		if (b.beansInPlay(SOUTH) + b.beans(SOUTH, POT) > b.beansInPlay(NORTH) + b.beans(NORTH, POT))
			value = -1000;
		else if (b.beansInPlay(SOUTH) + b.beans(SOUTH, POT) < b.beansInPlay(NORTH) + b.beans(NORTH, POT))
			value = 1000;
		else
			value = 0;
		return;
	}
	if (b.beans(SOUTH, POT) > b.totalBeans() / 2) {
	//	cerr << "Pot has more than half" << endl;
		bestHole = -1;
		value = -1000;
		return;
	}
	if (b.beans(NORTH, POT) > b.totalBeans() / 2) {
	//	cerr << "Pot has more than half" << endl;
		bestHole = -1;
		value = 1000;
		return;
	}
	for (int i = 1; i <= numHoles; i++) {
		if (ac.timedOut()) {
			cerr << "Timed out on hole " << i << endl;
			return;
		}
		if (b.beans(s, i) != 0) {
							//if (b.beans(s, bestHole) < 1) bestHole = i;
			Board c(b);
			int h2, v2 = -1000;
			if (s == NORTH) v2 = 1000;
			if (move(ac, c, s, i, recursionDepth - 1)) {
				findMove(ac, c, opponent(s), recursionDepth - 1, h2, v2, numHoles);
							//if (recursionDepth == 3) cerr << i << "  ";
							//cerr << "i is " << i << "\tFindMove called by side " << s << " at depth " << recursionDepth << ".\tv2 is " << v2 << ". \tValue is " << value << endl;
							//display(c);
				if ((s == NORTH && v2 > value) || (s == SOUTH && v2 < value)) {//this if statement never triggers if depth>1. Why is that?
							//	cerr << "Value / v2: \t" << value << " / " << v2 << "   \tUpdating bestHole to: " << i << endl;
					value = v2;
					bestHole = i;
				}
			}
		}
	}
	return;
}

void doGameTests() {
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&	g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 && g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	//g.display();
	g.move();	

	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	//g.display();
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
	g.move();
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
	g.move();
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
	g.move();
	//   0  0  0
	// 1         4
	//   0  0  0
	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4);
	assert(g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0);
	assert(g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);
	cout << "=====================" << endl << endl;
	HumanPlayer E("Ezra");
	BadPlayer B("Alec");
	//ga.play();
	SmartPlayer S("Smarty");
	Board testSmart(3, 2);
	testSmart.setBeans(SOUTH, 2, 1);
	testSmart.setBeans(NORTH, 2, 1);
	//assert(S.chooseMove(testSmart, SOUTH) == 2); ///LETS MAKE SURE THAT THIS IS STILL SMART
	
	
}
void doBoardTests(){
	Board b(6, 4);                  ////     N0  /4/4/4/4/4/4/  S0  /4/4/4/4/4/4/
	assert(b.holes() == 6);
	assert(b.beans(NORTH, 3) == 4);
	assert(b.beansInPlay(NORTH) == 24);
	assert(b.totalBeans() == 48);
	Side endSide = SOUTH;
	int endHole = 0;
	assert(b.sow(SOUTH, 3, endSide, endHole));    ////  N0  /4/4/4/4/4/4/  S1  /4/4/0/5/5/5/
	assert(endSide == SOUTH);
	assert(endHole == POT);//is this what endHole should be if it is South's pot?
	assert(b.beans(SOUTH, 3) == 0);
	assert(b.beans(SOUTH, 4) == 5);
	assert(b.moveToPot(NORTH, 2, SOUTH));          //// N0  /4/0/4/4/4/4/   S5  /4/4/0/5/5/5/
	assert(b.beans(NORTH, 2) == 0);
	assert(b.setBeans(SOUTH, 5, 2));              //// N0  /4/0/4/4/4/4/   S5  /4/4/0/5/2/5/
	assert(b.totalBeans() == 45);
	Board B(3, 2);							////   N0  /2/2/2/    S0   /2/2/2/
	assert(B.holes() == 3 && B.totalBeans() == 12 && B.beans(SOUTH, POT) == 0 && B.beansInPlay(SOUTH) == 6);
	B.setBeans(SOUTH, 1, 1);               ////   N0  /2/2/2/    S0   /1/2/2/
	B.moveToPot(SOUTH, 2, SOUTH);	       ////   N0  /2/2/2/    S2   /1/0/2/
	assert(B.totalBeans() == 11 && B.beans(SOUTH, 1) == 1 && B.beans(SOUTH, 2) == 0);
	assert(B.beans(SOUTH, POT) == 2 && B.beansInPlay(SOUTH) == 3);
	Side es;
	int eh;
	B.sow(SOUTH, 3, es, eh);		////   N0  /2/2/3/    S3   /1/0/0/
	assert(es == NORTH && eh == 3);
	assert(B.beans(SOUTH, 3) == 0);
	assert(B.beans(NORTH, 3) == 3 && B.beans(SOUTH, POT) == 3);
	assert(B.beansInPlay(SOUTH) == 1 && B.beansInPlay(NORTH) == 7);
	B.setBeans(NORTH, 1, 3);        ////   N0  /3/2/3/    S3   /1/0/0/
	assert(B.beans(NORTH, 1) == 3);
	B.sow(NORTH, 3, es, eh);
	//B.display();
	assert(B.beans(NORTH, POT) == 1 && B.beans(NORTH, 1) == 4 && 
		B.beans(NORTH, 2) == 3 && B.beans(NORTH, 3) == 0);
	Board testSmart(3, 2);
	assert(testSmart.setBeans(SOUTH, 2, 1) && testSmart.setBeans(NORTH, 2, 1));
	Board testFunct(testSmart);
	assert(testFunct.holes() == 3 && testFunct.beansInPlay(SOUTH) == 5 &&
		testFunct.beansInPlay(NORTH) == 5 && testFunct.beans(SOUTH, 1) == 2 &&
		testFunct.beans(NORTH, 2) == 1 && testFunct.beans(NORTH, 4) == -1 &&
		testFunct.beans(SOUTH, -1) == -1 && testFunct.totalBeans() == 10);
	Board so(4, 3);
	assert(so.setBeans(SOUTH, 2, 0) && so.setBeans(SOUTH, 3, 0));
	assert(so.beansInPlay(SOUTH) == 6 && so.beansInPlay(NORTH) == 12);
	assert(!so.sow(SOUTH, 0, endSide, endHole) && !so.sow(SOUTH, 5, endSide, endHole) &&
		!so.sow(SOUTH, 2, endSide, endHole) && so.sow(SOUTH, 1, endSide, endHole));
	assert(endSide == SOUTH && endHole == 4 && so.beans(SOUTH, 1) == 0 && 
		so.beans(SOUTH, 2) == 1 && so.beans(SOUTH, 4) == 4);
	assert(so.sow(SOUTH, 2, endSide, endHole) && so.sow(SOUTH, 3, endSide, endHole));
	assert(endSide == SOUTH && endHole == POT);

	assert(so.setBeans(NORTH, 2, 0) && so.setBeans(NORTH, 3, 0));
	assert(so.beansInPlay(SOUTH) == 5 && so.beansInPlay(NORTH) == 6);
	assert(!so.sow(NORTH, 0, endSide, endHole) && !so.sow(NORTH, 5, endSide, endHole) &&
		!so.sow(NORTH, 2, endSide, endHole) && so.sow(NORTH, 4, endSide, endHole));
	assert(endSide == NORTH && endHole == 1 && so.beans(NORTH, 4) == 0 &&
		so.beans(NORTH, 2) == 1 && so.beans(NORTH, 1) == 4);
	assert(so.sow(NORTH, 3, endSide, endHole) && so.sow(NORTH, 2, endSide, endHole));
	assert(endSide == NORTH && endHole == POT);
	assert(so.moveToPot(NORTH, 2, NORTH));
	BadPlayer D("Ezra");
	BadPlayer C("Avery");
	Game sg(so, &D, &C);
	bool over, win;
	Side who;
	sg.status(over, win, who);
	assert(!over);
	assert(so.moveToPot(NORTH, 1, SOUTH));
	for (int i = 0; i < so.holes(); i++)
		assert(so.beans(NORTH, i + 1) == 0);
	Game NEW(so, &D, &C);
	//sg = NEW;
	assert(so.beansInPlay(NORTH) == 0);
	NEW.status(over, win, who);
	assert(over);
	assert(win&& who == SOUTH);
}
void doPlayerTests() {
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge" && hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	SmartPlayer sp("Lisa");
	assert(sp.name() == "Lisa" && !sp.isInteractive());
	Board p(3, 2);
	p.setBeans(SOUTH, 2, 0);
	cout << "=========" << endl;
	int n = hp.chooseMove(p, SOUTH);
	cout << "=========" << endl;
	assert(n == 1 || n == 3);
	n = bp.chooseMove(p, SOUTH);
	assert(n == 1 || n == 3);
	n = sp.chooseMove(p, SOUTH);
	assert(n == 1 || n == 3);

}
int main() {

	//doBoardTests();
	cerr << "All tests passed for Board.cpp" << endl;

	//doPlayerTests();
	cerr << "All tests passed for Player.cpp" << endl;

	//doGameTests();  ///need some tests for if south starts with zero beans... see if it does the right thing
	cerr << "All tests passed for Game.cpp" << endl;
	SmartPlayer s("Smarty");
	HumanPlayer h("Ezra");
	BadPlayer b("Dummy");
	Board bo(6, 4);
	Board c(bo);
	Board d(c);
	Game g(bo, &h, &s);
	Game ha(c, &h, &b);
	Game i(d, &s, &b);
	g.play();
	ha.play();
	i.play();

	return 0;
}