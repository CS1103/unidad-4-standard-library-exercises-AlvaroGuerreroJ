#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <prettyprint.hpp>

std::vector<std::string> split_whitespace(std::string s);

int main()
{
    // First element of the pair are the number of problems solved, the second
    // is the time penalty.
    std::map<unsigned, std::pair<unsigned, unsigned>> scores;

    std::string temp;
    while (std::getline(std::cin, temp))
    {
        auto parts = split_whitespace(temp);
        unsigned participant = std::stoul(parts[0]);
        auto& participant_entry = scores[participant];
        if (parts[3] == "I")
        {
            participant_entry.second += 20;
        }
        else if (parts[3] == "C")
        {
            participant_entry.second += std::stoul(parts[2]);
            participant_entry.first++;
        }
    }

    using standings_element = std::pair<unsigned, std::pair<unsigned, unsigned>>;
    std::vector<standings_element> standings(scores.begin(), scores.end());
    std::sort(standings.begin(), standings.end(),
              [](standings_element const& l, standings_element const& r)
              {
                  if (l.second.first != r.second.first)
                  {
                      return l.second.first > r.second.first;
                  }
                  else if (l.second.second != r.second.second)
                  {
                      return l.second.second < r.second.second;
                  }
                  else
                  {
                      return l.first < r.first;
                  }
              });

    for (auto const& e : standings)
    {
        std::cout << e.first << " " << e.second.first << " " << e.second.second
                  << std::endl;
    }
}

std::vector<std::string> split_whitespace(std::string s)
{
    std::vector<std::string> ret;

    auto it = s.begin();
    while (true)
    {
        it = std::find_if(it, s.end(),
                          [](char c)
                          {
                             return !std::isspace(c);
                          });
        if (it == s.end())
        {
            break;
        }
        auto first_space = std::find_if(it, s.end(),
                                        [](char c) {
                                            return std::isspace(c);
                                        });
        ret.emplace_back(it, first_space);
        it = first_space;
    }

    return ret;
}
