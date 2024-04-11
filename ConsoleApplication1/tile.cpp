#include "tile.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>


void tile::setType(int num) {
	type = num;
}

void tile::randomTile(char mode,int seed) {
	int x = 0;
	x = seed;
	if (mode == 's') {
		x = x % 7;
		switch (x) {

		case 0 :
			type = 0;
			break;
		case 1:
			type = 1;
			break;
		case 2:
			type = 2;
			break;
		case 3:
			type = 7;
			break;
		case 4:
			type = 8;
			break;
		case 5:
			type = 9;
			break;
		case 6:
			type = 10;
			break;
		}
	}
	else if (mode == 't') {
		x = x % 9;
		switch (x) {
		case 0:
			type = 0;
			break;
		case 1:
			type = 3;
			break;
		case 2:
			type = 4;
			break;
		case 3:
			type = 5;
			break;
		case 4:
			type = 6;
			break;
		case 5:
			type = 7;
			break;
		case 6:
			type = 8;
			break;
		case 7:
			type = 9;
			break;
		case 8:
			type = 10;
			break;
		}
	}
}

void tile::printTopTile() {
	std::cout << topApper[type];
}

void tile::printMidTile() {
	std::cout << midApper[type];
}

void tile::printBotTile() {
	std::cout << botApper[type];
}

void tile::printArtTop() {
    std::cout << artTop[type];
}

void tile::printArtBot() {
    std::cout << artBot[type];
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