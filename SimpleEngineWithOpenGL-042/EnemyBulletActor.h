#pragma once
#include "Actor.h"
class EnemyBulletActor : public Actor
{
public:
	EnemyBulletActor(Actor* owner);
	~EnemyBulletActor();

	void updateActor(float dt) override;

private:
	class BillboardComponent* BBComponent;
	class SphereComponent* CollisionComponent;
	class ProjectileComponent* projComponent;
};

