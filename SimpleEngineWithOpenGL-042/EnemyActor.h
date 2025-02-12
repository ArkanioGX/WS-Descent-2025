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
	bool isActive = false;
	float maxDist = 1000;

public:
	void updateActor(float dt) override;

};

