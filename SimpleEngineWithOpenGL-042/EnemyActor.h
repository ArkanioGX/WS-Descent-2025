#pragma once
#include "Actor.h"
class EnemyActor : public Actor
{
public:
	EnemyActor();
	~EnemyActor();

private:
	class BillboardComponent* BBComponent;
	class SphereComponent* CollisionComponent;
	class HealthComponent* HPComponent;

	float count = 0;

public:
	void updateActor(float dt) override;

};

