#ifndef PACMAN_HEADERFILES_READY_HPP_
#define PACMAN_HEADERFILES_READY_HPP_

#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Globals.hpp"
#include "Texture.hpp"
#include "Timer.hpp"

class Ready{
	public:
		Ready(SDL_Renderer* Renderer, TTF_Font* Font);
		~Ready();
		void StartTimer();
		void StopTimer();
		bool IsReadyEnded();
		void Draw();
		void Reset();
		void Restart();
	private:
		Texture ReadyTexture;
		SDL_Rect ReadyRect;
		Timer ReadyTimer;
		int ReadyTimerTarget;
};

#endif
