#include "ShipCameraComponent.h"
#include "InputSystem.h"
#include <iostream>
#include "Actor.h"

ShipCameraComponent::ShipCameraComponent(Actor* ownerP):
	CameraComponent(ownerP)
{
}

void ShipCameraComponent::update(float dt)
{
	float rollInput =  rollLeft - rollRight;

	currentYaw = lastMousePos.x * sensitivity * dt;
	currentPitch = lastMousePos.y * sensitivity * dt;

	if (Maths::abs(lastMousePos.x) > 0) {
		additiveRoll = Maths::clamp(additiveRoll - currentYaw * additiveRollIntensity,-additiveRollMax, additiveRollMax);
	}
	else if (additiveRoll != 0) {
		//Reset additiveRoll
		additiveRoll = Maths::clamp(
			additiveRoll + (additiveRoll >= 0 ? -dt * additiveRollAdjustSpeed : dt * additiveRollAdjustSpeed),
			(additiveRoll >= 0 ? 0 : -additiveRollMax),
			(additiveRoll >= 0 ? additiveRollMax : 0));
	}
	
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
	
	if (rollInput != 0) {
		eulerAngle.x += rollInput * dt * rollSpeed;
	}
	else {
		//Find closest 90� angle
		float RadiansQuarter = Maths::piOver2;
		float closest90Angle = (fmodf((RadiansQuarter * 2) + eulerAngle.x, RadiansQuarter)) - (RadiansQuarter / 2);
		if (closest90Angle > -rollAdjustMinimum && closest90Angle < rollAdjustMinimum) {
			float minMaxAngle = eulerAngle.x / RadiansQuarter;
			eulerAngle.x = Maths::clamp(eulerAngle.x + AdjustRollSpeed * (closest90Angle > 0 ? 1 : -1) * dt, RadiansQuarter * floorf(minMaxAngle), RadiansQuarter * ceilf(minMaxAngle));
		}
	}

	owner.setRotation(Quaternion::FromEuler(eulerAngle));

	//Additive Roll

	eulerAngle.x += additiveRoll;

	Quaternion newRot = Quaternion::FromEuler(eulerAngle);

	Vector3 newFwd = Vector3::transform(Vector3::unitX, newRot);
	Vector3 newUp = Vector3::transform(Vector3::unitZ, newRot);

	Matrix4 lookAt = Matrix4::createLookAt(owner.getPosition(), owner.getPosition() + newFwd, newUp);
	setViewMatrix(lookAt);
}

void ShipCameraComponent::processInput(const InputState& inputState)
{
	Vector2 controllerLookInput = inputState.controller.getRightStick();
	controllerLookInput.y *= -1;
	lastMousePos = controllerLookInput.length() != 0 ? controllerLookInput : inputState.mouse.getPosition();

	rollLeft = inputState.keyboard.getKeyValue(SDL_SCANCODE_Q) || inputState.controller.getButtonValue(SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	rollRight = inputState.keyboard.getKeyValue(SDL_SCANCODE_E) || inputState.controller.getButtonValue(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);



}
