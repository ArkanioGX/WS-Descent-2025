#include "ProjectileComponent.h"
#include "Actor.h"
#include "SphereComponent.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "Collisions.h"

ProjectileComponent::ProjectileComponent(Actor* ownerP, Actor* bulletOwnerP) : Component(ownerP),
bulletOwner(bulletOwnerP)
{
	sphereColl = owner.getComponent<SphereComponent>();
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


}
