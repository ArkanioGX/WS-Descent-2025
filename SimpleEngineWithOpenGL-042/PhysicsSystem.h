#pragma once
#include "Vector3.h"
#include "LineSegment.h"
#include "Collisions.h"
#include <functional>
#include <vector>

using std::vector;

class PhysicsSystem
{
public:
	

	static vector<Actor*> DEFAULT_IGNORE;

public:
	PhysicsSystem();

	//void sphere

	void addBox(class BoxComponent* box);
	void removeBox(class BoxComponent* box);
	void addSphere(class SphereComponent* sphr);
	void removeSphere(class SphereComponent* sphr);
	bool segmentCast(const LineSegment& l, CInfo& outColl, std::vector<Actor*>& ActorsToIgnore = DEFAULT_IGNORE);

	bool SphereCast(const Sphere& l, CInfo& outColl, std::vector<Actor*>& ActorsToIgnore);

	// Tests collisions using naive pairwise
	void testPairwise(std::function<void(class Actor*, class Actor*)> f);
	// Test collisions using sweep and prune
	void testSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);


private:
	vector<class BoxComponent*> boxes;
	vector<class SphereComponent*> spheres;
};

