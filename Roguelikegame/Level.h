#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

using namespace std; 

class Level
{
public:
	Level();
	void Load(string fileName, Player &player);
	void Print(Player &player);

	void TryMove(char input, Player &player);
	void UpdateMonsters(Player &player);

	char GetTile(int x, int y);
	void SetTile(int x, int y, char tile);

private:
	void ProcessPlayerMove(Player &player, int targetX, int targetY);
	void ProcessEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
	void BattleMonster(Player &player, int targetX, int targetY);

	vector <string> _levelData;
	vector<Enemy> _enemies;
};

