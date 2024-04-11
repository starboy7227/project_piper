#include "board.h"

#include <conio.h>
#include <windows.h>

#include <iostream>

#define defultMode

bool finder(std::vector<int> a, std::vector<int> b, int x, int y) {
    for (int i = 0; i < a.size(); i++) {
        if (x == a[i] && y == b[i]) {
            return 1;
        }
    }
    return 0;
}

class tile;

int vectorMax(std::vector<std::vector<int>> input) {
    int max = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (max < input[i][j]) {
                max = input[i][j];
            }
        }
    }
    return max;
}

void mouseXY(int x, int y) {
    COORD  pos  = {x, y};
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, pos);
}

void setColor(int color = 7) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

tile board::getTile(int i, int j) {
    return gameBoard[j][i];
}

void board::setSeq(std::vector<std::vector<int>> con) {
    for (int i = 0; i < printSequence.size(); i++) {
        for (int j = 0; j < printSequence[i].size(); j++) {
            if (con[i][j]) {
                printSequence[i][j] = 1;
            }
        }
    }
}

void board::delSeq(std::vector<std::vector<int>> con) {
    for (int i = 0; i < printSequence.size(); i++) {
        for (int j = 0; j < printSequence[i].size(); j++) {
            if (con[i][j] == 0) {
                printSequence[i][j] = 0;
            }
        }
    }
}

void board::refresh() {
    mouseXY(0, 0);
    gameBoard.resize(length + 1);

    for (int i = 0; i < length; i++) {
        gameBoard[i].resize(width + 1);
    }
    this->resetSeq();
    this->setSeq(con);
    this->resetCon();
   
    
    this->pathDetect(xAns[0], yAns[0],1,1);
    for (int k = 1; k <= vectorMax(printSequence); k++) {
        Sleep(1);
        mouseXY(0, 0);
        for (int i = 0; i < length; i++) {
#ifdef defultMode
            for (int j = 0; j < width; j++) {
                if (j == pickedX && i == pickedY) {
                    setColor(139);
                }
                else if (j == xAns[0] && i == yAns[0]) {
                    setColor(161);
                }
                else if (j == xAns[xAns.size() - 1] && i == yAns[yAns.size() - 1]) {
                    setColor(224);
                }
                else if (con[i][j] && printSequence[i][j] <= k) {  //} else if (finder(xAns, yAns, j, i)) {
                    setColor(95);
                }
                gameBoard[i][j].printTopTile();
                setColor(15);
            }
            cout << endl;

            for (int j = 0; j < width; j++) {
                if (j == pickedX && i == pickedY) {
                    setColor(139);
                }
                else if (j == xAns[xAns.size() - 1] && i == yAns[yAns.size() - 1]) {
                    setColor(224);
                }
                else if (j == xAns[0] && i == yAns[0]) {
                    setColor(161);
                }
                else if (con[i][j] && printSequence[i][j] <= k) {
                    setColor(95);
                }
                gameBoard[i][j].printMidTile();
                setColor(15);
            }

            cout << endl;

            for (int j = 0; j < width; j++) {
                if (j == pickedX && i == pickedY) {
                    setColor(139);
                }
                else if (j == xAns[0] && i == yAns[0]) {
                    setColor(161);
                }
                else if (j == xAns[xAns.size() - 1] && i == yAns[yAns.size() - 1]) {
                    setColor(224);
                }
                else if (con[i][j] && printSequence[i][j] <= k) {
                    setColor(95);
                }
                gameBoard[i][j].printBotTile();
                setColor(15);
            }
            cout << endl;
#endif  // defultMode
#ifdef artMode
            for (int j = 0; j < width; j++) {
                if (j == pickedX && i == pickedY) {
                    setColor(139);  //�ǡA�襤
                }
                else if (j == xAns[0] && i == yAns[0]) {
                    setColor(161);  //��A�_�I(�H)
                }
                else if (j == xAns[xAns.size() - 1] && i == yAns[yAns.size() - 1]) {
                    setColor(224);  //���A���I(�H)
                }
                else if (con[i][j]) {
                    setColor(95);  //���A�w�]���|
                }
                gameBoard[i][j].printArtTop();
                setColor(15);
            }
            cout << endl;

            for (int j = 0; j < width; j++) {
                if (j == pickedX && i == pickedY) {
                    setColor(139);  //�ǡA�襤
                }
                else if (j == xAns[0] && i == yAns[0]) {
                    setColor(161);  //��A�_�I(�H)
                }
                else if (j == xAns[xAns.size() - 1] && i == yAns[yAns.size() - 1]) {
                    setColor(224);  //���A���I(�H)
                }
                else if (con[i][j]) {
                    setColor(95);  //���A�w�]���|
                }
                gameBoard[i][j].printArtBot();
                setColor(15);
            }

            cout << endl;

#endif
        }
    }
    
    mouseXY(0, length * 3);
    if (con[yAns[yAns.size() - 1]][xAns[xAns.size() - 1]] != 0) {
        clear = 1;
    } else {
        printf("direction:");
    }
}

