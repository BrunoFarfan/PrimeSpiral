#include <cmath>
#include "prime_computing.h"


bool PrimeComputing::isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i <= (int) sqrt(number); i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

std::vector<int> PrimeComputing::getPrimes(int end, int start) {
    std::vector<int> primes;
    for (int i = start; i <= end; i++) {
        if (this->isPrime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}