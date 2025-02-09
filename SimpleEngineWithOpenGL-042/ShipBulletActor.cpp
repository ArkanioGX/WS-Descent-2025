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
	std::vector<Actor*> toIgnore = { bulletOwner };
	CInfo outHit;
	if (Game::instance().getPhysicsSystem().SphereCast(CollisionComponent->getWorldSphere(), outHit, toIgnore)) {
		if (static_cast<WallActor*>(outHit.actor)) {
			BulletFlashActor* bfa = new BulletFlashActor();
			Vector3 preciseImpact = outHit.point;
			bfa->setPosition(preciseImpact - (projComponent->getForward()*10));
			bfa->setAngle(Random::getFloatRange(0, Maths::twoPi));
			bfa->getComponent<BillboardComponent>()->setTextureIndex(5);
			setState(ActorState::Dead);
		}
	}
}

void ShipBulletActor::fixCollisions()
{
}
