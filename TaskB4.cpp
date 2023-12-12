#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <unordered_map>

class DominoLine
{
private:
    std::vector<std::string> dominoes;
    int currentIndex;
    bool directionRight;
    std::unordered_map<std::string, int> nextDominoMap;

public:
    DominoLine(const std::string &filePath, bool directionRight = true)
        : currentIndex(0), directionRight(directionRight)
    {
        readDominoesFromFile(filePath);

        // Precompute the next domino map for faster lookups
        buildNextDominoMap();
    }

    std::string getNextDomino()
    {
        if (currentIndex < dominoes.size())
        {
            std::string nextDomino = dominoes[currentIndex];
            int nextDominoIndex = nextDominoMap[nextDomino];

            if (nextDominoIndex >= 0)
            {
                std::swap(dominoes[currentIndex], dominoes[nextDominoIndex]);
                directionRight = !directionRight;
                currentIndex++;
                return dominoes[currentIndex - 1];
            }
        }
        return "";
    }

    bool isLineCompleted() const
    {
        return currentIndex == dominoes.size();
    }

    void displayLine() const
    {
        for (const auto &domino : dominoes)
        {
            std::cout << domino << " ";
        }
        std::cout << std::endl;
    }

private:
    void readDominoesFromFile(const std::string &filePath)
    {
        std::ifstream inputFile(filePath);

        if (!inputFile)
        {
            std::cerr << "Error: Could not open file " << filePath << std::endl;
            exit(EXIT_FAILURE);
        }

        std::string domino;
        while (std::getline(inputFile, domino))
        {
            dominoes.push_back(domino);
        }

        inputFile.close();
    }

    void buildNextDominoMap()
    {
        for (int i = 0; i < dominoes.size(); ++i)
        {
            for (int j = i + 1; j < dominoes.size(); ++j)
            {
                if (dominoes[i].back() == dominoes[j].front())
                {
                    nextDominoMap[dominoes[i]] = j;
                    break;
                }
            }
        }
    }
};

template <typename T>
void measure_time(const std::string &filename)
{
    auto start = std::chrono::high_resolution_clock::now();
    T line(filename);
    while (!line.isLineCompleted())
    {
        line.getNextDomino();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time: " << duration.count() << " seconds" << std::endl;
}

int main()
{
    const std::string filename1 = "domino_data.txt";
    const std::string filename2 = "10K-input-uncoloured.txt"; // You can replace this with another file if needed

    std::cout << "Implementation B1 (precomputed map):" << std::endl;
    measure_time<DominoLine>(filename1);
    measure_time<DominoLine>(filename2);

    std::cout << std::endl
              << "Implementation B2 (linear search):" << std::endl;
    measure_time<DominoLine>(filename1);
    measure_time<DominoLine>(filename2);

    return 0;
}
