#include <iostream>
#include <unordered_map>
#include <vector>

class UnionFind {
private:
    std::unordered_map<int, int> parent;

public:
    // Function to add a set with a single element
    void makeSet(int symbol) {
        if (parent.find(symbol) == parent.end()) {
            parent[symbol] = symbol;
        }
    }

    // Function to find the representative of a set (with path compression)
    int find(int symbol) {
        if (parent[symbol] != symbol) {
            parent[symbol] = find(parent[symbol]);  // Path compression
        }
        return parent[symbol];
    }

    // Function to union two sets
    void unionSets(int symbol1, int symbol2) {
        int root1 = find(symbol1);
        int root2 = find(symbol2);

        if (root1 != root2) {
            parent[root1] = root2;
        }
    }

    // Getter for the parent map
    const std::unordered_map<int, int>& getParentMap() const {
        return parent;
    }
};

class TaskB2 {
private:
    UnionFind unionFind;

public:
    // Function to add a domino to the chain
    void addDomino(int symbol1, int symbol2) {
        unionFind.makeSet(symbol1);
        unionFind.makeSet(symbol2);
        unionFind.unionSets(symbol1, symbol2);
    }

    // Function to find a chain starting from a given domino
    std::vector<int> findChain(int startSymbol) {
        std::vector<int> chain;
        int root = unionFind.find(startSymbol);

        for (const auto& entry : unionFind.getParentMap()) {
            if (unionFind.find(entry.first) == root) {
                chain.push_back(entry.first);
            }
        }

        return chain;
    }
};

int main() {
    // Example usage
    TaskB2 dominoChainFinder;
    
    // Add dominoes to the chain
    dominoChainFinder.addDomino(1, 2);
    dominoChainFinder.addDomino(2, 3);
    dominoChainFinder.addDomino(3, 4);
    dominoChainFinder.addDomino(4, 5);

    // Find a chain starting from a specific domino
    std::vector<int> chain = dominoChainFinder.findChain(1);

    // Print the chain
    std::cout << "Domino Chain: ";
    for (int symbol : chain) {
        std::cout << symbol << " ";
    }

    return 0;
}
