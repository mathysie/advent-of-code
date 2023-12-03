#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <format>

#define OUT

std::pair<bool, int> IsColorValidAndGetMax(std::string_view sString, std::string_view svColor, int iMaxForValid)
{
    bool bValid = true;
    int iMaxFound = 0;

    std::smatch sm;
    std::regex regex(std::format(R"((\d+) {})", svColor));
    for (std::string sSearch{sString}; regex_search(sSearch, sm, regex);)
    {
        int nBalls = std::stoi(sm[1]);
        iMaxFound = std::max(nBalls, iMaxFound);
        if (nBalls > iMaxForValid)
            bValid = false;

        sSearch = sm.suffix();
    }

    return {bValid, iMaxFound};
}

int main()
{
    std::ifstream file("..\\Input.txt");
    if (!file.is_open())
    {
        std::cout << "Bestand niet open!" << std::endl;
        return 1;
    }

    int iPart1Sum = 0;
    int iPart2Sum = 0;

    std::string sLine;
    while (std::getline(OUT file, sLine))
    {
        std::size_t iColonPos = sLine.find(':');
        std::string sGames = sLine.substr(iColonPos + 1);

        bool bValidGame = true;
        int iProduct = 1;

        auto checkColor = [&sGames, &bValidGame, &iProduct](std::string_view sColor, int iMax)
        {
            auto [bValid, nMaxBalls] = IsColorValidAndGetMax(sGames, sColor, iMax);
            bValidGame = bValidGame && bValid;
            iProduct *= nMaxBalls;
        };

        checkColor("blue", 14);
        checkColor("red", 12);
        checkColor("green", 13);

        if (bValidGame)
            iPart1Sum += std::stoi(sLine.substr(5, iColonPos));

        iPart2Sum += iProduct;
    }

    std::cout << "Deel 1: " << iPart1Sum << std::endl;
    std::cout << "Deel 2: " << iPart2Sum << std::endl;

    return 0;
}
