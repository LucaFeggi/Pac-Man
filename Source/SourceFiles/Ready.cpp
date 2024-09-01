#include "Ready.hpp"

Ready::Ready(SDL_Renderer* Renderer, TTF_Font* Font) :
	ReadyTexture(Renderer),
	ReadyTimerTarget(4500)	
{
	ReadyTexture.LoadFromRenderedText("READY!", Color::Yellow, Font);
	ReadyRect = { WindowWidth / 2 - ReadyTexture.GetWidth() / 2, 21 * StdBlockSize - ReadyTexture.GetHeight() / 4, ReadyTexture.GetWidth(), ReadyTexture.GetHeight() };
	ReadyTimer.Start();
}

Ready::~Ready(){

}

void Ready::Reset(){
	ReadyTimerTarget = 4500;
	ReadyTimer.Start();
}

void Ready::Restart(){
	Reset();
}

void Ready::Draw(){
	ReadyTexture.Render(nullptr, &ReadyRect);
}

void Ready::StartTimer(){
	ReadyTimer.Start();
}

void Ready::StopTimer(){
	ReadyTimer.Stop();
}

bool Ready::IsReadyEnded() {
	if (ReadyTimer.GetTicks() > ReadyTimerTarget) {
		if (ReadyTimerTarget != 2500)
			ReadyTimerTarget = 2500;
		return true;
	}
	return false;
}
