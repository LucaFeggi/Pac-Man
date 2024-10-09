#include "Game.hpp"
#include "Sounds.hpp"

Game::Game() :
	InitSDL(SDL_Init(SDL_INIT_EVERYTHING)),
	Window(SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_SKIP_TASKBAR)),//SDL_WINDOW_BORDERLESS | 
	Renderer(SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)),
	Quit(false),
	IsToRestart(false),
	Mover{ Directions::Right, Directions::Right },
	MyGameInputs(&Quit, &IsToRestart, Mover),
	MyFpsManager(),
	MyGameStateMachine(Renderer, Mover, &IsToRestart)
{
	
}

Game::~Game() {
	Sounds::Destructor();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();	
}

void Game::Run() {
	while (!Quit) {
		MyFpsManager.SetTime();
		MyGameInputs.Get();
		if(Quit) {
			break;
		}
		SDL_RenderClear(Renderer);
		MyGameStateMachine.Run();
		SDL_RenderPresent(Renderer);
		MyFpsManager.CalculateDelay();
		SDL_Delay(MyFpsManager.GetDelay());
	}
}
