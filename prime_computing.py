import numpy as np


class PrimeComputing:
    def __innit__(self):
        pass


    def is_prime(self, number):
        # Check if a number is prime
        # number: integer
        # is_prime: boolean
        if number <= 1:
            return False
        for i in range(2, int(np.sqrt(number)) + 1):
            if number % i == 0:
                return False
        return True
    

    def get_primes(self, end, start=0):
        # Get all primes in a range
        # start: integer
        # end: integer
        # primes: list of integers
        primes = []
        for i in range(start + 1, end + 1):
            if self.is_prime(i):
                primes.append(i)
        return primes