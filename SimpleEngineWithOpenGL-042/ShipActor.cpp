#include "ShipActor.h"
#include "ShipCameraComponent.h"
#include "ShipMoveComponent.h"
#include "SphereComponent.h"
#include "ShipShootComponent.h"

ShipActor::ShipActor() :Actor(),
MoveComponent(nullptr),
CameraComponent(nullptr),
CollisionComponent(nullptr)
{
	CollisionComponent = new SphereComponent(this);
	MoveComponent = new ShipMoveComponent(this);
	CameraComponent = new ShipCameraComponent(this);
	ShootComponent = new ShipShootComponent(this);

	Sphere sphereColl = Sphere(Vector3::zero, 60);
	CollisionComponent->setObjectSphere(sphereColl);


	

}

ShipActor::~ShipActor()
{
}
