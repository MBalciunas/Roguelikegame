#include "GameSystem.h"
#include <iostream>
#include <conio.h>
#include <ctype.h>

using namespace std;


GameSystem::GameSystem(string levelFileName)
{
	_player.init(1, 100, 10, 2, 0);

	_level.Load("level1.txt", _player);
}

void GameSystem::PlayGame() {

	bool isDone = false;

	while (!isDone) {
		_level.Print(_player);
		PlayerMove();
		_level.UpdateMonsters(_player);
	}
}

void GameSystem::PlayerMove() {
	char input;
	printf("Enter a move command (w/s/a/d): \n");
	input = _getch();
//	putchar(tolower(input));
	
	_level.TryMove(input, _player);

	}
