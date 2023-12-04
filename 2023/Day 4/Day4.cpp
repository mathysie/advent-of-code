#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <set>
#include <cmath>

#define OUT

int ToInt(ranges::any_view<char> arr_numChars)
{
    return ranges::accumulate(
        arr_numChars, 0.,
        [](int iRhs, int iLhs)
        { return iRhs * 10 + iLhs; },
        [](char c)
        { return c - '0'; });
}

ranges::any_view<int> GetNumbersView(std::string_view sNumbers)
{
    return sNumbers |
           ranges::views::split(' ') |
           ranges::views::remove_if([](ranges::any_view<char, ranges::category::forward> view)
                                    { return view.empty(); }) |
           ranges::views::transform(ToInt);
}

int main()
{
    std::ifstream file("..\\Input.txt");
    if (!file.is_open())
        throw std::invalid_argument("Bestand niet open!");

    int iSum = 0;

    std::string sLine;
    while (std::getline(OUT file, sLine))
    {
        std::size_t colonPos = sLine.find(':');
        std::size_t pipePos = sLine.find('|');

        std::string sLuckyNumbers = sLine.substr(colonPos + 1, pipePos - colonPos - 1);
        std::string sMyNumbers = sLine.substr(pipePos + 1);

        std::set<int> arr_luckyNumbers = GetNumbersView(sLuckyNumbers) |
                                         ranges::to<std::set<int>>;

        int nMatches = ranges::count_if(GetNumbersView(sMyNumbers),
                                        [&arr_luckyNumbers](int iNumber)
                                        { return arr_luckyNumbers.contains(iNumber); });

        if (nMatches > 0)
            iSum += std::pow(2, nMatches - 1);
    }

    std::cout << "Deel 1: " << iSum << std::endl;

    return 0;
}