board::board() {
    length  = 0;
    width   = 0;
    pickedX = 0;
    pickedY = 0;
    /*for (int i = 0; i < 200; i++) {
        gameBoard[i].resize(100);
    }*/
}

void board::change(int i, int j, tile a) {
    a.rotate();
    gameBoard[j][i] = a;
}

void board::generateBoard(int length, int width) {
    this->length         = length;
    this->width          = width;
    int            x     = 0;
    int            y     = 0;
    int            endX  = 0;
    int            endY  = 0;
    int            count = 0;
    vector<string> maze;
    vector<int>    pathx;
    vector<int>    pathy;
    int            rnd = 0;

    srand(time(NULL));
    gameBoard.resize(length);
    maze.resize(length + 2);
    con.resize(length);
    printSequence.resize(length);
    for (int i = 0; i < length; i++) {
        gameBoard[i].resize(width);
        con[i].resize(width);
        printSequence[i].resize(width);
    }

    for (int i = 0; i < length + 2; i++) {
        maze[i].resize(width + 2);
    }

    for (int i = 0; i < length + 2; i++) {
        for (int j = 0; j < width + 2; j++) {
            maze[i][j] = 'a';
        }
    }
    for (int i = 1; i < length + 1; i++) {
        for (int j = 1; j < width + 1; j++) {
            maze[i][j] = 0;
        }
    }

    rnd = rand() % 2;
    if (rnd == 0) {
        rnd = rand() % width + 1;
        x   = rnd;
        y   = 1;
    } else {
        rnd = rand() % length + 1;
        y   = rnd;
        x   = 1;
    }

    endX = x;
    endY = y;
    while (x == endX && y == endY) {
        rnd = rand() % 2;
        if (rnd == 0) {
            rnd  = rand() % width + 1;
            endX = rnd;
            endY = length;
        } else {
            rnd  = rand() % length + 1;
            endX = width;
            endY = rnd;
        }
    }

    maze[y][x] = 's';
    pathx.push_back(x);
    pathy.push_back(y);
    count += 1;

    while (count != length * width) {
        rnd = rand() % 4;

        if (x == endX && y == endY) {
            xAns.resize(pathx.size());
            yAns.resize(pathy.size());
            for (int i = 0; i < pathx.size(); i++) {
                xAns[i] = pathx[i] - 1;
                yAns[i] = pathy[i] - 1;
            }
        }
        if (maze[y + 1][x] != 0 && maze[y - 1][x] != 0 && maze[y][x + 1] != 0 && maze[y][x - 1] != 0) {
            // cout << maze[y + 1][x] << " " << maze[y - 1][x] << " " << maze[y][x + 1] << " " << maze[y][x - 1];
            if (maze[y][x] == 0) {
                maze[y][x] = 'e';
                count += 1;
            }

            if (pathx.size() - 1 > 0) {
                pathx.pop_back();
                pathy.pop_back();
                x = pathx[pathx.size() - 1];
                y = pathy[pathy.size() - 1];
            }

        } else if (rnd == 0 && maze[y][x - 1] == 0) {
            if (maze[y][x] != 0) {
                maze[y][x] = 't';
            } else {
                maze[y][x] = 'l';
                count += 1;
            }

            x = x - 1;

            pathx.push_back(x);
            pathy.push_back(y);
        } else if (rnd == 1 && maze[y - 1][x] == 0) {
            if (maze[y][x] != 0) {
                maze[y][x] = 't';
            } else {
                maze[y][x] = 'u';
                count += 1;
            }
            y = y - 1;

            pathx.push_back(x);
            pathy.push_back(y);
        } else if (rnd == 2 && maze[y][x + 1] == 0) {
            if (maze[y][x] != 0) {
                maze[y][x] = 't';
            } else {
                maze[y][x] = 'r';
                count += 1;
            }

            x = x + 1;

            pathx.push_back(x);
            pathy.push_back(y);
        } else if (rnd == 3 && maze[y + 1][x] == 0) {
            if (maze[y][x] != 0) {
                maze[y][x] = 't';
            } else {
                maze[y][x] = 'd';
                count += 1;
            }

            y = y + 1;

            pathx.push_back(x);
            pathy.push_back(y);
        }
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            rnd = rand() % 11;
            gameBoard[i][j].setType(rnd);
        }
    }

    for (int i = 0; i < xAns.size(); i++) {
        if (i - 1 >= 0 && i + 1 < xAns.size()) {
            rnd = rand();
            if (xAns[i - 1] == xAns[i] && xAns[i + 1] == xAns[i]) {
                gameBoard[yAns[i]][xAns[i]].randomTile('s', rnd);
            } else if (yAns[i - 1] == yAns[i] && yAns[i + 1] == yAns[i]) {
                gameBoard[yAns[i]][xAns[i]].randomTile('s', rnd);
            } else if (xAns[i - 1] == xAns[i] && yAns[i + 1] == yAns[i]) {
                gameBoard[yAns[i]][xAns[i]].randomTile('t', rnd);
            } else if (xAns[i + 1] == xAns[i] && yAns[i - 1] == yAns[i]) {
                gameBoard[yAns[i]][xAns[i]].randomTile('t', rnd);
            }
        } else if (i - 1 >= 0 && i + 1 > xAns.size()) {
            gameBoard[yAns[i]][xAns[i]].randomTile('s', rnd);
        }
    }

    for (int i = 0; i < length + 1; i++) {
        for (int j = 0; j < 3; j++) {
            cout << endl;
        }
    }

    for (int i = 0; i < xAns.size(); i++) {
        cout << "xAns = " << xAns[i] << " yAns = " << yAns[i] << endl;
    }
    gameBoard[yAns[0]][xAns[0]].setType(0);

    refresh();
}

