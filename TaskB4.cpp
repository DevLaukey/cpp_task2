#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

class Dominoes
{
private:
    std::vector<std::pair<int, int>> dominoes;

public:
    // Add a domino to the collection
    void addDomino(int end1, int end2)
    {
        dominoes.push_back({end1, end2});
    }

    // Find the length of the longest chain of dominoes
    int longestChain()
    {
        auto start_time = std::chrono::high_resolution_clock::now();

        // Implementation code for sorting and finding the longest chain

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - start_time;

        std::cout << "Time elapsed: " << elapsed_seconds.count() << " seconds" << std::endl;

        return maxLength;
    }
};

int main()
{
    Dominoes dominoCollection;

    // Add a large number of dominoes to the collection (for testing scalability)
    const int totalDominoes = 10000;
    for (int i = 1; i <= totalDominoes; ++i)
    {
        dominoCollection.addDomino(i, i + 1);
    }

    // Measure time for Task B1
    std::cout << "Task B1:" << std::endl;
    int maxLengthB1 = dominoCollection.longestChain();
    std::cout << "Length of the longest chain: " << maxLengthB1 << std::endl;

    // Clear domino collection
    dominoCollection = Dominoes();

    // Add dominoes again for Task B2
    for (int i = 1; i <= totalDominoes; ++i)
    {
        dominoCollection.addDomino(i, i + 1);
    }

    // Measure time for Task B2
    std::cout << "Task B2:" << std::endl;
    int maxLengthB2 = dominoCollection.longestChain();
    std::cout << "Length of the longest chain: " << maxLengthB2 << std::endl;

    return 0;
}
