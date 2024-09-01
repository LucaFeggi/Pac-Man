#include "FpsManager.hpp"

FpsManager::FpsManager() :
	FpsLimit(StdBlockSize * 6),
	IterationStart(0.0),
	IterationEnd(0.0),
	ElapsedSeconds(0.0),
	Delay(0.0)
{

}

FpsManager::~FpsManager() {

}

void FpsManager::SetTime() {
	IterationStart = SDL_GetPerformanceCounter();
}

void FpsManager::CalculateDelay() {
	IterationEnd = SDL_GetPerformanceCounter();
	ElapsedSeconds = (IterationEnd - IterationStart) / (double)SDL_GetPerformanceFrequency();
	Delay = (1000.0 / (double)FpsLimit) - (ElapsedSeconds * 1000.0);
}

int FpsManager::GetDelay() {
	if (int(Delay) > 0)
		return int(Delay);
	return 0;	
}