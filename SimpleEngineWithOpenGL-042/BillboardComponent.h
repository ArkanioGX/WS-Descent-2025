#pragma once
#include "MeshComponent.h"
#include "CameraComponent.h"
class BillboardComponent : public MeshComponent
{
public:
	BillboardComponent(Actor* owner);

	void update(float dt) override;

private:
	//Actor* player;
};

