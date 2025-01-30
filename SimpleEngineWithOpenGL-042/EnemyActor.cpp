#include "EnemyActor.h"
#include "SphereComponent.h"
#include "BillboardComponent.h"

EnemyActor::EnemyActor()
{
	CollisionComponent = new SphereComponent(this);

	BBComponent = new BillboardComponent(this);
	BBComponent->setTextureIndex(1);

	setScale(150);
}

EnemyActor::~EnemyActor()
{
}

void EnemyActor::updateActor(float dt)
{
	count += dt;
}
