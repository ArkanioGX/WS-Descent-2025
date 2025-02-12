#pragma once
#include "Component.h"

enum Team
{
	None,
	Player,
	Enemy
};

class HealthComponent : public Component
{
public:
	HealthComponent(class Actor* ownerP);

	void update(float dt) override;

	void heal();
	void heal(int heal);
	bool dealDamage(int dmg, Team emmiterTeam = Team::None);

	void setMaxHP(int newMaxHP);
	void setTeam(Team newTeam);

	Team getTeam() { return currentTeam; }

	bool isPlayerDead = false;

private:
	
	
	Team currentTeam = Team::None;
	float explosionTImer = 0;
	int maxHP = 50;
	int currentHP = maxHP;

};

