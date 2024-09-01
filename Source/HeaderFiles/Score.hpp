#ifndef PACMAN_HEADERFILES_SCORE_HPP_
#define PACMAN_HEADERFILES_SCORE_HPP_

#include <SDL.h>
#include <SDL_ttf.h>
#include <fstream>
#include <sstream>
#include "Texture.hpp"

class Score {
	public:
		Score(SDL_Renderer* Renderer, TTF_Font* Font);
		~Score();
		void Update();
		void Draw();
		void Add(int x);
		unsigned int Get();
		void Restart();
private:
		void InitHighScore();
		void TermHighScore();
		void UpdateScoreTexture();
		void UpdateHighScoreTexture();
		TTF_Font* Font;
		Texture MyTextures[4];	//ScoreValueTexture, ScoreWordTexture, HighScoreValueTexture, HighScoreWordTexture
		unsigned int ActualScore;
		unsigned int OldScore;
		unsigned int HighScore;
};

#endif


