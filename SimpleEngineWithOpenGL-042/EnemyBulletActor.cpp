#include "EnemyBulletActor.h"
#include "ProjectileComponent.h"
#include "SphereComponent.h"
#include "BillboardComponent.h"
#include "PhysicsSystem.h"
#include "WallActor.h"
#include "BulletFlashActor.h"
#include "Random.h"
#include "Game.h"

EnemyBulletActor::EnemyBulletActor(Actor* owner)
{
	CollisionComponent = new SphereComponent(this);

	BBComponent = new BillboardComponent(this);
	BBComponent->setTextureIndex(2);

	projComponent = new ProjectileComponent(this,owner);

	setScale(10);
}

EnemyBulletActor::~EnemyBulletActor()
{
}

void EnemyBulletActor::updateActor(float dt)
{
	
}
