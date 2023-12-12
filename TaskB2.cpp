#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

class DominoLine
{
private:
    std::vector<std::string> dominoes;
    bool lineCompleted;

public:
    // Constructor with file paths
    DominoLine(const std::string &startingFilePath, const std::string &restOfDominoFilePath)
    {
        // Read starting domino from the file
        std::ifstream startingFile(startingFilePath);
        if (!startingFile.is_open())
        {
            std::cerr << "Error opening the starting domino file." << std::endl;
            exit(1);
        }

        std::string startingDomino;
        startingFile >> startingDomino;
        dominoes.push_back(startingDomino);
        startingFile.close();

        // Read rest of the dominoes from the file
        std::ifstream restOfFile(restOfDominoFilePath);
        if (!restOfFile.is_open())
        {
            std::cerr << "Error opening the rest of the domino file." << std::endl;
            exit(1);
        }

        std::string dominoValue;
        while (restOfFile >> dominoValue)
        {
            dominoes.push_back(dominoValue);
        }
        restOfFile.close();

        lineCompleted = false;
    }

    // Member function to determine the next domino to be placed in the line to the right
    std::string getNextDominoToRight()
    {
        if (!lineCompleted)
        {
            std::string matchingSide = dominoes.back(); // The matching side is the rightmost side of the current line
            auto it = std::find(dominoes.begin(), dominoes.end() - 1, matchingSide);

            if (it != dominoes.end() - 1)
            {
                // Found a domino with a matching side, add it to the line
                std::string nextDomino = *(it + 1);
                dominoes.push_back(nextDomino);
                return nextDomino;
            }
            else
            {
                // No more matching dominoes, mark the line as completed
                lineCompleted = true;
            }
        }

        return ""; // Return an empty string if the line is completed or there are no more matching dominoes
    }

    // Member function to determine the next domino to be placed in the line to the left
    std::string getNextDominoToLeft()
    {
        if (!lineCompleted && dominoes.size() > 1)
        {
            std::string matchingSide = dominoes.front(); // The matching side is the leftmost side of the current line
            auto it = std::find(dominoes.begin() + 1, dominoes.end(), matchingSide);

            if (it != dominoes.end())
            {
                // Found a domino with a matching side, add it to the line
                std::string nextDomino = *(it - 1);
                dominoes.insert(dominoes.begin(), nextDomino);
                return nextDomino;
            }
            else
            {
                // No more matching dominoes, mark the line as completed
                lineCompleted = true;
            }
        }

        return ""; // Return an empty string if the line is completed or there are no more matching dominoes
    }

    // Member function to determine if the line is completed
    bool isLineCompleted() const
    {
        return lineCompleted;
    }

    // Member function to display the current line of dominoes
    void displayLine() const
    {
        for (const std::string &domino : dominoes)
        {
            std::cout << domino << " ";
        }
        std::cout << std::endl;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <starting_domino_file> <rest_of_domino_file>" << std::endl;
        return 1;
    }

    

    DominoLine line(argv[1], argv[2]);

    // Interleaved steps of moving to the right and left
    while (!line.isLineCompleted())
    {
        std::string nextDominoToRight = line.getNextDominoToRight();
        std::string nextDominoToLeft = line.getNextDominoToLeft();

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

    return 0;
}
