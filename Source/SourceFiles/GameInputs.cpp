#include "GameInputs.hpp"

GameInputs::GameInputs(bool* Quit, bool* IsToRestart, Directions* Mover) :
	Quit(Quit),
	IsToRestart(IsToRestart),
	Mover(Mover),
	Event(),
	MyJoystick(),
	JoystickDeadZone(8000),
	IsFingerDown(false),
	FingerDownCoords{WindowWidth/2, WindowHeight/2}
{
	if (SDL_NumJoysticks() > 0) {
		SDL_JoystickOpen(0);
	}
}

GameInputs::~GameInputs() {
	SDL_JoystickClose(MyJoystick);
	Quit = nullptr;
	IsToRestart = nullptr;
	Mover = nullptr;
}

void GameInputs::Get() {
	while (SDL_PollEvent(&Event)) {
		if (Event.type == SDL_QUIT) {
			*Quit = true;
			break;
		}
		Keyboard();
		Joystick();
		Buttons();
		Touch();
	}
}

void GameInputs::Keyboard() {
	if (Event.key.state == SDL_PRESSED) {
		switch (Event.key.keysym.sym) {
		case SDLK_w:
			Mover[1] = Directions::Up;
			break;
		case SDLK_a:
			Mover[1] = Directions::Left;
			break;
		case SDLK_s:
			Mover[1] = Directions::Down;
			break;
		case SDLK_d:
			Mover[1] = Directions::Right;
			break;
		case SDLK_SPACE:
			*IsToRestart = true;
			break;
		case SDLK_ESCAPE:
			*Quit = true;
			break;
		default:
			break;
		}
	}
}

void GameInputs::Joystick() {
	if (Event.type == SDL_JOYAXISMOTION) {
		if (Event.jaxis.which == SDL_JoystickGetDeviceInstanceID(0)) {
			switch (Event.jaxis.axis) {
			case 0:
				if (Event.jaxis.value < -JoystickDeadZone) {
					Mover[1] = Directions::Left;
					break;
				}
				if (Event.jaxis.value > JoystickDeadZone) {
					Mover[1] = Directions::Right;
				}
				break;
			case 1:
				if (Event.jaxis.value < -JoystickDeadZone) {
					Mover[1] = Directions::Up;
					break;
				}
				if (Event.jaxis.value > JoystickDeadZone) {
					Mover[1] = Directions::Down;
				}
				break;
			default:
				break;
			}
		}
	}
}

void GameInputs::Buttons() {
	if (Event.type == SDL_JOYBUTTONDOWN) {
		if (Event.jbutton.which == SDL_JoystickGetDeviceInstanceID(0)) {
			switch (Event.jbutton.button) {
			case 0:
				Mover[1] = Directions::Down;
				break;
			case 1:
				Mover[1] = Directions::Right;
				break;
			case 2:
				Mover[1] = Directions::Left;
				break;
			case 3:
				Mover[1] = Directions::Up;
				break;
			case 4:
				*IsToRestart = true;
				break;
			default:
				break;
			}
		}
	}
}

void GameInputs::Touch() {
	if (Event.type == SDL_FINGERDOWN) {
		IsFingerDown = true;
		FingerDownCoords = { int(Event.tfinger.x * WindowWidth), int(Event.tfinger.y * WindowHeight)};
	}
	if (Event.type == SDL_FINGERUP && IsFingerDown) {
		*IsToRestart = true;
		IsFingerDown = false;
		Vec2<int> FingerUpCoords = { int(Event.tfinger.x * WindowWidth), int(Event.tfinger.y * WindowHeight)};
		if (FingerDownCoords == FingerUpCoords) {
			return;
		}
		int DiffX = FingerDownCoords.x - FingerUpCoords.x;
		int DiffY = FingerDownCoords.y - FingerUpCoords.y;
		if (abs(DiffX) > abs(DiffY)) {
			if (DiffX > 0) {
				Mover[1] = Directions::Left;
				return;
			}
			Mover[1] = Directions::Right;
			return;
		}
		if (DiffY > 0) {
			Mover[1] = Directions::Up;
			return;
		}
		Mover[1] = Directions::Down;
	}
}
