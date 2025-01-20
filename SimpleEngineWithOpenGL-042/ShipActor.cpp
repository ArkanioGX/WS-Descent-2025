#include "ShipActor.h"
#include "ShipCameraComponent.h"
#include "ShipMoveComponent.h"

ShipActor::ShipActor() :Actor(),
MoveComponent(nullptr),
CameraComponent(nullptr)
{

	MoveComponent = new ShipMoveComponent(this);
	CameraComponent = new ShipCameraComponent(this);
}

ShipActor::~ShipActor()
{
}
