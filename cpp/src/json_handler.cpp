#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json_handler.h"


Json::Value JsonHandler::createJson(std::string filename) {
    Json::Value prime_list;
    Json::Value json_file;
    json_file["prime_list"] = prime_list;
    json_file["prime_start"] = 0;

    std::ofstream file(filename);
    if (!file.good()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return json_file;
    } else if (file.good()) {
        std::cout << "Created file: " << filename << std::endl;
    }

    file << json_file;
    file.close();

    return json_file;
}

std::vector<int> JsonHandler::readPrimesListJson(std::string filename) {
    std::ifstream file(filename);
    Json::Value json_file;

    if (!file.good()) {
        // The file does not exist, create an empty JSON and try to read it again
        file.close();
        json_file = createJson(filename);
    } else {
        file >> json_file;
        file.close();
    }

    Json::Value primes = json_file["prime_list"];
    std::vector<int> prime_list;
    if (primes.isArray()) {
        for (int i = 0; i < primes.size(); i++) {
            prime_list.push_back(primes[i].asInt());
        }
    }
    return prime_list;
}

int JsonHandler::readMaxNumberJson(std::string filename) {
    std::ifstream file(filename);
    Json::Value json_file;

    if (!file.good()) {
        // The file does not exist, create an empty JSON and try to read it again
        file.close();
        json_file = createJson(filename);
    } else {
        file >> json_file;
        file.close();
    }

    return json_file["prime_start"].asInt();
}

void JsonHandler::writeJson(std::string filename, std::vector<int> primes, int prime_start) {
    Json::Value json_file;
    json_file["prime_start"] = prime_start;
    Json::Value prime_list;
    for (int i = 0; i < primes.size(); i++) {
        prime_list.append(primes[i]);
    }
    json_file["prime_list"] = prime_list;

    std::ofstream file(filename);
    file << json_file;
    file.close();
}