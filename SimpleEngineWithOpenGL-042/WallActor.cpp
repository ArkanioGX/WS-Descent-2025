#include "WallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Game.h"
#include "BoxComponent.h"

WallActor::WallActor() : Actor()
{
	mc = new MeshComponent(this);
	Mesh* mesh = &Assets::getMesh("Mesh_Cube");
	mc->setMesh(*mesh);
	mc->setTextureIndex(1);

	box = new BoxComponent(this);
	AABB boxLimits = AABB(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f));
	box->setObjectBox(boxLimits);

}

