#include "LevelManager.h"
#include "WallActor.h"
#include "Actor.h"
#include "ShipActor.h"

LevelManager::LevelManager()
{
}

bool LevelManager::initialize(vector<class Actor*>* actorsListIn)
{
	actors = actorsListIn;
	return true;
}

void LevelManager::loadLevel(Level lvlToLoad)
{
	unload();

	currentLevel = lvlToLoad;

	Vector3 StartPos = Vector3(-500.f, -500.f, 0.f);

	Level& l1 = Assets::getLevel("Level1");
	float size = 200.0f;
	int mapSize = l1.getMaxSize();
	//Load Tiles
	for (int x = 0; x < mapSize; x++) {
		for (int y = 0; y < mapSize; y++) {
			WallActor* wa;
			Quaternion q;
			switch (l1.getTileAt(x, y)) {
			case 1:
				wa = new WallActor();
				wa->setPosition(Vector3(x * size, y * size, 0));
				wa->setScale(200);
				wa->setRotation(q);
				break;
			case 4:
				//da = new DoorActor();
				//da->setPosition(Vector3(x * size, y * size, 0));
				//da->setSize(size);
				//da->createDoors();
				break;
			default:
				break;
			}

			//WallActor* p = new WallActor();
			//p->setPosition(Vector3(x * size, y * size, -size * 3));
			//p->setScale(200);

			//p = new WallActor();
			//p->setPosition(Vector3(x * size, y * size, size));
			//p->setScale(200);

		}
	}

	player = new ShipActor();
	player->setPosition(StartPos);
}

void LevelManager::reloadLevel()
{
	loadLevel(currentLevel);
}

void LevelManager::unload()
{
	for (int i = 0; i < actors->size(); i++) {
		actors->at(i)->setState(Actor::ActorState::Dead);
	}
	actors->clear();
}

Actor* LevelManager::getPlayer()
{
	return player;
}
