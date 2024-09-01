#ifndef PACMAN_HEADERFILES_GAMESTATEMACHINE_HPP_
#define PACMAN_HEADERFILES_GAMESTATEMACHINE_HPP_

#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Texture.hpp"
#include "Timer.hpp"
#include "Board.hpp"
#include "Score.hpp"
#include "Pac.hpp"
#include "GhostsManager.hpp"
#include "Ready.hpp"
#include "GameOver.hpp"
#include "Door.hpp"
#include "Lives.hpp"
#include "Level.hpp"
#include "Food.hpp"
#include "Sounds.hpp"

constexpr enum class GameStates {
	Ready = 0, GameStarted, LevelCompleted, PacDeath, GameOver
};

class GameStateMachine {
public:
	GameStateMachine(SDL_Renderer* Renderer, Directions* Mover, bool* IsToRestart);
	~GameStateMachine();
	void Run();
private:
	GameStates ProcessReady();
	GameStates ProcessGameStarted();
	GameStates ProcessLevelCompleted();
	GameStates ProcessPacDeath();
	GameStates ProcessGameOver();
	void RunAlways();
	void RunWhenReady();
	void RunWhenGameStarted();
	void RunWhenLevelCompleted();
	void RunWhenPacDeath();
	void RunWhenGameOver();
	const int InitIMG;
	const int InitTTF;
	bool* IsToRestart;
	TTF_Font* Emulogic;
	TTF_Font* VpPixel;
	GameStates MyGameState;
	Score MyScore;
	Board MyBoard;
	Ready MyReady;
	GameOver MyGameOver;
	Door MyDoor;
	Lives MyLives;
	Level MyLevel;
	Food MyFood;
	Pac MyPac;
	GhostsManager MyGhosts;
};

#endif