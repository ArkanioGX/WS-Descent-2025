#include "EnemyActor.h"
#include "SphereComponent.h"
#include "BillboardComponent.h"
#include "EnemyBulletActor.h"
#include "ProjectileComponent.h"
#include "BulletFlashActor.h"
#include "Game.h"
#include "Random.h"

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
	float cannonSpace = 65;
	count += dt;
	if (count > 0.5) {
		count -= 0.5;
		EnemyBulletActor* bullet = new EnemyBulletActor(this);
		
		bullet->setPosition(getPosition() + getRight() * cannonSpace);
		ProjectileComponent* pc = bullet->getComponent<ProjectileComponent>();
		Vector3 newFwd = Game::instance().getPlayer()->getPosition() - bullet->getPosition();
		newFwd.normalize();
		pc->setFwd(newFwd);

		BulletFlashActor* bfa = new BulletFlashActor();
		bfa->setPosition(bullet->getPosition() + newFwd * 10);
		bfa->setAngle(Random::getFloatRange(0, Maths::twoPi));

		bullet = new EnemyBulletActor(this);

		bullet->setPosition(getPosition() + getRight() * -cannonSpace);
		pc = bullet->getComponent<ProjectileComponent>();
		newFwd = Game::instance().getPlayer()->getPosition() - bullet->getPosition();
		newFwd.normalize();
		pc->setFwd(newFwd);

		 bfa = new BulletFlashActor();
		bfa->setPosition(bullet->getPosition() + newFwd * 10);
		bfa->setAngle(Random::getFloatRange(0, Maths::twoPi));

		
	}
}
