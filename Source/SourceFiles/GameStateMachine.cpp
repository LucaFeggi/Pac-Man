#include "GameStateMachine.hpp"

GameStateMachine::GameStateMachine(SDL_Renderer* Renderer, Directions* Mover, bool* IsToRestart) :
	InitIMG(IMG_Init(IMG_INIT_PNG)),
	InitTTF(TTF_Init()),
	Emulogic(TTF_OpenFont("Source/Fonts/Emulogic.ttf", StdBlockSize)),
	VpPixel(TTF_OpenFont("Source/Fonts/VpPixel.ttf", StdBlockSize)),
	IsToRestart(IsToRestart),
	MyGameState(GameStates::Ready),
	MyScore(Renderer, Emulogic),
	MyBoard(Renderer),
	MyPac(Renderer, Mover, &MyBoard),
	MyGhosts(Renderer, &MyBoard, &MyPac, VpPixel, &MyScore),
	MyReady(Renderer, Emulogic),
	MyGameOver(Renderer, Emulogic),
	MyDoor(Renderer),
	MyLives(Renderer, &MyScore),
	MyLevel(),
	MyFood(Renderer, &MyBoard, &MyPac, &MyScore, &MyLevel)
{
	Sounds::PlayIntro();
}

GameStateMachine::~GameStateMachine(){
	IsToRestart = nullptr;
	TTF_CloseFont(Emulogic);
	TTF_CloseFont(VpPixel);
	TTF_Quit();
	IMG_Quit();
}

void GameStateMachine::Run(){
	RunAlways();
	switch (MyGameState) {
		case GameStates::Ready:
			RunWhenReady();
			MyGameState = ProcessReady();
			break;
		case GameStates::GameStarted:
			RunWhenGameStarted();
			MyGameState = ProcessGameStarted();
			break;
		case GameStates::LevelCompleted:
			RunWhenLevelCompleted();
			MyGameState = ProcessLevelCompleted();
			break;
		case GameStates::PacDeath:
			RunWhenPacDeath();
			MyGameState = ProcessPacDeath();
			break;
		case GameStates::GameOver:
			RunWhenGameOver();
			MyGameState = ProcessGameOver();
			break;
		default:
			break;
	}
}

GameStates GameStateMachine::ProcessReady() {
	if (MyReady.IsReadyEnded()) {
		MyReady.StopTimer();
		return GameStates::GameStarted;
	}
	return GameStates::Ready;
}

GameStates GameStateMachine::ProcessGameStarted() {
	if (MyFood.IsLevelCompleted()) {
		MyFood.DespawnFruit();
		MyBoard.StartAnimationTimer();
		MyFood.StopFoodSound();
		Sounds::StopGhostFrightened();
		
		return GameStates::LevelCompleted;
	}
	if (!MyPac.IsAlive()) {
		Sounds::StopFood();
		return GameStates::PacDeath;
	}
	return GameStates::GameStarted;
}

GameStates GameStateMachine::ProcessLevelCompleted() {
	if (MyBoard.IsAnimationCompleted()) {
		MyLevel.Increase();
		MyFood.SelectCurrentFruit();
		MyFood.Reset();
		MyPac.Reset();
		MyBoard.Reset();
		MyGhosts.Reset();
		MyReady.StartTimer();
		return GameStates::Ready;
	}
	return GameStates::LevelCompleted;
}

GameStates GameStateMachine::ProcessPacDeath() {
	if (MyPac.IsAnimationEnded()) {
		MyFood.DespawnFruit();
		MyLives.Decrease();
		if (MyLives.Get() == 0) {
			return GameStates::GameOver;
		}
		MyPac.Reset();
		MyGhosts.Reset();
		MyPac.Live();
		MyReady.StartTimer();
		MyFood.ResetFruitScore();
		return GameStates::Ready;
	}
	return GameStates::PacDeath;
}

GameStates GameStateMachine::ProcessGameOver() {
	if (*IsToRestart) {
		*IsToRestart = false;
		MyScore.Restart();
		MyBoard.Restart();
		MyPac.Restart();
		MyGhosts.Restart();
		MyReady.Restart();
		MyLives.Restart();
		MyLevel.Restart();
		MyFood.Restart();
		Sounds::PlayIntro();
		return GameStates::Ready;
	}
	return GameStates::GameOver;
}

void GameStateMachine::RunAlways() {
	if (MyGameState != GameStates::GameOver && *IsToRestart == true) {
		*IsToRestart = false;
	}
	MyBoard.Draw();
	MyScore.Draw();
	MyLives.Draw();	
}

void GameStateMachine::RunWhenReady() {
	MyReady.Draw();
	MyDoor.Draw();
	MyFood.Draw();	
	MyGhosts.UpdateBodyFrame();
	MyGhosts.Draw();
	MyPac.Draw();
}

void GameStateMachine::RunWhenGameStarted() {
	if (MyLives.IsExtraLife()) {
		MyLives.Increase();
		MyLives.PlayExtraLifeSound();
	}
	MyScore.Update();
	MyPac.UpdateLiveFrame();
	MyPac.UpdatePosition();
	MyPac.UpdateEnergyState();
	MyFood.Update();
	MyDoor.Draw();
	MyFood.Draw();
	MyGhosts.Update();
	MyGhosts.Draw();
	MyGhosts.UpdateBodyFrame();
	MyPac.Draw();
}

void GameStateMachine::RunWhenLevelCompleted() {
	MyBoard.Animation();
}

void GameStateMachine::RunWhenPacDeath() {
	MyPac.UpdateDeathFrame();
	MyFood.Draw();
	MyDoor.Draw();
	MyGhosts.UpdateBodyFrame();
	MyGhosts.Draw();
	MyPac.Draw();
}

void GameStateMachine::RunWhenGameOver() {
	MyGameOver.Draw();
}