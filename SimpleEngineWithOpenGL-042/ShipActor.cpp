#include "ShipActor.h"
#include "ShipCameraComponent.h"
#include "ShipMoveComponent.h"
#include "SphereComponent.h"

ShipActor::ShipActor() :Actor(),
MoveComponent(nullptr),
CameraComponent(nullptr),
CollisionComponent(nullptr)
{
	CollisionComponent = new SphereComponent(this);
	MoveComponent = new ShipMoveComponent(this);
	CameraComponent = new ShipCameraComponent(this);
	

}

ShipActor::~ShipActor()
{
}
