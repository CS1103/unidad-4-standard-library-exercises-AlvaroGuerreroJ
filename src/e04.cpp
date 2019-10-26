#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    std::string temp;
    while (std::cin >> temp && temp != "#")
    {
        if (std::next_permutation(temp.begin(), temp.end()))
        {
            std::cout << temp << std::endl;
        }
        else
        {
            std::cout << "No Successor" << std::endl;
        }
    }
}
