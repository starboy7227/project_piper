#include "board.h"
#include <windows.h>
#include <iostream>
#include<conio.h>


bool finder(std::vector<int> a, std::vector<int> b,int x, int y) {
	for (int i = 0; i < a.size(); i++) {
		if (x == a[i] && y == b[i]) {
			return 1;
		}
	}
	return 0;
}

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

tile board::getTile(int i,int j) {
	return gameBoard[j][i];
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
				setColor(139);
				gameBoard[i][j].printTopTile();
				setColor(15);
			}
			else if (finder(xAns, yAns, j, i) ) {
				setColor(95);
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
				setColor(139);
				gameBoard[i][j].printMidTile();
				setColor(15);
			}
			else if(finder(xAns,yAns,j,i) ){
				setColor(95);
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
				setColor(139);
				gameBoard[i][j].printBotTile();
				setColor(15);
			}
			else if (finder(xAns, yAns, j, i) ) {
				setColor(95);
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

void board::change(int i,int j,tile a) {
	a.rotate();
	gameBoard[j][i] = a;
}

void board::generateBoard(int length, int width) {
	this->length = length;
	this->width = width;
	int x = 0;
	int y = 0;
	char face = 0;
	vector<string> maze;
	int rnd = 0;
	int brnd = 0;
	int rndTime = 0;
	int rndAns = 0;
	int rndDir = 0;
	gameBoard.resize(length);
	maze.resize(length);

	for (int i = 0; i < length; i++) {
		gameBoard[i].resize(width);
		maze[i].resize(width);
	}


	srand(time(NULL));

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			
			rnd = rand() % 2;
			if (j + 1 >= width) {
				maze[i][j] = 'd';
			}
			else if (i + 1 >= length) {
				maze[i][j] = 'r';
			}
			else if (rnd == 0) {
				maze[i][j] = 'r';
			}
			else if (rnd == 1) {
				maze[i][j] = 'd';
			}
		}
	}
	rnd = rand() % 2;
	if (rnd == 0) {
		rnd = rand() % length;
		x = rnd;
		y = 0;
		xAns.push_back(rnd);
		yAns.push_back(0);
	}
	else {
		rnd = rand() % width; 
		y = rnd;
		x = 0;
		yAns.push_back(rnd);
		xAns.push_back(0);
	}


	while (x != length - 1 || y != width - 1) {
		if (maze[y][x] == 'd') {
			y += 1;
			xAns.push_back(x);
			yAns.push_back(y);
		}
		else {
			x += 1;
			xAns.push_back(x);
			yAns.push_back(y);
		}
	}

	/*rndTime = rand() % 15;
	for (int i = 0; i < rndTime; i++) {
		rndAns = rand() % xAns.size();
		rndDir = rand() % 2;
		if (rndDir == 0) {
			if()
			for (int j = 1; j <=3; j++) {
				if (yAns[rndAns] - j >= 0) {
					xAns.push_back(xAns[rndAns]);
					yAns.push_back(yAns[rndAns] - j);
				}
			}

		}
		else {
			for (int j = 1; j <= 3; j++) {
				if (xAns[rndAns] + j < width) {
					xAns.push_back(xAns[rndAns] + j);
					yAns.push_back(yAns[rndAns]);
				}
			}
		}
	}*/
	/*for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}*/

	gameBoard[0][0].setType(0);

	face = maze[0][0];

	for (int i = 0; i < xAns.size(); i++) {
		if (maze[yAns[i]][xAns[i]] == 'r' && face == 'r') {
			face = 'r';
			gameBoard[yAns[i]][xAns[i]].setType(1);
		}else if (maze[yAns[i]][xAns[i]] == 'd' && face == 'r') {
			face = 'd';
			gameBoard[yAns[i]][xAns[i]].setType(3);
		}
		else if (maze[yAns[i]][xAns[i]] == 'r' && face == 'd') {
			face = 'r';
			gameBoard[yAns[i]][xAns[i]].setType(3);
		}
		else if (maze[yAns[i]][xAns[i]] == 'd' && face == 'd') {
			face = 'd';
			gameBoard[yAns[i]][xAns[i]].setType(1);
		}

	}
	refresh();
}

void board::Move() {
	mouseXY(5, length * 3);
	keyin();
}


void board::keyin() {
	mouseXY(10, length * 3);

	char reg = 0;
	int regx = pickedX;
	int regy = pickedY;
	reg = _getch();
	cout << reg;
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
	else if (reg == 13) {
		change(pickedX, pickedY, getTile(pickedX, pickedY));
		printf("@");

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


