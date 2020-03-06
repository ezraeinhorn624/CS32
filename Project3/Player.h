#ifndef PLAYER_D
#define PLAYER_D
#include "Board.h"
#include <string>

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
	AlarmClock(int ms)
	{
		m_timedOut = false;
		m_isRunning = true;
		m_alarmClockFuture = std::async([=]() {
			for (int k = 0; k < ms && m_isRunning; k++)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (m_isRunning)
				m_timedOut = true;
			});
	}

	~AlarmClock()
	{
		m_isRunning = false;
		m_alarmClockFuture.get();
	}

	bool timedOut() const
	{
		return m_timedOut;
	}

	AlarmClock(const AlarmClock&) = delete;
	AlarmClock& operator=(const AlarmClock&) = delete;
private:
	std::atomic<bool> m_isRunning;
	std::atomic<bool> m_timedOut;
	std::future<void> m_alarmClockFuture;
};


class Player {
public:
	Player(std::string name) : m_name(name) {}
	std::string name() const { return m_name; }
	virtual bool isInteractive() const { return false; }
	virtual int chooseMove(const Board& b, Side s) const = 0;
	//Every concrete class derived from this class must implement this function so that if the player were to be playing side sand had to make a move given board b, the function returns the move the player would choose.If no move is possible, return −1.
	virtual ~Player() {}
	//Since this class is designed as a base class, it should have a virtual destructor.
private:
	std::string m_name;
};

class HumanPlayer : public Player {
public:
	HumanPlayer(std::string name) :Player(name) {}
	bool isInteractive() const { return true; }
	int chooseMove(const Board& b, Side s) const;
	~HumanPlayer() {}
private:
};

class BadPlayer :public Player {
public:
	BadPlayer(std::string name) :Player(name) {}
	int chooseMove(const Board& b, Side s) const;
	~BadPlayer() {}
};

class SmartPlayer :public Player {
public:
	SmartPlayer(std::string name) :Player(name) {}
	int chooseMove(const Board& b, Side s) const;
	~SmartPlayer() {}
private:
	//void findMove(Board& b, Side s, int recursionDepth, int& bestHole, int& value);
};

#endif