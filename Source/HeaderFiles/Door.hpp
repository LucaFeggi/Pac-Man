#ifndef PACMAN_HEADERFILES_DOOR_HPP_
#define PACMAN_HEADERFILES_DOOR_HPP_

#include "Texture.hpp"

class Door{
	public:
		Door(SDL_Renderer* Renderer);
		~Door();
		void Draw();
	private:
		Texture DoorTexture;
		SDL_Rect DoorRect;
};

#endif
