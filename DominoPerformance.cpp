#include <iostream>
#include <list>
#include <algorithm>
#include <utility>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // Define data file names
    const string dataFileNames[] = {"data1.txt", "data2.txt", "data3.txt"};

    // Create table header
    cout << "Number of Dominoes | Time (microseconds)" << endl;
    cout << "-------------------- | ---------------------" << endl;

    // Process each data file
    for (const string &fileName : dataFileNames)
    {
        // Read data from file
        list<Domino> dominoes;
        Domino startingDomino;

        // Your code to read data from file and populate dominoes and startingDomino

        // Measure execution time
        long long elapsedTime = 0;
        buildDominoLine(startingDomino, dominoes, elapsedTime);

        // Print results to table
        cout << dominoes.size() * 2 << " | " << elapsedTime << " microseconds" << endl;
    }

    // Create and plot graph (refer to libraries and plotting techniques)

    return 0;
}
