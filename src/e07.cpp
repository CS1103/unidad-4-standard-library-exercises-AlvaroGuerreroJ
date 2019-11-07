#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <prettyprint.hpp>

int main()
{
    std::string temp;
    std::getline(std::cin, temp);
    std::istringstream numbers_to_read(temp);
    std::vector<unsigned> numbers;
    std::copy(std::istream_iterator<unsigned>(numbers_to_read),
              std::istream_iterator<unsigned>(), std::back_inserter(numbers));

    // Do bubble sort and count swaps
    unsigned swaps = 0;
    for (std::vector<unsigned>::size_type i = numbers.size() - 1; i != 0; i--)
    {
        bool swapped = false;
        for (std::vector<unsigned>::size_type j = 0; j < i; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                std::swap(numbers[j], numbers[j + 1]);
                swapped = true;
                swaps++;
            }
        }
        if (!swapped)
        {
            break;
        }
    }

    std::cout << "Optimal train swapping takes " << swaps << " swaps." << std::endl;
}
