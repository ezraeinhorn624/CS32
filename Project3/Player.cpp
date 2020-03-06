#include "Player.h"
#include <iostream>

int HumanPlayer::chooseMove(const Board& b, Side s) const {
	if (b.beansInPlay(s) == 0)
		return -1;
	std::cout << "Choose a hole for your turn: ";
	std::string choice;
	std::getline(std::cin, choice);
	int ichoice = 0;
	for (size_t i = 0; i < choice.size(); i++) {
		char c = choice[i];
		if (c == ' ' || c == '\n' || c == '\t');
		else if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9') {
			std::cout << "That is not a valid positive integer. Try again." << std::endl;
			return chooseMove(b, s);
		}
		else
			ichoice = ichoice * 10 + c - 48;
	}
	if (ichoice<1 || ichoice>b.holes() || b.beans(s,ichoice)==0) {
		std::cout << "That is not a valid hole number. Try again." << std::endl;
		return chooseMove(b, s);
	}
	//Side endSide;
	//int endHole;
	return ichoice;
}
int BadPlayer::chooseMove(const Board& b, Side s) const {
	if (b.beansInPlay(s) == 0)
		return -1;
	int m_nholes = b.holes();
	int choice = (rand() % m_nholes) + 1;
	while (b.beans(s,choice)==0)
		choice = (rand() % m_nholes) + 1;
	return choice;
}
int SmartPlayer::chooseMove(const Board& b, Side s) const {
	AlarmClock ac(4800);
	int hole = 1, value = 1000, numHoles = b.holes();
	if (s == NORTH) value = -1000;
	Board c(b);
	findMove(ac, c, s, 6, hole, value, numHoles);
	if (hole < 1 || hole > b.holes() || b.beans(s,hole) < 1) {
		if (b.beansInPlay(s) != 0) {
			std::cerr << "Smart computer is going random..." << std::endl;
			int m_nholes = b.holes();
			int choice = (rand() % m_nholes) + 1;
			while (b.beans(s, choice) == 0)
				choice = (rand() % m_nholes) + 1;
			return choice;
		}
	}
	std::cerr << "Computer chose hole: " << hole << std::endl;
	return hole;
}