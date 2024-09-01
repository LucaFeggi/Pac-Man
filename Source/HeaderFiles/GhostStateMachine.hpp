#ifndef PACMAN_HEADERFILES_GHOSTSTATEMACHINE_HPP_
#define PACMAN_HEADERFILES_GHOSTSTATEMACHINE_HPP_

#include "Timer.hpp"
#include "Pac.hpp"
#include "Ghost.hpp"

/*
Sistemare:
- se mangio l'energizer dopo un altro, e i ghost sono in chase ma ancora in casa, si sfancula.
Sti cazzi:
- animazioni degli occhi dei Ghost quando entrano ed escono di casa
	if(IsHome && Direction::Up)
		EyeFrame = Up;
	if(IsHome && Direction::Down, fino a che non ha raggiunto il OuterHomeTarget)
		EyeFrame = Down;
- animazione dei fantasmi, nel momento in cui riappare il corpo.
	Forse è dovuto al fatto che quando chiamo Reset() o Restart(), non stoppo il timer di aggiornamento dei frame
*/

static constexpr enum class GhostStates {
	Chase = 0, Scatter, Frightened, Eaten
};

class GhostStateMachine {
public:
	GhostStateMachine(Ghost* MyGhost, Pac* MyPac);
	~GhostStateMachine();
	void Run();
	void Reset();
	void Restart();
	Ghost* MyGhost;
	GhostStates MyGhostState;
private:
	GhostStates ProcessChase();
	GhostStates ProcessScatter();
	GhostStates ProcessFrightened();
	GhostStates ProcessEaten();
	void RunAlways();
	void RunWhenChase();
	void RunWhenScatter();
	void RunWhenFrightened();
	void RunWhenEaten();
	void FlashingAnimation();
	Timer GhostTimer;			
	const int ChasingTime, ScatterTime;
	bool IsToMoveFrightened;
	Pac* MyPac;
};

#endif