#include "Inky.hpp"

Inky::Inky(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac, Blinky* MyBlinky) :
	Ghost(Renderer, MyBoard, Tokens::Inky, Color::Cyan),
	MyBlinky(MyBlinky),
	MyPac(MyPac)
{

}

Inky::~Inky() {
	MyBlinky = nullptr;
	MyPac = nullptr;
}

Vec2<int> Inky::CalculateTarget() {
	Vec2<int> TemporaryPosition[2];
	TemporaryPosition[0] = MyPac->GetPosition();
	switch (MyPac->GetDirection()) {
		case Directions::Up:
			TemporaryPosition[0].y -= 2 * StdBlockSize;
			break;
		case Directions::Left:
			TemporaryPosition[0].x -= 2 * StdBlockSize;
			break;
		case Directions::Down:
			TemporaryPosition[0].y += 2 * StdBlockSize;
			break;
		case Directions::Right:
			TemporaryPosition[0].x += 2 * StdBlockSize;
			break;
		default:
			break;
	}
	TemporaryPosition[1] = { TemporaryPosition[0].x - MyBlinky->GetPosition().x, TemporaryPosition[0].y - MyBlinky->GetPosition().y};
	Vec2<int> FinalTarget = { TemporaryPosition[0].x + TemporaryPosition[1].x, TemporaryPosition[0].y + TemporaryPosition[1].y };
	return FinalTarget;
}