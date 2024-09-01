#include "Level.hpp"

Level::Level() :
	MyLevel(0)
{
	
}

Level::~Level(){

}

int Level::Get(){
	return MyLevel;
}

void Level::Increase(){
	MyLevel++;
}

void Level::Restart(){
	MyLevel = 0;
}
