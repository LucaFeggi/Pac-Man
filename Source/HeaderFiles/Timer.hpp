#ifndef PACMAN_HEADERFILES_TIMER_HPP_
#define PACMAN_HEADERFILES_TIMER_HPP_

#include <SDL.h>
#include <stdint.h>

class Timer{
public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	void Pause();
	void Unpause();
	uint32_t GetTicks();
	bool IsStarted();
	bool IsPaused();
private:
	uint32_t StartTicks;
	uint32_t PausedTicks;
	bool Paused;
	bool Started;
};

#endif