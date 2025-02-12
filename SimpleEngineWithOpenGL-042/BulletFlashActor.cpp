#include "BulletFlashActor.h"
#include "BillboardComponent.h"
#include "Random.h"

BulletFlashActor::BulletFlashActor():
	Actor()
{
	bbComponent = new BillboardComponent(this);
	bbComponent->setTextureIndex(3);
	bbComponent->setAngle(0);
}

void BulletFlashActor::updateActor(float dt)
{
	ttl -= dt;
	if (ttl <= 0) {
		
		setState(ActorState::Dead);

	}
	angle += angleSpeed * dt;

	bbComponent->setAngle(angle);
}

void BulletFlashActor::setAngle(float inAngle)
{
	angle = inAngle;
}
