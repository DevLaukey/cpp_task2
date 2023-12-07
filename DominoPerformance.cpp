#include <iostream>
#include <list>
#include <algorithm>
#include <utility>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

typedef pair<char, int> Domino;

void buildDominoLine(const Domino &startingDomino, const list<Domino> &dominoes, long long &elapsedTime)
{
    // Start time measurement
    auto startTime = chrono::steady_clock::now();

    // Your implementation of buildDominoLine
    list<Domino> listA(dominoes);
    list<Domino> listP;
    listP.emplace_back(startingDomino.second, 0);

    char currentRedSymbol = startingDomino.first; // New variable to track the current red symbol

    for (int distance = 1; distance < listA.size() + 1; distance *= 2)
    {
        list<Domino> listB(listA);
        list<Domino> listC;

        listA.sort([](const Domino &a, const Domino &b)
                   { return a.second < b.second; });
        listB.sort([](const Domino &a, const Domino &b)
                   { return a.first < b.first; });
        listP.sort([](const Domino &a, const Domino &b)
                   { return a.first < b.first; });

        auto itA = listA.begin();
        auto itB = listB.begin();
        auto itP = listP.begin();

        while (itB != listB.end())
        {
            if (itB->first == itA->second)
            {
                listC.emplace_back(*itA);
                itA++;
                itB++;
            }
            else if (itB->first == itP->first)
            {
                listP.emplace_front(itB->second, itP->second + distance);
                itA++;
                itP++;
            }
            else if (itB->first > itP->first)
            {
                itP++;
            }
            else if (itB->first > itA->second)
            {
                itA++;
            }

            if (itA == listA.end())
            {
                break;
            }
            else if (itP == listP.end())
            {
                break;
            }
        }

        listA = listC;
    }

    listP.sort([](const Domino &a, const Domino &b)
               { return a.second < b.second; });

    // Build the line of dominoes
    cout << "Domino Line: ";
    for (auto domino : listP)
    {
        cout << "(" << currentRedSymbol << "," << domino.first << ")"
             << " ";
        currentRedSymbol = domino.first;
    }
    cout << endl;

    // End time measurement
    auto endTime = chrono::steady_clock::now();

    // Calculate and store elapsed time
    elapsedTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
}

void readDominoFile(const string &fileName, list<Domino> &dominoes, Domino &startingDomino)
{
    ifstream inputFile(fileName);

    if (!inputFile)
    {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    if (getline(inputFile, line))
    {
        istringstream iss(line);
        char redSymbol, blueSymbol;
        if (iss >> redSymbol >> blueSymbol)
        {
            startingDomino = make_pair(redSymbol, blueSymbol);
        }
        else
        {
            cerr << "Invalid format in the first line of the file: " << fileName << endl;
            return;
        }
    }

    dominoes.clear(); // Clear the list in case there is data already

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        char firstSymbol, secondSymbol;
        if (iss >> firstSymbol >> secondSymbol)
        {
            dominoes.emplace_back(firstSymbol, secondSymbol);
        }
        else
        {
            cerr << "Invalid format in line: " << line << " in the file: " << fileName << endl;
            return;
        }
    }
}

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
        // Read data from file and populate dominoes and startingDomino
        list<Domino> dominoes;
        Domino startingDomino;

        readDominoFile("sample_domino_file.txt", dominoes, startingDomino);

        long long elapsedTime = 0;
        buildDominoLine(startingDomino, dominoes, elapsedTime);

        // Print the results
        cout << "Number of Dominoes | Time (microseconds)" << endl;
        cout << "-------------------- | ---------------------" << endl;
        cout << dominoes.size() * 2 << " | " << elapsedTime << " microseconds" << endl;

        return 0;
    }


    return 0;
}
