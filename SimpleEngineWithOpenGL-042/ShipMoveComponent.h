#pragma once
#include "Component.h"
class ShipMoveComponent : public Component
{
public:
	ShipMoveComponent(class Actor* ownerP);

	void update(float dt) override;

	void processInput(const struct InputState& inputState) override;
};

