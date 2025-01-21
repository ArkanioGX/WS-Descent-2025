#include "ShipCameraComponent.h"
#include "InputSystem.h"
#include <iostream>
#include "Actor.h"

ShipCameraComponent::ShipCameraComponent(Actor* ownerP):
	CameraComponent(ownerP)
{
	Quaternion pitchQ = Quaternion(getOwner().getRight(), 50);
	getOwner().setRotation(pitchQ);
}

void ShipCameraComponent::update(float dt)
{
	float rollInput = rollRight - rollLeft;
	//Adjust
	if (rollInput == 0 && (fmod(currentRoll,90)) != 0) {
		currentRoll = 0;
	}
	else {
		currentRoll = rollInput * dt * rollSpeed;
	}

	currentYaw = lastMousePos.x * sensitivity * dt;
	currentPitch = lastMousePos.y * sensitivity * dt;

	Quaternion currentRot = owner.getRotation();
	
	if (currentYaw != 0) {
		std::cout << currentPitch << std::endl;
		Quaternion yawQ = Quaternion::concatenate(owner.getRotation(),Quaternion(owner.getUp(), currentYaw));

		getOwner().setRotation(yawQ);

		Matrix4 lookAt = Matrix4::createLookAt(owner.getPosition(), owner.getPosition() + owner.getForward(), owner.getUp());

		setViewMatrix(lookAt);
	}
	if (currentPitch != 0) {
		std::cout << currentPitch << std::endl;
		Quaternion pitchQ = Quaternion::concatenate(owner.getRotation(), Quaternion(owner.getRight(), currentPitch));

		getOwner().setRotation(pitchQ);

		Matrix4 lookAt = Matrix4::createLookAt(owner.getPosition(), owner.getPosition() + owner.getForward(), owner.getUp());

		setViewMatrix(lookAt);
	}
	if (currentRoll != 0) {
		std::cout << currentRoll << std::endl;
		Quaternion RollQ = Quaternion::concatenate(owner.getRotation(), Quaternion(owner.getForward(), currentRoll));

		getOwner().setRotation(RollQ);

		Matrix4 lookAt = Matrix4::createLookAt(owner.getPosition(), owner.getPosition() + owner.getForward(), owner.getUp());

		setViewMatrix(lookAt);
	}

}

void ShipCameraComponent::processInput(const InputState& inputState)
{
	lastMousePos = inputState.mouse.getPosition();

	rollLeft = inputState.keyboard.getKeyValue(SDL_SCANCODE_Q);
	rollRight = inputState.keyboard.getKeyValue(SDL_SCANCODE_E);



}
