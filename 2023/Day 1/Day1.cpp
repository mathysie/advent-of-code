#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#define OUT

constexpr bool IsNumber(char c)
{
    return c >= '0' && c <= '9';
}

constexpr int ToInt(char c)
{
    return c - '0';
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
        int iFirstDigit = ToInt(*std::find_if(sLine.begin(), sLine.end(), &IsNumber));
        int iSecondDigit = ToInt(*std::find_if(sLine.rbegin(), sLine.rend(), &IsNumber));

        iSum += iFirstDigit * 10 + iSecondDigit;
    }

    std::cout << iSum << std::endl;
    return 0;
}
