#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class DominoChainFinder
{
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

public:
    // Function to add a domino to the chain
    void addDomino(int symbol1, int symbol2)
    {
        adjacencyList[symbol1].push_back(symbol2);
        adjacencyList[symbol2].push_back(symbol1);
    }

    // Function to find a chain starting from a given domino
    std::vector<int> findChain(int startSymbol)
    {
        std::vector<int> chain;
        std::unordered_map<int, bool> visited;

        dfs(startSymbol, chain, visited);

        return chain;
    }

private:
    // Depth-First Search to find a chain
    void dfs(int currentSymbol, std::vector<int> &chain, std::unordered_map<int, bool> &visited)
    {
        visited[currentSymbol] = true;
        chain.push_back(currentSymbol);

        for (int neighbor : adjacencyList[currentSymbol])
        {
            if (!visited[neighbor])
            {
                dfs(neighbor, chain, visited);
            }
        }
    }
};

int main()
{
    // Example usage
    DominoChainFinder dominoChainFinder;

    // Add dominoes to the chain
    dominoChainFinder.addDomino(1, 2);
    dominoChainFinder.addDomino(2, 3);
    dominoChainFinder.addDomino(3, 4);
    dominoChainFinder.addDomino(4, 5);

    // Find a chain starting from a specific domino
    std::vector<int> chain = dominoChainFinder.findChain(1);

    // Print the chain
    std::cout << "Domino Chain: ";
    for (int symbol : chain)
    {
        std::cout << symbol << " ";
    }

    return 0;
}
