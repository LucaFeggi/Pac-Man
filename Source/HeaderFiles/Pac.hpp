#ifndef PACMAN_HEADERFILES_PAC_HPP_
#define PACMAN_HEADERFILES_PAC_HPP_

#include <SDL.h>
#include "Texture.hpp"
#include "Timer.hpp"
#include "Entity.hpp"
#include "Board.hpp"
#include "Sounds.hpp"

class Pac : public Entity{
public:
	Pac(SDL_Renderer* Renderer, Directions* Mover, Board* MyBoard);
	~Pac();
	void UpdateDeathFrame();
	void UpdateLiveFrame();
	void UpdatePosition();
	void UpdateEnergyState();
	bool IsEnergized();
	void BecomeEnergized();
	int GetEnergyTimerTicks();
	Directions GetDirection();
	bool IsAnimationEnded();
	void SetFrame(int Frame);
	void Death();
	void Draw();
	void Reset();
	void Restart();
private:
	Directions GetTextureFacing();
	void LoseEnergy();
	Texture PacTexture;
	Directions* MoverPointer;
	int CurrentFrame;
	bool EnergyState;
	bool HasWallCollided;
	static constexpr int PacFrames = 10;
	SDL_Rect PacSpriteClips[PacFrames];
	Timer FrameTimer;
	Timer EnergyTimer;
	int EnergyTimerTarget;
};

#endif