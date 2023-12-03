#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <vector>
#include <range\v3\all.hpp>

#define OUT

constexpr bool IsNumber(char c)
{
    return c >= '0' && c <= '9';
}

constexpr bool IsSymbol(char c)
{
    return !IsNumber(c) && c != '.';
}

constexpr bool IsDot(char c)
{
    return c == '.';
}

constexpr int ToNumber(char c)
{
    return c - '0';
}

constexpr bool AboveOrBelowIsSymbol(const std::vector<std::vector<char>> &arr2_input, int iRow, int iCol)
{
    if (iRow == 0)
        return IsSymbol(arr2_input[iRow + 1][iCol]);
    else if (iRow == static_cast<int>(arr2_input.size()) - 1)
        return IsSymbol(arr2_input[iRow - 1][iCol]);
    else
        return IsSymbol(arr2_input[iRow + 1][iCol]) ||
               IsSymbol(arr2_input[iRow - 1][iCol]);
}

std::vector<std::vector<char>> ReadInput()
{
    std::ifstream file("..\\Input.txt");
    if (!file.is_open())
        throw std::invalid_argument("Bestand niet open!");

    std::vector<std::vector<char>> arr2_input;
    std::string sLine;
    while (std::getline(OUT file, sLine))
    {
        std::vector<char> &arr_inputRow = arr2_input.emplace_back();
        arr_inputRow = sLine | ranges::to_vector;
    }

    return arr2_input;
}

int GetSumOfLine(const std::vector<std::vector<char>> &arr2_input, int iRow)
{
    int iSum = 0;
    std::optional<int> foundNumber;
    auto addFoundNumber = [&iSum, &foundNumber]()
    {
        iSum += foundNumber.value();
        foundNumber = std::nullopt;
    };

    bool bNumberIsValid = false;
    int nCols = static_cast<int>(arr2_input.size());
    for (int iCol = 0; iCol < nCols; iCol++)
    {
        char currentChar = arr2_input[iRow][iCol];
        if (IsDot(currentChar))
        {
            if (foundNumber.has_value())
            {
                if (bNumberIsValid || AboveOrBelowIsSymbol(arr2_input, iRow, iCol))
                    addFoundNumber();
                else
                    foundNumber = std::nullopt;
            }

            bNumberIsValid = AboveOrBelowIsSymbol(arr2_input, iRow, iCol);
        }
        else if (IsSymbol(currentChar))
        {
            bNumberIsValid = true;
            if (foundNumber.has_value())
                addFoundNumber();
        }
        else if (IsNumber(currentChar))
        {
            bNumberIsValid = bNumberIsValid || AboveOrBelowIsSymbol(arr2_input, iRow, iCol);
            foundNumber = foundNumber.value_or(0) * 10 + ToNumber(currentChar);

            if (iCol == nCols - 1 && bNumberIsValid)
                addFoundNumber();
        }
        else
        {
            throw std::logic_error("Nummer is de laatste mogelijkheid.");
        }
    }

    return iSum;
}

int main()
{
    std::vector<std::vector<char>> arr2_input = ReadInput();

    int iSum = 0;
    for (int iRow = 0; iRow < static_cast<int>(arr2_input.size()); iRow++)
        iSum += GetSumOfLine(arr2_input, iRow);

    std::cout << iSum << std::endl;
    return 0;
}
