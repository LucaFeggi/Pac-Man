#include "Clyde.hpp"

Clyde::Clyde(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac) :
	Ghost(Renderer, MyBoard, Tokens::Clyde, Color::Orange),
	MyPac(MyPac)
{

}

Clyde::~Clyde() {
	MyPac = nullptr;
}

Vec2<int> Clyde::CalculateTarget() {
	int DistX = abs(Position.x - MyPac->GetPosition().x);
	if (DistX > WindowWidth / 2)
		DistX = WindowWidth - DistX;
	float Dist = static_cast<float>(sqrt(pow(DistX, 2) + pow(Position.y - MyPac->GetPosition().y, 2)));
	if (int(Dist) < 8 * StdBlockSize)
		return ScatterTarget;
	return MyPac->GetPosition();
}