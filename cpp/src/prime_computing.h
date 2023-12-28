#include <vector>
#pragma once


class PrimeComputing {
    public:
        // Métodos
        bool isPrime(int number);

        std::vector<int> getPrimes(int end, int start=0);
};