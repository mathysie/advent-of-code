#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include "Card.h"

#define OUT

std::vector<CCard> ReadInput()
{
    std::ifstream file("..\\Input.txt");
    if (!file.is_open())
        throw std::invalid_argument("Bestand niet open!");

    std::vector<CCard> arr_cards;

    std::string sLine;
    while (std::getline(OUT file, sLine))
    {
        std::size_t colonPos = sLine.find(':');
        std::size_t pipePos = sLine.find('|');

        std::string sLuckyNumbers = sLine.substr(colonPos + 1, pipePos - colonPos - 1);
        std::string sMyNumbers = sLine.substr(pipePos + 1);

        arr_cards.emplace_back(sLuckyNumbers, sMyNumbers);
    }

    return arr_cards;
}

void Part1(const std::vector<CCard> &arr_cards)
{
    int iPart1Sum = 0;

    for (const CCard &card : arr_cards)
    {
        int nMatches = card.CountMatches();
        if (nMatches > 0)
            iPart1Sum += std::pow(2, nMatches - 1);
    }

    std::cout << "Deel 1: " << iPart1Sum << std::endl;
}

void Part2(const std::vector<CCard> &arr_cards)
{
    std::vector<int> arr_cardCounts(arr_cards.size(), 1);
    for (auto [index, card] : arr_cards | ranges::views::enumerate)
    {
        int iCurrentCard = static_cast<int>(index);
        int nMatches = card.CountMatches();
        for (int iCard = iCurrentCard + 1; iCard <= std::min(iCurrentCard + nMatches, static_cast<int>(arr_cardCounts.size()) - 1); ++iCard)
            arr_cardCounts[iCard] += arr_cardCounts[iCurrentCard];
    }

    std::cout << "Deel 2: " << ranges::accumulate(arr_cardCounts, 0) << std::endl;
}

int main()
{
    std::vector<CCard> arr_cards = ReadInput();
    Part1(arr_cards);
    Part2(arr_cards);

    return 0;
}
