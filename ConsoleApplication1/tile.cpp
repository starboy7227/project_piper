#include "tile.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>


void tile::setType(int num) {
	type = num;
}

void tile::randomTile() {
	int x = 0;
	srand(time(NULL));
	x = rand() % 11;
	setType(x);
}

void tile::printTopTile(){
	std::cout << topApper[type];
}

void tile::printMidTile() {
	std::cout << midApper[type];
}

void tile::printBotTile() {
	std::cout << botApper[type];
}