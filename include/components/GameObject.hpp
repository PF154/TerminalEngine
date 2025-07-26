#pragma once

#include "ComponentUtils.hpp"

class GameObject
{
	public:
		// Default constructor/destructor
		GameObject() {};
		virtual ~GameObject() = default;

		// Dependency injected constructor/destructor
		// GameObject(Game* game);

		void update(double delta);

		// Store a reference to the game so that we have access to important constants
		// Game* game;

		Position position;
		Velocity velocity;
		Size size;

		
	protected:
		virtual void process(double delta);
		virtual void physicsProcess(double delta);

		void applyGravity(GameObject* object, double delta);

		
};