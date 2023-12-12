#include <iostream>
#include <vector>

class DominoLine {
private:
    std::vector<int> dominoes;

public:
    DominoLine(int startingDomino, const std::vector<int>& restOfDominoes) {
        dominoes.push_back(startingDomino);
        dominoes.insert(dominoes.end(), restOfDominoes.begin(), restOfDominoes.end());
    }

    int getNextDominoRight() {
        if (dominoes.empty()) {
            return -1; // No more dominoes to add
        }

        int nextDomino = dominoes.back() + 1;
        dominoes.push_back(nextDomino);
        return nextDomino;
    }

    bool isLineCompleted() {
        // Check if all dominoes have been added
        return dominoes.empty();
    }

    void displayLine() {
        for (int domino : dominoes) {
            std::cout << domino << " ";
        }
        std::cout << std::endl;
    }
    
};

int main()
{
    // Example usage for the DominoLine class
    std::vector<int> restOfDominoes = {2, 3, 4, 5};

    // Initialize with starting domino (1) and the rest of the collection
    DominoLine dominoLine(1, restOfDominoes);

    // Build the line by adding dominoes to the right
    while (!dominoLine.isLineCompleted())
    {
        int nextDomino = dominoLine.getNextDominoRight();
        if (nextDomino != -1)
        {
            std::cout << "Added domino to the right: " << nextDomino << std::endl;
            dominoLine.displayLine(); // Display the line after each addition
        }
    }

    return 0;
}
