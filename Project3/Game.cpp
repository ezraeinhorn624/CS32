#include "Game.h"
#include <iostream>

Game::Game(const Board& b, Player* south, Player* north) :m_board(b.holes(), 0), whoseTurn(SOUTH), south(south), north(north) {
	int holes = m_board.holes();
	m_board.setBeans(NORTH, POT, b.beans(NORTH, POT));
	m_board.setBeans(SOUTH, POT, b.beans(SOUTH, POT));
	for (int i = 0; i < holes; i++) {
		m_board.setBeans(SOUTH, i + 1, b.beans(SOUTH, i + 1));
		m_board.setBeans(NORTH, i + 1, b.beans(NORTH, i + 1));
	}
}
void Game::display() const {
	std::cout << "               ";
	for (int i = 0; i < m_board.holes(); i++) {
		std::cout << " ";
	}
	std::cout << "North: " << north->name() << std::endl << "                ";
	for (int i = 0; i < m_board.holes(); i++) {
		std::cout << m_board.beans(NORTH, i + 1) << "  ";
	}
	std::cout << std::endl << "North's Pot  " << m_board.beans(NORTH, POT);
	for (int i = 0; i < m_board.holes(); i++) {
		std::cout << "   ";
	}
	std::cout << "  " << m_board.beans(SOUTH, POT) << "  South's Pot" << std::endl << "                ";
	for (int i = 0; i < m_board.holes(); i++) {
		std::cout << m_board.beans(SOUTH, i + 1) << "  ";
	}
	std::cout << std::endl << "               ";
	for (int i = 0; i < m_board.holes(); i++) {
		std::cout << " ";
	}
	std::cout << "South: " << south->name() << std::endl << std::endl;
}
void Game::status(bool& over, bool& hasWinner, Side& winner) const {
	if (m_board.beansInPlay(NORTH) != 0 && m_board.beansInPlay(SOUTH) != 0) {
		over = false;
		return;
	}
	over = true;
	
	if (m_board.beans(NORTH, POT) == m_board.beans(SOUTH, POT)) {
		hasWinner = false;
		return;
	}
	hasWinner = true;
	if (m_board.beans(NORTH, POT) > m_board.beans(SOUTH, POT)) {
		winner = NORTH;
		return;
	}
	winner = SOUTH;
	return;
}
bool Game::move() {
	if (m_board.beansInPlay(whoseTurn) == 0 || m_board.beansInPlay(opponent(whoseTurn)) == 0) {// || m_board.beans(SOUTH, POT) > m_board.totalBeans() / 2 || m_board.beans(NORTH, POT) > m_board.totalBeans() / 2) {
		for (int i = 0; i < m_board.holes(); i++) {
			m_board.moveToPot(opponent(whoseTurn), i + 1, opponent(whoseTurn));
			m_board.moveToPot(whoseTurn, i + 1, whoseTurn);
		}
		return false;
	}
	Player* turns = south;
	if (whoseTurn == NORTH) turns = north;
	Side ES;
	int EH, choice = turns->chooseMove(m_board, whoseTurn);
	std::cerr << "Choice is " << choice << std::endl;
	m_board.sow(whoseTurn, choice, ES, EH);
	if (ES == whoseTurn) {
		if (EH == POT) {
			display();
			return move();
		}
		if (m_board.beans(whoseTurn, EH) == 1 && m_board.beans(opponent(ES), EH) > 0) {
			m_board.moveToPot(opponent(ES), EH, ES);
			m_board.moveToPot(ES, EH, ES);
		}
	}
	whoseTurn = opponent(whoseTurn);
	return true;
}
void Game::play() {
	display();
	if (m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0)
		move();
	bool isOver, isHasWinner;
	Side isWinner;
	std::string Swinner = "North";
	status(isOver, isHasWinner, isWinner);
	if (isOver) {
		Player* winner = north;
		if (isWinner == SOUTH) {
			winner = south;
			Swinner = "South";
		}
		if (!isHasWinner)
			std::cout << "The game ended in a tie." << std::endl;
		else
			std::cout << Swinner << ", " << winner->name() << ", has won the game." << std::endl;
		return;
	}
	if (!south->isInteractive() && !north->isInteractive()) {
		std::cout << "Press enter to continue ";
		std::cin.ignore(10000000, '\n');
	}
	move();
	play();
}