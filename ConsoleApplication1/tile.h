#include <string>

using namespace std;
class tile {
    private:
    string topApper[11] = {" # ", "   ", " # ", " # ", " # ", "   ", "   ", " # ", " # ", " # ", "   "};
    string midApper[11] = {"###", "###", " # ", "## ", " ##", " ##", "## ", "## ", "###", " ##", "###"};
    string botApper[11] = {" # ", "   ", " # ", "   ", "   ", " # ", " # ", " # ", "   ", " # ", " # "};
    string artTop[11]   = {"�}  �|", "�w�w�w�w", "�x  �x", "�}  �x", "�x  �|", "�z�w�w�w", "�w�w�w�{", "�}  �x", "�}  �|", "�x  �|", "�w�w�w�w"};
    string artBot[11]   = {"�{  �z", "�w�w�w�w", "�x  �x", "�w�w�w�}", "�|�w�w�w", "�x  �z", "�{  �x", "�{  �x", "�w�w�w�w", "�x  �z", "�{  �z"};

    public:
    int type = 0;

    void setType(int num);
    void randomTile(char mode, int seed);
    void printTopTile();
    void printMidTile();
    void printBotTile();
    void printArtTop();
    void printArtBot();

    void rotate();
};