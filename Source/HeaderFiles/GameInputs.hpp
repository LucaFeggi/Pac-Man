#ifndef PACMAN_HEADERFILES_GAMEINPUTS_HPP_
#define PACMAN_HEADERFILES_GAMEINPUTS_HPP_

#include <SDL.h>
#include <vector>
#include "Vec2.hpp"
#include "Timer.hpp"
#include "Globals.hpp"

class GameInputs {
public:
	GameInputs(bool* Quit, bool* IsToRestart, Directions* Mover);
	~GameInputs();
	void Get();
private:
	void Keyboard();
	void Buttons();
	void Joysticks();
	void Touch();
	bool* Quit;
	bool* IsToRestart;
	Directions* Mover;
	SDL_Event Event;
	const int JoystickDeadZone;
	std::vector<SDL_Joystick*> MyJoysticks;
	bool IsFingerDown;
	Vec2<int> FingerDownCoords;
};

#endif
