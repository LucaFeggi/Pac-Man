#ifndef PACMAN_HEADERFILES_INKY_HPP_
#define PACMAN_HEADERFILES_INKY_HPP_

#include "Ghost.hpp"
#include "Blinky.hpp"
#include "Pac.hpp"

class Inky : public Ghost {
public:
	Inky(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac, Blinky* MyBlinky);
	~Inky();
	Vec2<int> CalculateTarget() override;
private:
	Blinky* MyBlinky;
	Pac* MyPac;
};

#endif