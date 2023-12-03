#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <format>

#define OUT

bool IsColorValid(std::string_view sString, std::string_view svColor, int iMax)
{
    std::smatch sm;
    std::regex regex(std::format(R"((\d+) {})", svColor));

    for (std::string sSearch{sString}; regex_search(sSearch, sm, regex);)
    {
        if (stoi(sm[1]) > iMax)
            return false;

        sSearch = sm.suffix();
    }

    return true;
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
        bool bValidGame = true;
        std::size_t iColonPos = sLine.find(':');
        std::string sGames = sLine.substr(iColonPos + 1);

        if (!IsColorValid(sGames, "blue", 14))
            continue;

        if (!IsColorValid(sGames, "red", 12))
            continue;

        if (!IsColorValid(sGames, "green", 13))
            continue;

        iSum += std::stoi(sLine.substr(5, iColonPos));
    }

    std::cout << iSum << std::endl;
    return 0;
}
