#ifndef PACMAN_HEADERFILES_BLINKY_HPP_
#define PACMAN_HEADERFILES_BLINKY_HPP_

#include "Ghost.hpp"
#include "Pac.hpp"

class Blinky : public Ghost {
public:
	Blinky(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac);
	~Blinky();
	Vec2<int> CalculateTarget() override;
private:
	Pac* MyPac;
};

#endif