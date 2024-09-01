#ifndef PACMAN_HEADERFILES_GHOSTMANAGER_HPP_
#define PACMAN_HEADERFILES_GHOSTMANAGER_HPP_

#include <sstream>
#include "Blinky.hpp"
#include "Inky.hpp"
#include "Pinky.hpp"
#include "Clyde.hpp"
#include "Score.hpp"
#include "GhostStateMachine.hpp"
#include "Sounds.hpp"

class GhostsManager{
public:
	GhostsManager(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac, TTF_Font* Font, Score* MyScore);
	~GhostsManager();
	void Update();
	void Reset();
	void Restart();
	void Draw();
	void UpdateBodyFrame();
private:
	void CollisionChecking();
	void UpdateScorer(int i);
	void ResetScorer();
	void DrawScorers();
	bool IsToPlayFrighSound();
	bool IsToStopFrighSound();
	void PlayFrighSound();
	void StopFrighSound();
	bool IsToResetScorer();
	Blinky MyBlinky;
	Inky MyInky;
	Pinky MyPinky;
	Clyde MyClyde;
	static constexpr int GhostsNumber = 4;
	GhostStateMachine MyGhostsStateMachines[GhostsNumber];
	Texture ScoresTextures[GhostsNumber];
	Timer ScoresTimers[GhostsNumber];
	SDL_Rect ScoresRects[GhostsNumber];
	const int DefaultScorer;
	int Scorer;
	Score* MyScore;
	TTF_Font* Font;
	bool IsFrighPlayable;
	Pac* MyPac;
};

#endif
