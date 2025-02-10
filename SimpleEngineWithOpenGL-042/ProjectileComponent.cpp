#include "ProjectileComponent.h"
#include "Actor.h"
#include "SphereComponent.h"
#include "BulletFlashActor.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "Random.h"
#include "Collisions.h"
#include "WallActor.h"
#include "BillboardComponent.h"
#include "HealthComponent.h"

ProjectileComponent::ProjectileComponent(Actor* ownerP, Actor* bulletOwnerP) : Component(ownerP),
bulletOwner(bulletOwnerP)
{
	sphereColl = owner.getComponent<SphereComponent>();
	sphereColl->setCanPassThrough(true);
}

void ProjectileComponent::update(float dt)
{
	owner.setPosition(owner.getPosition() + (fwd * spd * dt));
	fixCollisions(dt);

	currentLifetime += dt;
	if (currentLifetime >= maxLifetime) {
		owner.setState(Actor::ActorState::Dead);
	}
}

void ProjectileComponent::fixCollisions(float dt)
{
	// Need to recompute world transform to update world box
	owner.computeWorldTransform();

	const Sphere& bulletSphere = sphereColl->getWorldSphere();

	CInfo collInfo;
	std::vector<Actor*> actorToIgnore = { bulletOwner, &getOwner()};
	if (Game::instance().getPhysicsSystem().SphereCast(bulletSphere, collInfo, actorToIgnore)) {
		//Collision Interactions
		if (dynamic_cast<WallActor*>(collInfo.actor) != nullptr) {
			BulletFlashActor* bfa = new BulletFlashActor();
			bfa->getComponent<BillboardComponent>()->setTextureIndex(owner.getComponent<BillboardComponent>()->getTextureIndex()+1);
			Vector3 preciseImpact = collInfo.point;
			bfa->setPosition(preciseImpact - (fwd * 10));
			bfa->setAngle(Random::getFloatRange(0, Maths::twoPi));
			owner.setState(Actor::ActorState::Dead);
			return;
		}
		if (HealthComponent* HitHC = collInfo.actor->getComponent<HealthComponent>()) {
			Team currentTeam = Team::None;
			if (HealthComponent* ownerHC = bulletOwner->getComponent<HealthComponent>()) {
				currentTeam = ownerHC->getTeam();
			}
			if (HitHC->dealDamage(dmg,currentTeam)) {
				std::cout << "Damage Dealt" << std::endl;
				BulletFlashActor* bfa = new BulletFlashActor();
				bfa->getComponent<BillboardComponent>()->setTextureIndex(owner.getComponent<BillboardComponent>()->getTextureIndex() + 1);
				Vector3 preciseImpact = collInfo.point;
				bfa->setPosition(preciseImpact - (fwd * 10));
				bfa->setAngle(Random::getFloatRange(0, Maths::twoPi));
				owner.setState(Actor::ActorState::Dead);
			}
			return;
		}
	}
}
