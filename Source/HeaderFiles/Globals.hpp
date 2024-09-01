#ifndef PACMAN_HEADERFILES_GLOBALS_HPP_
#define PACMAN_HEADERFILES_GLOBALS_HPP_

#include <SDL.h>

constexpr int StdBlockSize = 20;
constexpr int BoardWidth = 28, BoardHeight = 37;
constexpr int WindowHeight = StdBlockSize * BoardHeight;
constexpr int WindowWidth = StdBlockSize * BoardWidth;
constexpr int EntityBlockSize = StdBlockSize / 2 * 3;
constexpr int FastFrameTime = 80;
constexpr int SlowFrameTime = 140;

constexpr enum class Directions {
	Up = 0, Left, Down, Right
};

namespace Color {
	constexpr SDL_Color Black = {0, 0, 0};
	constexpr SDL_Color White = {255, 255, 255};
	constexpr SDL_Color Blue = {0, 0, 255};
	constexpr SDL_Color Yellow = {255, 255, 0};
	constexpr SDL_Color Red = {255, 0, 0};
	constexpr SDL_Color Cyan = {0, 192, 255};
	constexpr SDL_Color Pink = {255, 192, 203};
	constexpr SDL_Color Orange = {255, 128, 0};
};

inline void InitFrames(int TextureFrames, int TextureBlockSize, SDL_Rect SpriteClips[]) {
	int Counter = 0;
	for (int i = 0; i < TextureFrames; i++) {
		SpriteClips[i].x = Counter;
		SpriteClips[i].y = 0;
		SpriteClips[i].w = TextureBlockSize;
		SpriteClips[i].h = TextureBlockSize;
		Counter += TextureBlockSize;
	}
}

constexpr enum class Tokens : char {
	Nothing = ' ',
	Wall = '#',
	Door = '=',
	Pellet = '.',
	Energizer = 'o',
	Fruit = 'f',
	Pac = 'M',
	Blinky = 'B',
	Inky = 'I',
	Pinky = 'P',
	Clyde = 'C',
	BlinkyScatterTarget = 'b',
	InkyScatterTarget = 'i',
	PinkyScatterTarget = 'p',
	ClydeScatterTarget = 'c'
};

#endif