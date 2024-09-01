#include "Entity.hpp"

inline Vec2<int> InitPosition(Tokens Token, Board* MyBoard) {
	Vec2<int> Pos;
	for (int y = 0; y < BoardHeight; y++) {
		for (int x = 0; x < BoardWidth; x++) {
			if (char(Token) == MyBoard->GetPiece(x + y * BoardWidth)) {
				Pos.x = (x * StdBlockSize) + StdBlockSize / 2;
				Pos.y = (y * StdBlockSize);
			}

		}
	}
	return Pos;
}

Entity::Entity(Board* MyBoard, const Tokens Token) :
	MyBoard(MyBoard),
	Token(Token),
	Direction(Directions::Right),
	Position(InitPosition(Token, MyBoard)),
	DefaultPosition(Position),
	LifeStatement(true)
{

}

Entity::~Entity() {
	MyBoard = nullptr;
}


bool Entity::IsAlive() {
	return LifeStatement;
}

void Entity::Live() {
	LifeStatement = true;
}

void Entity::Die() {
	LifeStatement = false;
}

bool Entity::IsEntityColliding(Entity Other) {
	if (Other.Position.x > Position.x - StdBlockSize && Other.Position.x < Position.x + StdBlockSize)
		if (Other.Position.y > Position.y - StdBlockSize && Other.Position.y < Position.y + StdBlockSize)
			return true;
	return false;
}

Vec2<int> Entity::GetPosition() {
	return Position;
}

Vec2<int> Entity::GetTileInBoard(int Side, Vec2<int> TemporaryPosition) {
	Vec2<int> Tile = { 0, 0 };
	switch (Side) {
	case 0:
		Tile.x = floor(TemporaryPosition.x / float(StdBlockSize));
		Tile.y = floor(TemporaryPosition.y / float(StdBlockSize));
		break;
	case 1:
		Tile.x = floor(TemporaryPosition.x / float(StdBlockSize));
		Tile.y = ceil(TemporaryPosition.y / float(StdBlockSize));
		break;
	case 2:
		Tile.x = ceil(TemporaryPosition.x / float(StdBlockSize));
		Tile.y = floor(TemporaryPosition.y / float(StdBlockSize));
		break;
	case 3:
		Tile.x = ceil(TemporaryPosition.x / float(StdBlockSize));
		Tile.y = ceil(TemporaryPosition.y / float(StdBlockSize));
		break;
	default:
		break;
	}
	return Tile;
}

bool Entity::IsWallColliding(Vec2<int> TemporaryPosition, bool CanUseDoor) {
	Vec2<int> Tile;
	for(int i = 0; i < 4; i++) {
		Tile = GetTileInBoard(i, TemporaryPosition);
		if (MyBoard->GetPiece(abs(Tile.x % BoardWidth) + Tile.y * BoardWidth) == char(Tokens::Wall)) {
				return true;
		}
		if (MyBoard->GetPiece(abs(Tile.x % BoardWidth) + Tile.y * BoardWidth) == char(Tokens::Door)) {
			if (!CanUseDoor) {
				return true;
			}	
		}
	}
	return false;
}

void Entity::ResetPosition() {
	Position = DefaultPosition;
}

void Entity::WrapAround() {
	if (Position.x > WindowWidth + StdBlockSize)
		Position.x = -StdBlockSize;
	if (Position.x < -StdBlockSize)
		Position.x = WindowWidth + StdBlockSize;
}

void Entity::Move(Vec2<int>& Position) {
	switch (Direction) {
	case Directions::Up:
		Position.y -= 1;
		break;
	case Directions::Left:
		Position.x -= 1;
		break;
	case Directions::Down:
		Position.y += 1;
		break;
	case Directions::Right:
		Position.x += 1;
		break;
	default:
		break;
	}
}

Directions Entity::GetDirection() {
	return Direction;
}