#include "Lives.hpp"

Lives::Lives(SDL_Renderer* Renderer, Score* MyScore) :
	MyLives(5),
	GotExtraLife(false),
	LivesTexture(Renderer),
	MyScore(MyScore)
{
	LivesTexture.LoadFromFile("Source/Textures/Lives32.png");
}

Lives::~Lives(){
	MyScore = nullptr;
}

bool Lives::IsExtraLife(){
	if (!GotExtraLife && MyScore->Get() >= 10000) {
		GotExtraLife = true;
		return true;
	}
	return false;
}

void Lives::Increase(){
	MyLives++;
}

void Lives::Decrease(){
	MyLives--;
}

int Lives::Get(){
	return MyLives;
}

void Lives::Draw(){
	for (int i = 0; i < MyLives - 1; i++) {
		SDL_Rect LivesRect = { (i * int(1.25f * StdBlockSize)) + StdBlockSize / 2, (BoardHeight - 1) * StdBlockSize - StdBlockSize / 2, StdBlockSize, StdBlockSize };
		LivesTexture.Render(nullptr, &LivesRect);
	}
}

void Lives::Restart(){
	MyLives = 5;
	GotExtraLife = false;
}

void Lives::PlayExtraLifeSound() {
	Sounds::PlayExtraLife();
}
