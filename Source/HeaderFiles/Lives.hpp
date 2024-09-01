#ifndef PACMAN_HEADERFILES_LIVES_HPP_
#define PACMAN_HEADERFILES_LIVES_HPP_

#include <SDL_mixer.h>
#include "Texture.hpp"
#include "Score.hpp"
#include "Sounds.hpp"

class Lives{
	public:
		Lives(SDL_Renderer* MyRenderer, Score* MyScore);
		~Lives();
		bool IsExtraLife();
		void Increase();
		void Decrease();
		int Get();
		void Draw();
		void Restart();
		void PlayExtraLifeSound();
	private:
		int MyLives;
		bool GotExtraLife;
		Texture LivesTexture;
		Score* MyScore;
};

#endif
