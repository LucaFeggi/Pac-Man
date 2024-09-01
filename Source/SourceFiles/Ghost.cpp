#include "Ghost.hpp"

Ghost::Ghost(SDL_Renderer* Renderer, Board* MyBoard, const Tokens Token, const SDL_Color GhostColor) :
	Entity(MyBoard, Token),
	ScatterTarget(InitScatterTarget(Token, MyBoard)),
	Target(ScatterTarget),
	DoorTarget(InitDoorTarget(MyBoard)),
	HomeTarget(InitHomeTarget(Token, DefaultPosition)),
	LeftHomeTarget{ 11 * StdBlockSize + StdBlockSize / 2, HomeTarget.y },
	RightHomeTarget{ 15 * StdBlockSize + StdBlockSize / 2 , HomeTarget.y },
	CurrentBodyFrame(0),
	CurrentEyeFrame(int(Direction)),
	GhostBodyTexture(Renderer),
	GhostEyesTexture(Renderer),
	GhostBodySpriteClips{},
	GhostEyesSpriteClips{},
	FrameTimer(),
	GhostColor(GhostColor),
	CanUseDoor(false)
{
	GhostBodyTexture.LoadFromFile("Source/Textures/GhostBody32.png");
	GhostEyesTexture.LoadFromFile("Source/Textures/GhostEyes32.png");
	InitFrames(GhostBodyFrames, 32, GhostBodySpriteClips);
	InitFrames(GhostEyesFrames, 32, GhostEyesSpriteClips);
	GhostBodyTexture.SetColor(GhostColor);
	FrameTimer.Start();
}

Ghost::~Ghost() {
	
}

void Ghost::Death() {
	Die();
	Sounds::PlayGhostEaten();
}

void Ghost::DefaultColor() {
	GhostBodyTexture.SetColor(GhostColor);
	GhostEyesTexture.SetColor(Color::White);
}

bool Ghost::IsHome() {
	if (Position.x >= 11 * StdBlockSize && Position.x <= 17 * StdBlockSize) {
		if (Position.y >= 17 * StdBlockSize && Position.y <= 20 * StdBlockSize) {
			return true;
		}
	}
	return false;
}

void Ghost::UpdatePosRand() {
	CalcRandDir(int(Direction));
	Move(Position);
}

void Ghost::UpdatePosNonRand() {
	CalcNonRandDir(int(Direction));
	Move(Position);
}

void Ghost::UpdateEyeFrame() {
	CurrentEyeFrame = int(Direction);
}

void Ghost::BlueFlash() {
	GhostBodyTexture.SetColor(Color::Blue);
	GhostEyesTexture.SetColor(Color::White);
}

void Ghost::WhiteFlash() {
	GhostBodyTexture.SetColor(Color::White);
	GhostEyesTexture.SetColor(Color::Red);
}

void Ghost::Draw() {
	SDL_Rect GhostRect = { Position.x - EntityBlockSize / 6, Position.y - EntityBlockSize / 6, EntityBlockSize, EntityBlockSize };
	if (IsAlive())
		GhostBodyTexture.Render(&GhostBodySpriteClips[CurrentBodyFrame], &GhostRect);
	GhostEyesTexture.Render(&GhostEyesSpriteClips[CurrentEyeFrame], &GhostRect);
}

void Ghost::Reset() {
	Direction = Directions::Right;
	CurrentEyeFrame = int(Direction);
	Position = DefaultPosition;
	Live();
	CanUseDoor = false;
	GhostBodyTexture.SetColor(GhostColor);
	GhostEyesTexture.SetColor(Color::White);
}

void Ghost::Restart() {
	Reset();
}

void Ghost::UpdateBodyFrame() {
	if (FrameTimer.GetTicks() > FastFrameTime) {
		CurrentBodyFrame++;
		if (IsAlive() && CurrentBodyFrame % GhostBodyFrames == 0)
			CurrentBodyFrame = 0;
		FrameTimer.Start();
	}
}

void Ghost::CalcPossDir(std::vector<int>& Distances, std::vector<Directions>& PossibleDirections) {
	for (int i = 0; i < Distances.size(); i++) {
		for (int j = 0; j < Distances.size(); j++) {
			if (Distances.at(i) < Distances.at(j)) {
				float temp1 = Distances.at(i);
				Distances.at(i) = Distances.at(j);
				Distances.at(j) = temp1;
				Directions temp2 = PossibleDirections.at(i);
				PossibleDirections.at(i) = PossibleDirections.at(j);
				PossibleDirections.at(j) = temp2;
			}
		}
	}
}

