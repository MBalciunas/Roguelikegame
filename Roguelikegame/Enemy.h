#pragma once
#include <string>
#include "Player.h"

using namespace std;

class Enemy
{
public:
	Enemy(string name, char tile, int level, int attack, int defense, int health, int exp);

	//Setters
	void setPosition(int x, int y);

	//Getters
	void getPosition(int &x, int &y);
	char GetTile() { return _tile; }
	int GetDefense() { return _defense; }
	int GetHealth() { return _health; }
	int GetExperienceValue() { return _experienceValue; }
	string GetName() { return _name; }

	int Attack();
	int TakeDamage(int attack);

	//Gets AI move command
	char GetMove(int playerX, int playerY);

private:
	string _name;
	char _tile;

	int _level;
	int _attack;
	int _defense;
	int _health;
	int _experienceValue;

	//Position
	int _x;
	int _y;

};

