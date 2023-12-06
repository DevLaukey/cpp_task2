#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

class DominoChainFinder
{
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

public:
    void addDomino(int symbol1, int symbol2)
    {
        adjacencyList[symbol1].push_back(symbol2);
        adjacencyList[symbol2].push_back(symbol1);
    }

    std::vector<int> findChain(int startSymbol)
    {
        std::vector<int> chain;
        std::unordered_map<int, bool> visited;

        dfs(startSymbol, chain, visited);

        return chain;
    }

private:
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

// Function to measure the time usage for finding a chain
void measureFindChainTime(const std::vector<int> &dataset)
{
    DominoChainFinder dominoChainFinder;

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < dataset.size(); i += 2)
    {
        dominoChainFinder.addDomino(dataset[i], dataset[i + 1]);
    }

    // Choose a specific domino as the starting point
    std::vector<int> chain = dominoChainFinder.findChain(dataset[0]);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Dataset Size: " << dataset.size() / 2 << ", Time: " << duration.count() << " microseconds\n";
}

int main()
{
    // Example dataset sizes
    std::vector<int> dataset1 = {1, 2, 2, 3, 3, 4, 4, 5};
    std::vector<int> dataset2 = {1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9};

    // Measure the time for finding a chain with different dataset sizes
    measureFindChainTime(dataset1);
    measureFindChainTime(dataset2);

    return 0;
}
