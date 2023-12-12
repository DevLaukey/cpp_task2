#ifndef B1_H
#define B1_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

namespace B1
{

    class DominoLineB1
    {
    private:
        std::vector<std::pair<std::string, std::string>> dominoes;
        int currentIndex;
        bool directionRight;
        std::unordered_map<std::string, int> nextDominoMap;

    public:
        DominoLineB1(const std::vector<std::pair<std::string, std::string>> &dominoPairs, bool directionRight = true);

        std::pair<std::string, std::string> getNextDomino();

        bool isLineCompleted() const;

        void displayLine() const;

    private:
        void buildNextDominoMap();
    };

} // namespace B1

#endif // B1_H
