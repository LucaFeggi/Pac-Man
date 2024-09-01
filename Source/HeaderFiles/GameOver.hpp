#ifndef PACMAN_HEADERFILES_GAMEOVER_HPP_
#define PACMAN_HEADERFILES_GAMEOVER_HPP_

#include <SDL_ttf.h>
#include "Globals.hpp"
#include "Texture.hpp"

class GameOver{
	public:
		GameOver(SDL_Renderer* Renderer, TTF_Font* Font);
		~GameOver();
		void Draw();
	private:
		Texture GameOverTexture;
		SDL_Rect GameOverRect;
};

#endif
