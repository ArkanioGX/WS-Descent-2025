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

};

