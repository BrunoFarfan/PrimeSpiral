#include <jsoncpp/json/json.h>
#include <string>
#include <vector>
#pragma once


class JsonHandler {
    public:
        // Create an empty JSON file with the given filename.
        Json::Value createJson(std::string filename);

        // Read a JSON file and return a vector of the prime numbers in it.
        std::vector<int> readPrimesListJson(std::string filename);

        // Read a JSON file and return an int with the highest number to which 
        // the prime numbers were computed.
        int readMaxNumberJson(std::string filename);
  
        // Write a JSON file with the given vector of prime numbers and the highest
        // number to which the prime numbers were computed.
        void writeJson(std::string filename, std::vector<int> primes, int prime_start);
};