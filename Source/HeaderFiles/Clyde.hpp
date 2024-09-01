#ifndef PACMAN_HEADERFILES_CLYDE_HPP_
#define PACMAN_HEADERFILES_CLYDE_HPP_

#include "Ghost.hpp"
#include "Pac.hpp"

class Clyde : public Ghost {
public:
	Clyde(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac);
	~Clyde();
	Vec2<int> CalculateTarget() override;
private:
	Pac* MyPac;
};

#endif