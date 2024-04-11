#pragma once
#include <string>
#include <vector>

#include "tile.h"

class board {
    private:
    int                            length;
    int                            width;
    int                            pickedX;
    int                            pickedY;
    std::vector<int>               xAns;
    std::vector<int>               yAns;
    std::vector<std::vector<tile>> gameBoard;
    std::vector<std::vector<int>> con;  //表示連通情況，若con[終點座標]為1則通過遊戲
    std::vector<std::vector<int>> printSequence;  //the order of printing.

    public:
    bool clear = 0;
    board();

    void generateBoard(int length, int width);
    void keyin();
    void Move();
    tile getTile(int i, int j);
    void refresh();
    void change(int i, int j, tile a);
    void resetCon(void);
    void resetSeq(void);
    void delSeq(std::vector<std::vector<int>> con);
    void setSeq(std::vector<std::vector<int>> con);
    void pathDetect(int x, int y,int dir,int seq);  // just give it (xAns[0], yAns[0])
};