#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Vector3.h"
class ShipMoveComponent : public Component
{
public:
	ShipMoveComponent(class Actor* ownerP);

	void update(float dt) override;

	void processInput(const struct InputState& inputState) override;

	void fixCollisions(float dt);

	Vector3 getVelocity() { return velocity; }

private:

	class SphereComponent* sphereColl;

	Vector3 moveInput = Vector3::zero;

	Vector3 velocity = Vector3::zero;

	

	float maxMoveSpeed = 1000;
	float maxAccel = 2000;
	float maxDeccel = 800;

	float changeDirMultiplier = 2;
};

