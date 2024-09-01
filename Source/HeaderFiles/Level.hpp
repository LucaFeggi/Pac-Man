#ifndef PACMAN_HEADERFILES_LEVEL_HPP_
#define PACMAN_HEADERFILES_LEVEL_HPP_

#include <SDL.h>

class Level{
	public:
		Level();
		~Level();
		int Get();
		void Increase();
		void Restart();
	private:
		int MyLevel;
};

#endif
