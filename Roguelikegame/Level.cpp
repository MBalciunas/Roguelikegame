#include "Level.h"
#include <fstream>
#include <iostream>

using namespace std;

Level::Level()
{
}

void Level::Load(string fileName, Player &player) {

	//Loads the level
	_levelData.clear();
	_enemies.clear();
	ifstream file;
	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}

	string line;
	while (getline(file, line)) {
		_levelData.push_back(line);
	}
	file.close();

	//Process the level
	char tile;

	for (int i = 0; i < _levelData.size(); ++i) {
		for (int j = 0; j < _levelData[i].size(); ++j) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@': // player
				player.setPosition(j, i);
				break;
			case 's': // snake
				_enemies.push_back(Enemy("Snake", tile, 1, 3, 1, 10, 10));
				_enemies.back().setPosition(j, i);
				break;
			case 'g':
				_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'O':
				_enemies.push_back(Enemy("Ogre", tile, 4, 20, 20, 200, 500));
				_enemies.back().setPosition(j, i);
				break;
			case 'b':
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
				_enemies.back().setPosition(j, i);
				break;
			case 'D':
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 10000));
				_enemies.back().setPosition(j, i);
			default:
				break;
			}
		}
	}
}

void Level::Print(Player &player) {

	system("cls");
	for (int i = 0; i < _levelData.size(); ++i) {
		printf("%s", _levelData[i].c_str());
		switch (i) {
		case 1:
			printf("  Player stats:");
			break;
		case 2:
			printf("  Level: %d", player.GetLevel());
			break;
		case 3:
			printf("  Health: %d", player.GetHealth());
			break;
		case 4:
			printf("  Attack: %d", player.GetAttack());
			break;
		case 5:
			printf("  Defense: %d", player.GetDefense());
			break;
		case 6:
			printf("  Experience: %d", player.GetExperience());
			break;
		case 7:
			printf("  Experience to next level: %d", player.GetExperienceToNextLevel());
			break;
		default:
			break;
		}
		printf("\n");
	}
}

void Level::TryMove(char input, Player &player) {

	int playerX, playerY;
	player.getPosition(playerX, playerY);

	switch (input) {
	case 'w'://up
		ProcessPlayerMove(player, playerX, playerY - 1);
		break;
	case 's'://down
		ProcessPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a'://left
		ProcessPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd'://right
		ProcessPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("Invalid input!\n");
		break;
	}
}

void Level::UpdateMonsters(Player &player) {
	int playerX, playerY;
	int enemyX, enemyY;

	player.getPosition(playerX, playerY);
	char aiMove;
	for (int i = 0; i < _enemies.size(); ++i) {
		aiMove = _enemies[i].GetMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);

		switch (aiMove) {
		case 'w'://up
			ProcessEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's'://down
			ProcessEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a'://left
			ProcessEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd'://right
			ProcessEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		default:
			break;
		}
	}
}

char Level::GetTile(int x, int y) {
	return _levelData[y][x];
}

void Level::SetTile(int x, int y, char tile) {
	_levelData[y][x] = tile;
}

void Level::ProcessPlayerMove(Player &player, int targetX, int targetY) {
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	char moveTile = GetTile(targetX, targetY);
	switch (moveTile) {
	case '_':
		player.setPosition(targetX, targetY);
		SetTile(playerX, playerY, '_');
		SetTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	case 'H':
		Load("level2.txt", player);
	default:
		BattleMonster(player, targetX, targetY);
		break;
	}
}

void Level::ProcessEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
	int playerX, playerY;
	int enemyX, enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = GetTile(targetX, targetY);
	switch (moveTile) {
	case '_':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		SetTile(enemyX, enemyY, '_');
		SetTile(targetX, targetY, _enemies[enemyIndex].GetTile());
		break;
	case '#':
		break;
	case '@':
		BattleMonster(player, enemyX, enemyY);
	default:
		break;
	}


}

void Level::BattleMonster(Player &player, int targetX, int targetY) {
	int enemyX, enemyY;
	int attackRoll;
	int attackResult;
	int enemyDamage;
	int playerDamage;
	string enemyName;

	for (int i = 0; i < _enemies.size(); ++i) {

		_enemies[i].getPosition(enemyX, enemyY);
		enemyName = _enemies[i].GetName();

		if (targetX == enemyX && targetY == enemyY) {
			//Battle!
			attackRoll = player.Attack();
			playerDamage = attackRoll -_enemies[i].GetDefense();
			if (playerDamage < 0) playerDamage = 0;
		//	printf("Player attacked %s with attack: %d\n", enemyName.c_str(), attackRoll);
			attackResult = _enemies[i].TakeDamage(attackRoll);
			if (attackResult != 0) {
				SetTile(targetX, targetY, '_');
				Print(player);
				printf("%s died and granted you %d experience!\n", enemyName.c_str(), _enemies[i].GetExperienceValue());

				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				system("pause");
				player.AddExperience(attackResult);

				return;
			}
			attackRoll = _enemies[i].Attack();
			enemyDamage = attackRoll - player.GetDefense();
			if (enemyDamage < 0) enemyDamage = 0;
		//	printf("%s attacked player with attack: %d\n", enemyName.c_str(), attackRoll);
			attackResult = player.TakeDamage(attackRoll);
			if (attackResult != 0) {
				player.getPosition(targetX, targetY);
				SetTile(targetX, targetY, 'X');
				Print(player);
				printf("%s dealt you %d damage!\n", enemyName.c_str(), enemyDamage);
				printf("You died!\n");
				system("pause");

				exit(0);

				return;
			}
			Print(player);
			printf("You dealt %s %d damage!\n", enemyName.c_str(), playerDamage);
			printf("%s dealt you %d damage!\n", enemyName.c_str(), enemyDamage);
			printf("%s health: %d\n", enemyName.c_str(), _enemies[i].GetHealth());
			system("pause");
		}
	}
}