void Ghost::CalcNonRandDir(int Buffer) {
	std::vector<int> Distances;
	std::vector<Directions> PossibleDirections;
	Vec2<int> TemporaryPosition;
	for (int i = 0; i < 4; i++) {
		TemporaryPosition = Position;
		Direction = Directions(i);
		Move(TemporaryPosition);
		if (!IsWallColliding(TemporaryPosition, CanUseDoor)) {
			int DistSq, DistX;
			DistX = abs(TemporaryPosition.x - Target.x);
			if (DistX > WindowWidth / 2)
				DistX = WindowWidth - DistX;
			DistSq = pow(DistX, 2) + pow(TemporaryPosition.y - Target.y, 2);
			Distances.push_back(DistSq);
			PossibleDirections.push_back(Direction);
		}
	}
	if (PossibleDirections.size() == 1) {
		Direction = PossibleDirections.at(0);
		return;
	}
	CalcPossDir(Distances, PossibleDirections);
	for (int i = 0; i < PossibleDirections.size(); i++) {
		if (Buffer != ((int(PossibleDirections.at(i)) + 2) % 4)) {
			Direction = PossibleDirections.at(i);
			return;
		}
	}
}

void Ghost::CalcRandDir(int Buffer) {
	std::vector<Directions> MyDirections = {Directions::Up, Directions::Down, Directions::Left, Directions::Right};
	while(!MyDirections.empty()) {
		int i = rand() % MyDirections.size();
		Directions PossDir = MyDirections.at(i);
		if (Buffer == ((int(PossDir) + 2) % 4)) {
			MyDirections.erase(MyDirections.begin() + i);
			continue;
		}
		Direction = PossDir;
		Vec2<int> TemporaryPosition = Position;
		Move(TemporaryPosition);
		if (!IsWallColliding(TemporaryPosition, CanUseDoor)) {
			return;
		}
		MyDirections.erase(MyDirections.begin() + i);
	}
	Direction = Directions((Buffer + 2) % 4);
}

Tokens Ghost::InitScatterToken(Tokens Token) {
	Tokens ScatterToken = Tokens::BlinkyScatterTarget;
	switch (Token) {
	case Tokens::Blinky:
		ScatterToken = Tokens::BlinkyScatterTarget;
		break;
	case Tokens::Inky:
		ScatterToken = Tokens::InkyScatterTarget;
		break;
	case Tokens::Pinky:
		ScatterToken = Tokens::PinkyScatterTarget;
		break;
	case Tokens::Clyde:
		ScatterToken = Tokens::ClydeScatterTarget;
		break;
	default:
		break;
	}
	return ScatterToken;
}

Vec2<int> Ghost::InitScatterTarget(Tokens Token, Board* MyBoard) {
	Vec2<int> Pos = { 0, 0 };
	Tokens ScatterToken = InitScatterToken(Token);
	for (int y = 0; y < BoardHeight; y++) {
		for (int x = 0; x < BoardWidth; x++) {
			if (char(ScatterToken) == MyBoard->GetPiece(x + y * BoardWidth)) {
				Pos.y = y * StdBlockSize;
				Pos.x = x * StdBlockSize;
				return Pos;
			}
		}
	}
	return Pos;
}

Vec2<int> Ghost::InitDoorTarget(Board* MyBoard) {
	Vec2<int> Pos = { 0, 0 };
	for (int y = 0; y < BoardHeight; y++) {
		for (int x = 0; x < BoardWidth; x++) {
			if (char(Tokens::Blinky) == MyBoard->GetPiece(x + y * BoardWidth)) {
				Pos.x = x * StdBlockSize + StdBlockSize / 2;
				Pos.y = y * StdBlockSize;
				return Pos;
			}
		}
	}
	return Pos;
}

Vec2<int> Ghost::InitHomeTarget(Tokens Token, Vec2<int> DefaultPosition) {
	if (Token == Tokens::Blinky) {
		Vec2<int> HomeTarget = DefaultPosition;
		HomeTarget.y += 3 * StdBlockSize;
		return HomeTarget;
	}
	return DefaultPosition;
}

void Ghost::HomeMovement() {
	if (Target == HomeTarget) {
		if (Position == HomeTarget) {
			Target = LeftHomeTarget;
		}
	}
	if (Target == LeftHomeTarget) {
		if (Position == LeftHomeTarget) {
			Target = RightHomeTarget;
		}
	}
	if (Target == RightHomeTarget) {
		if (Position == RightHomeTarget) {
			Target = LeftHomeTarget;
		}
	}
}