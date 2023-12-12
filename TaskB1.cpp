#include <iostream>
#include <vector>

class DominoLine
{
private:
    std::vector<int> dominoes;
    int currentIndex;
    bool directionRight;

public:
    DominoLine(int startingDomino, const std::vector<int> &restOfDominoes, bool directionRight = true)
    {
        dominoes.push_back(startingDomino);
        dominoes.insert(dominoes.end(), restOfDominoes.begin(), restOfDominoes.end());
        currentIndex = 0;
        this->directionRight = directionRight;
    }

    int getNextDomino()
    {
        if (currentIndex < dominoes.size())
        {
            int nextDomino = dominoes[currentIndex];
            int matchingSide = directionRight ? nextDomino : dominoes[currentIndex - 1];
            int nextIndex = -1;

            for (int i = 0; i < dominoes.size(); ++i)
            {
                if (dominoes[i] == matchingSide)
                {
                    nextIndex = i;
                    break;
                }
            }

            if (nextIndex >= 0)
            {
                std::swap(dominoes[currentIndex], dominoes[nextIndex]);
                directionRight = !directionRight;
                currentIndex++;
                return dominoes[currentIndex - 1];
            }
        }
        return -1;
    }

    bool isLineCompleted()
    {
        return currentIndex == dominoes.size();
    }

    void displayLine()
    {
        for (int i = 0; i < dominoes.size(); ++i)
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
        if (nextDomino != -1)
        {
            std::cout << "Next domino: " << nextDomino << std::endl;
            line.displayLine();
        }
    }

    return 0;
}
