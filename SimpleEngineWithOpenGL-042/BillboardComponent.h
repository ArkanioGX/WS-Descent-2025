#pragma once
#include "MeshComponent.h"
#include "CameraComponent.h"
class BillboardComponent : public MeshComponent
{
public:
	BillboardComponent(Actor* owner);

	void update(float dt) override;

	void setAngle(float inAngle);
	float getAngle() const { return angle; }

private:

	float angle = 0.f;
};

