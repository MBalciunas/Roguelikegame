#pragma once


class Player 
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int experience);

	int Attack();

	//Setters
	void setPosition(int x, int y);

	void AddExperience(int experience);

	//Getters
	void getPosition(int &x, int &y);

	int TakeDamage(int attack);

	int GetLevel() { return _level; }
	int GetHealth() { return _health; }
	int GetAttack() { return _attack; }
	int GetDefense() { return _defense; }
	int GetExperience() { return _experience; }
	int GetExperienceToNextLevel(){ return _experienceRequired; }


private:
	//Properties
	int _experienceRequired = 50;
	int _level;
	int _maxHealth;
	int _health;
	int _attack;
	int _defense;
	int _experience;

	//Position
	int _x;
	int _y;

};

