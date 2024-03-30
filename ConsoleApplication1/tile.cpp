#include "tile.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>


void tile::setType(int num) {
	type = num;
}

void tile::randomTile() {
	int x = 0;
	srand(unsigned(time(NULL)));
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



void tile::rotate() {
	if (type == 0) {
	}
	else if (type >= 1 && type <= 2) {
		
		type = type % 2;
		type += 1;
	}
	else if (type >= 3 && type <= 6) {
		type += 2;
		type = type % 4;
		type += 3;
	}
	else if (type >= 7 && type <= 10) {
		type += 2;
		type = type % 4;
		type += 7;
	}
}