#pragma once
#include "Component.h"
#include "Vector3.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(class Actor* ownerP, class Actor* bulletOwner);

	void update(float dt) override;

	void fixCollisions(float dt);

	void setDamage(float inDmg) { dmg = inDmg; }
	void setFwd(Vector3 inFwd) { fwd = inFwd; }
	void setSpeed(float inSpd) { spd = inSpd; }

	Vector3 getForward() { return fwd; }

private:
	Actor* bulletOwner;

	class SphereComponent* sphereColl;


	Vector3 fwd = Vector3::unitX;
	float spd = 500;
	float dmg = 10;
	float maxLifetime = 10;
	
	float currentLifetime = 0;
};

