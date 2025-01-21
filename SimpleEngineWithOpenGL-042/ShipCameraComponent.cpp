#include "ShipCameraComponent.h"
#include "InputSystem.h"
#include <iostream>
#include "Actor.h"

ShipCameraComponent::ShipCameraComponent(Actor* ownerP):
	CameraComponent(ownerP)
{
	noRollRotation = owner.getRotation();
}

void ShipCameraComponent::update(float dt)
{
	float rollInput = rollRight - rollLeft;
	//Adjust
	

	currentYaw = lastMousePos.x * sensitivity * dt;
	currentPitch = lastMousePos.y * sensitivity * dt;

	currentRoll = dt * rollSpeed;

	
	std::cout << owner.getRotation().z << std::endl;
	Vector3 fwd = owner.getForward();
	
	if (currentYaw != 0) {
		Quaternion yawQ = Quaternion::concatenate(owner.getRotation(),Quaternion(owner.getUp(), currentYaw));
		//fwd = Vector3::transform(fwd, yawQ);
		getOwner().setRotation(yawQ);
	}
	if (currentPitch != 0) {
		Quaternion pitchQ = Quaternion::concatenate(owner.getRotation(), Quaternion(owner.getRight(), currentPitch));
		//fwd = Vector3::transform(fwd, pitchQ);
		getOwner().setRotation(pitchQ);
	}

	Vector3 eulerAngle = Quaternion::ToEulerAngles(owner.getRotation());
	if (currentRoll != 0) {
		
	}
	else {

	}
	owner.setRotation(Quaternion::FromEuler(eulerAngle));


	

	

	
	Matrix4 lookAt = Matrix4::createLookAt(owner.getPosition(), owner.getPosition() + owner.getForward(), owner.getUp());
	setViewMatrix(lookAt);


}

void ShipCameraComponent::processInput(const InputState& inputState)
{
	lastMousePos = inputState.mouse.getPosition();

	rollLeft = inputState.keyboard.getKeyValue(SDL_SCANCODE_Q);
	rollRight = inputState.keyboard.getKeyValue(SDL_SCANCODE_E);



}
