#include "board.h"
#include <windows.h>
#include <iostream>
#include<conio.h>


class tile;

void mouseXY(int x, int y) {
	COORD pos = { x,y };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, pos);
}


void setColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void board::refresh() {
	mouseXY(0, 0);
	gameBoard.resize(length+1);

	for (int i = 0; i < length; i++) {
		gameBoard[i].resize(width+1);
	}

	for (int i = 0; i < length; i++) {

		for (int j = 0; j < width; j++) {

			if (j == pickedX && i == pickedY) {
				setColor(240);
				gameBoard[i][j].printTopTile();
				setColor(15);
			}
			else {
				gameBoard[i][j].printTopTile();
			}

		}
		cout << endl;

		for (int j = 0; j < width; j++) {
			if (j == pickedX && i == pickedY) {
				setColor(240);
				gameBoard[i][j].printMidTile();
				setColor(15);
			}
			else {
				gameBoard[i][j].printMidTile();
			}
		}

		cout << endl;

		for (int j = 0; j < width; j++) {
			if (j == pickedX && i == pickedY) {
				setColor(240);
				gameBoard[i][j].printBotTile();
				setColor(15);
			}
			else {
				gameBoard[i][j].printBotTile();
			}
		}
		cout << endl;
	}
	
	mouseXY(0, length * 3);
	printf("direction:");
}

board::board() {
	length = 0;
	width = 0;
	pickedX = 0;
	pickedY = 0;
	/*for (int i = 0; i < 200; i++) {
		gameBoard[i].resize(100);
	}*/
}

void board::generateBoard(int length, int width) {
	this->length = length;
	this->width = width;

	gameBoard.resize(length);
	for (int i = 0; i < length; i++) {
		gameBoard[i].resize(width);
	}

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			gameBoard[i][j].randomTile();
		}
	}
	
	refresh();
}

void board::keyin() {
	mouseXY(10, length * 3);
	char reg = 0;
	int regx = pickedX;
	int regy = pickedY;
	reg = _getch();
	if (reg == 77) {
		printf(">");
		pickedX += 1;
	}
	else if (reg == 75) {
		printf("<");
		pickedX -= 1;
	}
	else if (reg == 80) {
		printf("V");
		pickedY += 1;
	}
	else if (reg == 72) {
		printf("^");
		pickedY -= 1;
	}

	mouseXY(0, length * 3 + 1);

	if (pickedX < 0 || pickedX >= width || pickedY < 0 || pickedY >= length) {
		pickedX = regx;
		pickedY = regy;
		printf("Error:Out of range");
	}
	else {
		printf("                              ");
	}

	mouseXY(0, length * 3);
}

void board::Move() {
	mouseXY(5, length * 3);
	 keyin();
}

