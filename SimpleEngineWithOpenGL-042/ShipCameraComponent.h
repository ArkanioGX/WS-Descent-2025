#pragma once
#include "CameraComponent.h"
#include "Vector2.h"

class ShipCameraComponent : public CameraComponent
{
public:
	ShipCameraComponent(class Actor* ownerP);

	void update(float dt) override;
	void processInput(const struct InputState& inputState) override;

private:

	Vector2 lastMousePos = Vector2::zero;

	bool rollLeft = false;
	bool rollRight = true;

	//Changeable 

	float rollSpeed = 1;
	float AdjustRollSpeed = 10;

	float sensitivity = 1;

	//Do not change
	float currentYaw = 0;
	float currentPitch = 0;
	float currentRoll = 0;

	Quaternion noRollRotation;
	Quaternion finalRotation;

	float additiveRoll = 0;
};

