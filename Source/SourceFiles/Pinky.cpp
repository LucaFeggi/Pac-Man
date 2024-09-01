#include "Pinky.hpp"

Pinky::Pinky(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac) :
	Ghost(Renderer, MyBoard, Tokens::Pinky, Color::Pink),
	MyPac(MyPac)
{

}

Pinky::~Pinky() {
	MyPac = nullptr;
}

Vec2<int> Pinky::CalculateTarget() {
	Vec2<int> TemporaryPosition = MyPac->GetPosition();
	switch (MyPac->GetDirection()) {
		case Directions::Up:
			TemporaryPosition.y -= 4 * StdBlockSize;
			TemporaryPosition.x -= 4 * StdBlockSize;
			break;
		case Directions::Left:
			TemporaryPosition.x -= 4 * StdBlockSize;
			break;
		case Directions::Down:
			TemporaryPosition.y += 4 * StdBlockSize;
			break;
		case Directions::Right:
			TemporaryPosition.x += 4 * StdBlockSize;
			break;
		default:
			break;
	}
	return TemporaryPosition;
}