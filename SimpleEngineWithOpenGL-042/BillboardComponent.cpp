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
	if (angle != 0.f) {
		Vector3 euler = Quaternion::ToEulerAngles(playerRotation);
		euler.x += angle;
		playerRotation = Quaternion::FromEuler(euler);
	}
	owner.setRotation(playerRotation);
}

void BillboardComponent::setAngle(float inAngle)
{
	angle = Maths::fmod(inAngle, Maths::twoPi);
}

