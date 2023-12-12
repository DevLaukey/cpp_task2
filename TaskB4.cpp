#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include "TaskB1.h" 
#include "TaskB2.h" 

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
    measure_time<B1::DominoLineB1>(filename1); // Use B1::DominoLineB1 instead of DominoLine
    measure_time<B1::DominoLineB1>(filename2);

    std::cout << std::endl
              << "Implementation B2 (linear search):" << std::endl;
    measure_time<B2::DominoLineB2>(filename1); // Use B2::DominoLineB2 instead of DominoLine
    measure_time<B2::DominoLineB2>(filename2);

    return 0;
}
