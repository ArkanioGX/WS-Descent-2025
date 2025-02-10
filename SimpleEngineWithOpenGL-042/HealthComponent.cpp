#include "HealthComponent.h"
#include "Actor.h"

HealthComponent::HealthComponent(Actor* ownerP):
Component(ownerP)
{

}

void HealthComponent::heal()
{
	heal(maxHP);
}

void HealthComponent::heal(int heal)
{
	currentHP = Maths::clamp(currentHP + heal, 0, maxHP);
}


bool HealthComponent::dealDamage(int dmg, Team emmiterTeam)
{
	if (emmiterTeam == Team::None || currentTeam == Team::None || emmiterTeam != currentTeam) {
		currentHP = Maths::clamp(currentHP - dmg, 0, maxHP);
		if (currentHP == 0) {
			owner.setState(Actor::ActorState::Dead);
		}
		return true;
	}
	return false;
}

void HealthComponent::setMaxHP(int newMaxHP)
{
	maxHP = newMaxHP;
	heal();
}

void HealthComponent::setTeam(Team newTeam)
{
	currentTeam = newTeam;
}


