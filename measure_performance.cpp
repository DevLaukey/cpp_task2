// measure_performance.cpp
#include "domino_line.h"
#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <starting_domino_file> <rest_of_domino_file>" << std::endl;
        return 1;
    }

    // Measure Task B1
    auto startB1 = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<std::string, std::string>> dominoInputB1;
    std::string firstDomino, secondDomino;

    std::ifstream startingFile(argv[1]);
    if (!startingFile.is_open())
    {
        std::cerr << "Error opening the starting domino file." << std::endl;
        return 1;
    }

    while (startingFile >> firstDomino >> secondDomino)
    {
        dominoInputB1.push_back({firstDomino, secondDomino});
    }

    DominoLine lineB1(dominoInputB1);
    lineB1.displayLine();

    auto endB1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationB1 = endB1 - startB1;

    std::cout << "Task B1 Time: " << durationB1.count() << " seconds" << std::endl;

    // Measure Task B2
    auto startB2 = std::chrono::high_resolution_clock::now();

    DominoLine lineB2(argv[1], argv[2]);

    // Interleaved steps of moving to the right and left
    while (!lineB2.isLineCompleted())
    {
        std::string nextDominoToRight = lineB2.getNextDominoToRight();
        std::string nextDominoToLeft = lineB2.getNextDominoToLeft();

        if (!nextDominoToRight.empty())
        {
            std::cout << nextDominoToRight << " ";
        }

        if (!nextDominoToLeft.empty())
        {
            std::cout << nextDominoToLeft << " ";
        }
    }

    std::cout << std::endl;

    std::ifstream restOfFile(argv[2]);
    if (restOfFile.is_open())
    {
        std::string dominoValue;
        while (restOfFile >> dominoValue)
        {
            std::cout << dominoValue << " ";
        }
        restOfFile.close();
    }
    else
    {
        std::cerr << "Error opening the rest of the domino file." << std::endl;
        return 1;
    }

    std::cout << std::endl;

    auto endB2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationB2 = endB2 - startB2;

    std::cout << "Task B2 Time: " << durationB2.count() << " seconds" << std::endl;

    return 0;
}
