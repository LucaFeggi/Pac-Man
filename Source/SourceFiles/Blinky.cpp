#include "Blinky.hpp"

Blinky::Blinky(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac) :
	Ghost(Renderer, MyBoard, Tokens::Blinky, Color::Red),
	MyPac(MyPac)
{

}

Blinky::~Blinky() {
	MyPac = nullptr;
}

Vec2<int> Blinky::CalculateTarget() {
	return MyPac->GetPosition();
}