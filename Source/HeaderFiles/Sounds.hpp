#ifndef PACMAN_HEADERFILES_SOUNDS_HPP_
#define PACMAN_HEADERFILES_SOUNDS_HPP_

#include <SDL_mixer.h>

namespace Sounds {
	namespace {
		static int InitMIX = Mix_Init(0);
		static int InitAUD = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
		static int Volume = Mix_Volume(-1, 5);
		enum Channels {
			IntroChannel = 0, FoodChannel, FruitChannel, GhostFrightenedChannel, GhostEatenChannel, ExtraLifeChannel, PacDeathChannel, Total
		};
		static int TotalChannels = Mix_AllocateChannels(Channels::Total);
		static Mix_Chunk* Intro = Mix_LoadWAV("Source/Sounds/Intro.wav");
		static Mix_Chunk* Food = Mix_LoadWAV("Source/Sounds/Food.wav");
		static Mix_Chunk* Fruit = Mix_LoadWAV("Source/Sounds/Fruit.wav");
		static Mix_Chunk* GhostFrightened = Mix_LoadWAV("Source/Sounds/GhostFrightened.wav");
		static Mix_Chunk* GhostEaten = Mix_LoadWAV("Source/Sounds/GhostDeath.wav");
		static Mix_Chunk* ExtraLife = Mix_LoadWAV("Source/Sounds/ExtraLife.wav");
		static Mix_Chunk* PacDeath = Mix_LoadWAV("Source/Sounds/PacDeath.wav");	
	}
	static void Destructor(){
		Mix_FreeChunk(Intro);
		Mix_FreeChunk(Food);
		Mix_FreeChunk(Fruit);
		Mix_FreeChunk(GhostFrightened);
		Mix_FreeChunk(GhostEaten);
		Mix_FreeChunk(ExtraLife);
		Mix_FreeChunk(PacDeath);
		Mix_CloseAudio();
		Mix_Quit();
	}
	static void PlayIntro(){
		Mix_PlayChannel(Channels::IntroChannel, Intro, 0);
	}
	static void PlayFood(){
		Mix_PlayChannel(Channels::FoodChannel, Food, -1);
	}
	static void StopFood(){
		Mix_HaltChannel(Channels::FoodChannel);
	}
	static void PlayFruit(){
		Mix_PlayChannel(Channels::FruitChannel, Fruit, 0);
	}
	static void PlayGhostFrightened() {
		Mix_PlayChannel(Channels::GhostFrightenedChannel, GhostFrightened, -1);
	}
	static void StopGhostFrightened(){
		Mix_HaltChannel(Channels::GhostFrightenedChannel);
	}
	static void PlayGhostEaten() {
		Mix_PlayChannel(Channels::GhostEatenChannel, GhostEaten, 0);
	}
	static void PlayExtraLife() {
		Mix_PlayChannel(Channels::ExtraLifeChannel, ExtraLife, 0);
	}
	static void PlayPacDeath() {
		Mix_PlayChannel(Channels::PacDeathChannel, PacDeath, 0);
	}
};

#endif