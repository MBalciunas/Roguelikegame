#include "Player.h"
#include <random>
#include <time.h>

using namespace std;

Player::Player()
{
}

void Player::init(int level, int health, int attack, int defense, int experience) {
	_level = level;
	_maxHealth = health;
	_health = _maxHealth;
	_attack = attack;
	_defense = defense;
	_experience = experience;
}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Player::AddExperience(int experience) {
	_experience += experience;
	while (_experience > _experienceRequired) {
		printf("Leveled up!\n", _experience);
		_experience -= _experienceRequired;
		_attack += 10;
		_defense += 5;
		_maxHealth += 10;
		_health = _maxHealth;
		_level++;
		_experienceRequired += 50;
		system("pause");
	}
}

void Player::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}
int Player::Attack() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackRoll(_attack/2, _attack);

	return attackRoll(randomEngine);
}

int Player::TakeDamage(int attack) {
	attack -= _defense;
	if (attack > 0) {
		_health -= attack;
		//check if died
		if (_health <= 0) {
			return 1;
		}
	}
	
	return 0;
}