#ifndef B2_H
#define B2_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

namespace B2
{

    class DominoLineB2
    {
    private:
        std::vector<std::string> dominoes;
        bool lineCompleted;

    public:
        DominoLineB2(const std::string &startingFilePath, const std::string &restOfDominoFilePath);

        std::string getNextDominoToRight();

        std::string getNextDominoToLeft();

        bool isLineCompleted() const;

        void displayLine() const;

    private:
        void readDominoesFromFile(const std::string &filePath);
    };

} // namespace B2

#endif // B2_H
