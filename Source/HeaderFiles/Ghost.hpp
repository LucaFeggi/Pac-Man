#ifndef PACMAN_HEADERFILES_GHOST_HPP_
#define PACMAN_HEADERFILES_GHOST_HPP_

#include <SDL_mixer.h>
#include <vector>
#include "Texture.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"
#include "Entity.hpp"
#include "Sounds.hpp"

class Ghost : public Entity{
public:
	Ghost(SDL_Renderer* Renderer, Board* MyBoard, const Tokens Token, const SDL_Color GhostColor);
	~Ghost();
	bool IsHome();
	void UpdatePosRand();
	void UpdatePosNonRand();
	void UpdateEyeFrame();
	void BlueFlash();
	void WhiteFlash();
	void Draw();
	void Reset();
	void Restart();
	void DefaultColor();
	void UpdateBodyFrame();
	void Death();
	void HomeMovement();
	virtual Vec2<int> CalculateTarget() = 0;
	const Vec2<int> DoorTarget;
	const Vec2<int> HomeTarget;
	const Vec2<int> ScatterTarget;
	Vec2<int> Target;
	bool CanUseDoor;
	int CurrentEyeFrame;
private:
	void CalcPossDir(std::vector<int>& Distances, std::vector<Directions>& PossibleDirections);
	void CalcNonRandDir(int Buffer);
	void CalcRandDir(int Buffer);
	Vec2<int> InitScatterTarget(Tokens Token, Board* MyBoard);
	Vec2<int> InitDoorTarget(Board* MyBoard);
	Vec2<int> InitHomeTarget(Tokens Token, Vec2<int> DefaultPosition);
	Tokens InitScatterToken(Tokens Token);
	static constexpr int GhostBodyFrames = 6;
	static constexpr int GhostEyesFrames = 5;
	const SDL_Color GhostColor;
	int CurrentBodyFrame;
	Texture GhostBodyTexture;
	Texture GhostEyesTexture;
	SDL_Rect GhostBodySpriteClips[GhostBodyFrames];
	SDL_Rect GhostEyesSpriteClips[GhostEyesFrames];
	Timer FrameTimer;
	const Vec2<int> LeftHomeTarget;
	const Vec2<int> RightHomeTarget;
};
	
#endif
