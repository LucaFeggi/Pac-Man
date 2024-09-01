#include "GhostsManager.hpp"

GhostsManager::GhostsManager(SDL_Renderer* Renderer, Board* MyBoard, Pac* MyPac, TTF_Font* Font, Score* MyScore) :
	MyBlinky(Renderer, MyBoard, MyPac),
	MyInky(Renderer, MyBoard, MyPac, &MyBlinky),
	MyPinky(Renderer, MyBoard, MyPac),
	MyClyde(Renderer, MyBoard, MyPac),
	MyGhostsStateMachines{ GhostStateMachine(&MyBlinky, MyPac), GhostStateMachine(&MyInky, MyPac), GhostStateMachine(&MyPinky, MyPac), GhostStateMachine(&MyClyde, MyPac) },
	ScoresTextures{ Texture(Renderer), Texture(Renderer), Texture(Renderer), Texture(Renderer) },
	ScoresTimers{ Timer(), Timer(), Timer(), Timer()},
	ScoresRects{ SDL_Rect(), SDL_Rect(), SDL_Rect(), SDL_Rect() },
	DefaultScorer(200),
	Scorer(DefaultScorer),
	MyScore(MyScore),
	Font(Font),
	IsFrighPlayable(true),
	MyPac(MyPac)
{

}

GhostsManager::~GhostsManager() {
	MyScore = nullptr;
	Font = nullptr;
	MyPac = nullptr;
}

void GhostsManager::Update() {
	for (int i = 0; i < GhostsNumber; i++) {
		MyGhostsStateMachines[i].Run();
	}
	CollisionChecking();
	DrawScorers();
	if (IsToResetScorer()) {
		ResetScorer();
	}
	if (IsToPlayFrighSound()) {
		PlayFrighSound();
	}
	if (IsToStopFrighSound()) {
		StopFrighSound();
	}
}

bool GhostsManager::IsToResetScorer() {
	for (int i = 0; i < GhostsNumber; i++) {
		if (MyGhostsStateMachines[i].MyGhostState == GhostStates::Frightened)
			return false;
	}
	return true;
}

bool GhostsManager::IsToPlayFrighSound() {
	for (int i = 0; i < GhostsNumber; i++) {
		if (MyGhostsStateMachines[i].MyGhostState == GhostStates::Frightened && IsFrighPlayable) {
			IsFrighPlayable = false;
			return true;
		}
	}
	return false;
}

bool GhostsManager::IsToStopFrighSound() {
	for (int i = 0; i < GhostsNumber; i++) {
		if (MyGhostsStateMachines[i].MyGhostState == GhostStates::Frightened)
			return false;
	}
	IsFrighPlayable = true;
	return true;
}

void GhostsManager::StopFrighSound() {
	Sounds::StopGhostFrightened();
}

void GhostsManager::PlayFrighSound() {
	Sounds::PlayGhostFrightened();
}

void GhostsManager::Reset() {
	for (int i = 0; i < GhostsNumber; i++) {
		MyGhostsStateMachines[i].Reset();
	}
	ResetScorer();
	StopFrighSound();
}

void GhostsManager::Restart() {
	for (int i = 0; i < GhostsNumber; i++) {
		MyGhostsStateMachines[i].Restart();
	}
	ResetScorer();
	StopFrighSound();
}

void GhostsManager::Draw() {
	for (int i = 0; i < GhostsNumber; i++) {
		MyGhostsStateMachines[i].MyGhost->Draw();
	}
}

void GhostsManager::UpdateBodyFrame() {
	for (int i = 0; i < GhostsNumber; i++) {
		MyGhostsStateMachines[i].MyGhost->UpdateBodyFrame();
	}
}

void GhostsManager::CollisionChecking() {
	for (int i = 0; i < GhostsNumber; i++) {
		if (MyGhostsStateMachines[i].MyGhost->IsEntityColliding(*MyPac)) {
			if (MyGhostsStateMachines[i].MyGhostState == GhostStates::Frightened) {
				UpdateScorer(i);
				MyGhostsStateMachines[i].MyGhost->Death();
			}
			if(MyGhostsStateMachines[i].MyGhostState != GhostStates::Frightened && MyGhostsStateMachines[i].MyGhostState != GhostStates::Eaten) {
				MyPac->Death();
			}
		}
	}
}

void GhostsManager::UpdateScorer(int i) {
	ScoresTimers[i].Start();
	std::stringstream String;
	String << Scorer;
	ScoresTextures[i].LoadFromRenderedText(String.str(), Color::White, Font);
	ScoresRects[i] = { MyGhostsStateMachines[i].MyGhost->GetPosition().x + StdBlockSize / 2 - ScoresTextures[i].GetWidth() / 2, MyGhostsStateMachines[i].MyGhost->GetPosition().y + StdBlockSize / 2 - ScoresTextures[i].GetHeight() / 2, ScoresTextures[i].GetWidth(), ScoresTextures[i].GetHeight()};
	MyScore->Add(Scorer);
	Scorer *= 2;
}

void GhostsManager::ResetScorer() {
	Scorer = DefaultScorer;
}

void GhostsManager::DrawScorers() {
	for (int i = 0; i < GhostsNumber; i++) {
		if (ScoresTimers[i].GetTicks() > 1000) {
			ScoresTimers[i].Stop();
		}
		if (ScoresTimers[i].IsStarted()) {
			ScoresTextures[i].Render(nullptr, &ScoresRects[i]);
		}
	}
}
