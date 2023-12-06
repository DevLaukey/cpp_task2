#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

class UnionFind
{
private:
    std::unordered_map<int, int> parent;

public:
    void makeSet(int symbol)
    {
        if (parent.find(symbol) == parent.end())
        {
            parent[symbol] = symbol;
        }
    }

    int find(int symbol)
    {
        if (parent[symbol] != symbol)
        {
            parent[symbol] = find(parent[symbol]); // Path compression
        }
        return parent[symbol];
    }

    void unionSets(int symbol1, int symbol2)
    {
        int root1 = find(symbol1);
        int root2 = find(symbol2);

        if (root1 != root2)
        {
            parent[root1] = root2;
        }
    }

    const std::unordered_map<int, int> &getParentMap() const
    {
        return parent;
    }
};

// Function to measure the time usage for finding a chain
void measureFindChainTime(const std::vector<int> &dataset)
{
    UnionFind unionFind;

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < dataset.size(); i += 2)
    {
        unionFind.makeSet(dataset[i]);
        unionFind.makeSet(dataset[i + 1]);
        unionFind.unionSets(dataset[i], dataset[i + 1]);
    }

    // Choose a specific domino as the starting point
    std::vector<int> chain;
    for (const auto &entry : unionFind.getParentMap())
    {
        chain.push_back(entry.second);
    }
    
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
