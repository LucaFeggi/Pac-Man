#ifndef PACMAN_HEADERFILES_TEXTURE_HPP_
#define PACMAN_HEADERFILES_TEXTURE_HPP_

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "Globals.hpp"

class Texture {
public:
	Texture(SDL_Renderer* Renderer);
	~Texture();
	bool LoadFromFile(std::string Path);
	bool LoadFromRenderedText(std::string TextureText, SDL_Color TextColor, TTF_Font* Font);
	void Free();
	void SetColor(SDL_Color Color);
	void SetBlendMode(SDL_BlendMode Blending);
	void SetAlpha(uint8_t Alpha);
	void Render(SDL_Rect* Source = nullptr, SDL_Rect* Destination = nullptr, Directions Direction = Directions::Up);
	int GetWidth();
	int GetHeight();
private:
	SDL_Renderer* Renderer;
	SDL_Texture* MyTexture;
	int Width;
	int Height;
};

#endif