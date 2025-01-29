#pragma once
#include "Level.h"
#include "Assets.h"


class LevelManager
{
public:
	LevelManager();
	bool initialize(vector<class Actor*>* );

	void loadLevel(Level lvlToLoad);

	void reloadLevel();

	void unload();

	class Actor* getPlayer();

private:
	Level currentLevel;

	class Actor* player;

	Vector3 startPos;

	vector<class Actor*>* actors;
};

