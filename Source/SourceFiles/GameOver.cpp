#include "GameOver.hpp"

GameOver::GameOver(SDL_Renderer* Renderer, TTF_Font* Font) :
	GameOverTexture(Renderer)
{
	GameOverTexture.LoadFromRenderedText("GAME  OVER", Color::Red, Font);
	GameOverRect = { WindowWidth / 2 - GameOverTexture.GetWidth() / 2, 21 * StdBlockSize - GameOverTexture.GetHeight() / 4, GameOverTexture.GetWidth(), GameOverTexture.GetHeight() };
}

GameOver::~GameOver(){

}

void GameOver::Draw(){
	GameOverTexture.Render(nullptr, &GameOverRect);
}

