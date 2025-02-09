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
	const Sphere& bulletSphere = CollisionComponent->getWorldSphere();

	CInfo collInfo;
	std::vector<Actor*> actorToIgnore = { this };
	if (Game::instance().getPhysicsSystem().SphereCast(bulletSphere, collInfo, actorToIgnore)) {
		//Collision Interactions
		if (static_cast<WallActor*>(collInfo.actor)) {
			BulletFlashActor* bfa = new BulletFlashActor();
			Vector3 preciseImpact = collInfo.point;
			bfa->setPosition(preciseImpact - (projComponent->getForward() * 10));
			bfa->setAngle(Random::getFloatRange(0, Maths::twoPi));
			setState(ActorState::Dead);
		}
	}
}
