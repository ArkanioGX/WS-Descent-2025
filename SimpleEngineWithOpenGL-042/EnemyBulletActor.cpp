#include "EnemyBulletActor.h"
#include "ProjectileComponent.h"
#include "SphereComponent.h"
#include "BillboardComponent.h"

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
