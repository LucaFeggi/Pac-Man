#ifndef PACMAN_HEADERFILES_FRUIT_HPP_
#define PACMAN_HEADERFILES_FRUIT_HPP_

#include <SDL.h>
#include <sstream>
#include "Board.hpp"
#include "Pac.hpp"
#include "Score.hpp"
#include "Level.hpp"
#include "Sounds.hpp"

class Fruit {
public:
	Fruit(SDL_Renderer* Renderer, Board* MyBoard, Score* MyScore, Level* MyLevel, const int TotalFood);
	~Fruit();
	void SelectFruit();
	void Despawn();
	void Update(Vec2<int> PacPosition, int FoodCounter);
	void Draw();
	void ResetCurrentFruit();
	void ResetScore();
private:
	SDL_Rect GetFruitRect(Board* MyBoard);
	bool IsToSpawn(int FoodCounter);
	void Spawn();
	bool IsToDespawn();
	bool IsEatable();
	bool IsPacColliding(Vec2<int> PacPosition);
	void Collision();
	void SpawnScore();
	bool IsScoreToDespawn();
	void DespawnScore();
	int GetScore();
	Score* MyScore;
	Level* MyLevel;
	static constexpr int TotalFruits = 8;
	const int ScoreTable[TotalFruits];
	const int TotalFood;
	const int FirstFruitSpawned;
	const int SecondFruitSpawned;
	int LastFoodCounter;
	int CurrentFruit;
	int FruitDuration;
	Texture FruitTexture;
	SDL_Rect FruitRect;
	Texture FruitScoreTexture;
	TTF_Font* FruitFont;
	Timer FruitTimer;
	Timer FruitScoreTimer;
	SDL_Rect FruitSpriteClips[TotalFruits];
};

#endif