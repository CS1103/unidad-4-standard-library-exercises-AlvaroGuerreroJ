#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <list>

#include <prettyprint.hpp>

unsigned disorder_score(std::string s);

int main()
{
    std::string temp;
    std::getline(std::cin, temp);
    using entry = std::pair<std::string, unsigned>;
    std::list<entry> dna_disorder;
    while (std::getline(std::cin, temp))
    {
        entry temp_entry(temp, disorder_score(temp));
        auto insert_position = std::lower_bound(dna_disorder.begin(), dna_disorder.end(), temp_entry,
                                                [](entry const& l, entry const& r)->bool {
                                                    return l.second < r.second;
                                                });
        dna_disorder.insert(insert_position, temp_entry);
    }

    for (auto const p : dna_disorder)
    {
        std::cout << p.first << std::endl;
    }
}

unsigned disorder_score(std::string s)
{
    unsigned ret = 0;
    for (auto it0 = s.begin(); it0 != s.end(); it0++)
    {
        for (auto it1 = std::next(it0); it1 != s.end(); it1++)
        {
            if (*it0 > *it1)
            {
                ret++;
            }
        }
    }
    return ret;
}
