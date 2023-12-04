#include "Card.h"
#include <range/v3/all.hpp>

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

CCard::CCard(std::string_view sLuckyNumbers, std::string_view sMyNumbers)
{
    m_arr_luckyNumbers = GetNumbersView(sLuckyNumbers) | ranges::to<std::set<int>>;
    m_arr_myNumbers = GetNumbersView(sMyNumbers) | ranges::to_vector;
}

int CCard::CountMatches() const
{
    return ranges::count_if(m_arr_myNumbers,
                            [this](int iNumber)
                            { return m_arr_luckyNumbers.contains(iNumber); });
}