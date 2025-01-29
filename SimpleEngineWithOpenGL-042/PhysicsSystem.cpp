#include "PhysicsSystem.h"
#include "Collisions.h"
#include "BoxComponent.h"
#include "SphereComponent.h"
#include "Actor.h"
#include <algorithm>

std::vector<Actor*> PhysicsSystem::DEFAULT_IGNORE = std::vector<Actor*>();

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::addBox(BoxComponent* box)
{
	boxes.emplace_back(box);
}

void PhysicsSystem::removeBox(BoxComponent* box)
{
	auto iter = std::find(begin(boxes), end(boxes), box);
	if (iter != end(boxes))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, boxes.end() - 1);
		boxes.pop_back();
	}
}

void PhysicsSystem::addSphere(SphereComponent* sphr)
{
	spheres.emplace_back(sphr);
}

void PhysicsSystem::removeSphere(SphereComponent* sphr)
{
	auto iter = std::find(begin(spheres), end(spheres), sphr);
	if (iter != end(spheres))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, spheres.end() - 1);
		spheres.pop_back();
	}
}



bool PhysicsSystem::segmentCast(const LineSegment& l, CInfo& outColl, std::vector<Actor*>& ActorsToIgnore)
{
	bool collided = false;
	// Initialize closestT to infinity, so first
	// intersection will always update closestT
	float closestT = Maths::infinity;
	Vector3 norm;
	// Test against all boxes
	for (auto box : boxes)
	{
		float t;
		// Does the segment intersect with the box?
		if (Collisions::intersect(l, box->getWorldBox(), t, norm) )
		{
			// Is this closer than previous intersection?
			if (t < closestT && std::find(ActorsToIgnore.begin(),ActorsToIgnore.end(),&box->getOwner()) == ActorsToIgnore.end())
			{
				closestT = t;
				outColl.point = l.pointOnSegment(t);
				outColl.normal = norm;
				outColl.comp = box;
				outColl.actor = &box->getOwner();
				collided = true;
			}
		}
	}
	return collided;
}

bool PhysicsSystem::SphereCast(const Sphere& l, CInfo& outColl, std::vector<Actor*>& ActorsToIgnore)
{
	bool collided = false;
	// Initialize closestT to infinity, so first
	// intersection will always update closestT
	float closestT = Maths::infinity;
	Vector3 norm;
	// Test against all boxes
	
	for (auto box : boxes)
	{
		float t;
		// Does the segment intersect with the box?
		if (Collisions::intersect(l, box->getWorldBox()))
		{
			t = Maths::abs((l.center - box->getOwner().getPosition()).length());
			// Is this closer than previous intersection?
			if (t < closestT && std::find(ActorsToIgnore.begin(), ActorsToIgnore.end(), &box->getOwner()) == ActorsToIgnore.end())
			{
				closestT = t;
				Vector3 contactPoint = Vector3{
					Maths::clamp(l.center.x,box->getWorldBox().min.x,box->getWorldBox().max.x),
					Maths::clamp(l.center.y,box->getWorldBox().min.y,box->getWorldBox().max.y),
					Maths::clamp(l.center.z,box->getWorldBox().min.z,box->getWorldBox().max.z)
				};
				outColl.point = contactPoint;
				outColl.normal = (l.center - contactPoint);
				outColl.normal.normalize();
				outColl.comp = box;
				outColl.actor = &box->getOwner();
				collided = true;
			}
		}
	}
	return collided;
	return false;
}

void PhysicsSystem::testPairwise(std::function<void(Actor*, Actor*)> f)
{
	// Naive implementation O(n^2)
	for (size_t i = 0; i < boxes.size(); i++)
	{
		// Don't need to test vs itself and any previous i values
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			BoxComponent* a = boxes[i];
			BoxComponent* b = boxes[j];
			if (Collisions::intersect(a->getWorldBox(), b->getWorldBox()))
			{
				// Call supplied function to handle intersection
				f(&a->getOwner(), &b->getOwner());
			}
		}
	}
}

void PhysicsSystem::testSweepAndPrune(std::function<void(Actor*, Actor*)> f)
{
	// Sort by min.x
	std::sort(begin(boxes), end(boxes),
		[](BoxComponent* a, BoxComponent* b) {
			return a->getWorldBox().min.x < b->getWorldBox().min.x;
		});

	for (size_t i = 0; i < boxes.size(); i++)
	{
		// Get max.x for current box
		BoxComponent* a = boxes[i];
		float max = a->getWorldBox().max.x;
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			BoxComponent* b = boxes[j];
			// If AABB[j] min is past the max bounds of AABB[i],
			// then there aren't any other possible intersections
			// against AABB[i]
			if (b->getWorldBox().min.x > max)
			{
				break;
			}
			else if (Collisions::intersect(a->getWorldBox(), b->getWorldBox()))
			{
				f(&a->getOwner(), &b->getOwner());
			}
		}
	}
}