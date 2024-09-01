#ifndef PACMAN_HEADERFILES_BOARD_HPP_
#define PACMAN_HEADERFILES_BOARD_HPP_

#include <SDL.h>
#include "Texture.hpp"
#include "Timer.hpp"

class Board {
public:
	Board(SDL_Renderer* Renderer);
	~Board();
	std::string Get();
	char GetPiece(int Index);
	void ModPiece(int Index, char Substitute);
	void StartAnimationTimer();
	void StopAnimationTimer();
	void Animation();
	bool IsAnimationCompleted();
	void Draw();
	void Reset();
	void Restart();
private:
	const std::string DefaultSketch;
	std::string ActualSketch;
	Texture BoardTexture;
	Timer AnimationTimer;
};

#endif