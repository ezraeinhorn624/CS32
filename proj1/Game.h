#ifndef GAME
#define GAME

#include "Arena.h"
#include "Player.h"
#include "Zombie.h"


using namespace std;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nZombies);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;
};
#endif