void board::Move() {
    mouseXY(5, length * 3);
    keyin();
}

void board::keyin() {
    mouseXY(10, length * 3);

    char reg  = 0;
    int  regx = pickedX;
    int  regy = pickedY;
    reg       = _getch();
    cout << reg;
    if (reg == 77) {
        printf(">");
        pickedX += 1;
    } else if (reg == 75) {
        printf("<");
        pickedX -= 1;
    } else if (reg == 80) {
        printf("V");
        pickedY += 1;
    } else if (reg == 72) {
        printf("^");
        pickedY -= 1;
    } else if (reg == 13) {
        change(pickedX, pickedY, getTile(pickedX, pickedY));
        printf("@");
    }

    mouseXY(0, length * 3 + 1);

    if (pickedX < 0 || pickedX >= width || pickedY < 0 || pickedY >= length) {
        pickedX = regx;
        pickedY = regy;
        printf("Error:Out of range");
    } else {
        printf("                              ");
    }

    mouseXY(0, length * 3);
}

void board::resetCon(void) {
    for (int i = 0; i < con.size(); i++) {
        for (int j = 0; j < con[i].size(); j++) {
            con[i][j] = 0;
        }
    }
}

void board::resetSeq(void) {
    for (int i = 0; i < printSequence.size(); i++) {
        for (int j = 0; j < printSequence[i].size(); j++) {
            printSequence[i][j] = 0;
        }
    }
}

void board::pathDetect(int x, int y,int dir,int seq) {
    con[y][x] = dir;
    if (printSequence[y][x] == 1) {

    }
    else {
        printSequence[y][x] = seq;
    }
    
    bool upave[11]{1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0};
    bool downave[11]{1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1};
    bool leftave[11]{1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1};
    bool rightave[11]{1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1};

    if (upave[gameBoard[y][x].type] && y > 0 && !con[y - 1][x] && downave[gameBoard[y - 1][x].type]) {
        pathDetect(x, y - 1,2, printSequence[y][x] +1);
    }
    if (downave[gameBoard[y][x].type] && y < con.size() - 1 && !con[y + 1][x] && upave[gameBoard[y + 1][x].type]) {
        pathDetect(x, y + 1, 4, printSequence[y][x] + 1);
    }
    if (leftave[gameBoard[y][x].type] && x > 0 && !con[y][x - 1] && rightave[gameBoard[y][x - 1].type]) {
        pathDetect(x - 1, y, 1, printSequence[y][x] + 1);
    }
    if (rightave[gameBoard[y][x].type] && x < con[y].size() - 1 && !con[y][x + 1] && leftave[gameBoard[y][x + 1].type]) {
        pathDetect(x + 1, y, 3, printSequence[y][x] + 1);
    }
}

