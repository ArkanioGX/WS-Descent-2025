#include "ShipMoveComponent.h"
#include "InputSystem.h"
#include "Actor.h"
#include "iostream"

ShipMoveComponent::ShipMoveComponent(Actor* ownerP):
	Component(ownerP)
{
}

void ShipMoveComponent::update(float dt)
{
	Vector3 newVel = Vector3::zero;
	newVel += owner.getForward() * moveInput.y;
	newVel += owner.getRight() * moveInput.x;
	if (newVel.length() != 0) {
		newVel.normalize();

		Vector3 currentVelNormalized = velocity;
		currentVelNormalized.normalize();
		if (Vector3::dot(newVel, currentVelNormalized) < 0.8) {
			newVel *= (maxAccel * dt);
			velocity += newVel * changeDirMultiplier;
		}
		else {
			newVel *= (maxAccel * dt);
			velocity += newVel;
		}
	}
	else {
		if (velocity.length() > 0)
		velocity = Vector3::clamp(velocity, velocity.length() - maxDeccel * dt);
	}
	
	

	velocity = Vector3::clamp(velocity, maxMoveSpeed);
	std::cout << " x : " << velocity.x << " y : " << velocity.y << " z : " << velocity.z << std::endl;
	owner.setPosition(owner.getPosition() + velocity * dt);
}

void ShipMoveComponent::processInput(const InputState& inputState)
{
	Vector2 controllerMoveInput = inputState.controller.getLeftStick();
	if (controllerMoveInput.length() == 0) {
		moveInput.x = inputState.keyboard.getKeyValue(SDL_SCANCODE_D) - inputState.keyboard.getKeyValue(SDL_SCANCODE_A);
		moveInput.y = inputState.keyboard.getKeyValue(SDL_SCANCODE_W) - inputState.keyboard.getKeyValue(SDL_SCANCODE_S);
	}
	else {
		moveInput.x = controllerMoveInput.x;
		moveInput.y = controllerMoveInput.y;
	}
	
}
