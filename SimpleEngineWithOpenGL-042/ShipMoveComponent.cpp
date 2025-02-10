#include "ShipMoveComponent.h"
#include "InputSystem.h"
#include "Actor.h"
#include "iostream"
#include "BoxComponent.h"
#include "SphereComponent.h"
#include "Game.h"
#include "Collisions.h"

ShipMoveComponent::ShipMoveComponent(Actor* ownerP):
	Component(ownerP)
{
	sphereColl = owner.getComponent<SphereComponent>();
}

void ShipMoveComponent::update(float dt)
{
	Vector3 newVel = Vector3::zero;
	newVel += owner.getForward() * moveInput.y;
	newVel += owner.getRight() * moveInput.x;
	newVel += owner.getUp() * moveInput.z;
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
	fixCollisions(dt);
	owner.setPosition(owner.getPosition() + velocity * dt);
}

void ShipMoveComponent::processInput(const InputState& inputState)
{
	Vector2 controllerMoveInput = inputState.controller.getLeftStick();
	float controllerVerticalInput = inputState.controller.getButtonValue(SDL_CONTROLLER_BUTTON_A) - inputState.controller.getButtonValue(SDL_CONTROLLER_BUTTON_B);
	if (controllerMoveInput.length() == 0 &&  controllerVerticalInput == 0) {
		moveInput.x = inputState.keyboard.getKeyValue(SDL_SCANCODE_D) - inputState.keyboard.getKeyValue(SDL_SCANCODE_A);
		moveInput.y = inputState.keyboard.getKeyValue(SDL_SCANCODE_W) - inputState.keyboard.getKeyValue(SDL_SCANCODE_S);
		moveInput.z = inputState.keyboard.getKeyValue(SDL_SCANCODE_SPACE) - inputState.keyboard.getKeyValue(SDL_SCANCODE_LSHIFT);
	}
	else {
		moveInput.x = controllerMoveInput.x;
		moveInput.y = controllerMoveInput.y;
		moveInput.z = controllerVerticalInput;
	}
	
}

void ShipMoveComponent::fixCollisions(float dt)
{
	// Need to recompute world transform to update world box
	owner.computeWorldTransform();

	const Sphere& playerSphere = sphereColl->getWorldSphere();
	Vector3 pos = owner.getPosition();

	//TODO : DO COLLISIONS HERE
	CInfo collInfo;
	std::vector<Actor*> actorToIgnore = {&getOwner()};
	if (Game::instance().getPhysicsSystem().SphereCast(playerSphere, collInfo, actorToIgnore)) {
		if (SphereComponent* sc = dynamic_cast<SphereComponent*>(collInfo.comp)) {
			if (sc->getCanPassThrough()) { return; }
		}
		std::cout << " x : " << collInfo.point.x << " y : " << collInfo.point.y << " z : " << collInfo.point.z << std::endl;
		velocity = Vector3::reflect(velocity,collInfo.normal);
		owner.setPosition(owner.getPosition() + velocity * dt);
	}
}
