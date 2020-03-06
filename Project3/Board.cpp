#include "Board.h"
Board::Board(int nHoles, int nInitialBeansPerHole) :m_nholes(nHoles) {
	if (nHoles < 1) { 
		m_nholes = 1;
		nHoles = 1;
	}
	if (nInitialBeansPerHole < 0) { 
		nInitialBeansPerHole = 0;
	}
	north = new Hole;
	south = new Hole;
	Hole* ptr = south;
	for (int i = 0; i < m_nholes; i++) {
		ptr->next = new Hole;
		ptr = ptr->next;
		ptr->beans = nInitialBeansPerHole;
	}
	ptr->next = north;
	ptr = ptr->next;
	for (int i = 0; i < m_nholes; i++) {
		ptr->next = new Hole;
		ptr = ptr->next;
		ptr->beans = nInitialBeansPerHole;
	}
	ptr->next = south;
}
Board::Board(const Board& other):m_nholes(other.holes()) {
	north = new Hole;
	south = new Hole;
	Hole* ptr = south;
	for (int i = 0; i < m_nholes; i++) {
		ptr->next = new Hole;
		ptr = ptr->next;
	}
	ptr->next = north;
	ptr = ptr->next;
	for (int i = 0; i < m_nholes; i++) {
		ptr->next = new Hole;
		ptr = ptr->next;
	}
	ptr->next = south;
	north->beans = other.beans(NORTH, POT);
	south->beans = other.beans(SOUTH, POT);
	for (int i = 0; i < m_nholes; i++) {
		setBeans(NORTH, i + 1, other.beans(NORTH, i + 1));
		setBeans(SOUTH, i + 1, other.beans(SOUTH, i + 1));
	}
}
Board::~Board() {
	if (m_nholes == 0) {
		if (north != nullptr)
			delete north;
		if (south != nullptr)
			delete south;
	}
	else {
		for (int i = 0; i < m_nholes; i++) {
			Hole* ptr = south;
			ptr = ptr->next;
			south->next = ptr->next;
			delete ptr;			
		}
		delete south;
		for (int i = 0; i < m_nholes; i++) {
			Hole* ptr = north;
			ptr = ptr->next;
			north->next = ptr->next;
			delete ptr;
		}
		delete north;
	}
}
int Board::beans(Side s, int hole) const {
	if (hole > m_nholes || hole < 0) return -1;
	if (hole == 0) {
		if (s == NORTH)
			return north->beans;
		else if (s == SOUTH)
			return south->beans;
	}
	Hole* ptr = north;
	if (s == NORTH) {
		hole = m_nholes + 1 - hole;
		ptr = south;
	}
	
	for (int i = 0; i < hole; i++)
		ptr = ptr->next;
	return ptr->beans;
}
int Board::beansInPlay(Side s) const {
	int nBeans = 0;
	Hole* ptr = north;
	if (s == NORTH)
		ptr = south;
	for (int i = 0; i < m_nholes; i++) {
		nBeans += ptr->next->beans;
		ptr = ptr->next;
	}
	return nBeans;
}
int Board::totalBeans() const{
	int number = 0;
	Hole* ptr = north;
	number += ptr->beans;
	ptr = ptr->next;
	while (ptr != north) {
		number += ptr->beans;
		ptr = ptr->next;
	}
	return number;
}
bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
	Hole* ptr = north;								//establishing the head of our search for a hole
	if (s == NORTH) {								//making sure it's the right head
		ptr = south;
		hole = m_nholes + 1 - hole;
	}
	for (int i = 0; i < hole; i++)					//loop through to find the exact hole in question
		ptr = ptr->next;
	if (hole <= 0 || hole > m_nholes || ptr->beans == 0) //check for invalid input (s,hole)
		return false;
	Hole* opponentsPOT = south;					//makes sure we know where the pots are so we only put in our pot
	Hole* myPOT = north;
	if (s == SOUTH) {
		opponentsPOT = north;
		myPOT = south;
	}
	int beansInHand = ptr->beans; //we pick up all the beans
	ptr->beans = 0;				  // now there are none left in the hole
	endSide = s;
	Side otherSide = opponent(s);
	
	while (beansInHand != 0) { //this will continue placing beans until we are out
		if (ptr->next != opponentsPOT) { //make sure not to place any in opponent's pot
			ptr->next->beans++;
			beansInHand--;
		}
		if (ptr->next == myPOT && beansInHand > 0) //if we are going to end up on the other side...say so
			endSide = otherSide;
		else if (ptr == opponentsPOT) //otherwise we are going to end up on our side
			endSide = s;
		ptr = ptr->next; //loop to the next hole
	}
	endHole = 0;
	while (ptr != north && ptr != south) {
		endHole++;
		ptr = ptr->next;
	}
	if (endSide == SOUTH) {
		endHole = m_nholes + 1 - endHole;
		if (endHole == m_nholes + 1)
			endHole = 0;
	}
	return true;
}
bool Board::moveToPot(Side s, int hole, Side potOwner) {
	if (hole <= 0 || hole > m_nholes) // checks input is valid
		return false;
	if (s == NORTH)
		hole = m_nholes + 1 - hole;
	Hole* targetPot = north; //the pot we are shooting for 
	Hole* otherPotAKAhead = south;  //the head of our loop for finding the hole
	if (potOwner == SOUTH)
		targetPot = south;
	if (s == SOUTH)
		otherPotAKAhead = north;
	Hole* ptr = otherPotAKAhead; //starts our loop out at the head of our side
	for (int i = 0; i < hole; i++) {
		ptr = ptr->next;             //finds the right hole to take beans out of
	}

	targetPot->beans += ptr->beans;       //puts the beans into the potOwner's pot
	ptr->beans = 0;                //resets beans in hole to zero

	return true;	
}
bool Board::setBeans(Side s, int hole, int beans) {
	if (hole == 0) {
		if (s == NORTH)
			north->beans = beans;
		else if (s == SOUTH)
			south->beans = beans;
		return true;
	}
	if (s == NORTH)
		hole = m_nholes + 1 - hole;
	if (beans < 0 || hole<0 || hole>m_nholes)
		return false;
	Hole* head = south;
	if (s == SOUTH)
		head = north;
	for (int i = 0; i < hole; i++) {
		head = head->next;
	}
	head->beans = beans;
	return true;
}