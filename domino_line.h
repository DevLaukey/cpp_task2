// domino_line.h
#ifndef DOMINO_LINE_H
#define DOMINO_LINE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class DominoLine
{
private:
    std::vector<std::string> dominoes;
    bool lineCompleted;

public:
    DominoLine(const std::vector<std::pair<std::string, std::string>> &dominoPairs, bool directionRight = true);
    DominoLine(const std::string &startingFilePath, const std::string &restOfDominoFilePath);

    std::string getNextDominoToRight();
    std::string getNextDominoToLeft();
    bool isLineCompleted() const;
    void displayLine() const;

private:
    void buildNextDominoMap(const std::vector<std::pair<std::string, std::string>> &dominoPairs);

    std::string getNextDominoToRightHelper();
    std::string getNextDominoToLeftHelper();
};

#endif // DOMINO_LINE_H
