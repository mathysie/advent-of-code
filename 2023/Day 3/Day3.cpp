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

void Part1(const std::vector<std::vector<char>> &arr2_input)
{
    int iTotalSum = 0;
    for (int iRow = 0; iRow < static_cast<int>(arr2_input.size()); iRow++)
    {
        int iRowSum = 0;
        std::optional<int> foundNumber;
        auto addFoundNumber = [&iRowSum, &foundNumber]()
        {
            iRowSum += foundNumber.value();
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

        iTotalSum += iRowSum;
    }

    std::cout << "Deel 1: " << iTotalSum << std::endl;
}

std::vector<std::pair<int, int>> GetNumberCoordinatesAroundStar(const std::vector<std::vector<char>> &arr2_input, int iRow, int iCol)
{
    int nCols = static_cast<int>(arr2_input[iRow].size());

    std::vector<std::pair<int, int>> arr_numbers;
    if (iCol > 0 && IsNumber(arr2_input[iRow][iCol - 1]))
        arr_numbers.emplace_back(iRow, iCol - 1);

    if (iCol < nCols && IsNumber(arr2_input[iRow][iCol + 1]))
        arr_numbers.emplace_back(iRow, iCol + 1);

    auto findDistinctNumbersInRow = [&arr2_input, &arr_numbers, iCol, nCols](int iLocalRow)
    {
        bool bNumberInRow = false;
        if (iCol > 0 && IsNumber(arr2_input[iLocalRow][iCol - 1]))
        {
            bNumberInRow = true;
            arr_numbers.emplace_back(iLocalRow, iCol - 1);
        }
        if (IsNumber(arr2_input[iLocalRow][iCol]))
        {
            if (!bNumberInRow)
            {
                arr_numbers.emplace_back(iLocalRow, iCol);
                bNumberInRow = true;
            }
        }
        else
        {
            bNumberInRow = false;
        }

        if (iCol < nCols - 1 && IsNumber(arr2_input[iLocalRow][iCol + 1]) &&
            !bNumberInRow)
            arr_numbers.emplace_back(iLocalRow, iCol + 1);
    };

    if (iRow > 0)
        findDistinctNumbersInRow(iRow - 1);
    if (iRow < static_cast<int>(arr2_input.size()) - 1)
        findDistinctNumbersInRow(iRow + 1);

    return arr_numbers;
}

int GetGearRatio(const std::vector<std::vector<char>> &arr2_input, const std::vector<std::pair<int, int>> &arr_coordinates)
{
    if (arr_coordinates.size() != 2)
        throw std::logic_error("Aantal coordinaten moet 2 zijn!");

    auto GetNumber = [&arr2_input, &arr_coordinates](int iIndex)
    {
        auto [iRow, iCol] = arr_coordinates[iIndex];

        // Zoek startpositie getal
        while (iCol > 0 && IsNumber(arr2_input[iRow][iCol - 1]))
            iCol--;

        int iNumber = 0;
        while (iCol < static_cast<int>(arr2_input[iRow].size()) &&
               IsNumber(arr2_input[iRow][iCol]))
        {
            iNumber = iNumber * 10 + ToNumber(arr2_input[iRow][iCol]);
            iCol++;
        }

        return iNumber;
    };

    int iFirstNumber = GetNumber(0);
    int iSecondNumber = GetNumber(1);

    return iFirstNumber * iSecondNumber;
}

void Part2(const std::vector<std::vector<char>> &arr2_input)
{
    int iTotalSum = 0;

    for (int iRow = 0; iRow < static_cast<int>(arr2_input.size()); iRow++)
    {
        int nCols = static_cast<int>(arr2_input.size());
        for (int iCol = 0; iCol < nCols; iCol++)
        {
            char currentChar = arr2_input[iRow][iCol];
            if (currentChar == '*')
            {
                auto arr_numbersAroundStar = GetNumberCoordinatesAroundStar(arr2_input, iRow, iCol);
                if (arr_numbersAroundStar.size() == 2)
                    iTotalSum += GetGearRatio(arr2_input, arr_numbersAroundStar);
            }
        }
    }

    std::cout << "Deel 2: " << iTotalSum << std::endl;
}

int main()
{
    std::vector<std::vector<char>> arr2_input = ReadInput();

    Part1(arr2_input);
    Part2(arr2_input);

    return 0;
}
