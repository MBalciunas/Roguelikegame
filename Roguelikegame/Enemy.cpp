#include "Enemy.h"
#include <string>
#include <random>
#include <time.h>


Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int exp) {
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defense = defense;
	_health = health;
	_experienceValue = exp;
}

void Enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Enemy::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

int Enemy::Attack() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(_attack / 2, _attack);

	return attackRoll(randomEngine);
}

int Enemy::TakeDamage(int attack) {
	attack -= _defense;
	if (attack > 0) {
		_health -= attack;
		//check if died
		if (_health <= 0) {
			return _experienceValue;
		}
	}
	return 0;
}

char Enemy::GetMove(int playerX, int playerY) {
	static default_random_engine randEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0, 6);
	int distance;
	int dx = _x - playerX;
	int dy = _y - playerY;
	int adx = abs(dx);
	int ady = abs(dy);

	distance = adx + ady;

	if (distance <= 5) {

		if (adx > ady) {
			if (dx > 0) return 'a';
			else return 'd';
		}
		else {
			if (dy > 0) return 'w';
			else return 's';

		}
	}
	int randomMove = moveRoll(randEngine);
	switch (randomMove) {
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return '.';
	}
}