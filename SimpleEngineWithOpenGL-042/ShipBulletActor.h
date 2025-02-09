#pragma once
#include "Actor.h"
class ShipBulletActor : public Actor
{
public:
	ShipBulletActor(Actor* owner);
	~ShipBulletActor();

	void updateActor(float dt) override;
	void fixCollisions();

private:
	class BillboardComponent* BBComponent;
	class SphereComponent* CollisionComponent;
	class ProjectileComponent* projComponent;

	Actor* bulletOwner;
};

