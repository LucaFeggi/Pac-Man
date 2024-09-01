#include "Food.hpp"

Food::Food(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac, Score* MyScore, Level* MyLevel) :
	MyBoard(MyBoard),
	MyPac(MyPac),
	MyScore(MyScore),
	MyLevel(MyLevel),
	TotalFood(InitTotalFood(MyBoard)),
	FoodCounter(TotalFood),
	PelletTexture(Renderer),
	EnergizerTexture(Renderer),
	MyFruit(Renderer, MyBoard, MyScore, MyLevel, TotalFood),
	IsFoodSoundStarted(false)
{
	PelletTexture.LoadFromFile("Source/Textures/Pellet24.png");
	EnergizerTexture.LoadFromFile("Source/Textures/Energizer24.png");
}

void Food::SelectCurrentFruit() {
	MyFruit.SelectFruit();
}

Food::~Food(){
	MyBoard = nullptr;
	MyPac = nullptr;
	MyScore = nullptr;
	MyLevel = nullptr;
}

int Food::InitTotalFood(Board* MyBoard) {
	int Counter = 0;
	for (int y = 0; y < BoardHeight; y++) {
		for (int x = 0; x < BoardWidth; x++) {
			if (char(Tokens::Pellet) == MyBoard->GetPiece(x + y * BoardWidth)) {
				Counter++;
				continue;
			}
			if (char(Tokens::Energizer) == MyBoard->GetPiece(x + y * BoardWidth)) {
				Counter++;
				continue;
			}
		}
	}
	return Counter;
}

void Food::DespawnFruit() {
	MyFruit.Despawn();
}

const int Food::GetTotalFood() {
	return TotalFood;
}

int Food::GetFoodNumber() {
	return FoodCounter;
}

void Food::CheckPacCollision() {
	Vec2<int> Tile;
	for (int i = 0; i < 4; i++) {
		Tile = MyPac->GetTileInBoard(i, MyPac->GetPosition());
		if (MyBoard->GetPiece(Tile.x + Tile.y * BoardWidth) == char(Tokens::Pellet)) {
			MyScore->Add(10);
			FoodCounter--;
			MyBoard->ModPiece(Tile.x + Tile.y * BoardWidth, char(Tokens::Nothing));
			FoodSoundTimer.Start();
			if (!IsFoodSoundStarted) {
				IsFoodSoundStarted = true;
				Sounds::PlayFood();
			}
		}
		if (MyBoard->GetPiece(Tile.x + Tile.y * BoardWidth) == char(Tokens::Energizer)) {
			MyScore->Add(50);
			FoodCounter--;
			MyBoard->ModPiece(Tile.x + Tile.y * BoardWidth, char(Tokens::Nothing));
			MyPac->BecomeEnergized();
			FoodSoundTimer.Start();
			if (!IsFoodSoundStarted) {
				IsFoodSoundStarted = true;
				Sounds::PlayFood();
			}
		}
	}
	if (FoodSoundTimer.GetTicks() > 300) {
		Sounds::StopFood();
		IsFoodSoundStarted = false;
	}
}

bool Food::IsLevelCompleted() {
	if (FoodCounter == 0) {
		return true;
	}
	return false;
}

void Food::IncreaseLevel() {
	MyLevel->Increase();
}

void Food::Update() {
	CheckPacCollision();
	MyFruit.Update(MyPac->GetPosition(), FoodCounter);
}

void Food::Draw() {
	for (int y = 0; y < BoardHeight; y++) {
		for (int x = 0; x < BoardWidth; x++) {
			if (char(Tokens::Pellet) == MyBoard->GetPiece(x + y * BoardWidth)) {
				SDL_Rect PelletRect = { x * StdBlockSize, y * StdBlockSize, StdBlockSize, StdBlockSize };
				PelletTexture.Render(nullptr, &PelletRect);
				continue;
			}
			if (char(Tokens::Energizer) == MyBoard->GetPiece(x + y * BoardWidth)) {
				SDL_Rect EnergizerRect = { x * StdBlockSize, y * StdBlockSize, StdBlockSize, StdBlockSize };
				EnergizerTexture.Render(nullptr, &EnergizerRect);
			}
		}
	}
	MyFruit.Draw();
}

void Food::Reset() {
	FoodCounter = TotalFood;
}

void Food::Restart() {
	Reset();
	MyFruit.ResetCurrentFruit();
}
