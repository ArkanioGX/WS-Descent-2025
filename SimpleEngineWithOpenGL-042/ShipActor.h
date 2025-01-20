#pragma once
#include "Actor.h"
class ShipActor : public Actor
{
public:
	ShipActor();
	~ShipActor();

private:
	class ShipCameraComponent* CameraComponent;
	class ShipMoveComponent* MoveComponent;
};

