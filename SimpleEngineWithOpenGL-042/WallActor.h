#pragma once
#include "Actor.h"
class WallActor : public Actor
{
public:
	WallActor();

private:
	class BoxComponent* box;
	class MeshComponent* mc;
};

