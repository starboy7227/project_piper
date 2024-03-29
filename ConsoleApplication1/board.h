#pragma once
#include <vector>
#include<string>
#include "tile.h"


class board 
{
private:
	int length;
	int width;
	int pickedX;
	int pickedY;
	std::vector<std::vector <tile>> gameBoard;
public:
	board();
	void generateBoard(int length, int width);
	void keyin();
	void Move();
	void refresh();
	
};