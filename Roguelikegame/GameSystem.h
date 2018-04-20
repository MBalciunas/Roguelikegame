#pragma once
#include "Player.h"
#include "Level.h"
#include <string>

using namespace std;

//Constructor sets up the game
class GameSystem
{
public:
	GameSystem(string levelFileName);

	void PlayGame();
	void PlayerMove();
private:
	Level _level;
	Player _player;
};

