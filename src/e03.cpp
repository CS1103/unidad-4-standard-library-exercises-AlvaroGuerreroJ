#include <bitset>
#include <iostream>
#include <vector>

#include <prettyprint.hpp>

int main()
{
    int n;

    while (std::cin >> n)
    {
        size_t const int_octets = sizeof(int);
        size_t const int_bits = sizeof(int) * 8;
        std::bitset<int_bits> number_bits(n);
        std::bitset<int_bits> result;

        for (size_t i = 0; i < int_octets; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                result[i * 8 + j] = number_bits[(int_octets - 1 - i) * 8 + j];
            }
        }

        std::cout << int(number_bits.to_ulong()) << " converts to " << int(result.to_ulong()) << std::endl;

        // Without using std::bitset
        // size_t const int_octets = sizeof(int);
        // unsigned int n_uns = n;
        // int converted = 0;
        // for (size_t i = 0; i < int_octets; i++)
        // {
        //     converted <<= 8;
        //     converted |= n_uns % 256;
        //     n_uns >>= 8;
        // }

        // std::cout << n << " converts to " << converted << std::endl;
    }
}
