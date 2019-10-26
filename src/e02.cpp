/**
 * From now on we are gonna ignore the fact that there could be more than one
 * test case, that's because it's annoying and there is no challenge in
 * wrapping the entire main body in a loop (as done in e01.cpp).
 */

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include <prettyprint.hpp>

int main()
{
    size_t paid_characters;
    std::cin >> paid_characters;
    std::cin.ignore();

    std::map<char, unsigned> characters_pay;
    for (; paid_characters > 0; paid_characters--)
    {
        char temp_char;
        std::cin >> temp_char;
        unsigned temp_unsigned;
        std::cin >> temp_unsigned;
        characters_pay[temp_char] = temp_unsigned;
    }
    std::cin.ignore();

    std::cin.ignore();
    std::string temp;
    unsigned pay = 0;
    while (std::cin >> temp)
    {
        for (char const& c : temp)
        {
            auto it = characters_pay.find(c);
            if (it != characters_pay.end())
            {
                pay += it->second;
            }
        }
    }

    auto old_width = std::cout.width();
    auto old_fillch = std::cout.fill();
    std::cout << pay / 100 << "." << std::setw(2) << std::setfill('0')
              << pay % 100 << std::setfill(old_fillch) << std::setw(old_width)
              << "$" << std::endl;
}
