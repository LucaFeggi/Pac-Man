#ifndef PACMAN_HEADERFILES_FOOD_HPP_
#define PACMAN_HEADERFILES_FOOD_HPP_

#include <SDL.h>
#include "Texture.hpp"
#include "Vec2.hpp"
#include "Board.hpp"
#include "Pac.hpp"
#include "Score.hpp"
#include "Level.hpp"
#include "Fruit.hpp"
#include "Sounds.hpp"

class Food{
public:
	Food(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac, Score* MyScore, Level* MyLevel);
	~Food();
	void CheckPacCollision();
	bool IsLevelCompleted();
	const int GetTotalFood();
	int GetFoodNumber();
	void IncreaseLevel();
	void Update();
	void Draw();
	void Reset();
	void Restart();
	void SelectCurrentFruit();
	void DespawnFruit();
	int InitTotalFood(Board* MyBoard);
	void StopFoodSound() {
		Sounds::StopFood();
	}
	void ResetFruitScore() {
		MyFruit.ResetScore();
	}
private:
	Board* MyBoard;
	Pac* MyPac;
	Score* MyScore;
	Level* MyLevel;
	const int TotalFood;
	int FoodCounter;
	Texture PelletTexture;
	Texture EnergizerTexture;
	bool IsFoodSoundStarted;
	Timer FoodSoundTimer;
	Fruit MyFruit;
};

#endif
