#include "BillboardComponent.h"
#include "Actor.h"
#include "Game.h"
#include "RendererOGL.h"

BillboardComponent::BillboardComponent(Actor* owner) : MeshComponent(owner)
{
	setMesh(Assets::getMesh("Mesh_Billboard"));
	owner->setScale(100);
}

void BillboardComponent::update(float dt)
{
	Quaternion playerRotation = Game::instance().getPlayer()->getRotation();
	owner.setRotation(playerRotation);
}

