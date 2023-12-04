#pragma once
#include <set>
#include <vector>
#include <string>

class CCard
{
public:
    CCard(std::string_view sLuckyNumbers, std::string_view sMyNumbers);

    int CountMatches() const;

private:
    std::set<int> m_arr_luckyNumbers;
    std::vector<int> m_arr_myNumbers;
};
