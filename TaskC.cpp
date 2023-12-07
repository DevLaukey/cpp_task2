#include <iostream>
#include <list>
#include <algorithm>

class ConvolutionDominoLine
{
public:
    ConvolutionDominoLine(const std::string &startingDomino, const std::list<std::pair<std::string, std::string>> &restDominoes);

    void displayLine();

private:
    std::list<std::pair<std::string, std::string>> dominoData;
    std::list<std::pair<std::string, int>> positionList;

    void computePositionNumbers();
    void buildDominoLine();
};

ConvolutionDominoLine::ConvolutionDominoLine(const std::string &startingDomino, const std::list<std::pair<std::string, std::string>> &restDominoes)
{
    dominoData = std::list<std::pair<std::string, std::string>>(restDominoes.begin(), restDominoes.end());
    dominoData.push_front(std::make_pair(startingDomino.substr(1, 1), startingDomino));

    computePositionNumbers();
    buildDominoLine();
}

void ConvolutionDominoLine::computePositionNumbers()
{
    int distance = 1;
    while (distance < dominoData.size())
    {
        std::list<std::pair<std::string, std::string>> listB = dominoData;
        std::list<std::pair<std::string, int>> listC;

        listB.sort([](const auto &lhs, const auto &rhs)
                   { return lhs.second < rhs.second; });

        positionList.sort([](const auto &lhs, const auto &rhs)
                          { return lhs.first < rhs.first; });

        auto iterA = dominoData.begin();
        auto iterB = listB.begin();
        auto iterP = positionList.begin();

        while (iterB != listB.end())
        {
            if (iterB->first == iterA->second)
            {
                listC.push_back(std::make_pair(iterA->second, std::stoi(iterB->second)));
                ++iterA;
                ++iterB;
            }
            else if (iterB->first == iterP->first)
            {
                positionList.push_front(std::make_pair(iterB->second, iterP->second + distance));
                ++iterA;
                ++iterP;
            }
            else if (iterB->first > iterP->first)
            {
                ++iterP;
            }
            else if (iterB->first > iterA->second)
            {
                ++iterA;
            }
            ++iterB;
        }

        dominoData.clear();
        for (const auto &pair : listC)
        {
            dominoData.push_back(std::make_pair(pair.first, std::to_string(pair.second)));
        }

        distance *= 2;
    }

    positionList.sort([](const auto &lhs, const auto &rhs)
                      { return lhs.second < rhs.second; });
}

void ConvolutionDominoLine::buildDominoLine()
{
    for (const auto &pair : positionList)
    {
        std::cout << "Red: " << pair.first << ", Blue: " << dominoData.front().first << std::endl;
        dominoData.pop_front();
    }
}

void ConvolutionDominoLine::displayLine()
{
    buildDominoLine();
}

int main()
{
    // Initialize restDominoes using the list constructor
    std::list<std::pair<std::string, std::string>> restDominoes;
    restDominoes.emplace_back("BR", "RB");
    restDominoes.emplace_back("RB", "BR");
    restDominoes.emplace_back("BR", "RB");
    restDominoes.emplace_back("RB", "BR");

    ConvolutionDominoLine convDominoLine("RB", restDominoes);

    convDominoLine.displayLine();

    return 0;
}
