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
	bool rollRight = false;

	//Changeable 

	float currentRollVelocity = 0;
	float rollSpeed = 1;
	float AdjustRollSpeed = 0.65;

	float rollAdjustMinimum = Maths::piOver2 - Maths::toRadians(5);

	float sensitivity = 1;

	//Do not change
	float currentYaw = 0;
	float currentPitch = 0;
	float currentRoll = 0;

	Quaternion noRollRotation;
	Quaternion finalRotation;

	float additiveRoll = 0;
	float additiveRollAdjustSpeed = 3;
	float additiveRollMax = Maths::toRadians(35);
	float additiveRollIntensity = 0.1;
};

