#include "HealthComponent.h"
#include "BulletFlashActor.h"
#include "Actor.h"
#include "Game.h"
#include "Random.h"
#include "GameOverScreen.h"

HealthComponent::HealthComponent(Actor* ownerP):
Component(ownerP)
{

}

void HealthComponent::update(float dt)
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
		if (&owner == Game::instance().getPlayer()) {
			Game::instance().getHUD()->updateHP(currentHP);
			if (currentHP == 0 && !isPlayerDead) {
				isPlayerDead = true;
				new GameOverScreen();
			}
		}
		else {
			if (currentHP == 0) {
				owner.setState(Actor::ActorState::Dead);
			}
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


