#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

#define OUT

static const std::array<std::string, 20> c_arr_numbers{
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"};

constexpr std::optional<int> CheckNumber(std::string_view svString)
{
    for (int i = 0; i < static_cast<int>(c_arr_numbers.size()); i++)
        if (svString.starts_with(c_arr_numbers[i]))
            return i % 10;

    return std::nullopt;
}

int main()
{
    std::ifstream file("..\\Input.txt");
    if (!file.is_open())
    {
        std::cout << "Bestand niet open!" << std::endl;
        return 1;
    }

    int iSum = 0;

    std::string sLine;
    while (std::getline(OUT file, sLine))
    {
        const std::string_view svLine{sLine};

        int iFirstDigit = 0;
        for (int i = 0; i < static_cast<int>(sLine.size()); i++)
        {
            if (std::optional<int> digit = CheckNumber(svLine.substr(i)))
            {
                iFirstDigit = *digit;
                break;
            }
        }

        int iSecondDigit = 0;
        for (int i = static_cast<int>(sLine.size()) - 1; i >= 0; i--)
        {
            if (std::optional<int> digit = CheckNumber(svLine.substr(i)))
            {
                iSecondDigit = *digit;
                break;
            }
        }

        iSum += iFirstDigit * 10 + iSecondDigit;
    }

    std::cout << iSum << std::endl;
    return 0;
}
