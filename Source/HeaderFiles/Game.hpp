#ifndef PACMAN_HEADERFILES_GAME_HPP_
#define PACMAN_HEADERFILES_GAME_HPP_

#include <SDL.h>

#include "Globals.hpp"
#include "GameInputs.hpp"
#include "FpsManager.hpp"
#include "GameStateMachine.hpp"

class Game {
	public:
		Game();
		~Game();
		void Run();
	private:	
		const int InitSDL;
		SDL_Window* Window;
		SDL_Renderer* Renderer;
		bool Quit;
		bool IsToRestart;
		Directions Mover[2];
		GameInputs MyGameInputs;
		FpsManager MyFpsManager;
		GameStateMachine MyGameStateMachine;
};

#endif