#pragma once
#include "Component.h"
#include "Sphere.h"

class SphereComponent : public Component
{
public:
	SphereComponent(class Actor* ownerP, int updateOrderP = 100);
	virtual ~SphereComponent();

	const Sphere& getWorldSphere() const { return worldSphere; }
	void setObjectSphere(const Sphere& objectBoxP);

	void onUpdateWorldTransform() override;

	void setCanPassThrough(bool b) { canPassThrough = b; }
	bool getCanPassThrough() { return canPassThrough; }


private:
	Sphere objectSphere;
	Sphere worldSphere;
	bool canPassThrough = false;
};

