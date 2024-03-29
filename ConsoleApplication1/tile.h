#include<string>

using namespace std;
class tile {
private:
	int type = 0;
	string topApper[11] = { "*#*","***","*#*","*#*" ,"*#*" ,"***" ,"***" ,"*#*" ,"*#*" ,"*#*" ,"***" };
	string midApper[11] = { "###","###","*#*","##*" ,"*##" ,"*##" ,"##*" ,"##*" ,"###" ,"*##" ,"###" };
	string botApper[11] = { "*#*","***","*#*","***" ,"***" ,"*#*" ,"*#*" ,"*#*" ,"***" ,"*#*" ,"*#*" };
public:
	void setType(int num);
	void randomTile();
	void printTopTile();
	void printMidTile();
	void printBotTile();
};