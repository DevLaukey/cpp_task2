#include <iostream>
#include <vector>
#include <algorithm>

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
        // Sort the dominoes based on the second end only (more efficient)
        std::sort(dominoes.begin(), dominoes.end(), [](const auto &a, const auto &b)
                  { return a.second < b.second; });

        int n = dominoes.size();
        std::vector<int> dp(n, 1);

        // Dynamic programming to find the longest chain
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (dominoes[i].first > dominoes[j].second)
                {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }

        // Find the maximum length in the dp array
        int maxLength = *std::max_element(dp.begin(), dp.end());

        // Print the dominos in the longest chain
        std::cout << "Dominos in the longest chain: ";
        for (int i = n - 1; i >= 0; --i)
        {
            if (dp[i] == maxLength)
            {
                std::cout << "(" << dominoes[i].first << ", " << dominoes[i].second << ") ";
                --maxLength;
            }
        }
        std::cout << std::endl;

        return *std::max_element(dp.begin(), dp.end());
    }
};

int main()
{
    Dominoes dominoCollection;

    // Add dominoes to the collection
    dominoCollection.addDomino(1, 2);
    dominoCollection.addDomino(5, 3);
    dominoCollection.addDomino(4, 8);
    dominoCollection.addDomino(7, 6);
    dominoCollection.addDomino(9, 10);

    // Find and print the length of the longest chain
    int maxLength = dominoCollection.longestChain();
    std::cout << "Length of the longest chain: " << maxLength << std::endl;

    return 0;
}
