#include "GhostStateMachine.hpp"

GhostStateMachine::GhostStateMachine(Ghost* MyGhost, Pac* MyPac) :
	MyGhost(MyGhost),
	MyPac(MyPac),
	GhostTimer(),
	ChasingTime(20000),
	ScatterTime(7000),
	MyGhostState(GhostStates::Chase),
	IsToMoveFrightened(true)
{
	GhostTimer.Start();
}

GhostStateMachine::~GhostStateMachine() {
	MyGhost = nullptr;
	MyPac = nullptr;
}

void GhostStateMachine::Run() {	
	RunAlways();
	switch (MyGhostState) {
		case GhostStates::Chase:
			RunWhenChase();
			MyGhostState = ProcessChase();
			break;
		case GhostStates::Scatter:
			RunWhenScatter();
			MyGhostState = ProcessScatter();
			break;
		case GhostStates::Frightened:
			RunWhenFrightened();
			MyGhostState = ProcessFrightened();
			break;
		case GhostStates::Eaten:
			RunWhenEaten();
			MyGhostState = ProcessEaten();
			break;
		default:
			break;
	}
}

void GhostStateMachine::RunAlways() {
	MyGhost->WrapAround();
}

void GhostStateMachine::RunWhenChase() {
	if (MyGhost->IsHome()) {
		MyGhost->CanUseDoor = true;
	}
	if (MyGhost->GetPosition() == MyGhost->DoorTarget) {
		MyGhost->CanUseDoor = false;
	}
	MyGhost->Target = MyGhost->DoorTarget;
	if (!MyGhost->CanUseDoor) {
		MyGhost->Target = MyGhost->CalculateTarget();
	}
	MyGhost->UpdatePosNonRand();
	MyGhost->UpdateEyeFrame();
}

GhostStates GhostStateMachine::ProcessChase() {
	if (GhostTimer.GetTicks() > ChasingTime) {
		MyGhost->Target = MyGhost->ScatterTarget;
		GhostTimer.Start();
		return GhostStates::Scatter;
	}
	if (MyPac->IsEnergized() && !MyGhost->CanUseDoor) {
		MyGhost->BlueFlash();
		MyGhost->CurrentEyeFrame = 4;
		MyGhost->Target = MyGhost->ScatterTarget;
		GhostTimer.Stop();
		return GhostStates::Frightened;
	}
	return GhostStates::Chase;
}

void GhostStateMachine::RunWhenScatter() {
	if (MyGhost->IsHome()) {
		MyGhost->HomeMovement();
	}
	MyGhost->UpdatePosNonRand();
	MyGhost->UpdateEyeFrame();
}

GhostStates GhostStateMachine::ProcessScatter() {
	if (GhostTimer.GetTicks() > ScatterTime) {
		GhostTimer.Start();
		return GhostStates::Chase;
	}
	if (MyPac->IsEnergized()) {
		MyGhost->BlueFlash();
		MyGhost->CurrentEyeFrame = 4;
		MyGhost->Target = MyGhost->ScatterTarget;
		GhostTimer.Stop();
		return GhostStates::Frightened;
	}
	return GhostStates::Scatter;
}

void GhostStateMachine::RunWhenFrightened() {
	if (MyGhost->IsHome()) {
		MyGhost->DefaultColor();
		MyGhost->HomeMovement();
		MyGhost->UpdatePosNonRand();
		MyGhost->UpdateEyeFrame();
		return;
	}
	if (IsToMoveFrightened) {
		MyGhost->UpdatePosRand();
	}
	IsToMoveFrightened = !IsToMoveFrightened;
	FlashingAnimation();
}

GhostStates GhostStateMachine::ProcessFrightened() {
	if (!MyPac->IsEnergized()) {
		MyGhost->DefaultColor();
		GhostTimer.Start();
		return GhostStates::Chase;
	}
	if (!MyGhost->IsAlive()) {
		MyGhost->CanUseDoor = true;
		MyGhost->DefaultColor();
		MyGhost->Target = MyGhost->HomeTarget;
		return GhostStates::Eaten;
	}
	return GhostStates::Frightened;
}

void GhostStateMachine::RunWhenEaten() {
	MyGhost->UpdatePosNonRand();
	MyGhost->UpdateEyeFrame();
	if (!MyGhost->IsHome()) {
		MyGhost->UpdatePosNonRand();
		return;
	}
	MyGhost->CanUseDoor = false;
	if (!MyGhost->IsAlive())
		MyGhost->Live();
	MyGhost->HomeMovement();
}

GhostStates GhostStateMachine::ProcessEaten() {
	if (!MyPac->IsEnergized() && MyGhost->GetPosition() == MyGhost->HomeTarget) {
		GhostTimer.Start();
		return GhostStates::Chase;
	}
	return GhostStates::Eaten;
}

void GhostStateMachine::FlashingAnimation() {
	if (MyPac->GetEnergyTimerTicks() > ScatterTime - 2000) {
		if ((MyPac->GetEnergyTimerTicks() / 250) % 2 == 1) {
			MyGhost->WhiteFlash();
			return;
		}
		MyGhost->BlueFlash();
		return;
	}
	MyGhost->BlueFlash();
}

void GhostStateMachine::Reset() {
	MyGhostState = GhostStates::Chase;
	GhostTimer.Start();
	MyGhost->Reset();
}

void GhostStateMachine::Restart() {
	Reset();
	MyGhost->Restart();
}