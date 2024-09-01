#include "Door.hpp"

Door::Door(SDL_Renderer* Renderer) :
	DoorTexture(Renderer),
	DoorRect{ 13 * StdBlockSize, 16 * StdBlockSize + int(StdBlockSize * 0.6f), 2 * StdBlockSize, StdBlockSize / 3 }
{
	DoorTexture.LoadFromFile("Source/Textures/Door24.png");
}

Door::~Door(){
	
}

void Door::Draw(){
	DoorTexture.Render(nullptr, &DoorRect);
}
