#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

class DominoLine
{
private:
    std::vector<std::pair<std::string, std::string>> dominoes;
    int currentIndex;
    bool directionRight;
    std::unordered_map<std::string, int> nextDominoMap;

public:
    DominoLine(const std::vector<std::pair<std::string, std::string>> &dominoPairs, bool directionRight = true)
        : dominoes(dominoPairs.size()), currentIndex(0), directionRight(directionRight)
    {
        std::copy(dominoPairs.begin(), dominoPairs.end(), dominoes.begin());
        buildNextDominoMap();
    }

    std::pair<std::string, std::string> getNextDomino()
    {
        if (currentIndex < dominoes.size())
        {
            std::string nextDomino = dominoes[currentIndex].second;
            int nextDominoIndex = nextDominoMap[nextDomino];
            if (nextDominoIndex >= 0)
            {
                std::swap(dominoes[currentIndex], dominoes[nextDominoIndex]);
                directionRight = !directionRight;
                currentIndex++;
                return dominoes[currentIndex - 1];
            }
        }
        return {"", ""}; // Return an empty pair if the line is completed
    }

    bool isLineCompleted() const
    {
        return currentIndex == dominoes.size();
    }

    void displayLine() const
    {
        for (const auto &dominoPair : dominoes)
        {
            std::cout << dominoPair.first << ":" << dominoPair.second << " ";
        }
        std::cout << std::endl;
    }

private:
    void buildNextDominoMap()
    {
        for (int i = 0; i < dominoes.size(); ++i)
        {
            nextDominoMap[dominoes[i].first] = i;
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <starting_domino_file> <rest_of_domino_file>" << std::endl;
        return 1;
    }

    std::ifstream startingFile(argv[1]);
    std::ifstream restOfFile(argv[2]);

    if (!startingFile.is_open() || !restOfFile.is_open())
    {
        std::cerr << "Error opening the files." << std::endl;
        return 1;
    }

    std::vector<std::pair<std::string, std::string>> dominoInput;
    std::string firstDomino, secondDomino;

    while (startingFile >> firstDomino >> secondDomino)
    {
        dominoInput.push_back({firstDomino, secondDomino});
    }

    while (restOfFile >> firstDomino >> secondDomino)
    {
        dominoInput.push_back({firstDomino, secondDomino});
    }

    DominoLine line(dominoInput);
    line.displayLine();

    return 0;
}

// to run ./TaskB1 domino_data.txt domino_data.txt