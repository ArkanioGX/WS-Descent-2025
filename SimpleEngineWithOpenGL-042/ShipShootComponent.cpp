#include "ShipShootComponent.h"
#include "InputSystem.h"
#include "ShipBulletActor.h"
#include "ProjectileComponent.h"
#include "Actor.h"
#include "iostream"
#include "Game.h"

ShipShootComponent::ShipShootComponent(Actor* ownerP):
	Component(ownerP)
{
}

void ShipShootComponent::update(float dt)
{
	currentDelay = Maths::clamp(currentDelay - dt, 0.f, delayBetweenShots);
	if (shootInput && currentDelay == 0.f) {
		float cannonSpace = 65;

		ShipBulletActor* bullet = new ShipBulletActor(&getOwner());

		bullet->setPosition(owner.getPosition() + owner.getRight() * cannonSpace);
		ProjectileComponent* pc = bullet->getComponent<ProjectileComponent>();
		Vector3 newFwd = Vector3::transform(Vector3::unitX, owner.getRotation());
		pc->setFwd(newFwd);

		bullet = new ShipBulletActor(&getOwner());

		bullet->setPosition(owner.getPosition() + owner.getRight() * -cannonSpace);
		pc = bullet->getComponent<ProjectileComponent>();
		newFwd = Vector3::transform(Vector3::unitX, owner.getRotation());
		pc->setFwd(newFwd);

		currentDelay = delayBetweenShots;

	}
}

void ShipShootComponent::processInput(const InputState& inputState)
{
	shootInput = inputState.controller.getRightTrigger() + inputState.mouse.getButtonValue(1);
	//shootInput = fmin(1, shootInput);
}
