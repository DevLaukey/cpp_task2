#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

// Define the Domino structure
struct Domino
{
    char symbol1;
    char symbol2;

    // Constructor to initialize the domino with symbols
    Domino(char s1, char s2) : symbol1(s1), symbol2(s2) {}
};

// Define the SymbolPair structure for List C
struct SymbolPair
{
    char symbol1;
    char symbol2;

    // Constructor to initialize the symbol pair
    SymbolPair(char s1, char s2) : symbol1(s1), symbol2(s2) {}
};

// Function to print a list of dominos
void printDominoList(const std::vector<Domino> &list, const std::string &listName)
{
    std::cout << listName << ":" << std::endl;
    for (const auto &domino : list)
    {
        std::cout << domino.symbol1 << " - " << domino.symbol2 << std::endl;
    }
}

// Function to print a list of symbol pairs
void printSymbolPairList(const std::vector<std::pair<char, int>> &list, const std::string &listName)
{
    std::cout << listName << ":" << std::endl;
    for (const auto &pair : list)
    {
        std::cout << pair.first << " - Position " << pair.second << std::endl;
    }
}

// Function to load domino data from a file
std::vector<Domino> loadDominoData(const std::string &filename)
{
    std::vector<Domino> dominoList;
    std::ifstream inputFile(filename);

    if (inputFile.is_open())
    {
        std::string line;
        while (std::getline(inputFile, line))
        {
            // Assuming the format is "symbol1:symbol2"
            char symbol1 = line[0];
            char symbol2 = line[2];
            dominoList.push_back(Domino(symbol1, symbol2));
        }
        inputFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }

    return dominoList;
}

int main()
{
    // Load domino data from the input file
    std::vector<Domino> listA = loadDominoData("domino_data.txt");

    // Create a list to record the position of each red symbol (List P)
    std::vector<std::pair<char, int>> listP;
    char startingRedSymbol = 'A';
    listP.push_back(std::make_pair(startingRedSymbol, 0));

    // Loop to gradually compute the position numbers of every red symbol
    int distance = 1;
    while (distance < listA.size())
    {
        std::cout << "Processing distance: " << distance << std::endl;

        // Make a copy of List A (List B)
        std::vector<Domino> listB = listA;

        // Create an empty list of symbol pairs (List C)
        std::vector<SymbolPair> listC;

        // Sort List A based on the second symbol, and sort List B based on the first symbol
        std::sort(listA.begin(), listA.end(), [](const Domino &a, const Domino &b)
                  { return a.symbol2 < b.symbol2; });
        std::sort(listB.begin(), listB.end(), [](const Domino &a, const Domino &b)
                  { return a.symbol1 < b.symbol1; });

        // Sort List P based on the symbol
        std::sort(listP.begin(), listP.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b)
                  { return a.first < b.first; });

        // Use iterators to advance through Lists A, B, and P
        auto iterA = listA.begin();
        auto iterB = listB.begin();
        auto iterP = listP.begin();

        // Loop to gradually compute the position numbers of every red symbol
        int distance = 1;
        int maxIterations = 5; 
        int iterationCount = 0;

        while (distance < listA.size() && iterationCount < maxIterations)
        {
            std::cout << "Processing distance: " << distance << std::endl;

            // Rest of the code remains unchanged

            // Display the current state of Lists A and P for debugging
            printDominoList(listA, "List A");
            printSymbolPairList(listP, "List P");

            // Double the distance for the next iteration
            distance *= 2;

            // Increment iteration count
            iterationCount++;

            // Add debug statements to identify where it might be getting stuck
            std::cout << "After doubling distance. Iteration count: " << iterationCount << std::endl;
            std::cout << "List A size: " << listA.size() << std::endl;
        }

        if (iterationCount >= maxIterations)
        {
            std::cerr << "Error: Exceeded maximum iterations. Exiting." << std::endl;
            break;
        }
    }

    // Sort List P based on the position numbers
    std::sort(listP.begin(), listP.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b)
              { return a.second < b.second; });

    // Display the final contents of Lists A and P
    printDominoList(listA, "List A");
    printSymbolPairList(listP, "Sorted List P");

    return 0;
}
