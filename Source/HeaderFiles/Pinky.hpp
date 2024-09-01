#ifndef PACMAN_HEADERFILES_PINKY_HPP_
#define PACMAN_HEADERFILES_PINKY_HPP_

#include "Ghost.hpp"
#include "Pac.hpp"

class Pinky : public Ghost {
public:
	Pinky(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac);
	~Pinky();
	Vec2<int> CalculateTarget() override;
private:
	Pac* MyPac;
};

#endif