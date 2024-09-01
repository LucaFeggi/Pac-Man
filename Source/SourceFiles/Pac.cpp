#include "Pac.hpp"

Pac::Pac(SDL_Renderer* Renderer, Directions* Mover, Board* MyBoard) :
	Entity(MyBoard, Tokens::Pac),
	PacTexture(Renderer),
	MoverPointer(Mover),
	CurrentFrame(0),
	EnergyState(false),
	HasWallCollided(false),
	EnergyTimerTarget(7000)
{
	MoverPointer[0] = Directions::Right;
	MoverPointer[1] = Directions::Right;
	PacTexture.LoadFromFile("Source/Textures/Pac32.png");
	InitFrames(PacFrames, 32, PacSpriteClips);
	FrameTimer.Start();
}

Pac::~Pac() {	
	MoverPointer = nullptr;
}

void Pac::UpdateDeathFrame() {
	if (FrameTimer.GetTicks() > SlowFrameTime) {
		CurrentFrame++;
		FrameTimer.Start();
	}
}

void Pac::UpdateLiveFrame() {
	if (FrameTimer.GetTicks() > FastFrameTime) {
		CurrentFrame++;
		FrameTimer.Start();
	}
	if (CurrentFrame % 3 == 0) {
		CurrentFrame = 0;
	}
	if (CurrentFrame == 4) {
		CurrentFrame = 3;
	}
	if (HasWallCollided) {
		CurrentFrame = 3;
	}
}

void Pac::UpdatePosition() {
	HasWallCollided = false;
	Direction = MoverPointer[1];
	Vec2<int> TemporaryPosition = GetPosition();
	Move(TemporaryPosition);
	if (!IsWallColliding(TemporaryPosition)) {
		Move(Position);
		this->WrapAround();
		MoverPointer[0] = MoverPointer[1];
		return;
	}
	Direction = MoverPointer[0];
	TemporaryPosition = Position;
	Move(TemporaryPosition);
	if (!IsWallColliding(TemporaryPosition)) {
		Move(Position);
		WrapAround();
		return;
	}
	HasWallCollided = true;
}

void Pac::UpdateEnergyState() {
	if (EnergyTimer.GetTicks() > EnergyTimerTarget) {
		LoseEnergy();
	}
}

bool Pac::IsEnergized() {
	return EnergyState;
}

void Pac::BecomeEnergized() {
	EnergyState = true;
	EnergyTimer.Start();
}

int Pac::GetEnergyTimerTicks() {
	return EnergyTimer.GetTicks();
}

Directions Pac::GetDirection() {
	return Direction;
}

bool Pac::IsAnimationEnded() {
	if (CurrentFrame % PacFrames == 0) {
		CurrentFrame = 0;
		return true;
	}
	return false;
}

void Pac::SetFrame(int NewFrame) {
	CurrentFrame = NewFrame;
}

void Pac::Death() {
	Die();
	Sounds::PlayPacDeath();
	SetFrame(1);
}

void Pac::Draw() {
	SDL_Rect PacRect = { Position.x - EntityBlockSize / 6, Position.y - EntityBlockSize / 6, EntityBlockSize, EntityBlockSize };
	PacTexture.Render(&PacSpriteClips[CurrentFrame], &PacRect, GetTextureFacing());
}

void Pac::Reset() {
	Position = DefaultPosition;
	CurrentFrame = 0;
	MoverPointer[0] = Directions::Right;
	MoverPointer[1] = Directions::Right;
	HasWallCollided = false;
	EnergyState = false;
	Live();
	FrameTimer.Start();
}

void Pac::Restart() {
	Reset();
}

Directions Pac::GetTextureFacing() {
	Directions RenderDirection = Directions::Up;
	switch (Direction) {
	case Directions::Up:
		RenderDirection = Directions::Right;
		break;
	case Directions::Left:
		RenderDirection = Directions::Down;
		break;
	case Directions::Down:
		RenderDirection = Directions::Left;
		break;
	case Directions::Right:
		RenderDirection = Directions::Up;
		break;
	default:
		break;
	}
	return RenderDirection;
}

void Pac::LoseEnergy() {
	EnergyState = false;
	EnergyTimer.Stop();
}
