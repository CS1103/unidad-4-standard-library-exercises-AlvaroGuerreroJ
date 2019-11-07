#include <iostream>
#include <vector>

int main()
{
    unsigned sequence_size;
    while (std::cin >> sequence_size && sequence_size != 0)
    {
        std::vector<unsigned> sequence;
        for (unsigned i = 0; i < sequence_size; i++)
        {
            unsigned temp;
            std::cin >> temp;
            sequence.push_back(temp);
        }

        unsigned swaps = 0;
        for (auto it0 = sequence.cbegin(); it0 != sequence.cend(); it0++)
        {
            for (auto it1 = std::next(it0); it1 != sequence.cend(); it1++)
            {
                if (*it0 > *it1)
                {
                    swaps++;
                }
            }
        }
        std::cout << swaps << std::endl;
    }
}
