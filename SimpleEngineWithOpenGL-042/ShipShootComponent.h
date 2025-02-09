#pragma once
#include "Component.h"

class ShipShootComponent : public Component
{
public:
	ShipShootComponent(class Actor* ownerP);

	void update(float dt) override;

	void processInput(const struct InputState& inputState) override;

private:

	bool shootInput = false;

	float currentDelay = 0;
	float delayBetweenShots = 0.2f;
};

