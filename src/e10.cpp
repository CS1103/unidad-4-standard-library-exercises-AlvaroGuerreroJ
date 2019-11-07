#include <iomanip>
#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, unsigned> trees_count;
    unsigned long total = 0;

    std::string temp;
    while (std::getline(std::cin, temp))
    {
        total++;
        trees_count[temp]++;
    }

    for (auto const& p : trees_count)
    {
        auto prec = std::cout.precision();
        std::cout << p.first << " " << std::fixed << std::setprecision(4)
                  << double(p.second) * 100 / total << std::setprecision(prec)
                  << std::endl;
    }
}
