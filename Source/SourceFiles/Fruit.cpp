#include "Fruit.hpp"

Fruit::Fruit(SDL_Renderer* Renderer, Board* MyBoard, Score* MyScore, Level* MyLevel, const int TotalFood) :
	MyScore(MyScore),
	MyLevel(MyLevel),
	ScoreTable{ 100, 300, 500, 700, 1000, 2000, 3000, 5000 },
	TotalFood(TotalFood),
	FirstFruitSpawned(TotalFood - int(TotalFood * 0.3f)),
	SecondFruitSpawned(TotalFood - int(TotalFood * 0.8f)),
	LastFoodCounter(TotalFood),
	CurrentFruit(0),
	FruitDuration(9000),
	FruitTexture(Renderer),
	FruitRect(GetFruitRect(MyBoard)),
	FruitScoreTexture(Renderer),
	FruitFont(TTF_OpenFont("Source/Fonts/VpPixel.ttf", StdBlockSize))
{
	FruitTexture.LoadFromFile("Source/Textures/Fruit32.png");
	InitFrames(TotalFruits, 32, FruitSpriteClips);
}

Fruit::~Fruit() {
	MyScore = nullptr;
	MyLevel = nullptr;
}

void Fruit::SelectFruit() {
	if (MyLevel->Get() > 21) {
		if (CurrentFruit != 7)
			CurrentFruit = 7;
		return;
	}
	CurrentFruit = static_cast<unsigned char>(floor(MyLevel->Get() / 3.0f));
}

void Fruit::Despawn() {
	FruitTimer.Stop();
}

void Fruit::Update(Vec2<int> PacPosition, int FoodCounter) {
	if (IsToDespawn())
		Despawn();
	if (IsToSpawn(FoodCounter))
		Spawn();
	if (IsPacColliding(PacPosition))
		Collision();
	if (IsScoreToDespawn())
		DespawnScore();
}

void Fruit::Draw() {
	if (IsEatable()) {
		FruitTexture.Render(&FruitSpriteClips[CurrentFruit], &FruitRect);
	}
	if (FruitScoreTimer.IsStarted()) {
		std::stringstream String;
		String << ScoreTable[CurrentFruit];
		FruitScoreTexture.LoadFromRenderedText(String.str(), Color::White, FruitFont);
		SDL_Rect FruitScoreRect = { WindowWidth / 2 - FruitScoreTexture.GetWidth() / 2, FruitRect.y, FruitScoreTexture.GetWidth(), FruitScoreTexture.GetHeight() };
		FruitScoreTexture.Render(nullptr, &FruitScoreRect);
	}
}

void Fruit::ResetCurrentFruit() {
	CurrentFruit = 0;
}

void Fruit::ResetScore() {
	FruitScoreTimer.Stop();
}

SDL_Rect Fruit::GetFruitRect(Board* MyBoard) {
	SDL_Rect FruitRect = {};
	for (int y = 0; y < BoardHeight; y++) {
		for (int x = 0; x < BoardWidth; x++) {
			if (char(Tokens::Fruit) == MyBoard->GetPiece(x + y * BoardWidth)) {
				return FruitRect = { x * StdBlockSize + EntityBlockSize / 6, y * StdBlockSize - EntityBlockSize / 6, EntityBlockSize, EntityBlockSize };
			}
		}
	}
	return FruitRect;
}

bool Fruit::IsToSpawn(int FoodCounter) {
	if (FoodCounter == FirstFruitSpawned || FoodCounter == SecondFruitSpawned) {
		if (LastFoodCounter != FoodCounter) {
			LastFoodCounter = FoodCounter;
			if (!FruitTimer.IsStarted())
				return true;
		}
	}
	return false;
}

void Fruit::Spawn() {
	FruitTimer.Start();
}

bool Fruit::IsToDespawn() {
	if (FruitTimer.GetTicks() > FruitDuration)
		return true;
	return false;
}

bool Fruit::IsEatable() {
	if (FruitTimer.IsStarted())
		return true;
	return false;
}

bool Fruit::IsPacColliding(Vec2<int> PacPosition) {
	SDL_Rect PacRect = { PacPosition.x - EntityBlockSize / 6, PacPosition.y - EntityBlockSize / 6, EntityBlockSize, EntityBlockSize };
	if (SDL_HasIntersection(&FruitRect, &PacRect) && IsEatable())
		return true;
	return false;
}

void Fruit::Collision() {
	Despawn();
	SpawnScore();
	MyScore->Add(GetScore());
	Sounds::PlayFruit();
}

void Fruit::SpawnScore() {
	FruitScoreTimer.Start();
}

bool Fruit::IsScoreToDespawn() {
	if (FruitScoreTimer.GetTicks() > 1000)
		return true;
	return false;
}

void Fruit::DespawnScore() {
	FruitScoreTimer.Stop();
}

int Fruit::GetScore() {
	return ScoreTable[CurrentFruit];
}