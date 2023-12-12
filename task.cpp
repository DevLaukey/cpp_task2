#include <iostream>
#include <vector>

class DominoLine
{
private:
    std::vector<int> dominoes;
    int currentIndex;

public:
    DominoLine(int startingDomino, const std::vector<int> &restOfDominoes)
    {
        dominoes.push_back(startingDomino);
        dominoes.insert(dominoes.end(), restOfDominoes.begin(), restOfDominoes.end());
        currentIndex = 0;
    }

    int getNextDomino()
    {
        if (currentIndex < dominoes.size())
        {
            int nextDomino = dominoes[currentIndex];
            currentIndex++;
            return nextDomino;
        }
        return -1; // No more dominoes to add
    }

    bool isLineCompleted()
    {
        return currentIndex == dominoes.size();
    }

    void displayLine()
    {
        for (int i = 0; i <= currentIndex; i++)
        {
            std::cout << dominoes[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    DominoLine line(1, {2, 3, 4, 5, 6, 7, 8, 9, 10});
    while (!line.isLineCompleted())
    {
        int nextDomino = line.getNextDomino();
        std::cout << "Next domino: " << nextDomino << std::endl;
        line.displayLine();
    }

    return 0;
}