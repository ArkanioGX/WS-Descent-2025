#include "SphereComponent.h"
#include "Actor.h"
#include "Game.h"

SphereComponent::SphereComponent(Actor* ownerP, int updateOrderP) :
	Component(ownerP, updateOrderP),
	objectSphere(Vector3::zero, 0),
	worldSphere(Vector3::zero, 0)
{
	Game::instance().getPhysicsSystem().addSphere(this);
}

SphereComponent::~SphereComponent()
{
	Game::instance().getPhysicsSystem().removeSphere(this);
}

void SphereComponent::setObjectSphere(const Sphere& objectSphereP)
{
	objectSphere = objectSphereP;
}

void SphereComponent::onUpdateWorldTransform()
{
	// Reset to object space box
	worldSphere = objectSphere;

	worldSphere.radius *= owner.getScale();
	worldSphere.center += owner.getPosition();
}
