#ifndef PACMAN_HEADERFILES_FPSMANAGER_HPP_
#define PACMAN_HEADERFILES_FPSMANAGER_HPP_

#include <SDL.h>
#include "Globals.hpp"

class FpsManager {
public:
	FpsManager();
	~FpsManager();
	void SetTime();
	void CalculateDelay();
	int GetDelay();
private:
	const int FpsLimit;
	double IterationStart, IterationEnd, ElapsedSeconds, Delay;
};

#endif