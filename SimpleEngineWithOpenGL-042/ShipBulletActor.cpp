#include "ShipBulletActor.h"
#include "ProjectileComponent.h"
#include "SphereComponent.h"
#include "BillboardComponent.h"
#include "PhysicsSystem.h"
#include "WallActor.h"
#include "BulletFlashActor.h"
#include "Random.h"
#include "Game.h"

ShipBulletActor::ShipBulletActor(Actor* owner)
{
	CollisionComponent = new SphereComponent(this);

	BBComponent = new BillboardComponent(this);
	BBComponent->setTextureIndex(4);

	projComponent = new ProjectileComponent(this, owner);

	bulletOwner = owner;

	setScale(10);
}

ShipBulletActor::~ShipBulletActor()
{
}

void ShipBulletActor::updateActor(float dt)
{
	
}

void ShipBulletActor::fixCollisions()
{
}
