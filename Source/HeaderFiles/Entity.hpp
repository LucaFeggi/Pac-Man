#ifndef PACMAN_HEADERFILES_ENTITY_HPP_
#define PACMAN_HEADERFILES_ENTITY_HPP_

#include "Vec2.hpp"
#include "Globals.hpp"
#include "Board.hpp"

class Entity {
	public:
		Entity(Board* MyBoard, const Tokens Token);
		~Entity();
		bool IsAlive();
		void Live();
		void Die();
		bool IsEntityColliding(Entity Other);
		Vec2<int> GetPosition();
		Vec2<int> GetTileInBoard(int Side, Vec2<int> TemporaryPosition);
		void WrapAround();
		Directions GetDirection();
	protected:
		bool IsWallColliding(Vec2<int> TemporaryPosition, bool CanUseDoor = false);
		void ResetPosition();
		void Move(Vec2<int>& Position);	
		Board* MyBoard;
		Vec2<int> Position;
		Directions Direction;
		const Vec2<int> DefaultPosition;
		const Tokens Token;
		bool LifeStatement;
};

#endif