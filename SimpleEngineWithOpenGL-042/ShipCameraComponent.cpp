#include "ShipCameraComponent.h"
#include "InputSystem.h"
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

	}
	else {
		currentRoll += rollInput * dt * rollSpeed;
	}

	currentYaw = lastMousePos.x * sensitivity * dt;
	currentPitch = lastMousePos.y * sensitivity * dt;

	Vector3 newForward = owner.getForward();
	Quaternion yawQ = Quaternion(getOwner().getUp(), currentYaw);
	Vector3::transform(newForward, yawQ);

	getOwner().setRotation(yawQ);

	newForward = owner.getForward();
	Quaternion pitchQ = Quaternion(getOwner().getRight(), currentPitch);
	Vector3::transform(newForward, pitchQ);

	getOwner().setRotation(pitchQ);

	
	Vector3 viewForward = Vector3::transform(owner.getForward(), yawQ);
	Vector3 viewUp = Vector3::transform(owner.getUp(), yawQ);
	Vector3 cameraPosition = owner.getPosition();
	Vector3 cameraForward = cameraPosition + viewForward;
	

	Matrix4 rot = Matrix4::createLookAt(cameraPosition, cameraForward, viewUp);

	setViewMatrix(rot);
}

void ShipCameraComponent::processInput(const InputState& inputState)
{
	lastMousePos = inputState.mouse.getPosition();

	rollLeft = inputState.keyboard.getKeyValue(SDL_SCANCODE_Q);
	rollRight = inputState.keyboard.getKeyValue(SDL_SCANCODE_E);



}
