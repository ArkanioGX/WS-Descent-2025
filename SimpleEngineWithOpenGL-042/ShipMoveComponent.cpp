#include "ShipMoveComponent.h"
#include "InputSystem.h"
#include "Actor.h"

ShipMoveComponent::ShipMoveComponent(Actor* ownerP):
	Component(ownerP)
{
}

void ShipMoveComponent::update(float dt)
{
	Vector3 newPos = owner.getPosition();
	newPos += owner.getForward() * (moveInput.y * (dt * moveSpeed));
	newPos += owner.getRight() * (moveInput.x * (dt * moveSpeed));

	owner.setPosition(newPos);
}

void ShipMoveComponent::processInput(const InputState& inputState)
{
	moveInput.x = inputState.keyboard.getKeyValue(SDL_SCANCODE_D) - inputState.keyboard.getKeyValue(SDL_SCANCODE_A);
	moveInput.y = inputState.keyboard.getKeyValue(SDL_SCANCODE_W) - inputState.keyboard.getKeyValue(SDL_SCANCODE_S);
}
