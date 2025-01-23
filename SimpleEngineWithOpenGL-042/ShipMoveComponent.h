#pragma once
#include "Component.h"
#include "Vector2.h"
class ShipMoveComponent : public Component
{
public:
	ShipMoveComponent(class Actor* ownerP);

	void update(float dt) override;

	void processInput(const struct InputState& inputState) override;

private:

	Vector2 moveInput = Vector2::zero;

	float moveSpeed = 1000;
};

