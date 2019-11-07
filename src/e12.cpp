#include <iostream>
#include <iterator>
#include <set>

#include <prettyprint.hpp>

int main()
{
    unsigned n_days;
    while (std::cin >> n_days && n_days != 0)
    {
        std::multiset<unsigned> urn;

        unsigned total_cost = 0;

        for (unsigned i = 0; i < n_days; i++)
        {
            unsigned n_bills = 0;
            std::cin >> n_bills;

            for (unsigned j = 0; j < n_bills; j++)
            {
                unsigned temp;
                std::cin >> temp;
                urn.insert(temp);
            }

            total_cost += *urn.rbegin() - *urn.begin();
            urn.erase(urn.begin());
            urn.erase(std::prev(urn.end()));
        }

        std::cout << total_cost << std::endl;
    }
}
