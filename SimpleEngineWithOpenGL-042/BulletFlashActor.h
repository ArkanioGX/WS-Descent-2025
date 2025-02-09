#pragma once
#include "Actor.h"
class BulletFlashActor : public Actor
{
public:
	BulletFlashActor();

	void updateActor(float dt)override;
	void setAngle(float dt);

private:
	float angleSpeed =  Maths::toRadians(720);
	float ttl = 0.1f;

	float angle = 0;

	class BillboardComponent* bbComponent;
};

