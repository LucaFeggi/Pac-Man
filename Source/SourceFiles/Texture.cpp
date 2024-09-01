#include "Texture.hpp"

Texture::Texture(SDL_Renderer* Renderer) :
	Renderer(Renderer),
	MyTexture(nullptr),
	Width(0),
	Height(0)
{

}

Texture::~Texture() {
	Free();
	Renderer = nullptr;
}

bool Texture::LoadFromFile(std::string Path) {
	Free();
	SDL_Texture* NewTexture = nullptr;
	SDL_Surface* LoadedSurface = IMG_Load(Path.c_str());
	if (LoadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", Path.c_str(), IMG_GetError());
	}
	else {
		SDL_SetColorKey(LoadedSurface, SDL_TRUE, SDL_MapRGB(LoadedSurface->format, 0, 0xFF, 0xFF));
		NewTexture = SDL_CreateTextureFromSurface(Renderer, LoadedSurface);
		if (NewTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", Path.c_str(), SDL_GetError());
		}
		else {
			Width = LoadedSurface->w;
			Height = LoadedSurface->h;
		}
		SDL_FreeSurface(LoadedSurface);
	}
	MyTexture = NewTexture;
	return MyTexture != nullptr;
}

bool Texture::LoadFromRenderedText(std::string TextureText, SDL_Color TextColor, TTF_Font *Font) {
	Free();
	SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, TextureText.c_str(), TextColor);
	if (TextSurface == nullptr) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		MyTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
		if (MyTexture == nullptr) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			Width = TextSurface->w;
			Height = TextSurface->h;
		}
		SDL_FreeSurface(TextSurface);
	}
	return MyTexture != nullptr;
}

void Texture::Free() {
	if (MyTexture != nullptr) {
		SDL_DestroyTexture(MyTexture);
		MyTexture = nullptr;
		Width = 0;
		Height = 0;
	}
}

void Texture::SetColor(SDL_Color Color) {
	SDL_SetTextureColorMod(MyTexture, Color.r, Color.g, Color.b);
}

void Texture::SetBlendMode(SDL_BlendMode Blending) {
	SDL_SetTextureBlendMode(MyTexture, Blending);
}

void Texture::SetAlpha(uint8_t Alpha) {
	SDL_SetTextureAlphaMod(MyTexture, Alpha);
}

void Texture::Render(SDL_Rect* Source, SDL_Rect* Destination, Directions Direction) {
	SDL_RenderCopyEx(Renderer, MyTexture, Source, Destination, int(Direction) * 90.0, nullptr, SDL_FLIP_NONE);
}

int Texture::GetWidth() {
	return Width;
}

int Texture::GetHeight() {
	return Height;
}